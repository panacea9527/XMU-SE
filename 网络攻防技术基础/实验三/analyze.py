import pyshark
from scapy.all import *


pcap_file_path = './2.pcap'
cap_file_path = './1.cap'
tshark_path = r'F:\Wireshark\tshark.exe'

def analyze_tcp_with_scapy(packet):
    if packet.haslayer(TCP):
        # 将FlagValue对象转换为整数
        tcp_flags = int(packet[TCP].flags)
        flags_description = []
        if tcp_flags & 0x01:
            flags_description.append("FIN")
        if tcp_flags & 0x02:
            flags_description.append("SYN")
        if tcp_flags & 0x04:
            flags_description.append("RST")
        if tcp_flags & 0x08:
            flags_description.append("PSH")
        if tcp_flags & 0x10:
            flags_description.append("ACK")
        if tcp_flags & 0x20:
            flags_description.append("URG")
        if tcp_flags & 0x40:
            flags_description.append("ECE")
        if tcp_flags & 0x80:
            flags_description.append("CWR")
        
        print(f"TCP标志位: {bin(tcp_flags)} ({', '.join(flags_description)})")

def analyze_dhcp_with_scapy(packet):
    if packet.haslayer(DHCP):
        # 解析DHCP选项
        dhcp_options = packet[DHCP].options
        for option in dhcp_options:
            if isinstance(option, tuple): 
                print(f"DHCP选项: {option[0]} - {option[1]}")

def analyze(pcap_path):
    scapy_packets = rdpcap(pcap_path)  # 预先读取所有包以供Scapy分析
    try:
        with pyshark.FileCapture(pcap_path, tshark_path=tshark_path) as cap:
            packet_count = 0
            for packet in cap:
                packet_count += 1
                print(f"\n=== 第{packet_count}个数据包信息 ===\n")
                if 'IP' in packet:
                    print(f"IP层: 源IP: {packet.ip.src}, 目的IP: {packet.ip.dst}")
                if 'TCP' in packet:
                    print(f"TCP段: 源端口: {packet.tcp.srcport}, 目的端口: {packet.tcp.dstport}")
                    analyze_tcp_with_scapy(scapy_packets[packet_count-1])
                if 'UDP' in packet:
                    print(f"UDP数据报: 源端口: {packet.udp.srcport}, 目的端口: {packet.udp.dstport}")
                    if int(packet.udp.srcport) in [67, 68] or int(packet.udp.dstport) in [67, 68]:
                        analyze_dhcp_with_scapy(scapy_packets[packet_count-1])
                if 'HTTP' in packet: # 检查是否为HTTP数据包
                    print("HTTP信息:")
                    if hasattr(packet.http, 'request_method'):
                        print(f"  请求方法: {packet.http.request_method}")
                        print(f"  主机: {packet.http.host}")
                        print(f"  URI: {packet.http.request_uri}")
                    if hasattr(packet.http, 'response_code'):
                        print(f"  响应代码: {packet.http.response_code}")
                        print(f"  响应短语: {packet.http.response_phrase}")
    except FileNotFoundError:
        print(f"文件未找到: {pcap_path}")
    except Exception as e:
        print(f"发生错误: {e}")

# 调用函数分析PCAP
print("=== 分析CAP文件 ===")
analyze(cap_file_path)
print("\n\n=== 分析PCAP文件 ===")
analyze(pcap_file_path)
