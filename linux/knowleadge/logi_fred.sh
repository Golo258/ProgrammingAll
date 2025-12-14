
# Punkt 2 -- ustawienie sygnału ICMP zwracany
# przez REJECT na porcie ssh na net unreachable


#           HOST VM1 -- FIREWALL server
#--------------------------------------------------------
# Setup zmiennych
root@trixie:/home/student# ATTACKER_IP_ADDR="192.168.1.13"
root@trixie:/home/student# LOCAL_WINDOWS_HOST="192.168.1.10"
root@trixie:/home/student# 
#--------------------------------------------------------
# reset polityk
root@trixie:/home/student# ./fire.off
root@trixie:/home/student# iptables -L INPUT -v
Chain INPUT (policy ACCEPT 38 packets, 2832 bytes)
 pkts bytes target     prot opt in     out     source               destination
root@trixie:/home/student#
# czysto po resecie
#--------------------------------------------------------
# ustawianie reguły blokującej
root@trixie:/home/student# iptables --append INPUT \
>     --protocol tcp \
>     --dport 22 \
>     --jump REJECT --reject-with icmp-net-unreachable
root@trixie:/home/student# 
# check - czy sie zaaplikowała 
root@trixie:/home/student# iptables -L INPUT -v
Chain INPUT (policy ACCEPT 203 packets, 16174 bytes)
 pkts bytes target     prot opt in     out     source               destination
    0     0 REJECT     tcp  --  any    any     anywhere             anywhere             tcp dpt:ssh reject-with icmp-net-unreachable
root@trixie:/home/student# 
#--------------------------------------------------------

# sprawdzenie komunikatu
#                   VM2 -- atakujący
# check - ping do VM1 - jest, bo reguła jest pod ssh, nie icmp
root@trixie:/home/student# ping 192.168.1.12
PING 192.168.1.12 (192.168.1.12) 56(84) bytes of data.     
64 bytes from 192.168.1.12: icmp_seq=1 ttl=64 time=0.372 ms
64 bytes from 192.168.1.12: icmp_seq=2 ttl=64 time=0.345 ms
64 bytes from 192.168.1.12: icmp_seq=3 ttl=64 time=0.426 ms
# check -ssh 
root@trixie:/home/student# ssh student@192.168.1.12
ssh: connect to host 192.168.1.12 port 22: Network is unreachable
root@trixie:/home/student#
# odrzuca as expected
#                   WINDWOS - lokalny host 
PS C:\Users\Grzesiek\Desktop\Repos\ProgrammingAll> ssh student@192.168.1.12
ssh: connect to host 192.168.1.12 port 22: Connection timed out


# czemu nie - network is unreachable
# bo REJECT z VM1 wysyła ICMP
# a klient windows oczekuje TCP RST / ignoruje ICMP unreachable
#-------------------------------------
# PUNKT 3  -- odblokować wejście na port ssh dla komputerów z własnej sieci lokalnej 
#      VM1 FIREWALL
# cleanup  --  
root@trixie:/home/student# ./fire.off 
root@trixie:/home/student# 

# ustawienie akceptowania dla lokalnego
root@trixie:/home/student# iptables --append INPUT \
>     --source "$LOCAL_WINDOWS_HOST" \
>     --protocol tcp \
>     --dport 22 \
>     --jump ACCEPT
root@trixie:/home/student# iptables -L INPUT -v
Chain INPUT (policy ACCEPT 1249 packets, 102K bytes)
 pkts bytes target     prot opt in     out     source               destination
  630 47412 ACCEPT     tcp  --  any    any     192.168.1.10         anywhere             tcp dpt:ssh

# reszte blokujemy
root@trixie:/home/student# iptables --append INPUT \
>     --protocol tcp \
>     --dport 22 \
>     --jump REJECT --reject-with icmp-net-unreachable
root@trixie:/home/student# 
root@trixie:/home/student# iptables -L INPUT -v
Chain INPUT (policy ACCEPT 1262 packets, 104K bytes) pkts bytes target     prot opt in     out     source               destination
  827 62464 ACCEPT     tcp  --  any    any     192.168.1.10         anywhere      
       tcp dpt:ssh
    0     0 REJECT     tcp  --  any    any     anywhere             anywhere      
       tcp dpt:ssh reject-with icmp-net-unreachable

#  lokalny host WINDOWS -- można zalogować
PS C:\Users\Grzesiek\Desktop\Repos\ProgrammingAll> ssh student@192.168.1.12
student@192.168.1.12's password: '

# VM attacker .13 -- blokujemy 
root@trixie:/home/student# ssh student@192.168.1.12
ssh: connect to host 192.168.1.12 port 22: Network is unreachable
root@trixie:/home/student# 
#-------------------------------------
# Punkt 4 -- Zablokować cały ruch na protokole ICMP poza wychodzącym ping .
# Przetestować!. (tj. ping 8.8.8.8 ma działać ale ping z hosta na guesta nie)

#               VM 1 -firewall
# ping VM1- wysyłamy echo-request | VM2- odpowiada echo-reply
# set - my możemy wysyłać wiadomości
# fire.off teoretycznie nam odblokował polityke ale można zprezyować że pozwalamy na to
root@trixie:/home/student# ./fire.off
root@trixie:/home/student# iptables --append OUTPUT \
>     --protocol icmp \
>     --icmp-type echo-request \
>     --jump ACCEPT
root@trixie:/home/student# 
# zezwalamy na możliwośc odebrania pingu 
root@trixie:/home/student# iptables --append INPUT \
>     --protocol icmp \
>     --icmp-type echo-reply \
>     --jump ACCEPT
root@trixie:/home/student# 
# nikt do nas nie może wysyłać requestów
root@trixie:/home/student# iptables --append INPUT \
>     --protocol icmp \
>     --icmp-type echo-request \
>     --jump DROP
root@trixie:/home/student#
# check reguł
root@trixie:/home/student# iptables -L -n -v
    Chain INPUT (policy ACCEPT 895 packets, 79073 bytes)
    pkts bytes target     prot opt in     out     source               destination
        0     0 ACCEPT     icmp --  *      *       0.0.0.0/0            0.0.0.0/0            icmptype 0
        0     0 DROP       icmp --  *      *       0.0.0.0/0            0.0.0.0/0            icmptype 8

    Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
    pkts bytes target     prot opt in     out     source               destination

    Chain OUTPUT (policy ACCEPT 597 packets, 46396 bytes)
    pkts bytes target     prot opt in     out     source               destination
        0     0 ACCEPT     icmp --  *      *       0.0.0.0/0            0.0.0.0/0            icmptype 8
root@trixie:/home/student#
# czy ping działa z VM1 - do innych 
root@trixie:/home/student# ping 8.8.8.8
PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_seq=1 ttl=114 time=45.0 ms
64 bytes from 8.8.8.8: icmp_seq=2 ttl=114 time=34.8 ms
64 bytes from 8.8.8.8: icmp_seq=3 ttl=114 time=49.9 ms
64 bytes from 8.8.8.8: icmp_seq=3 ttl=114 time=49.9 ms
64 bytes from 8.8.8.8: icmp_seq=4 ttl=114 time=30.3 ms
64 bytes from 8.8.8.8: icmp_seq=5 ttl=114 time=25.1 ms
64 bytes from 8.8.8.8: icmp_seq=6 ttl=114 time=29.0 ms
64 bytes from 8.8.8.8: icmp_seq=7 ttl=114 time=24.5 ms
# jeszcze jak 
# ---------------------
# czy ping z innych od nas działa
#                VM2 - attacker 
root@trixie:/home/student# ping -c 3 -W 1 192.168.1.12
PING 192.168.1.12 (192.168.1.12) 56(84) bytes of data.

--- 192.168.1.12 ping statistics ---
3 packets transmitted, 0 received, 100% packet loss, time 2043ms


#               local host
PS C:\Users\Grzesiek\Desktop\Repos\ProgrammingAll> ping 192.168.1.12

Pinging 192.168.1.12 with 32 bytes of data:
Request timed out.
Request timed out.
# --- no raczej nie -- zablokowane 