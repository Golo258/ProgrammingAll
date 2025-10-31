
Kierunki transmisji danych miedzy urządzeniami:
    1. Downlink (łącze w dół):
        przesyła danych od sieci (z BTSa) do użytkownika (UE)
        jest on prioretyzowany, gdyż użytkownicy cześciej pobieraja dane niż je wysyłają

    2. Uplink (łącze w górę):
        przesyła danych od UE do stacji bazowej
        prędkości są niższe gdyz cześciej się pobiera dane ( downlink )
        aniżeli się je przesyła (uplink)


CUS komponenty:
    WS - workstation - stacja robocza
        uruchamia oprogramowanie kontrolujące:
            konfiguracją
            wywoływaniem testów
            logowaniem
        conajmniej jedna stacja robocza

    TGR-MS - traffic generator/receiver Mobile Side (UE Side)
        - generator/ odbiorca ruchu strona mobilna
        Komponent który uruchamia oprogramowanie które generuje i mierzy ruch danych
        Działa dwukierunkowo, pełni role odbiorcy i nadawcy danych
        Generuje uplink ( wysyła dane z urzadzenia do stacji )
        Odbiera downlink (odbiera dane ze stacji )

        Dane przesyłane sa przez TGR-MS -> CUS_Ctrl -> eNodeB -> EPC -> TGR-SS

        conajmniej jeden TGR-MS

    TGR-SS - traffic generator /receive System Side (BTS side)
        uruchamia oprogramowanie które generuje i mierzy ruch danych
        Generuje downlink ( przesyła dane ze stacji bazowej UE )
        Odbiera uplink (odbiera dane od użadzenia TGR-MS)
        Dane przesyłane TGR-SS -> EPC -> eNodeB -> CUS_Ctrl -> TGR_MS

        conajmniej jeden TGR-SS

    CUS_Ctrl:
         komponent bazujący na sprzęcie AirSkale eNodeB z oprogramowaniem CUS

    CUS_net - prywatna sieci dla komunikacji komponentów CUS

eNodeB: ( evolved Node B)
    stacja bazowa w sieciach LTE
        przesyła dane w trybie downlink - ( z sieci do UE )
        odbiera dane w trybie uplink    - ( od UE do sieci)

    - kontroluje zasoby radiowe
    - zarzadza przydzielaniem kanałów,
    - ustawia parametry transmisji i dba o jakość sygnału
    - umożliwia przekazywanie połączeń miedzy BTS-ami, gdy użytkownik sie przemieszcza (Handover)

EPC - evolved packet core - rdzeń pakietowy
    centralny rdzen sieci LTE
    zarżadza ruchem danych, mobilnością oraz usługami LTE
    Komponenty:
        MME - mobile management entity - jednostka zarządzająca mobilnością
            zarzadza mobilnością UE:
                rejestracją
                autoryzacją
                uwierzytelnianiem
                obsługa połączeń

        SGW - serving gateway  - brama obsługująca
            obsługuje ruch danych miedzy eNodeB a EPC
            zarządza przepłwem danych do UE

        PGW - packet data network gateway - brama sieci pakietowej transmisji danych
            umożliwia połączenie z sieciami zewnętrznymi (internetem)
            zapewnia dostep do usług internetowych i kontroluje routing danych

        HSS - home subsriber server
            przechwouje dane o abonamentach, o subskrybcji oraz dane o mobilności UE


Gdy urządzenie użytkownika łączy się z siecią LTE, najpierw nawiązuje kontakt z najbliższym eNodeB,
 który zapewnia zasięg i podstawową obsługę komunikacji.
 eNodeB przekazuje dane do EPC, który zarzadza autoryzacją, mobilnością i przepływem danych

Bearer - kanał / nośnik:
    logiczny kanał transmisji danych umożliwiający przesyłanie danych miedzy UE a EPC
    zapewnia określony poziom jakości usługi QoS - quality of service:
        przepustowość, opóxnienia, priorytet danych

    - to specyficzna konfiguracja, któa definuje sposób przesyłania danych,
        dostepne zasoby, przepustowość, wymagania jakościowe usługi

    - kazdy kanał jest przypisywany do danej sesji:
        np: przegladanie internetu | połączenia VoIP | wiadomości multimedialne

    Jak działa w praktyce:
        Kiedy user chce połączyc się z LTE, siec konfiguruje 1 podstawowy bearer do transmisji danych
        W zależności od potrzeb, siec ustanawia nowe bearery
        Każdy kanał przesyła dane, zapewniając odpowiednią jakość usługi (zgodnie z konfiguracją QoS)

    Pojawiają w się w architekturze EPC, EPC - eNodeB, eNodeB -> UE:
        Między Ue -> eNodeB są tworzone DRB - Data Radio Bearars
            przenoszenie danych UE interfejs radiowy do eNodeB

        Miedzy eNodeB a EPC (SGW)
            S1 Bearer - przechodzi przez interfejs S1
            łaczy eNodeB z SGW który jest odpowiedzialny za ruch danych z urządzeń usera

        Wewnątrz EPC - SGW i PGW:
            EPS Berar - przebieg transmisji UE do EPC (PGW)

Chłopski rozum komponenty LTE:
    UE - User Equipment:
        telefon, tablet , laptop czy inne urządzenie użytkownika
        Łączy się z siecią LTE, przez najbliższą stacje bazową eNodeB, odbiera i wysyła dane:
            wiadomośći, połączenia i transmisje internetowe

    eNodeB - Evolved Node B - stacja bazowa
        antenta, nadajnik
        zadania:
            umożliwia komunikacje miedzy UE a siecią
            przekazuje sygnał radiowy do urządzenia
            zarządza połączeniami i przydzielaniem zasobów ( czestotliwość, pasma)
            handovery - zmiana stacji dla przemieszczającego się usera

    EPC  - evolved packet core - rdzeń sieci:
        serce lte, posiada serwery i bramy które zarzadzaj ruchem danych i dbaja o połączenie

        MME:
            zarządza mobilnością użytkowników ( logowanie, uwierzytelnianie, sesje )
            sprawdza kto jest zalogowany i gdzie sie znajduje, dba o dobre połączenie UE i handovery

        SGW:
            obsługuje cały ruch danych miedzy eNodeB a EPC, przekieruje dane od UE do sieci
            to coś jak magistrala która kieruje ruchem danych z UE do sieci, pilnuje poprawność danych

        PGW:
            końcowa brama do internetu dla UE
            wrota do Internetu, przekazuje dane z sieci operatora do internetu i na odwrót

        HSS:
            baza danych abonamentów ( uprawnienia i usługi )
            ksiązka abonamentow mówiaca kim jesteś i jakie masz uprawnienia i dostepy

Protokoły L3:
    Odpowiada za sygnalizacje i zarzadzanie połączeniami midzy UE a EPC:
        RRC (radio resource control) - kontroler zasobów radiowych
            działa na interfejsie radiowym miedzy UE a eNodeB
            Zadania :
                nawiązywanie
                utrzymywanie
                zwalnianie połączeń radiowych miedzy UE a eNodeB
            Funkcje:
                ustanawianie sesji i rozłączeń połączeń
                zmiana stanu z connected na idle (urzadzenie oszczedza energie)
                zarządzanie mobilność czyli handoverami miedzy BTSami
                zarządzanie i przekazywanie parametrów QoS oraz inicjaowanie beraera dla transmisji danych

        NAS (Non-Access-Stratum) - warstwa bez dostępu
            Działa miedzy UE a EPC ( a dokładniej MME)
            protokół sygnalizacyjny, obsługujący komunikacje między UE, a EPC na poziomie kontrolnym
            Odpowiedzialny za:
                logowanie UE do sieci i autoryzacje dostepu do usług
                monitorowanie lokalizacji UE w sieci (handovery)
                ustawianie i zarzadzanie sesjami IP, UE ma przypisany adres i może wymieniać dane
                zarządzanie bearerami - tworzy i obsługuje kanały, zapewniając odpowiednią jakość usług QoS

        IP: internet protocol
            odpowiedzialny za przesyłanie danych UE, czyli pakietów IP, z urzadzenia przez sieci do internetu i z powrotem
                Obejmuje:
                    przesyłanie danych aplikacyjnych
                    end-to-end połączeń z serwerami w interneecie

            trnaposrt danych UE przez sieci, zapewnienie że trafią do właściwego miejsca

    RRC – zarządzanie połączeniem radiowym na poziomie radiowym między UE a eNodeB.
    NAS – sygnalizacja i zarządzanie sesjami między UE a EPC, w szczególności z MME.
    IP – transport danych użytkownika przez sieć LTE i dalej do Internetu.


EARFCN  - (Evolved Absolute Radio Frequency Channel Number)
    EARFCN jest to numer kanału przypisany do danej częstotliwości operacyjnej w sieci LTE i 5G.
    Każda częstotliwość, której używa stacja bazowa (eNodeB),
    jest jednoznacznie identyfikowana przez ten numer.
    Dzięki EARFCN, urządzenie (telefon) wie, 
    z  jaką częstotliwością ma się połączyć, nawet jeśli w sieci działa wiele różnych pasm.


# Test knowleage:
Sanity Tests:
    proste i szybkie testy przeprowadzane na oprogramowaniu
    sprawdzające funkcje systemu po wprowadzeniu updatów
    werfikacja czy system jest stabilny aby przeprowadzić inne esty

    obejmują tylko najważniejsze funkcjanolności zmienione lub wprowadzenone do modyfikacji
    są szybkie i zazwyczaj wprowadzano po naprawieniu błędów

ET - exploratory test  -testy eksploracyjne
    metoda testowania w której aktywnie szuka błędów i problem w systemie 
    bez wcześniejszego przygotowania przypadków testowych



PET - Performance / Efficiency / Throughput Testing 
    Testy wydajności, efekywności i przepustowości
    Performance Testing (wydajności)
        sprawdza system pod obciążeniem
        celem upewnienia sie że system może obsłużyć przewidywane obciążenie
            (liczba userów, liczba zapytań)

        Efficiency Testing (efekywności)
            bada efekywności zarządzania zasobami, aby zapewnić jaknajlepsza wydajność
                bez nadmiernego obciążenia procesora/ pamięci/ sieci

        Throughput Testing (przepustowości)
            ocenia ile danych system może przetworzyć w jednostce czasu
                istotne w telekomunikacji gdzie systemy obsługją duży przepływ danych 

LAA (Licensed Assisted Access) 
    Technologia pozwalająca operatorom sieci wykorzystywać dodatkowe
        nielicencjonowane pasmo czestotliwości do zwiekszania prędkosci transmisji danych
        przy zapewnieniu niezawodności dzieki połączeniu z pasmem licencjonowanym

SISO - single input single ouput
    podstawowy model transmji sygału w telekomunikacji
        w ktorych korzysta sie z jednej anteny nadawczej i jednej anteny odbiorczej

    dane są przesyłane przy użyciu jednego strumienia sygnału
    najprostszy model transmisji 
    stosowane tam gdzie wymagania przepustościowe nie są wysokie lub gdzie 
        sieć i urzadzenia sa ograniczone technicznie i kosztwo

CATM - CAtegory M1 
    Technologia LTE Cat-M! 
        zaprojektowana z mysla (OiT) Internet of Things - komunikacji internu rzeczy
        oferująca  niską przepustowości, niskie zużycie energi i wsparcie dla 
        urządzeń o niewielkich wymaganiach transmisji danych 

    Jeden ze standardów LPWAN (Low power wide area network)
    Testy:
        Data Throughput Testing - wydajności transmisji danych
            testy oceniają prędkość przesyłania danych dla CATM w różnych warunkach sieciowych
            min /max prędkości transmisji 

        Coverage and Signal quality testing - pokrycia i jakości sygnału    
            zoptymalizowane pod kątem pracy w trudny warunkach sygnałowych
                wewnątrz budynów na obszarach wiejskich
    
CA_MMIMO
    CA - Carrier Aggregation - agregacja nośnych 
        technologia pozwalając operatorom na łączenie wielu pasm częstotliwości 
        (nośnych - Carrier) w celu zwiększenie przepustowości sieci
        i poprawy szybkości transmsji danych

        Pozwala użytkownikowi uzyskać wyższe prędkości transmisji danych 
        poniewaz jednocześnie wykorzystuje wiele połączonych pasm 

    MIMMO- massive multiple input multiple output  - masywne wieloktronte wejście i wyjście
        rozwiniecie technologii MIMO, w których stosuje sie wiele anten niż w standardowym MIMO
        Dzięki dużej ilości anten (64 / 128 lub wiecej)
            pozwala na równoczesną obsługę wielu użytkowników, zwiekszona przepustowości 

        Używana w środowiskach o dużej gestośi userów (stadiony, galerie)

    CA_MMIMO testing:
        obejmuje sprawdzenie efekywności współpracowania tych technologia
        Testy:
            Throughput testing - przepustowości
                oceniają max i average przepustowość sieci z aktywnymi CA i MIMMO

            Spectral Efficency Testing ( efekywności spektrealnej)
                sa wymagane do optymalnego wykorzystania pasma
                spektrum - pasmo czestotliwości - zakres czestotliwości fal radiowych
                sprawdza czy poprawnie wykorzstuje dostępne spektrum 

            Signal quality and Stability Test - stabilności i jakości sygnału

            Moblity and Handover testing - mobilności i przełączania
                duża ilość anten i połączonych pasm
                sprawdza czy skutecznie user moze sie przemieszczac miedzy antenami
            
            Interference Testing 
                MIMMO minimalizuje interferencje i połączenie pasm 
                sprawdza czy przemieszczający sie userzy nie tracą jakości połączenia
                interferencja 
                    - zakłócenia fal radiowych gdy sygnały nadawane w tym samym czasie 

Płaszczyzny w telekomunikacji:
    1. UPLANE  - user Plane - płaszczyzna użytkownika
        odpowiada za przesyłanie danych użytkownika (głos/text/video)
            pomiedzy urzadzeniami końcowymi a siecą
            wlaściwa transmisja danych

    2. CPlane - control plane - płaszczyzna sterowania
        odpowiada za zarządzanie i kontrolowanie komunikacji wsieci
            zestawienie połączeń / routing sygnałów sterujących
            przekazywanie informacji o sesji, obsługa protokołów i sesji połączeniowych
        
    3. MPLANE - Management Plane - płaszczyzna zarządzania 
        odpowiada za monitorowanie i zarzadzanie całym systemem sieciowym
            zarzadzanie konfiguracja / błędami / bezpieczeństwem / optymalizacją wydajności
        
        monitorowanie i utrzymywanie sieci, naprawianie problemów
        

PERF - Performance Test Automation Framework
    aby dostarczyć autonomoie do procesów testowych


Robot test execution:
    Generic command:
        robot -L DEBUG -b debug.log -d PATH_TO_OUTPUT PATH_TO_TESTSUITES
    
    or if config files are needed
        robot -V PATH_TO_TL_CONFIG -L DEBUG -b debug.log -d PATH_TO_OUTPUT PATH_TO_TESTSUITES
    
    Example:
        robot -L DEBUG -b debug.log -d /tmp/ testsuite/WTS/DCM/LTE4947/


PLMN (ang. Public Land Mobile Network)
    Oznacza ono publiczną, naziemną sieć mobilną obsługiwaną przez operatora telekomunikacyjnego,
    ...    takiego jak Orange, T-Mobile, Plus czy Play
    Selected PLMN:
        nosi się do sieci mobilnej, z którą aktualnie jest połączone Twoje urządzenie.
    Urządzenia (np. smartfony) mogą automatycznie wybierać sieć lub pozwalać użytkownikowi ręcznie wybrać,
    ...    z którym operatorem chce się połączyć    

MMEGI (MME Group Identifier)
    - identyfikuje grupę MME w ramach publicznej sieci lądowej (PLMN).

MMEC (MME Code):
    - unikalny kod identyfikujący konkretną jednostkę MME w danej grupie.

    Razem tworzą unikalny identyfikator MME w sieci, 
    ...    co umożliwia efektywne zarządzanie mobilnością i 
    ...    identyfikację urządzeń w sieciach takich jak LTE.

#--------------------------------------------------------------
#--------------------------------------------------------------
Informacje telekomunikacjyjne:
    PCMD - Packet Core Measurement Data
                rodzaj raportu / statystyk zbieranytch z elementów EPC 
                    zawiera sesje danych (bearerach)
                    attach /detach ue 
                    user plane 
                    qos qci tedit ip ue , itp

    CATM - CAT - category - kategorai urzadzenia LTE
        jakie możliwości ma dane urzadzenie,
            predkość
            ilość antent MIMO
            bandwitch
            VOLTE itp

        CATM -CAT-LTE-M1 - specjalna wersja LTE dla IoT
            IoT- małe urzqadzenia, małe predkosci, wytzrymałą bateria
                mąły bandwitch 1,4Mhz
                
        CAT-M1 - dla IoT
        CAT-M2 - NB-IoT -- to samo co IoT tylko nie używa Bandu LTE, i DSSS
        CAT-M4 - smartfony 
        CAT-8 - ?
        CAT-10
--------------------------------------------------------------
    
    HARQ: Hybrid automatic repeat reQuest
        mechanizm retransmisji danych
            naprawia błędy w przesyłaniu bez czekania na nowy pakiet
            Kiedy przesyłamy dane to zamiast retransmisji całego pakietu 
            to dajemy tylko te kawałek informacji zakodowanej inaczej, łaczy te dwa kawałki i jest git
                - UE nie wywala błędnego pakietu!
                - UE trzyma go w pamięci i „dokleja” kolejne retransmisje.
                - Poem, ok, teraz mam dość danych, mogę to złożyć poprawnie!

--------------------------------------------------------------
    Kanały:
        LTE-M - ma dla IoT - prefix M - Machine-Type Communication
        NP:
            PUCCH- physical uplionk control chanell
            MPUCCH- machine type --- 

        Podział kanałów:
            Logiczne - co wysyłamy  - wartswa RLC  - informacje logiczne 
            Transportowe  - jak to wysyłamy   - warstwa MAC - format transmisji
            Fizyczny - gdzie to wysyłamy   - wartswa PHy- faktycze sygnał radiowe

            PDSCH / PUSCH - physical downlink/uplink shared channel
            PDCCH / PUCCH - physical downlink/uplink control channel
            PBCH - physical broadcast channel

                S/C/H/B/R - shared / control / hharq / broadcast / random
                P - paging / RA - random access / CC - common control / D- dedicaed
                DT- dedeicaed traffic  

            Każdy kanał ma jakąs funkcje coś robi:
                S - Shared - współdzielony:
                    kanał jest dzielony miedzy wielu UE  

                C - control - kontrolne sygnąły
                    kanał przesyła sygnały, kto co gdzie i kiedy ma wysyłać i odbiertać
                        sygnalizacja co sie dzieje i ma sie dziać z danymi 
                        DCI -downlink control information - intrkcje 
                
                B - brodcast - rozgłoszeniowy 
                    kanał wysyła dane do wszystkich UE w komórce 

                RA - /PRACH  - random access
                    kanał do zgłoszenia sie do sieci, przy włączeniu sie UE 

                P - paging - przywyołanie  
                    gdy UE jest idle, to kanał go budzi i mówi że ma wiadomość 

                D - dedicated - 
                    kanał tylko dla danego UE
                        Np: do przesyłania syngalizacji RRC VOIP
--------------------------------------------------------------

    UE CRNTI - cell radio network temporary indentifier 
        - tymczasowy identyfikator 

    PCMD - performance cell mesaurement data 
        zbior danych pomiarowych, rejestracje zdarzeń, pomiary itp
    
    WB - wideband - szerokopasmowy ( 15 / 20 MHz)

    ETWS - earthquake and tsunami warning system
        - ostrzeganie przed trzesieniem i tsunami 
        - natychmiastowe rozgłaszanie komunikatów alarmowych do UEków
        - działa bez połączenia z internetem, w trybie uśpienia
        - przesyłane przez Cell Broadcast - do wszystkich UE w zasięgu danej celki
    
    CMAS - Commrcial Mobile Alert System 
        - system powiadamania - szerszy zakres niż ETWS - bardziej publiczne
        - umożliwia rządowi wysyłanie alarmowych wiadomości do wszystkich telefonoów
        w danym obszarze - bez potrzeby znajomości numeów
        Cell Brodcast - nadawane przez BTSy do wszystkich urzadzeń w zasiegu

    PRACH - phyical  random acces channel 
        - kanal w uplinku 
        - pierwszy kontakt / synchronizacja czasowa / żadanie przedzielenia zasobów

        Jak ustawimy na celce - to m,ówi nam jak czesto
            ma sloty na ten kanał

    CR RA DL 
        contention Resolution random acces downlink
        rozstrzyganie kolicji w dostepie losowym na dowlniknu
        - kiedy wiele UE jednoczesnie chce sie dostac do przez PRACH (rando access)
        mogą sie zderzyć, wtedy siec identyfiukuje i rozwiazuje konflikty
        -- wiadomośc RAR ( Random Access Reposne ) albo RRC Connection Setup

    TTI:    
        transmision time interval
            jednostka czasu transisji danych wysyłana w 1ms 
            w każdej jednostce można wysłać jeden blok danych

        TTI bundling - (łaczenie)
            łaczenie takich jednostek w jedną wiązke z tymi samymi danymi
            zwieksza szanse na dotarcie do celu
        które są powtarzane kilka razy z rzędu
            zwiększa niezawodność ( w trakcie problemów/ słąby sygnał telefonu )

    CATM HARQ Bundling:
        CATM (IoT) Harq- (niezwodność) (łaczenie w przypadku słąbego sygnału)

    PM counters:
        Performance measuremnt counters
            liczniki pomiarowe wydajności 
            do monitorowanie i analizy dziąłania sieci

#--------------------------------------------------------------

    CoMP- Coordnated multipoint feature activation for eNB
    uplink - COMP- coordinated multi point transmission
        koordynuje uplink od UE do wiecej niż jednego eNB
        zwiększa traffic na uplinku

    SINR- signal to interference plus noise tatio
        stosunek sygnału do zakłoceń i szumu
        - mirzy jak czysty jest odbierany sygnał radiowy 
        jak bardzo jest zagłuszany prze szumy (noise)
         zakłocenia z innych komnórek (interefence)
         i inne \

    QAM - quadrature amplitude modulation
        kwadratowa modulacja amplituy 
        -- metoda modulacji sygnału radiowego -pozwala przesyłać dużo
        danych w krótkim czasie 
        -- poleca na tym żę amplituda ( siła sygnału ) i 
        faza ( przesuniecie sygnału w czasie ) sa uzywane jednoczesnie do dekodowania informacji

    256 - liczba możliwych symboli (Stanów )
        256 - 8 bitów 

    Donut Cell - niewielki zasieg lub jakośc sygnału w środku
        dobra jakość wokół siebie 
        specjalna antenat która nadaje na boki( nie wali danymi w ziemie )
        dlatego jest słaby zasieg blisko

    PDN - packet data network - sieć danych pakietowych
        zewnętrzna sieć 
        internet lub sieć, do której sieć operatora Cię dopuszcza
         po zestawieniu PDN connection

    APN - access point aname - 
        identyfikuje z jakim PDN chcesz sie połączyć

    IPsec - internet protocol security 
        zestaw protokołów sieciowych zapewniających bezpieczne przesyłanie danych
        w sieciach IP -- uwierzytelnianie / szyforwanie /
        tworzy tunel szyfrowania Securiy Association pomiedzy UE a PGW
        Transport mode -- szyfruje dane
        tunnel mode - szyfruje cały pakiet IP

    High speed users
        komórka która jest przystosowana do obsługi bardzo szybko
        poruszających sie urzadzeń (pociagi auto samoloty)

    CDMA - code division multilple access
        technologia dsotepu wielkrotnego 
        wiele urządzeń możę nadawać jednocześnie na tej samej częstotliwości
        każdy UE ma swój unikalny kod 
        sygnał jest rozszerzany- rozrzucany po całym paśmie


    OFDMA - orthogonal frequncy division multiple access
        dzielenie czestotliwości i czasu meidzy wielu UE
        wiele UE jednocześnie korzysta z jednej czestotliwości
            każdy dostaje mały kawałek pasma (subcarrier) na krótki czas

        wiele urządzeń może nadawać i odbierać dane jednocześnie, bez zakłóceń.

    1xRTT - standard transmisjii dany w CDMA 
        1x - pojedynczy kanał transmisji
        RTT (round trip time)- czas potrzeby do wysłania i odebrania sygnału
        
    CS - circiut switched - połączenie komutowane 
        dla każdego połazcenia jest rezerwacja dedykowanego kanału
        zamiast połączeń pakietowych, połączenie jest stałe przez cały czas rozmowy

    Fallback - awaryjne połączenie/ powrót do poprzedniej wersji
        połączenie głosowe automatycznie przełącza sie na starsza sieć
        CDMA 1x, aby zapewnić ciąg rozmowy

    CSFB - circuit switched fallback
        przełączenie sie UE z LTE na 2G/3G 
        LTE to technologia ałkowicie pakietowa all-IP - nie ma wudowanego głosu
        dlatego dopóki nie ma VoLTE musi robić fallback do starszej sieci

    
    IMS - IP multimedia subsystem
        system multimedialny oparty na protokle IP 
            obsługuje VoIP i inne

    MT - mobile terminated - połączenie przychodzące
        połączenie które jest odbierane przez UE 
    
    MO- przeciwieństwo MT - mobile originated - wychodzące
        połączenie inicjowane przez UE 
    
    MAC-I - message authentication code for Integrity
        pieczątka bezpieczeństwa dodana do komunikatu RRC
        sieć wie że wiadomość nie została zmieniona ani sfałszowana


    Preregistration:
        proces w którym UE rejestruje sie w tle w sieci CDMA
        jeszcze zanim cokolwiek zadzwoni
        -- żeby jaknajszybciej zrobić fallback 

    BSC - (Base Station Controller)
        element sieci 2 (GSM)
        zarządza BTSami - kieruje ruchem, ho, zasobami
        GSM -- global system for mobile ocmmunications
            pierwszy standard telefonni 

    RNC - radio network controller
        - główny kontroller w sieciach 3G(UMTS / WCDMA)
        
    ARFN  - absolute radio frequency number
        numer który identyfikuje konkretna czestotliwośc w GSM
        ustawiani bearera w testach 
    
    RAT- radio access technology
        technologia dostępu radiowego
        to konkretna technologia która określa jak UE komunikuje sie z BTSem
        np:
            GSM - global system for mobile COMmuniication -2G
                głównie dzwonienie i wysyłanie SMSów
            UMTS - universal mobile telekomsystem - 3G

            CDMA2000 - Code Division multiple access 2G/3G
            LTE - Long Term Evolution - 4G
            NR - New Radio - 5G
    
    #-----------------------------
    2G - dzwonienie, SMs, proste dane (GPRS /EDGE)
        GSM - global system for mobile commmunuiactions
        Działa na:
            TDMA/FDMA - time /frequency division multiple access
            każdy UE ma 
                inny czas  | inną czestotliwość
                transmisja przerywana, słaba przepustowość
    
    3G - wchodzi internet, przeglardki YT MMSy, poczta itp
        UMTS - universal mobile telecommunication system    
            eurpejska wersaj sieci 3G
        działa na 
        WCDMA - wideband code division multiple access
            sposób komunikacji radiowej miedzy UE a eNB
            nadawanie w tym samym czasie i na tej samej czestotliwości
                dane sa kodowane 
                UE i ENB znają swój kod

    4G: szybki internet, VoIP, streaming HD, brak klasycznego dzwoneinia
        LTE - long term evolution
            calkowicie pakietowa transmisja (IP based)
            rozmowy przez VoLTE
        Działa na:
            OFDMA - orthogonal frequency division mutliple access
            użytkownik dostaje różne podnośne (subcarriers)
            podział w czasie i czestotliwośc
            wysoka efektywnośc i małe opóxnienia

    5G: ultra sztybki net, niskie opóźnienia, IoT
        NR: New Radio
            nowa architektura, elastyczna i modułowa
        Działa na:
            OFDMA + pełna optymalizacja
                dynamiczne przydziały zasób
                massive MIMO
                beamforming
                slicing - siec podzielona na warstwy
    #-----------------------------

    UPF - user plan function
        komponent w sieciach 5G
        przesyła dane użytkowniak (USser plane) czyli twój internet /voip /video
        cześć 5GCore
            odpowiada za routowanie danych UE 
            tunelowanie danych GTPU
            itd
    
    Radio - fizyczny nadajnik odbiornik - podpięty do anteny
        nadaje i odbiera sygnały radiowe
        działa na konkretnej czestotliwosci
        jest sterowane przez enb 

    CPRI: - common public radio interface
        standard interfejsu (jakiegoś protokołu) który łączy
        BBU (Baseband Unit):
            mózg stacji bazowej 
            koduje dekoduje dane
            szyfruje deszyfruje 
            modulacje demodulacje
            harmonogram transmisji
            
        wszystko co logiczne i cyfrowe dzieje sie w BBU

        CPRI: superszbkie i cyfrowe połączenie 
            światłowód lub szybka linia która przenosi
            - dane wejściowe/modulacyjne -gotowe do nadania radiowego
            - sterowanie radia 
            - zsynchronizowane zegary 

        RRU: (Remote Radio Unit) czyli nadajnik/odbiornik antena - dane radiowe do UE
            montowany blisko anteny 
            obiera dane przez CPRI od BBU
                zamienia sygnał cyfrowy -> analogowy -> wysyla fale radiowe
                lub odwrotnie odbiera fale -> analog -> cyfrowy - odsyła przez CPRI
            
     +---------+      CPRI       +--------+      ~~~~~~~
     |  BBU    |================>|  RRU   | ---> | antena |
     +---------+                +--------+      ~~~~~~~
        
    OBSAI: open base station architecture initiative
        standard interfejsu do koomunikacji- jak CPRI ale modularny
        OBSAI dzieli komunikacje na moduły logiczne:  
        osobne kanały do:
            sygnałów I/Q
            sterowania
            zarzadzania
            synchronizacji
        
                            OBSAI Link (wiele kanałów 
                        wiele niezależnych strumieni danych)
    ┌────────────┐═══════════════════╗  
    │  Baseband  │──I/Q Data─────────┼──▶│ Radio Unit │───▶ Antena
    │   Module   │──Control──────────┤
    │   (BBU)    │──Timing───────────|
    └────────────┘═══════════════════╝

        BBU przygotowuje dane I/Q, steruje RRu i zapewnia synchronizacje 
        RRU - dostaje dane, wysyła /odbiera do/od UE


    Carrier: (nośna) - to jedna częstotliwości radiowa
        z okresloną szerokościa pasma, nadanie/odbieranie danych
        np pasmo to 1800 MHz, to jeden carrier bedzie np 20Mhz
        każdy carrier to jak osobna autostrada dla danych
        to taki pakiet transmisji:
            downlink -z eNB do UE
            uplink - z UE do eNB
            sync, itp
    
    Slim-carrier- odchudozona wersja carriera
        czesto do IoT, CAT-M, NB-IoT
        ma mniejsze pasmo 1.4Mhz

    Super cell 
        logiczna celka zbudowana z podcelek (subcells)
        mają tą samą nośną i bandwich 
        kazda supecelka ma swój cellID

        SFN - single frequnecy network 
            sieć, gdzie jest wiele nadajnikó subcels

    MIMO: multiple input multiple output
        wiele anten nadawczych i odbiorczych
        aby zwiekszych przpeustowość jakośc i odpornośc sygnału
        
        zamiast nadawać jedną fale radiowoą rodziela dane na wiele strumieni
        8x2
        [nadawcze] x [odbiorcze]
        8 anten nadawczych, 2 odbiorcze
        praktyce oznacza to, 
            że stacja bazowa może jednocześnie 
                wysyła 8 strumieni do UE 
                i jednoczesnie odbiera przez 4 
        
    FDD - frequency division duplex
        DL i UL używają różnych czestotliwośći
        pasmo - dwa kanały jeden dl | jeden ul
        brak synchrocnizacji z neighbour cell
        w enb duplexMode = 

    TDD - time division duplex
        dl i ul dziela czas na tym samym paśmie
        pasmo jeden kanał dla dl i ul naprzemiennie
        potrzebuje synchronizacji (np GPS)
    
    pgw_lmts_param bearer_activation_by_trf
        okresla czy połączenie ma być aktywowane 
        przez pakiety danych przychdzace na określony port
    aktywacja bearera pojawia sie gdy zacznie sie trafik na danym porcie
    NW-init inicjalizacja połączenia bearerra pochodzi od sieci a nie od UE


2_7:
    dla TDD - Time Division Duplex
        - jedno pasmo, uplink i downlink, w różnych odstępach czasowych
    2 - frame config (numer od 0 do 6)
        ile subframów (slotów czasu) przypada na downlink, uplink i specjalny subframe
        np układ: DL-DL-DL-S-UL-UL-UL-DL-DL-S

    7 - special subframe config (numer od 0 do 9) 
        określa jak wygląda ten subframe - przejscie z DL na UL
        Dzieli sie go na:
            DwPTS (Downlink Pilot Time Slot) -- początek przesyłu
            GP (Guard Period - bufor, żeby się nie zakłócały) 
            UpPTS (Uplink Pilot Time Slot) - końcowy uplink, krótki
            np 9 3 1 - dużo downlink, buffor - 1 uplink

    Ustawienie na eNB: tddFrameConf

Liczenie pakietów:
    packetSize = 1300 bajtów - rozmiar pakietu
    packetRate = 12600 pakietów na sekundę
    Czas transmisji = 10 minut = 600 sekund

    Liczenie dla Mbps- megabity na sekunde
    1bajt = 8 bitów
    1 megabit -= 1000000 bitów 


    2 UEki = 2 * 12600 (pakietów) = 25200 pakietow na sekunde

    Ile bajtów na sekunde -  25200 pak/s * 1300 bajtów (rozmiar)= 32 760 000 bajtów /s 
    32 760 000 bajtów/s  * 8 = 262 080 000 bitów/s
    x : 1 000 000 = 262.08 Mbps
    