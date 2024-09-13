from scapy.all import sniff, TCP, IP


# 定义一个回调函数来处理捕获的包
def process_packet(packet):
    # 确认包是TCP包且目的端口是23（Telnet的默认端口）
    if packet.haslayer(TCP) and packet[TCP].dport == 23:
        # 尝试提取并打印出TCP层载荷（payload）的内容
        try:
            # 将payload转换为字符串，忽略非打印字符
            payload = packet[TCP].payload.load.decode('ascii', errors='ignore')
            if payload:  # 如果payload不为空
                print(f"捕获到的数据（来自{packet[IP].src}到{packet[IP].dst}）: {payload}")
        except Exception as e:
            pass  # 在处理数据时发生错误，忽略该包

if __name__ == "__main__":
    print("开始监听目标主机间的Telnet通信...")
    try:
        # 使用sniff函数开始捕获数据包
        # 过滤规则设置为捕获TCP端口23的数据包
        # store=0表示不将捕获的包存储在内存中
        sniff(filter="tcp port 23", prn=process_packet, store=0)
    except KeyboardInterrupt:
        print("停止监听。")
