#include <pcap.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h> 

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    // 跳过以太网头部
    const struct ether_header* eth_header = (struct ether_header *)packet;
    if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) {
        printf("Not an IP packet. Skipping...\n\n");
        return;
    }

    // 获取IP头部，并从中提取源IP地址和目标IP地址
    const struct ip* ip_header = (struct ip*)(packet + sizeof(struct ether_header));
    char src_ip[INET_ADDRSTRLEN];
    char dst_ip[INET_ADDRSTRLEN];

    // 将网络字节序的IP地址转换为点分十进制格式
    inet_ntop(AF_INET, &(ip_header->ip_src), src_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_header->ip_dst), dst_ip, INET_ADDRSTRLEN);

    // 确保是ICMP数据包
    if (ip_header->ip_p == IPPROTO_ICMP) {
        printf("Got a packet\nFrom: %s\nTo: %s\n\n", src_ip, dst_ip);
    }
}

int main() {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    char filter_exp[] = "icmp"; // 只捕获ICMP数据包
    bpf_u_int32 net;

    // 打开网络设备进行数据包捕获
    handle = pcap_open_live("ens33", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", "ens33", errbuf);
        return(2);
    }

    // 编译并应用过滤器
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }

    // 捕获数据包
    pcap_loop(handle, -1, got_packet, NULL);

    // 清理
    pcap_close(handle);
    return 0;
}
