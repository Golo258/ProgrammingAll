# Linux Network Commands Cheat Sheet

This document summarizes essential Linux commands for network management and diagnostics, with examples and explanations.

## Basic Network Commands

### 1. `ifconfig` / `ip`
- **Description**: View or configure network interfaces.
- **Example**:
    ```bash
    ifconfig eth0
    ```
    or modern alternative:
    ```bash
    ip addr show eth0
    ```
- **Explanation**: Displays details about the `eth0` network interface, including IP address, netmask, and more.

### 2. `ping`
- **Description**: Test connectivity between hosts.
- **Example**:
    ```bash
    ping google.com
    ```
- **Explanation**: Sends ICMP echo requests to check if `google.com` is reachable.

### 3. `traceroute`
- **Description**: Trace the route packets take to reach a destination.
- **Example**:
    ```bash
    traceroute google.com
    ```
- **Explanation**: Shows the path (via routers) packets take to `google.com`, useful for troubleshooting routing issues.

### 4. `netstat` / `ss`
- **Description**: Display network connections, routing tables, and interface statistics.
- **Example**:
    ```bash
    netstat -tuln
    ```
    or:
    ```bash
    ss -tuln
    ```
- **Explanation**: Shows a list of all listening TCP/UDP ports with numeric addresses.

### 5. `nslookup` / `dig`
- **Description**: Query DNS records.
- **Example**:
    ```bash
    nslookup google.com
    ```
    or advanced tool:
    ```bash
    dig google.com
    ```
- **Explanation**: Resolves the domain name `google.com` to its IP address.

### 6. `route`
- **Description**: Display or modify the IP routing table.
- **Example**:
    ```bash
    route -n
    ```
- **Explanation**: Shows the kernel routing table with numerical addresses.

### 7. `tcpdump`
- **Description**: Capture and analyze network packets.
- **Example**:
    ```bash
    tcpdump -i eth0
    ```
- **Explanation**: Captures all network traffic on the `eth0` interface.

### 8. `nmap`
- **Description**: Network scanning and security auditing tool.
- **Example**:
    ```bash
    nmap 192.168.1.1
    ```
- **Explanation**: Scans the device with IP `192.168.1.1` for open ports.

### 9. `nmcli`
- **Description**: Command-line interface for NetworkManager.
- **Example**:
    ```bash
    nmcli connection show
    ```
- **Explanation**: Displays all active and inactive network connections managed by NetworkManager.

### 10. `systemctl`
- **Description**: Manage system services, including networking.
- **Example**:
    ```bash
    sudo systemctl restart networking
    ```
- **Explanation**: Restarts the networking service to apply new configurations.

### 11. `ufw` (Uncomplicated Firewall)
- **Description**: Manage a simple firewall.
- **Example**:
    ```bash
    sudo ufw enable
    ```
- **Explanation**: Enables the firewall to block unauthorized traffic.

---

## Diagnostic Tools

### 1. `top` / `htop`
- **Description**: Monitor system resource usage (CPU, memory, etc.).
- **Example**:
    ```bash
    top
    ```
- **Explanation**: Provides real-time information about system resource usage.

### 2. `iftop`
- **Description**: Real-time bandwidth monitoring.
- **Example**:
    ```bash
    iftop -i eth0
    ```
- **Explanation**: Monitors incoming and outgoing traffic on `eth0`.

### 3. `dstat` / `vmstat`
- **Description**: Show system performance, including network usage.
- **Example**:
    ```bash
    dstat -n
    ```
- **Explanation**: Shows network-related statistics in real-time.

### 4. `nload`
- **Description**: Monitor network bandwidth usage in real-time.
- **Example**:
    ```bash
    nload
    ```
- **Explanation**: Provides visual real-time feedback on network traffic.

---

## File Transfer Commands

### 1. `scp`
- **Description**: Securely copy files between systems.
- **Example**:
    ```bash
    scp file.txt user@192.168.1.100:/path/to/destination/
    ```
- **Explanation**: Copies `file.txt` to a remote host with IP `192.168.1.100`.

### 2. `rsync`
- **Description**: Synchronize files between local and remote systems.
- **Example**:
    ```bash
    rsync -avz /local/path user@remote:/remote/path
    ```
- **Explanation**: Syncs files from a local directory to a remote server.

---

## Advanced Network Commands

### 1. `ethtool`
- **Description**: Display or modify Ethernet device settings.
- **Example**:
    ```bash
    ethtool eth0
    ```
- **Explanation**: Displays information about the `eth0` network interface.

### 2. `iwconfig`
- **Description**: Configure wireless network interfaces.
- **Example**:
    ```bash
    iwconfig
    ```
- **Explanation**: Shows configuration of wireless interfaces.

### 3. `arp`
- **Description**: View or modify the ARP table.
- **Example**:
    ```bash
    arp -a
    ```
- **Explanation**: Displays the ARP table, showing the mapping of IP addresses to MAC addresses.

### 4. `whois`
- **Description**: Query domain registration information.
- **Example**:
    ```bash
    whois example.com
    ```
- **Explanation**: Displays registration details of the domain `example.com`.

---

## Network Security and Firewall Management

### 1. `iptables`
- **Description**: Manage firewall rules (advanced).
- **Example**:
    ```bash
    sudo iptables -L
    ```
- **Explanation**: Lists all current firewall rules.

### 2. `fail2ban`
- **Description**: Protect against brute-force attacks by banning IPs.
- **Example**:
    ```bash
    sudo fail2ban-client status
    ```
- **Explanation**: Displays the status of `fail2ban` and shows active bans.

---

## Additional System Commands

### 1. `lspci`
- **Description**: List PCI devices, useful for finding network cards.
- **Example**:
    ```bash
    lspci | grep Ethernet
    ```
- **Explanation**: Shows details about Ethernet devices.

### 2. `lsusb`
- **Description**: List USB devices, useful for troubleshooting.
- **Example**:
    ```bash
    lsusb
    ```
- **Explanation**: Lists all devices connected via USB.

---

## Useful Aliases

For easier use of frequently used commands, set up aliases:
```bash
alias ipconfig="ip a"
alias pingg="ping google.com"
