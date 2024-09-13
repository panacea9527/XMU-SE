import pyshark

# 替换这里的文件路径为你的PCAP文件路径
pcap_file_path = './2.pcap'
cap_file_path = './1.cap'
tshark_path = r'F:\Wireshark\tshark.exe'

def analyze_pcap(pcap_path):
    try:
        # 使用FileCapture读取PCAP文件，并指定tshark的路径
        cap = pyshark.FileCapture(pcap_path, tshark_path=tshark_path)

        packet_count = 0

        # 遍历PCAP文件中的每个包
        for packet in cap:
            packet_count += 1
            print(f"\n=== 第{packet_count}个数据包信息 ===\n")
            
            if 'IP' in packet:
                print(f"IP层: 源IP: {packet.ip.src}, 目的IP: {packet.ip.dst}")
            
            if 'TCP' in packet:
                print(f"TCP段: 源端口: {packet.tcp.srcport}, 目的端口: {packet.tcp.dstport}")

            if 'UDP' in packet:
                print(f"UDP数据报: 源端口: {packet.udp.srcport}, 目的端口: {packet.udp.dstport}")
                # 检查UDP端口是否为67或68，以确定是否为DHCP数据包
                if packet.udp.srcport in ['67', '68'] or packet.udp.dstport in ['67', '68']:
                    print("检测到DHCP数据包")


            if 'HTTP' in packet:
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
analyze_pcap(cap_file_path)
print("\n\n=== 分析PCAP文件 ===")
analyze_pcap(pcap_file_path)
