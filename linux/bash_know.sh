

# debug skryptów, dajemy do #!bin/bash -xv
#!!!!!!!!! od pjotrusia protip !!!!!!!!!
 !/bin/bash -xv

BASH syntax:
    # switch case:   
    case "$1" in
        start)           # option 1
            echo "Startuję system"
            ;;
        *)            # default 
            echo "Nieznana opcja"
            ;;        # end sign 
    esac

    Przekazywanie wszystkich argumentów == $@
    for arg in "$@"; do

    done
    IFS=','   -- input field seperator - dzielimy w read po przecinku
        np:
            IFS=',' read -ra ZMIENNA <<< wartosc


    #------------------

    #!/bin/bash
    ENB_LIST=()
    MME_LIST=()
    # Parsowanie argumentów
    for arg in "$@"; do
    VALUES="${arg#*=}"
    case $arg in
        ENBs=*)
        IFS=',' read -ra ENB_LIST <<<  "$VALUES"
        ;;
        MMEs=*)
        IFS=',' read -ra MME_LIST <<< "$VALUES"
        ;;
        *)
        echo "Unknown argument: $arg"
        ;;
    esac
    done

    echo "Received IPs:"
    for ip in "${ENB_LIST[@]}"; do
    echo "$ip"
    done

    for ip in "${MME_LIST[@]}"; do
    echo "$ip"
    done

    # przypisawanie wywoływania komendy do zmiennej
    zmienna=$( komenda)
        np: NODES=$(epmd -names)

# wyniki z grepa w zmiennej 
np:$(ip addr show eth3 | grep -oP '10\.0\.(?:10|[0-9])\.1\d{2}')
to jak damy do zmiennej to bedzie tekst a chcemy tablice 
to konewrtujemy sobie na 
readarray -t zmienna < < (grep)


#---------------------

# Bash zabawa i nauka 
tablica asocjacyjna -- mapa w bashu
declare -A  nazwa (czyli klucz wartosc)
for pattern in "${!cus_patterns[@]}"; do
    echo "Pattern: $pattern → Value: ${cus_patterns[$pattern]}"
done

[[ -n $zmienna ]] -- niepusta
[[ -z $zmienna ]] -- pusta

  declare -A cus_patterns=(
        ['^CUS_2\.0\.REL\.([0-9]{6}\.[0-9]{2})$']="CUS_2.0|cus_2.0.REL.{date}_amd64.deb"
        ['^CUS_2\.0\.DEV\.([0-9]{6}\.[0-9]{2})$']="CUS_2.0|cus_2.0.DEV.{date}_amd64.deb"
        ['^CUS\.([0-9]{6}\.[0-9]{2})$']="CUS_TRUNK|cus_{date}_amd64.deb"
        ['^CUS\.([0-9]{6}\.[0-9]{2})\.DEV$']="CUS_TRUNK|cus_{date}.dev_amd64.deb"
    )
declare -A REPOSITORIES=(
    ['CUS_TRUNK']="\
        link1 \
        link1 \
        link1 \
    ",
    ['CUS_2.0']="\
        link1 \
        link1 \
    ",
    ['Esim']="link1"
)
iteracja wydobywanie
CUS_PATTERNS[@] -- wartosci
!CUS_PATTERNS[@] -- klucze 
${!REPOSITORIES[@]}
${!REPOSITORIES[CUS_TRUNK]}


cut - przyciannie / wyciaganie stringow
    echo "file.txt,2.0" | cut -d ',' -f2
        -d --delimeter - separator 
        -f -field x - wyciaga dane pole


@? -- kod jaki zwraca wywołanie ostatniej komendey
# redirections - przekierowania wyjśc strumienia
-- gdzie trafia wynik
strumienie
0 - stdin - read /cat 
1 - stout - wyjście programu echo 
2 - stderr - wyjście błedów

    >/dev/null - wycisza stdout

    2>/dev/null- wycisza stderr

    > /dev/null 2>&1 - wycisza wszystko 

    2> somewhere.txt - wyjscie stderr przekieruj do 

    2>&1 - wyjscie stderr to stdut


ping -c (count) -W (wait - timeout)

tworzenie zmiennych i czytanie z listy
local user host password
read -r user host password <<< "$@"

# default values
: "${host:=127.0.0.1}"
: "${user:=ute}"

run_func "admin" "" "pass123" # lsita

#ustawianie wartosci do zmiennej jesli jestp usta
    var:=default_value
    local host="${5:-$LOCALHOST}"
        - od razu przypisanie 

date +$s

# operacje arytmetyczne
var=$(( 2 + 2 ))
var=$(( data - data2 ))

sed -i 's|/sciezka1|sciezka2|g' /sciezk3
- zamienia wystapienia sciezka1 na sciezka2 w pliku sciezka3

'something $zmienna' -- wszystko traktowane literalnie tak jak jest
"something $zmienna" -- interpretuje zmienne i inne

operator:
    =~ - sprawdzanie wyrażenia regularnego



"CUS_2.0|cus_2.0.REL.{date}_amd64.deb"
    substring removal:
    skłądnia:
        $var%%  -- usuwa dopasowanie wzorca od końca (sufix)
        $var##  -- usuwa dopasowanie wzorca od poczatku (prefix)
    cus_version="${matched%%|*}"
    package_template="${matched##*|}"
    


