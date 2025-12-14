
# Linux INFO
#---------------------------------------------------------------------------------------------------------------------------------
def LINUX:
    1. xterms
    xterm -geometry 88x51+1000+10 -fa 'Monospace' -fs 10 -bg black -fg yellow -T "Terminal 1" &
    xterm -geometry 93x28+30+10 -fa 'Monospace' -fs 10 -bg black -fg yellow -T "Terminal 2" &
    xterm -geometry 93x19+30+640 -fa 'Monospace' -fs 10 -bg black -fg yellow -T "Terminal 3" &

    2. processes
    # szukanie procesu
        ps aux | grep "name of started process"
    #albo    
        pgrep - process grep
         - wyszukaj proces o  danej nazwie pasujacej do wzorca
            defaultowo wypisuje pid 
        -f 
            dopasuj wzorzec do całej lini polecenia, nie tylko do nazwy

        pgrep -f "nazwa_processu"  # ex: python 
            -x - exact match- dopasuj dokładnie cały ciag, nie tylko fragment
            -c - count - zamiast wypisywać pid, wypisz liczbe znalezionych procesów
        
    # szukanie rekursywne w katalogach
        grep -rl "string" /path

    # fajne do szukania regexów
        grep -Eo "abc[0-9]+cd" /etc/hosts
            -E ci umożliwa matchowanie
            -o zwraca ci tylko to ci chcesz znaleźć

        grep -oP "RUN = \k[^ ]+"
            \k - ucina wszystkoo co było przed 
            Czyli jeśli mamy RUN = BUILD_CUS
                to zwróci nam tylko BUILD_CUS
            [^ ]+ - wszystko oprócz spacji
            
    #sprawdzanie priorytetu procesu:
        ps -o pid,ni,cmd -p <pid>

    # zmienianie priorytetu

        sudo renice -n -15 -p <pid>  #-20 (max) do 20 (min)
        nice -n -5 python script.py  # uruchamianie z danym priorytetem
    # szukanie plików
    ## find way
        find . -type f -name "*UE.ex"

    ## fd way
        sudo apt  install fd # jesli nie masz 
        fd "UE\.ex$"

    # usuwanie wyczyszczenie aplikacji
        sudo apt purge -y groovy groovy-*
        sudo pat autoremove -y 
        
    ## po aliasach i aplikacje 
        which alias_name
        alias | grep alias_name
        type definied_things  # aliasy / funkcje / sćieżki
        whereis application

    # serwisy
        sudo systemctl restart executor.service
            status / restart / enable -(start z systemem) / disable /status

        systemctl list-units --type=service # wszystkie aktywnych serwisów
        systemctl list-unit-files --type=service # wszystko 
        
        journalctl -u executor.service  # logi danego serwisu 
            -n 20 # ostatnie 20 linijek

        /etc/systemd/system/x.sevice # path do serwisów


    # robot framework 
        pyenv activate test_repo # aktywacja środowisk
        cd /home/ute/MN/UTE/robotlte # uruchmianie testu
        robot --nostatusrc -C off -L TRACE -b result/debug.log --xunit result/results.xml --output result/output.xml --log result/log.html --report result/report.html <sciezka do testu>
        robot --dryrun --nostatusrc -C off -L TRACE -b result/debug.log --xunit result/results.xml --output result/output.xml --log result/log.html --report result/report.html <sciezka do testu>

        alias rt='/home/ute/test_repository/resources/DevKr/FTK12/rt.sh'
        alias rl='tail -f /home/ute/results/latest/robot_debug.log'
            rt Test.robot
            rl - czytanie logów robotowych


    # upgrade systemu
        sudo apt upgrade -y # wszyskie pakiety
        sudo apt update && sudo apt full-upgrade -y # usuwa stare i aktualizuje nowe 
        sudo apt autoremove -y && sudo apt autoclean # sprzatanie po updatecie

    # różnica miedzy dpkg a apt 
        wget paczka.deb
        dpkg -i paczka.deb
        

    # przenoszenie plików
    # 
        scp /sciezka ute@adres:/docelowa
        scp -r /sciezka .. - wszystkie katalogi

        rsync -avz /sciezka ute@ip:/docelowa 
            -a - wszystkie uprawnienia 
            -v - logi
            -z - kompresja

        # Kopiowanie plików z wykluczeniem
        rsync -a --exclude='.git' ./src/ ./dest/
        
        lub 
        rsync -azP ./folder ute@adres:/docelowy 
            - z progressem 

        #!! przenoszenie plików z TL na windowsa 
        # masz powiedzmy pliczek na TL   /tmp/pliczek.txt
        to robisz z cmd windowsa 
            scp ute@ipczek_tl:/tmp/pliczek.txt .
            i w tej ścieżce gdzie to wywołujesz to bedzie pliczek

    # ip addresy
        ip a 
        ip -4 addr show eth0 # tylko eth0
        hostname -I | awk '{print $1}' -- tylko ip maszyny 

        sudo ss -tuln -- otwarte porty | TCP/UDP + listening + numeric (ip/port)
        
        ip -4 addr show eth0 | grep -oP '(?<=inet\s)\d+(\.\d+){3}' # get_vm_ip_addr

        # sobaczenie ipka TL
         ip a show eth0 i inet masz
            2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 5000
                link/ether 52:54:0a:b8:5e:10 brd ff:ff:ff:ff:ff:ff
                altname enp0s3
                altname ens3
                inet 10.84.159.4/23 brd 10.84.159.255 scope global dynamic eth0 # to ten chuj
                valid_lft 36634sec preferred_lft 36634sec
                inet6 fe80::5054:aff:feb8:5e10/64 scope link 
                valid_lft forever preferred_lft forever



    # linki 
        ln -s /home/gg/testy Tests # symboliczny -- taki skrót do ścieżki
        ln /home/gg/testy.txt testy.txt  # twardy - tworzy identyczny plik jako kopie -- delete casade

        ln -sfn /home/gg/nowy_katalog Tests -- nadpisanie linku syembolicznego

    # miejsce na dysku - czyszczenie TL 
        df -h -- miejsce na zamontowanych dyskach 

        du -sh /katalog - dla danego katalogu
        du -ah /ścieżka | sort -rh | head -n 10  # top 10 najwiekszych katalogółw

        # czyszczenie systemowe
            sudo apt clean # paczki z /var/cache/apt/archives
            sudo apt autoremove # zbedne dependencies
            sudo journalctl --vacuum-size=100M  # logi systemowe


        du -h --max-depth=1 /home/ute | sort -hr
            du - disk usage - ile miejsca zajmuiją pliki i foldery na dysku
            -h - human reable - pokazujey rozmiary MB/GB
            --max-depth=1 -- ogranicza naalize do poerwszego poziomu podfolderów
            /katalog - ktory analizujesz
            | sort - sortuje linie 
                -h human 
                -r odwraca kolejnośc - od najwiekszych do najmniejszych

    # vs code 
    ## instalacja vs coda :
    # ustaw wcześniej proxy do https / http
        wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
        sudo install -o root -g root -m 644 packages.microsoft.gpg /usr/share/keyrings/
        rm packages.microsoft.gpg
        sudo sh -c 'echo "deb [arch=amd64 signed-by=/usr/share/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
        sudo apt update
        sudo apt install code

        # ustawienia debugera
        CTRL + SHIFT + P --> Preferences: Open Keyboard Shortcuts (JSON)
            // Place your key bindings in this file to override the defaults
                [
                {
                    "key": "f5",
                    "command": "workbench.action.debug.continue"
                },
                {
                    "key": "f10",
                    "command": "workbench.action.debug.stepOver"
                },
                {
                    "key": "f11",
                    "command": "workbench.action.debug.stepInto"
                },
                {
                    "key": "shift+f11",
                    "command": "workbench.action.debug.stepOut"
                },
                {
                    "key": "f4",
                    "command": "workbench.action.debug.start"
                }
                ]


    ## dodawanie wtyczek
        code --install-extension nazwa_pliku.vsix # ex robotframework-lsp.vsix
        code --install-extension robocorp.robotframework-lsp

    ## serwer do połączeń ssh
        mkdir -p ~/.vscode-server/bin
        wget -qO- https://update.code.visualstudio.com/latest/server-linux-x64/stable | tar -xz -C ~/.vscode-server/bin/
    
    # ustawienia ekranu vmki
    alias res_vnc="xrandr --newmode '1904x990_60.00'  155.75  1904 2016 2216 2528  990 993 1003 1027 -hsync +vsync; xrandr --addmode Virtual-1 '1904x990_60.00'; xrandr --output Virtual-1 --mode '1904x990_60.00';"
    res_vnc
    vnc -> properties -> options -> scaling 100%

    # zmienne środowiskowe, aliasy, funkcje, bashrc\
    export VAR="/path" 
        echo $VAR - zobaczysz zmienną 
        printenv PATH -- pokazuje zmienne środowiskowe
        
    # alias - skrót do długich komend lub sewencji komend
        alias ll="ls -la "

    # sprawdzanie adres ip po eth

    ip -4 addr show ethx
    lub 
        samo ip addr show eth0

    # herbata - standardowe wyjscie (stdout ) i do pliczku
    komenda | tee pliczek 

    # dodawnaie użytkownikó group + root
        sudo adduser ute
        sudo usermod -aG sudo ute
    
    # szukanie pid po po porcie
        lsof -i :PORT

    # Zamiana tekstu na kolumny i wypisanie AWK
    echo "Jan Kowalski 30" | awk '{ print $1 }'
    # tak samo operacje arytmetyczne
    awk '{ sum += $2 } END { print sum }' dane.txt
        # Jak chcesz przetwarzać dane rekord bo jest ich dużo to dajesz
        awk 'NR==2 { print $2 }'

        # -F field seperator- czyli co bedzie oddzielało wyrazy albo wyraz
        np ipczki: 10.0.1.1
            awk -F. '{ print $4 }' podzieli nam wyraz wzgledem kropki i da 4 oktet 

    # sprawdzeczenie czy na danym hoscie (ipczku) dany port słucha
        nc -zv 127.0.0.1 4369
        netcat 
        4639 - port epmd

    # dodanie rzeczy do patha
        export PATH="/opt/cus/lib/erlang/bin:$PATH"

    # sciezki fajne
        uex: pliki .ez
        cd /opt/cus/lib/uex/

    # grepowanie z regexem
        ls | grep -E '^s'
    
    # sciezki do pythonowego repo: test_repo
        /home/ute/.pyenv/versions/test_repo/lib/python3.9/site-packages/
        np: ta_uexgate
        
    # 
        pierwsze generujemy seedy 
            generateSeeds
    	
        potem generateJobs

    #  sedowanie -0 zamienianie
        cat $ZMIenna | sed 's/cos_zamieniamy/na_co/g'
            g - global - że sie zmieni
            

    # nasłuchiwanie danej komendy
        watch -n (ilosc sekund) (komenda)
            watch -n 5 df -h 
            watch -n 2 'ps aux | grep nazwa_procesu'
            watch -n 1 -d free -h
                -d - podswietla zmiany 
    
    # podsłuchiwanie ruchu sieciowego
        tcpdump - co przelatuje przez karte sieciową , pakiety / IP / port  protokoły / dane 
            - do debugowania połączeń / analizy ruchu / szukania błedów

        sudo tcpdump -ni <interface> <filtr>
            -n - nie tłumaczy nazw hostów 
            -i - jaki interface
            -c - ilosc pakietów 
    
    # fajnie komendy sieciowe
        ip link  -- wszystkie interfacy sieciowe
        ss -tulpn -- zamiast netstat

        nmap - network mapper - skanowanie sieci / otwarte porty / usługi

    # rota 
        \\eseefsn50.emea.nsn-net.net\rotta4internal\LTE_2\pgolonka
        file://eseefsn50.emea.nsn-net.net/rotta4internal/LTE_2/pgolonka/
 
    # usuwanie interaceów
        ip link del ethx -- usuwa dany interface
    # usuwanie adresów
        ip a del  10.0.1.1/24  dev eth3 
                  ipczek /maska  rozdzaj port

    # po usunieciu interaceów czyszczenie i przywracanie 
        systemctl restart networking 
        service networking restart 
            -- przywraca nam interfacy i adresy do wersji z 
                /etc/network/interfaces
            
        tcpdump -ni br0

        sudo ip link set dev eth3 up -- aktywacja interfacu 
        ip addr show dev eth3 - pokazuje aktualna konfiguracje 

    # pyenv lock i tym podobne, tworzenie środowisko
        poetry
            poetry init -- interaktywnie 
                lub
            poetry new my_project
                cd my_project            

            dodawanie zależności
                poetry add paramiko scp
            
            uruchamianie środowiska 
                poetry shell
            
            instalacja na innym systemie
                poetry install

            poetry env info --path -- gdzie jest zapisane środowisko
                -- sciezka do interpretera

    # kolejka, ubijanie sprawdzanie 
        atq - 
        atrm - usuwanie 

    #--------------- TAR - ARCHIWIZACJA -------------
        -> tworzenie archiwum
            tar -czf archiwum.tar.gz  [Pliki/katalogi]
            - c - create - tworzy archiwum
            - z - kopmresja do zip
            - f - nazwa pliku archiwum
            
        Jak mamy kilka plików danym katalogu, to przydaje się  
            -C - zmienia katalog wchodzi do niego
            tar -czf archiwum.tar.gz -C /katalog  pliki_z_tego_katalogu
        
        -> sprawdzanie zawartości archwium:
            tar -tzf archwium.tar.gz
                - t - listowanie - wyświetla zawartośc
                - z - kompresja zip
                - f - plik archiwum

        -> rozpakowanie archwium:
            tar -xzf archiwum.tar.gz
                - x - extract rozpwkowanie
            
            tar -xzf archiwum.tar.gz -C /sciezka/docelowa
                -C - rozpakuje do danej ścieżki

        -> dodanie pliku do istniejacego archwium
            tar -rf archwium.tar nowy.plik.txt

        du -sh archiwum.tar.gz - rozmiar arcghiwum
        
            
    #-------------------------------------------------
    # python - virutalenv
        znajduje sie w 
        /home/ute/.pyenv/versions/
            tutaj masz wszystkie wersje 
        jak sie zjebie test_repo to kopiujesz sobie pliczki do
            /home/ute/.pyenv/versions/python_version/envs/test_repo
            i robisz linka symbolicznego 
                ln -s  /home/ute/.pyenv/versions/python_version/envs/test_repo /home/ute/.pyenv/versions/test_repo

        inaczej łatwiej tworzenie test_repo:
            patrzysz
                pyenv versions
                    bierzesz tą która chcesxz
                    
                    pyenv virtualenv 3.9.14 test_repo
                    i ci to tworzy
                        ~/.pyenv/versions/3.9.14/envs/test_repo/
                        ~/.pyenv/versions/test_repo → ~/.pyenv/versions/3.9.14/envs/test_repo

    # montowanie - mount
        podpinanie systemu plików(jakiegoś zasobu)
            do konkretnego katalogu w drzewie plików
        W linuxie: wszystko jest widoczne w jednym drzewie kataogów /

            montowanie logstora:
                sudo mount -t cifs -o user=ute,pass='Y9-Qb35v$suQ',uid=1000,gid=1000 //p05-nas.p05.ska-lab.nsn-rdnet.net/logstore /mnt
                potem masz w /mnt/CUS1/ i se mozesz manewrować
                

    # vs code dodawanie kolejnego hosta 
        w ~/.ssh/config dodajesz 
            Host nazwa_hosta_alias
                HostName ipczek
                User ute
        i żeby ci zachyciło to musisz mieć na vmce swój klucz publiczny dodany
            vim ~/.ssh/authorized_keys
            i wrzucasz tam ze swojego windwosa ~/.ssh/id_rsa.pub
                jak nie masz kluczy to generujesz 
                    ssh-keygen -t ed25519 -C "your@email.com"

    
    # łatwiejsze debugowanie interaktywna konsola 
        pip install ptpython
        ptpython
        alias python="ptpython"
        
    pip install mccabe pylint
    # python sprawdzanie skłądni 
        pylint path_to_file.py

    # sprawdzanie złożoności  -complexity
        python -m mccabe --min 7 path/to/your_file.py

    # pytest uruchamianie
        pytest -v -s test/plik.py 
            --verbose - czyli szczeółowe info
            -s pokazuje printy

            potem precyzja 
                ::nazwa_testu
                ::NazwaKlasy.nazwa_testu


    # netcat:
        fajne narzedzie do sprawdzania połączenia sieciowego na danym porcie
            nc -vz ipczek port
            np: nc -vz 10.34.76.122 80 - 
                -v -verbose 
                -z - tryb skan, tylko sprtawdza port, nie wysyła danych

    # BASH ustawianie automatyczne zmienną globalnych
    set -a | source ${zmienna}; set +a # +a konczy ustawienia 

    # robienie fajnych pętli
        while; do something; done;
        np:
            while; do curl link > link.log; sleep 1; done;
    # wyszukiwanie zainstalowanych aplikacji
        dpkg -l | grep vnc - na przykłąd vnc 

Ustawianie terminali:
    xterm -geometry 88x47+1000+10 -fa 'Monospace' -fs 10 -bg black -fg yellow -T "Terminal 1" &
    xterm -geometry 95x28+30+10 -fa 'Monospace' -fs 10 -bg black -fg yellow -T "Terminal 2" &
    xterm -geometry 95x18+30+577 -fa 'Monospace' -fs 10 -bg black -fg yellow -T "Terminal 3" &

    alias res_vnc="xrandr --newmode '1904x990_60.00'  155.75  1904 2016 2216 2528  990 993 1003 1027 -hsync +vsync; xrandr --addmode Virtual-1 '1904x990_60.00'; xrandr --output Virtual-1 --mode '1904x990_60.00';"
    res_vnc
#--------------------------------------------------
    #Debian wirtulaka ustawienia
    Dodawanie kopiowania VM -> Windows
    VBox -> urzadzenia - > zamontuj 
    sudo mkdir -p /mnt/cdrom
    sudo mount /dev/cdrom /mnt/cdrom
    cd /mnt/cdrom
    sudo ./VBoxLinuxAdditions.run
#--------------------------------------------------
NEOVIM CONFIG:
    sudo apt update 
    sudo apt install neovim -y
    nvim --version

    source % -- załaduj plik jakbyś go uruchamił 
     % -- akutalnie otwarty plik 

    < < cofnięcie o jeden tab 
    >> -- dodanie tabu

    Esc $ - przeniesienie na koniec linii
    Esc 0 - przeniesienie na poczatek linii
    Esc Shift 6 -- do pierwszego stringa
    
    # dodawanie pluginu -- wstęp
        dodajesz rzecz do plugins {}
        potem :w i :Lazy reload albo :Lazy sync

    Kopiowanie:
        V - virtual | potem albo dd -- usuwanie i sie kopiuje
            albo V  -> y (yank) -- przejscie w miejsce i p (put)

    # usuwanie danego słowa
        escp dw - delete word

    Neotree manewrowanie:
        struktura:
            j - dół 
            k - góra
            enter - wejdz do pliku

        pliki:
            a - nowy  a file   a folder/
            d - usuń
            r - rename
            y - skopiuj
            x - wynij
            p - wklej
            c - kopiuj ścieżke 

        # ustawianie okien
            przechodzisz do neotree
                -> wyszukujesz plik i dajesz 
                    -S na dole 
                    -s z prawej
                Jak chcesz zakmnąc dane okno to jak jesteś w oknie to :close
    Jak cos zjebiesz to dajesz u -- undo
        a jak za dużo cofnąłeś to ctrl + r 

    # szukanie po pliku przechodzenie dalej
        :/something -> enter
            n - nastepne wystapienie
            N - poprzednie  

#--------------------------------------------------
tcpdmp -ni  interface_name --obczaj tą komende TODO

    name interface

#----------------------
Add interface eth3:SGW8 with address 10.0.1.108 and mask 21
dodawanie adresu jako aliasu:
    ip addr add ipczek/maska dev interfgace  labelka interface:alias
    np:
        sudo ip addr add 10.0.1.108/21 dev eth3 label eth3:SGW8
        label alias -- używana do odróznienia aliasów 


#-----------------
    sprawdzenie dokłądne procesów
    ps -eo pid,comm | grep nbio


# zajecia 
    update
    upgrade 
    less
    ssh-keygen
    ssh-copy-id

    ssh user@host -v -- szczegółowe logi

    PermitRootLogin prohibit-password
        jeśli ktoś ma klucz prywatny to może sie dostać

    zmiana kolorów ip a


10.55.269.1-19 / 16

    10.55.249.1-14 /16 - + dodać brame jak z windows
    Adresy do wykorzystania 
            /etc/network/interfaces
        Gateway...
            Nameservery - 8.8.8.8
            namsepaserer - 149.156.24.24
                /etc/resolv.conf
            testowanie dig / nslookup


    /potem test
    systemctl restart networking 
        restartuje konfiguracje 

    
255.255.0.0 / 16

auto enp0s3 
iface enp0s3  inet static
    address 10.55.249.6/16
    gateway 10.55.0.1
    dns-nameservers 8.8.8.8 149.156.24.24


    wygenerować autentykacje na roota za pomocą swojej pary kluczy publicznych
nameserver 8.8.8.8
nameserver 149.156.24.24

type idrsa.pub

ssh user@host -i .id_rsa -v -- używa innego klucza 


sudo nano /etc/apt/sources.list -- repozytoria
    # wrzucamy
    deb http://deb.debian.org/debian/ bookworm main contrib non-free non-free-firmware
    deb http://deb.debian.org/debian/ bookworm-updates main contrib non-free non-free-firmware
    deb http://security.debian.org/debian-security bookworm-security main contrib non-free non-free-firmware

# Zmiana hasła
    jesli znasz hasło to
    passwd  -- na akutalnym userze

    jeśli nie to 
    sudo su
    sudo passwd user


#--------------------------------------
Linuxowe sieci notatki:
#--------------------------------------
interfacy sieciowe: 
    enp0s3, eth0, eth3, eth300 
        to są interfejsy sieciowe w systemie
        czyli karty sieciowe tylko w linuxie


#--------------------------------------
Nazewnictwo interfaców:
    Stary system nazw:
        eth0 - Ethernet karta 0
        wlan0 - Wifi
    Nowy system nazw - predicable intercface names:
        enp0s3
        enp2s0
        ens33
        elp2s0
            każda część coś innego znaczy
            e - ethernet
            n - predicable name
            p0 - PCI bus 0 
              
            s3 - slot 3
            inaczej 
#---------------------------
Co to jest PCI BUS 0:
    PCI -  peripheral Component Interconnect
    - z ang - połączenie komponentów peryferyjnych
    płyta główna ma kilka magistrali - PCI  
    czyli autostrada (BUS)
    do każdej autostrady są podłączone urzadzenia
        karta graficzna
        sieciowa
        dźwiekowa
        konrolery USB itd
    Autostrada to PCI  Interconnect
    Każde miejsce gdzie można coś wpiąć to slot
        „karta sieciowa Ethernet wpięta w slot nr 3 na pierwszym busie PCI”
    Obrazowo:
        Płyta główna
        ────────────
        BUS 0
        ├── SLOT 1 ── karta graficzna
        ├── SLOT 3 ── karta sieciowa (enp0s3)
        └── SLOT 8 ── karta sieciowa druga (enp0s8)

        BUS 1
        ├── SLOT 0 ── kontroler USB
        └── SLOT 2 ── NVMe
        
#---------------------------
Sprawdzanie interfejsów:
    ip a  - interfacy sieciowe i adresy ip które system posiada

2: enp0s3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 08:00:27:46:e8:c5 brd ff:ff:ff:ff:ff:ff
    altname enx08002746e8c5
    inet 10.55.249.11/16 brd 10.55.255.255 scope global enp0s3
       valid_lft forever preferred_lft forever
    inet 192.168.1.12/24 brd 192.168.1.255 scope global dynamic noprefixroute enp0s3   
       valid_lft 6046sec preferred_lft 5146sec
    inet6 fe80::f469:5d37:6573:e3e7/64 scope link 
       valid_lft forever preferred_lft forever

Co to wszystko znaczy:
    1. enp0s3 - nazwa interfacu
    2. <BROADCAST,MULTICAST,UP,LOWER_UP>
        - flagi interfacu - czyli co potrafi i co wspiera
        - BRODCAST - potrafi wysyłać broadcast, komunikaty do wszystkich w sieci
        - MULTICAST - wspiera multicast
        - UP - jest włączony na systemie  | Down wyłączony
        LOWER_UP - połączenie fizyczne jest ok 
        - mtu 1500 - maksymalny rozmiar pakietu
        - qdiscfq_codel - algorytm kolejkowania pakietów
        - qlen 1000 - długość kolejki pakietów - ile może czekać
    3 link/ ether - adres MAC karty
        brd - adres brodcast
    4. altname - alternatywna nazwa
    5. inet - adresy IPv4
        10.55.255.255 -adres ip 
        /16 - maska
        brd- brodcast 
        scope global - jest normalnym adresem do użytku w sieci
        dynamic - przydzielone przez DHCP
        valid_lft - adres jest ważny ile czasu
    6. inet6 - adres IPv6

    INET:
        to jest adres/y ip który jest przypisany do danego 
        interfacu sieciowego dla systemu
            poprzez niego będzie można sie odezwać do akutalnego systemu 
        /16 - pod sieć w której sie znajduje urzadzenia
        do wszystkich hostów w danej podsieci mamy dostęp

//--------------------------------
Jak sie porozumiewają
    ip r - tablica routingu
    lista zasad:
        któredy aktualny sytem wysyła pakiety,
        w zależnosci od adresu docelowego

    W zależności gdzie kierujemy pakiet to przez tak pójdzie

default via 192.168.0.1 dev enp0s3
192.168.0.0/24 dev enp0s3 proto kernel scope link src 192.168.0.25

Tłumaczenie:
    default via 192.168.0.1 dev enp0s3
        dla wszystkich nieznanych adresów, wysyła ruch przez router/gateway
        - default - wszystko co nie pasuje do znanych
        - via .. - przez co ma iść
        - dev .. - użyj tej karty
    
    192.168.0.0/24 dev enp0s3 proto kernel scope link src 192.168.0.25
        192.168.0.0 - karta sieciowa lokalna
          - dana podsiec jest osiągalna przez tą karte 

//--------------------------------
    ip link - pokazuje same intefacy / karty sieciowe
        - czysta linia sprzętu
//--------------------------------
Skąd sie bierze IP- dhcp vs static
    DHCP - dynamiczne ip
        router sam automatycznie przydziela adresy ip

    Static - reczne ustawianie IP:
        używane w labach /serwerach / nietypowych sieciach
        ustawiasz go sam albo w network/interfaces



Podsieci i maski? (mega skrót, ale wystarczy)
    Typowe maski:
        /24 = 255.255.255.0 → najczęściej w domach
        sieć: 192.168.0.0 - 192.168.0.255

        /16 = 255.255.0.0 → jak lab uczelniany
        sieć: 10.55.0.0 - 10.55.255.255

VirtualBox:
    Tryby kart:
        Bridge 
        - VM jest jak normalny komputer w mojej sieci
        - router daje ip 
        NAT:
        - VM wychodz id ointrnetu, ale jest a NAT-em hosta
        - nie można pingować z sieci
        Host-Only:
        - VM widzi tylko hosta, nie ma intenetu

//------------------------
Ustawianie ip:
Trwałe - poprzez pliki konfiguracyjne
    /etc/network/interfaces - już 

    iface enp0s3 inet static
        address 10.55.249.11/16
        gateway 10.55.0.1   
    
    1. iface .. - dla intefacu x użyj statycznego adresu IPv4
    2. addres -- ustaw dla danego komputera i karty ten adres ip
    3  gateway - wyjscie do internetu poza sieć, to wysyłaj tutaj - adres rutera/ brama domyślna

Tymczasowe:
    tymczasowe ustawianie
    ip addr add 192.168.1.200/24 dev enp0s3
            dodaj <ip_addr>/maska device(na tym danym urzadzeniu) karta_sieciowa
        - opcje 
            del - usuniecie danego adresu
    ustawianie jakiś parametrów:
        mtu - maksymalny rozmiar pakietu chyba
        ip addr set dev enp0s3 mtu 1400
                ustaw na danym urzadzeniu - co i ile
    
    ip link set dev enp0s3 up
        -włącz urzadzenie  | down - wyłącz
    
    ip addr flush dev enp0s3
        - reset starych adresów na kartcie
    
    # ustawianie routy 
    ip route add 10.0.1.1/16 via 192.168.1.1 dev ensp03
            del - usuwanie

    ip -4 a - wypisuje tylko adresy ipv4

    reset interfacu:
        ifdown enp0s3
        ifup enp0s3 
        - czysci stan, ładuje z plików
        albo    
            ip link set enp0s3 down lub up
    
    sudo dhclient -v enp0s3
    pobranie ip z dhcp - ręcznie
        -v verbose - pokazuje 
        DISCORE - wysyła brodcast
        OFFER - daje propozycje IP
        REQUEST - prosi o IP
        ACK - przyjmuje IP

    ustawiani bramy domyślnej
        ip route add default via 192.168.2.2 dev enp0s3
        poza moją sieciową lokalną, wysyłaj pakiety przez router

    ip -brief link
        krótkie info - tylko nazwy i adresy i stan

//------------------------
Diagnostyka sieci
    ping  ip
        - działa routing - z ip route - jest widoczny dany host 
            /albo przez ruter albo lokalnie znany 
    traceroute ip
        cała droga pakietu przez co przechodzi
        - na przykład najpierw przez router potem przez coś innego i tak dalej
        traceroute 8.8.8.8
            pierwszy hop → TWÓJ ROUTER (192.168.1.1)
            drugi → Twój operator
            kolejne → trasy między operatorami
            ostatni → Google (8.8.8.8)

ARP: - address resolution protocl
    służy do:
        mam ip jakiegoś urzadzenia, ale musze poznać jego adres MAC
        żeby móc do niego cokolwiek wysłać
        bo komputery w sieci lokalnej wysyłają pakiety po adresie MAC a nie po IP
    IP mówi, DO KOGO chcesz wysłać pakiet
    MAC mówi, JAK DO NIEGO TRafić po kablu / Wi-Fi

Jak PC nie zna MAC:
    to rozsyła brodcast - po całej lokalnej sieci
    ARP REQUEST-
        pyta kto ma dany adres ip, i prosi o adres MAC
        zapisuje w tablicy ARRP i od tej pory go zna
    
    linux: 
        ip neigh - pokazuje tablice arp

    output:    
    192.168.1.10 dev enp0s3 lladdr b8:8a:60:9b:05:6e REACHABLE 
    192.168.1.2 dev enp0s3 lladdr 28:af:42:3e:10:60 STALE
    192.168.1.1 dev enp0s3 lladdr 78:8c:b5:10:0e:1e STALE

    stany:
        REACHABLE - mac jest znany, host odpowiada
        STALE - mac znany, host nie odpowiada
        incomplete - trwa prób ARP, nie odpowiada

    ip neigh flush all - czyszczenie tablicy 

#-------------------------

192.168.1.12 - server firewal
192.168.1.13 - attacker - nmap
192.168.1.10 - host - windows

# Zadanie do zrobienia:
    Nauka firewalla na najniższym poziomie
        iptables
        tablica filtrów
        łańcuch input / output

Mamy maszyne VM1
    piszemy skrypt firewalla, który kontroluje
        ja pakiety są wpuszane i wypuszczane na daną VMkę
    
Mamy drugą VM2 + twój host 
    służa one jako źródło testów
    symulacja ruchu
    sposób na pokazanie czy firewall działa

Jak działa przepyw pakietów przez iptables
    co to jest input / output 

#-----------------------
iptables - maszyna decyzyjna 
    - program / narzedzie w userspace, 
        który konfiguruje netfiltera
    netfliter - kawałek jądra linuxa, który decyduje co robić z pakietami
        - silnik firewalla 
    iptables - zarzadza silnikiem, ustawiamy nim reguły

Trzy pojecia :
    table - tablica - zestaw reguł do konkretnego celu
    chain - łanuch - lista reguł wykonywanych w danym momencie życia pakietu
    rule - reguła - pojedynczy warunek - akcja 

W linuxie jest kilka tablic:
    tabela to jest rodzaj operacji np:
        filter - filtrowanie pakietów, czyli firewall 
        nat - translacja adresów 
        mangle - modyfikacja pakietów
        raw - bardziej zaawansowane do conttrack

Filter:
    łancuchy: - czyli lista wykonywanych reguł podczas przepływu pakietu
    - INPUT - pakiety do tej maszyny 
        np gdy ktoś łączy sie poprzez SSH do obecnej maszyny
        INPUT:
            [reguła 1]
            [reguła 2]
            [reguła 3]

    - OUTPUT - pakiety z maszyny
        ty pingujesz, próbujesz sie dostać do kogoś innego
    - FORWARD - pakiety, przelatujące przez maszyne
        obecny linux jest routerem i przekazuje dane dalej
    
Jak płynie pakiet przez iptables:
    Ktoś łączy sie do twojej maszyny
    Pakiet przechodzi z sieci na karte  
    Kernel patrzy, pakiet do mnie, kierunek LOCAL_IN
    pakeit wpada do tablicy filter, łaćuch INPUT
    w INPUT jest lista reguł, idziemy od góry do dołu
    pierwsza reguła, do której pakiet pasuje, wykonuje akcje
    Decydujemy co z nim robimy , action (TARGET):
        ACCEPT - przepuszczamy dalej
        DROP - odrzuca po cichu (zero odpowiedz)
        REJECT - odrzucasz i odsyłą ICPM
        LOG - loguje, pakiet idzie dalej
        RETURN - zwraca z łańcucha

    na odwrót 
    ty wsyłasz 
    aplikacja generuje pakie
    kernel patrzy - LOCAL_OUT
    trafa do filter, łancuch OUTPUT
    reguły, robimy akcje 

Jak wygląda reguła:
    jeden warunek + jedna akcja
    iptables 
        -t filter # defaultowo --table 
        -A INPUT \ -- append dodaj na koniec tablicy INPUT
        -p tcp \ -- --protocol protokół tcp
        --dport 22 \  -- destination port port docelowy 22 -- ssh
        -s 192.168.1.10 \ -- source źródłowy ip hosta
        -j ACCEPT -- // --jump target
    
    -A -- append 
    -C -- check
    -D -- delete
    -I -- insert
    -R -- replace
    -L -- list 
    -F -- flush
    -s --source -- jak nie podane to wtedy wszystko
    -d --destination - dla każdego adresu docelowego
        ale to raczej dla OUTPUTU

Jak dopasować przychodzący pakiet ICMP:
czyli „jaki ICMP do mnie przyszedł”
    icmp-type:
        echo-request - ping przychodzący -> zapytanie
        echo-reply - ping -> odpowidx
        destination-unreacable
        time-exceeded
        redirect
        itp

Jak określić jakim komunikatem odrzucamy dane pakiet icmp:
    --reject-with 
        icmp-net-unreachable
        icmp-host-unreachable
        icmp-port-unreachable

// ---------------------- poglądowo
Internet / LAN
    ↓
Twoja karta (enp0s3)
     ↓
ŁAŃCUCH INPUT
   ├─ reguła 1: czy to host 192.168.1.10? jeśli tak → ACCEPT → KONIEC
   ├─ reguła 2: czy protokół tcp i port 22? jeśli tak → DROP → KONIEC
   └─ nic nie pasuje → domyślna polityka (ACCEPT)

// ---------------------- poglądowo
komendy fajne
    iptables -L - sprawdzenie jakie śa reguły 
            -L INPUT -v (--verbose)

    iptables -L -n -v - wszystko ładnie

    iptables -F INPUT
        --flush - czyści wszystkie reguły z łańcucha

    iptables -P INPUT ACCEPT
        --policy - ustawia polityke domyślną
        czyli wszystko jest przepuszczane itd


Ip mówi dokąd wysłać pakiet
PORT mówi do jakiej aplikacji
| Usługa | Port        | Protokół |
| ------ | ----------- | -------- |
| SSH    | 22          | TCP      |
| HTTP   | 80          | TCP      |
| HTTPS  | 443         | TCP      |
| DNS    | 53          | UDP/TCP  |
| DHCP   | 67/68       | UDP      |
| ping   | brak portów | ICMP     |

TCP ma handshake, sekwencje, stany połączeń itd.
ICMP to proste komunikaty.
ssh używa TCP na porcie 22.

Polityka: --policy
    każdy łaćńuch ma regułe, którą dodajemy
    oraz polityke domyślną, która mówi co zrobić z pakietem
    jeśli żadna reguła nie pasuje/ nie jest ustawiona
    
    czyli jak reguły nie złapią pakietu
        to co zrobić z nim decyduje poliyka
    takie finally 
   
    iptables -P INPUT ACCEPT
        Jeśli pakiet DO CIEBIE nie pasuje
             do żadnej reguły → WPUSZCZAMY.

        DROP 
            - nie wpuszczamy, nie ufamy

ICMP:  
    Ping to dwa różne pakiety ICMP:
1. echo-request
    → „hej, żyjesz?”

2. echo-reply
    → „tak, żyję”
Ping zawsze jest parą:
    request w jedną stronę
    reply w drugą
