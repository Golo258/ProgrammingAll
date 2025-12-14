
VM - server .12
    HOST_IP: 192.168.1.12/24
    LAN_CIDR - 102.168.1.0/24  (adres sieci)
    DHCP_IP - 192.168.1.1

VM- server .13
    HOST_IP: 192.168.1.13/24
    LAN_CIDR - 102.168.1.0/24  (adres sieci)
    DHCP_IP - 192.168.1.1

    # mac carty 
    ip link show enp0s3
        08:00:27:f9:27:43

Skrypt fire.on

#!bin/bash -xv

#-----------VARIABLES----------------
HOST_IP="192.168.1.12"
LAN_CIDR="192.168.1.0/24"
DNS_IP="192.168.1.1"
ATTACKER_IP_ADDR="192.168.1.13"
ATTACKER_MAC_ADDR="08:00:27:f9:27:43"
LOCAL_WINDOWS_HOST="192.168.1.10"

#-----------------SETUP------------------------
echo "---Policy reset---"
iptables --flush
iptables --policy INPUT DROP
iptables --policy OUTPUT DROP
iptables --policy FORWARD DROP

echo "---Loopback Setup---"
iptables --append INPUT --interface lo --jump ACCEPT
iptables --append OUTPUT --interface lo --jump ACCEPT

iptables --append INPUT  -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables --append OUTPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

echo "---Setup DHCP---"
iptables --append OUTPUT --protocol udp--sport 68 --dport 67 --jump ACCEPT
iptables --append INPUT  --protocol udp--sport 67 --dport 68 --jump ACCEPT

#-------------------------------------------------------

echo "First example. Dropping Ssh on attacker side"

iptables --append INPUT \
    --protocol tcp --dport 22 \
    --source "$ATTACKER_IP_ADDR" \
    --jump ACCEPT

echo "Dropping ssh access from attacker side"
iptables --append INPUT \
    --protocol tcp --dport 22 \
    --source "$ATTACKER_IP_ADDR" \
    --jump DROP

echo "Rejecting ssh accept from attacker side"
iptables --append INPUT \
    --protocol tcp --dport 22 \
    --source "$ATTACKER_IP_ADDR" \
    --jump REJECT


# różnica DROP | REJECT
# przy DROP po prostu zaliczymy timeouta, nie powie nam co sie dzieje
# przy REJECT od razu przy próbie połączenia dostaniemy 
# connect to host $host port 22: Connection refused

echo "ICMP net unchreable --REJECT na porcie ssh "
# ping brak portów wiec nie ustawiamy protocol ani port 
# icmp to protokół
iptables --append INPUT \
    --protocol tcp \
    --dport 22 \
    --jump REJECT --reject-with icmp-net-unreachable


# punkt 3 
iptables --append INPUT \
    --source "$LOCAL_WINDOWS_HOST" \
    --protocol tcp \
    --dport 22 \
    --jump ACCEPT

iptables --append INPUT \
    --protocol tcp \
    --dport 22 \
    --jump REJECT --reject-with icmp-net-unreachable

# zadanie 4
# blokada icmp do VM-firewall, 
# VM-firewall ma możliwośc wysyłania icmp

#  ustawiamy że moożemy wysyłać requesty z VMKI do innych
iptables --append OUTPUT \
    --protocol icmp \
    --icmp-type echo-request \
    --jump ACCEPT

# ustawianie my możemy odebrać jesli wysyłamy 
iptables --append INPUT \
    --protocol icmp \
    --icmp-type echo-reply \
    --jump ACCEPT

#  ustawiamy blokowanie doo nas - nie można wysłać requesta
iptables --append INPUT \
    --protocol icmp \
    --icmp-type echo-request \
    --jump DROP



