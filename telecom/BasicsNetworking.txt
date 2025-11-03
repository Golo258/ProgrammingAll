
- **Model OSI i TCP/IP**
  - 7-warstwowy model OSI i 4-warstwowy model TCP/IP.
  - Protokoły na poszczególnych warstwach (np. Ethernet, IP, TCP, UDP, HTTP).
  	
Model OSI (7-warstwowy)
	Teoretyczny model, dzieli proces komunikacji sieciowej na 7 warstw
	Warstwy komunikują się między sobą. Pomaga zrozumieć i zarządzać komunikacją modułowo

	Zadania | Przykłądy | Funkcja
	1. Aplikacji - Application layer
		Task: Zapewnia interface miedzy aplikacjami usera a siecią. 
			Właściwa komunikacja usera z siecia

		Ex: HTTP(browsers), FTP(file transfer), SMTP(mail)
		Fun: Zapewnia usługi sieciowe bezposrednio do aplikacji usera

	2. Prezentacja - Presentation layer
		Task: Odpowiada za przekształcanie danych do formatu zrozumiałego dla aplikacji
			Kompresja, Szyfrowanie, Deszyfrowanie

		Ex: TLS/SSL(szyfrowanie) JPEG, PNG(file formats)
		Fun: Konwersja i bezpieczeństwo danych

	3. Sesji - Session Layer
		Task: Zarządzanie sesjami miedzy aplikacjami na 2 urządzeniach
			Umożliwia nawiązywanie, utrzymywanie, kończenie sesji

		EX: RLC, PPTP
		Fun: Synchronizacja i zarządzanie dialogiem miedzy aplikacjami

	4. Transportowa - Transport Layer
		Task: Niezawodna transmisja danych miedzy urządzeniami 
			Dzieli na segmenty i zapewnia uporządkowane dostarczenie, kontrolę błędów

		EX: TCP, UDP
		FUn: Niezawodne przesyłanie danych (TCP), szybki ale bez gwarancji dostarczenia (UDP)

	5. Sieciowa - Network Layer
		Task: Zarzadzanie ruchem sieciowym, adresowanie i routing pakietów (dostarczenie do odbiorcy)
	
		Ex: IP(Internet Protocol), ICMP(ping)
		Fun: Trasowanie, Routing pakietów danych przez różne sieci

	6. Łącza danych - Data Link Layer
		Task: Transmisja danych miedzy bezpośrednio połączonymi urzadzeniami
			Dodaje nagłówki - adres MAC, pomagającej w lokalnej komunikacji

		Ex: Ethernet, Wi-Fi
		Fun: Bezbłedna transmisja danych miedzy urzadzeniami na poziomie fizycznym

	7. Fizyczna - Physical Layer
		Task: Fizyczne połączenie miedzy urządzeniami
			Transmisja sygnałów elektr, optycznych, radiowych

		Ex: Przewody (Ethernet), światłowód, radiowe (Wi-Fi), karty sieciowe
		Fun: Konwersja danych na sygnały, przesyłanie i odbiór 

#---------------------------------
Model TCP/IP (4-warstwowy)
	Model TCP/IP jest bardziej praktycznym modelem i jest standardem używanym w internecie. Ma mniej warstw niż OSI, ale pełni podobną funkcję. Skupia się na protokołach używanych w komunikacji internetowej.

	1. Application Layer:
		Bezpośrednia interakcja aplikacji z usere
		Dostarcza aplikacjom narzedzia do korzystania z sieci(przegladraka korzysta z HTTP)
		Protokoły (HTTP, FTP, DNS, SMTP, POP3, IMAP)
			HTTP/HTTPS (HyperText Transfer Protocol):
				przesyłanie stron internetowych
				komunikacja klient-serwer 
				
			FTP (File Transfer Protocol:
				przesyłanie plików miedzy serwerami, a komputerami

			DNS (Domain Name System):	
				Konwertuje adresy URL (google.com) na IP. DNS-- przechowuje te domeny

			SMTP (Simple Mail Transfer Protocol), IMAP, POP3
				Przesyłanie i odbieranie emaili

		Korzystając z aplikacji, dane są przetwarzane przez protokoły i przygotowywane do transmisji
		Np: Przegladarka poprzez wpisany URL wysyła requesta do serwera WWW i on zwraca nam strone

	  Status Codes:
      	1xx - informational 
      		100 continue - client can continue forwarding the data
      		101 - switching protocols - serwer agrees to change used protocol

    		2xx - sucessful
    			200 - OK - request ends successfully
    			201 - Created - request completed successfully, new element created
    			202 - Acceped - request accepted but not performed yet
    			204 - No content - request ends successfully, but there is not content to return

			  3xx - Redirection
			  	301 - Moved permantently - the resource has been moved to another URL
			  	302 - Found (303/307) - Temporary redirection. Resource find itself on different URL, but can return

			  4xx - Cient Error:
			  	400 - Bad request - request with wrong syntax, wrong data
			  	401 - Unauthorized - the access is not granted
			  	403 - Forbidden - Client authorized but dont have access to resource
			  	404 - Not Found - Server can't find wanted resource
			  	405 - Method Not Allowed - request method not allowed for the resource
			  
			  5xx - Server Error:
			  	500 - Internal Server Error - basic error, used with unexpected error
			  	501 - Not implemented - method not found 
			  	503 - Service Unavailable - Server is temporary unavailable 

	2. Transport Layer:
		Komunikacja miedzy komputerami, zapewnia przesyłanie danych, oragnizuje połączenia
		Zarzadzanie połaczeniami (TCP - niezawodne, UDP - szybkie)
		Protokoły: TCP,UDP
			TCP - (Transmission Control Protocol)
				Niezawodny protokół, gwarantujący dostarczenie danych.
				Działa na zasadzie połączeń, najpierw nawiązujemy połaczenie miedzy urzadzeniami(hansdshake)
				Potem dane są przesyłane, Kontrola błędów i retransmisja uraconych pakietów

			UDP - (User Datagram Protocol)
				Szybki, mniej niezawodny. Liczy sie predkość, a nie każde dostarczone dane
					(Transmisja wideo, VoIP, gry online).
				Brak rentransmiji ani kontroli błędów.

		Dane z aplikacji, są segmentowane w miejsze porcje i wysłane. 
		TCP upewnia sie, że wszystkie dotrą , UDP wysyła nie martwiąc sie czy wszystkie dotrą.

	3. Internet Layer:
		Trasowanie (routing) danych miedzy różnymi sieciami
		Dzieli dane na pakiety które muszą znaleść swoją droge do miejsca docelowego
			 ustala adresacje, trasy i wysyła dane przez sieć
		Protokoły: IP, ICMPO, ARP

			IP (Internet Protocol):
				Każdy komputer ma unikalny IP ( v4 np: 192.168.1.1) (v6: 2001:.....)
				Dzieli dane na pakiety i zarządza ich przesyłaniem miedzy sieciami
					bez gwarancji dostarczenia

			ICMP (Internet Control Message Protocol):
				Wysyłanie komunikatów diagnostycznych i kontrolnych w sieci
					np: komunikaty o błędach 
					ping używa ICMP

			ARP (Adress Resolution Protocol)
				Tłumaczy adresy IP na adresy MAC (fizyczne adresy urzadzen w LAN)

			Dane są opakowywane w pakiety i wyposażone w adres IP nadawcy i odbiorcy
			Routery w sieci analizują te adresy aby przekazać dane do odpowiedniej sieci docelowej


	4. Acess to Network (Link Layer + Phiscical):
		Połączenie urządzeń w tej samej sieci lokalnej (Ethernet, Wi-Fi)
		Komunikacja na poziomie sprzetu sieciowego, adresowanie fizyczne (MAC)
			przesyłanie ramek danych w obrębie sieci lokalnej

		Protokoły: Ethernet , Wi-Fi, PPP
			Ethernet
				Komunikacja w sieci przewodowych (LAN)
				Używa adresów MAC do identyfikowania urządzeń w sieci

			Wi-Fi:
				Protokół bezprzewodowy, podobnie do Ethernet tylko bezprzewodowo

			PPP(Point-to-POint Protocol)
				Bezpośrednie połączenia  (internet z modemem)

		Dane są przesyłane fizycznie prze miedzy urządzeniami w sieci lokalnej
		Pakiety przekształcane w ramki, które zawierają adres MAC, i inne informacje


Przykłady protokołów w modelu OSI i TCP/IP
	Warstwa fizyczna (OSI): Ethernet, Wi-Fi (sygnały, nośniki fizyczne).
	
	Warstwa łącza danych (OSI): Ethernet, Wi-Fi (adres MAC).
	
	Warstwa sieciowa (OSI, TCP/IP): IP (adresacja, routing).
	
	Warstwa transportowa (OSI, TCP/IP): TCP, UDP (kontrola przepływu, niezawodność).
	
	Warstwa aplikacji (OSI, TCP/IP): HTTP, FTP, SMTP, DNS (usługi dla aplikacji).


Cały proces przykład:
    Wysyłanie requestu do przeglądarki: https://domena.com/endpoint

    1. Warstwa Aplikacji (HTTP/DNS):
        User wpisuje w przeglądarkę www.example.com
        - HTTP generuje HTTP request:
            request zawiera: metodę (GET), adres URL, nagłówki (dodatkowe informacje o połączeniu), body (jeśli POST)
            oraz Host docelowy (domena.com)
                Przykład:
                    GET /index.html HTTP/1.1
                    Host:  www.example.com
                    User-Agent: Mozilla/5.0

        - DNS:
            Jeśli przeglądarka nie zna adresu IP serwera, DNS zamienia nazwę domeny na odpowiedni adres IP.
            Zapisuje ten adres w pamięci podręcznej przeglądarki i/lub systemu.
      

    2. Warstwa Transportowa (TCP/UDP):
        Otrzymujemy dane (HTTP request) od warstwy aplikacji, wybieramy odpowiedni protokół transportowy:
            HTTP wymaga niezawodnej komunikacji, więc używamy TCP.
                TCP:
                    - Dzieli dane na mniejsze części, **segmenty**, i dodaje do nich nagłówki TCP:
                        - Numer sekwencyjny (aby potem złożyć segmenty do całości).
                        - Suma kontrolna (checksum) do sprawdzenia poprawności danych przez serwer.
                        - Port źródłowy: Numer portu nadawcy.
												- Port docelowy: Numer portu odbiorcy.
                    - TCP nawiązuje połączenie z serwerem, znając jego IP (pobrane z cache przez DNS):
                        - Przeprowadza **3-way handshake**:
                            SYN: Klient wysyła prośbę o otwarcie połączenia.
                            SYN-ACK: Serwer odpowiada, zgadzając się na połączenie.
                            ACK: Klient potwierdza nawiązanie połączenia.
                        - Każda z tych wiadomości (SYN, SYN-ACK, ACK) przechodzi przez wszystkie kolejne warstwy do serwera i z powrotem, przy okazji dostarczając umówione wartości numerów sekwencyjnch.
                    - Po nawiązaniu połączenia TCP, każdy segment przechodzi przez kolejne warstwy, a serwer potwierdza ich odbiór poprzez **ACK**:
                        - Jeżeli segment zostanie odebrany bez błędów (zgodnie z sumą kontrolną), serwer wysyła ACK i prosi o kolejny segment.
                        - Jeżeli segment zostanie uszkodzony, serwer nie wysyła ACK, co powoduje retransmisję (ponowne wysłanie segmentu).
                        - Dzięki numerom sekwencyjnym, serwer jest w stanie złożyć segmenty we właściwej kolejności.

    3. Warstwa Internetowa (IP):
        Segmenty są przesyłane do warstwy internetowej, gdzie są zamieniane na **pakiety**.
            Pakiety zawierają:
                - IP nadawcy (komputera użytkownika).
                - IP odbiorcy (serwera docelowego, pobranego z DNS/cache).
        
        **Routing**: 
            Protokół IP analizuje, jak dotrzeć do serwera docelowego. 
            - Używa do tego tablic routingu oraz adresów IP, próbując znaleźć najkrótszą i najefektywniejszą drogę, jaką pakiety mają zostać przesłane.
            - Pakiety są przesyłane z routera na router (każdy router analizuje IP docelowe) aż dotrą do sieci docelowej, czyli sieci serwera.

    4. Warstwa Dostępu do Sieci:
        Pakiety docierają do lokalnego routera serwera, gdzie przechodzą do warstwy dostępu do sieci.
        - Pakiety są enkapsulowane w **ramki** (ramki zawierają dane pakietu IP) oraz:
            - Adres MAC nadawcy (routera lokalnego, przypisany do karty sieciowej routera).
            - Adres MAC odbiorcy (serwera).
            	Aby go otrzymać używamy mechanizmu ARP  (Address Resolution Protocol)
            		ARP działa na poziome sieci LAN, służy do mapowania adresów IP na adresy MAC
            		Kroki działania:
            			Nadawca wysyla brodcast ARP request ("DAj mi adres MAC urzadzenia o adresie  IP ....")
            				Brodcast - pakiet jest wysyłany do wszystkich urzadzeń w sieci LAN
          				Odbiorca odpowiada ARP reply:
          					Urzadzenie z tym IP odpowiada wysyłając swoj adres MAC, bezpośrednio od nadawcy requesta
        					Nadawca odbiera odpowiedz, zapisuje informacje w tablicy ARP (ARP cashe)

        				Jeśli jest serwer jest w innej sieci:
        					To ARP request jest wysyłany do routera i potem sie dzieje 
        
        - Ramki są konwertowane na bity i przesyłane jako sygnał elektryczny lub radiowy:
            - Przez media transmisyjne (kabel, fale radiowe) i przesyłane przez sieć.
            - Wysyłane do karty sieciowej serwera docelowego.
        
        - Serwer odbiera bity, dekapsuluje je do ramek, następnie z ramek do pakietów i segmentów.
            - TCP odbudowuje dane z segmentów, sprawdzając ich poprawność na podstawie sumy kontrolnej.
            - Serwer składa segmenty we właściwej kolejności (zgodnie z numerami sekwencyjnymi).
        
        - Po złożeniu segmentów, mamy pełen HTTP request, który serwer interpretuje i odpowiada np. kodem HTML strony.

#--------------------------------
Trasnmisja UDP:
	Protokół bezpołączeniowy, bez mechanizmów retransmisji, mniejszy narzut niż TCP.
	Stosowany w aplikacjach, gdzie liczy się szybkość, a nie niezawodność, np. streaming wideo, VoIP, gier sieciowych, 

	1. Dane z warstwy aplikacji:
		Podobnie jak w TCP, dane z warstwy aplikacji (np. zapytanie DNS, transmisja wideo itp.) są przekazywane do warstwy transportowej.

	2. Datagram UDP:
		W warstwie transportowej dane są umieszczane w datagramie UDP.
		UDP nie dzieli danych na segmenty tak jak TCP, ponieważ UDP jest protokołem bezpołączeniowym i nie ma mechanizmu kontroli sekwencji czy retransmisji. Całe dane są zamknięte w jednym datagramie.
		
		Nagłówek UDP jest bardzo prosty i zawiera tylko cztery główne pola:
			Port źródłowy: Numer portu nadawcy.
			Port docelowy: Numer portu odbiorcy.
			Długość: Określa długość całego datagramu, włącznie z nagłówkiem i danymi.
			Suma kontrolna: Używana do weryfikacji poprawności danych (ale w UDP nie jest wymagana – w przypadku błędu pakiet może zostać odrzucony bez powiadomienia nadawcy).

	3. Przekazanie do warstwy internetowej:
			Datagram UDP jest przekazywany do warstwy internetowej, gdzie zostaje opakowany w pakiet IP, a następnie przesyłany przez sieć.

	4. Brak retransmisji i kontroli sekwencji:
		W przeciwieństwie do TCP, UDP nie zapewnia niezawodności. Oznacza to, że:
		Datagramy nie mają numerów sekwencyjnych, więc odbiorca nie ma gwarancji, że dotrą w tej samej kolejności, w jakiej zostały wysłane.
		Brak retransmisji: Jeśli datagram zostanie utracony w sieci, nie ma mechanizmu, który automatycznie wymusi jego ponowne wysłanie.
		Brak potwierdzeń (ACK): Serwer nie wysyła potwierdzenia otrzymania datagramu.

	5. Zalety UDP:
		UDP jest szybszy niż TCP, ponieważ nie ma narzutu związanego z zestawianiem połączenia, retransmisją i kontrolą sekwencji.
		Idealny do zastosowań, w których liczy się niskie opóźnienie, a utrata kilku pakietów danych nie wpływa znacząco na jakość usługi, jak w przypadku transmisji strumieniowych (np. wideo, VoIP) lub zapytań DNS

	6. Struktura datagramu:
		+---------------------+---------------------+
		| Port źródłowy        | Port docelowy       |
		+---------------------+---------------------+
		| Długość             | Suma kontrolna       |
		+---------------------+---------------------+
		|       Dane aplikacyjne (payload)           |
		+--------------------------------------------+

DNS:
	DNS (Domain Name System) działa jako "książka telefoniczna" internetu, zamieniając nazwę domeny (np. www.example.com) na adres IP (np. 192.168.1.1).
	
	1. Rodzaje rekordów DNS:
		A (Address): 
			Mapuje nazwę domeny do jej adresu IPv4.
		AAAA:
			 Mapuje nazwę domeny do adresu IPv6.
		CNAME (Canonical Name):
			 Alias dla innej nazwy domeny. Używany, aby jedna domena mogła wskazywać na inną domenę.
		MX (Mail Exchange):
			 Rekord używany do określenia serwera pocztowego, na który mają być dostarczane e-maile.
		NS (Name Server):
			 Określa serwery nazw dla danej domeny.
		PTR (Pointer Record):
			 Używany do mapowania adresu IP na nazwę domeny (odwrotny rekord DNS, często używany w kontekście sprawdzania wiarygodności serwerów pocztowych).
		Kiedy wpisujesz adres strony WWW, DNS używa rekordów A lub AAAA, aby znaleźć odpowiedni adres IP serwera.

		Przeglądarka najpierw sprawdza lokalną pamięć podręczną DNS.
		Jeśli nie znajdzie odpowiedzi, kontaktuje się z serwerem DNS (zazwyczaj dostawcy internetu) i prosi o zamianę nazwy domeny na IP. Jeśli serwer DNS nie zna odpowiedzi, kieruje zapytanie do wyższych serwerów DNS.


	2. Zapytania DNS:
		Zapytania rekurencyjne: Klient (np. przeglądarka) oczekuje, że serwer DNS dostarczy ostateczny wynik. Serwer DNS wykonuje wszystkie potrzebne zapytania do innych serwerów, aby znaleźć odpowiedni rekord.
	
		Zapytania iteracyjne: Klient może otrzymać odpowiedź, która nie jest ostateczna, ale wskazuje, gdzie może znaleźć odpowiedź (np. adres innego serwera DNS).

	3. Cashe DNS:
		Serwery DNS i klienci przechowują wyniki zapytań w pamięci podręcznej (cache), co przyspiesza kolejne zapytania do tej samej domeny, ponieważ nie trzeba ponownie wykonywać zapytania do serwera DNS.

	4. Hierarchia serwerów:
		System DNS jest zorganizowany hierarchicznie, gdzie:
			Root servers: Na szczycie hierarchii, odpowiedzialne za najwyższy poziom domen (np. .com, .org, .net).
			TLD servers: Odpowiadają za domeny najwyższego poziomu (Top-Level Domains), jak .com czy .edu.
			Authoritative DNS servers: Odpowiadają za konkretne domeny i ich rekordy.

	5. Czas życia (TTL):
		Każdy rekord DNS ma ustawiony czas życia (Time To Live), który określa, jak długo dany rekord może być przechowywany w cache. Po upływie tego czasu rekord musi być odświeżony.	

### Przykładowe pytanie i odpowiedź:
Jak działa proces zapytania DNS od momentu, gdy użytkownik wpisuje nazwę domeny do przeglądarki, aż do otrzymania adresu IP serwera?

#---------------------------------

**Proces zapytania DNS:**
1. **Wpisanie domeny w przeglądarkę**: Gdy użytkownik wpisuje adres URL (np. www.example.com) w przeglądarkę, przeglądarka najpierw sprawdza swoją lokalną pamięć podręczną (cache), aby zobaczyć, czy ma już zapisany adres IP dla tej domeny.

2. **Sprawdzenie lokalnej pamięci podręcznej**:
   - **Jeśli adres IP jest w cache**:
     - Przeglądarka korzysta z zapisanej wartości i kontynuuje proces ładowania strony.
   - **Jeśli adres IP nie jest w cache**:
     - Przeglądarka wysyła zapytanie DNS do skonfigurowanego serwera DNS (zwykle jest to serwer DNS dostarczony przez dostawcę internetu).

3. **Rekurencyjne zapytanie DNS**:
   - Serwer DNS sprawdza swoją własną pamięć podręczną. Jeśli nie ma odpowiedzi, rozpoczyna rekurencyjne zapytanie do innych serwerów DNS.
   - Serwer DNS może najpierw skontaktować się z serwerem głównym (root DNS server), który kieruje go do odpowiednich serwerów TLD (Top-Level Domain) dla danej domeny (np. .com, .org).

4. **Wyszukiwanie w serwerach TLD**:
   - Serwer TLD przekazuje zapytanie do autorytatywnego serwera DNS dla danej domeny, który zawiera ostateczne rekordy DNS (np. rekordy A dla adresów IPv4).

5. **Otrzymanie odpowiedzi**:
   - Autorytatywny serwer DNS zwraca adres IP odpowiadający domenie.
   - Serwer DNS zapisuje ten adres IP w swojej pamięci podręcznej, aby przyspieszyć przyszłe zapytania.

6. **Zwrócenie adresu IP do przeglądarki**:
   - Adres IP zostaje przekazany z powrotem do przeglądarki, która może teraz nawiązać połączenie z odpowiednim serwerem, aby pobrać zasoby strony.

### Różnice między zapytaniami rekurencyjnymi a iteracyjnymi:

- **Rekurencyjne zapytanie DNS**:
  - Klient oczekuje, że serwer DNS samodzielnie znajdzie odpowiedź.
  - Serwer DNS staje się odpowiedzialny za całą procedurę zapytań do innych serwerów DNS.
  - Jeśli serwer DNS nie ma odpowiedzi, samodzielnie wykonuje wszystkie niezbędne zapytania, aż do uzyskania odpowiedzi.

- **Iteracyjne zapytanie DNS**:
  - Klient oczekuje odpowiedzi bezpośrednio od serwera DNS, ale serwer może zwrócić adres innego serwera DNS, jeśli nie zna odpowiedzi.
  - Klient przejmuje odpowiedzialność za kierowanie zapytań do kolejnych serwerów DNS, co może prowadzić do większej liczby zapytań w porównaniu do zapytania rekurencyjnego.
  - Serwer DNS nie musi przeprowadzać wszystkich zapytań – może tylko wskazać, gdzie można uzyskać odpowiedź.

Ilość serwerów TLD i autorytatywnych
	1. Wielu serwerów TLD:
		Istnieje wiele serwerów TLD dla różnych końcówek domenowych (np. .com, .org, .net, .pl itp.). Każda z tych końcówek ma swoje własne serwery TLD, które są odpowiedzialne za przechowywanie informacji o autorytatywnych serwerach DNS dla wszystkich domen, które kończą się na daną końcówkę.	

	2. Kierowanie zapytań:
		Gdy zapytanie DNS dociera do lokalnego serwera DNS i ten serwer TLD nie ma informacji o żądanej domenie, zwraca adres serwera TLD odpowiedzialnego za daną końcówkę. Na przykład, jeśli pytanie dotyczy www.example.com, lokalny serwer DNS zwraca adres jednego z serwerów TLD dla .com.

	3. Serwery autorytatywne:
		Istnieje wiele autorytatywnych serwerów DNS dla każdej zarejestrowanej domeny. Gdy serwer TLD zwraca adres autorytatywnego serwera DNS dla example.com, ten serwer przechowuje informacje o wszystkich subdomenach tej domeny (w tym www.example.com).
		Serwery te są zarządzane przez rejestratorów domen, którzy mają kontrolę nad tymi domenami.

#---------------------------------

3. ICMP:
ICMP:
    ICMP (Internet Control Message Protocol) to protokół używany głównie do komunikacji diagnostycznej i kontroli w sieci.
        Przykłady:
            ping:
                Używa ICMP do sprawdzenia, czy dany host jest osiągalny, wysyłając żądanie "echo" i czekając na odpowiedź.
            traceroute:
                Używa ICMP, aby wyświetlić trasę, jaką pakiety muszą przejść, aby dotrzeć do określonego hosta. Przydatne do diagnostyki opóźnień w sieci.
        ICMP nie jest wykorzystywany do przesyłania danych aplikacyjnych jak TCP czy UDP, ale jest istotny w kontekście monitorowania sieci.
        ICMP może również przesyłać komunikaty o błędach (np. Destination Unreachable, Time Exceeded), co pomaga w identyfikacji problemów z trasowaniem pakietów.
        Nieprzesyłanie danych aplikacyjnych: 
        	Podkreślenie, że ICMP nie służy do przesyłania danych użytkowych, a jedynie do zarządzania komunikacją w sieci, jest istotne.

#-------------------------------------
IP i sieci:
	1. Adresacja IPv4 i IPv6:
		IPv4:
			Format:
				 Adres IPv4 składa się z 32 bitów, zazwyczaj przedstawianych w formacie dziesiętnym jako cztery liczby oddzielone kropkami (np. 192.168.1.1).
			Maski podsieci:
				 Maska podsieci jest używana do podziału adresu IP na część sieciową i hostową. Przykładowo, w masce 255.255.255.0, pierwsze trzy oktety identyfikują sieć, a ostatni oktet identyfikuje urządzenia (hosty) w tej sieci.
			Ograniczenia:
				 Adres IPv4 ma ograniczoną liczbę dostępnych adresów (około 4 miliardów), co stało się problematyczne w miarę rozwoju Internetu.
		
		Adresacja IPv6:
			Format:
				 Adres IPv6 składa się z 128 bitów, zapisywanych jako osiem grup czterech cyfr szesnastkowych oddzielonych dwukropkami (np. 2001:0db8:85a3:0000:0000:8a2e:0370:7334).
			Zalety:
				 IPv6 oferuje znacznie większą przestrzeń adresową, eliminując problemy z brakiem adresów. Umożliwia również lepsze zarządzanie adresacją, wsparcie dla automatycznej konfiguracji i wbudowane funkcje bezpieczeństwa.
			Maski podsieci:
				 W IPv6 używamy prefiksów, np. /64, co oznacza, że pierwsze 64 bity adresu są używane do identyfikacji sieci.

	2. Adresy IP: Publiczne i Prywatne:
		Adresy Publiczne:
			Adresy publiczne to adresy IP, które są widoczne w Internecie. Są unikalne w skali globalnej i przypisywane 
			przez organizacje, które zarządzają adresacją IP (np. IANA, regionalne rejestry).
			
			Przykład:
				 Adresy takie jak 203.0.113.1 lub 8.8.8.8 to adresy publiczne.
			Użycie:
				 Służą do identyfikacji urządzeń w Internecie. Każde urządzenie z publicznym adresem IP może komunikować się z innymi urządzeniami w Internecie.
			Ograniczenia:
				 Zasoby adresów IPv4 są ograniczone (około 4 miliardy), więc nie każde urządzenie może mieć unikalny publiczny adres IP

	 Adresy Prywatne:
			Adresy prywatne to adresy IP, które są używane w sieciach lokalnych i nie są routowane w Internecie. Są używane do komunikacji w obrębie lokalnej sieci, np. w domach lub firmach.
			
			Zakresy adresów prywatnych IPv4:
				10.0.0.0 do 10.255.255.255 (10.0.0.0/8)
				172.16.0.0 do 172.31.255.255 (172.16.0.0/12)
				192.168.0.0 do 192.168.255.255 (192.168.0.0/16)
			Przykład:
				 Adresy takie jak 192.168.1.1 lub 10.0.0.5 to adresy prywatne.
			Zastosowanie:
				 Umożliwiają urządzeniom w sieci lokalnej komunikację bez potrzeby przypisywania publicznych adresów IP.


		2.NAT: ( Network Address Translation):
			NAT to technika używana do tłumaczenia prywatnych adresów IP (w sieciach lokalnych) na publiczne adresy IP. Dzięki temu wiele urządzeń w sieci lokalnej może współdzielić jeden publiczny adres IP.

		Jak działa NAT:
			Przekazywanie pakietów:
				Gdy urządzenie w sieci lokalnej (np. komputer z adresem prywatnym 192.168.1.10) chce się połączyć z Internetem, wysyła pakiet do routera.
				Router NAT zamienia adres prywatny na swój publiczny adres IP (np. 203.0.113.1) i zapisuje tę informację w tablicy tłumaczeń.
			
			Odpowiedzi z Internetu:
				Kiedy serwer w Internecie odpowiada, pakiet wraca do routera NAT.
				Router używa swojej tablicy tłumaczeń, aby wiedzieć, do którego prywatnego adresu należy przesłać pakiet.
				Router zmienia adres docelowy pakietu z publicznego na odpowiedni prywatny adres (np. 192.168.1.10).
			Korzystanie z portów:
				NAT często używa również portów, aby móc śledzić wiele sesji. Na przykład, jeśli dwa urządzenia w sieci lokalnej łączą się z tym samym publicznym adresem IP, NAT przydziela różne porty do tych sesji, co pozwala na rozróżnienie ich.

			Dlaczego usuful:
				Oszczędność adresów IP:
					NAT pozwala na korzystanie z prywatnych adresów IP w sieciach lokalnych, co oznacza, że wiele urządzeń może dzielić jeden publiczny adres IP. Dzięki temu organizacje nie muszą kupować wielu publicznych adresów, co zmniejsza koszty.
			
				Zwiększenie bezpieczeństwa:
					NAT ukrywa wewnętrzną strukturę sieci przed dostępem z Internetu. Urządzenia w sieci lokalnej nie mają bezpośrednich publicznych adresów IP, co zmniejsza ryzyko ataków z zewnątrz.

			Zarządzanie siecią:
				NAT ułatwia zarządzanie siecią lokalną, ponieważ administratorzy mogą łatwo zmieniać urządzenia wewnętrzne, nie zmieniając publicznego adresu IP.


	Przykład w praktyce
		Wyobraź sobie, że masz domową sieć z routerem. Każde urządzenie w tej sieci (np. laptop, telefon, drukarka) ma przypisany prywatny adres IP w zakresie 192.168.1.0/24. Kiedy laptop chce otworzyć stronę internetową:

		Wysyła zapytanie do routera NAT, który ma publiczny adres IP 203.0.113.1.
		Router NAT zamienia prywatny adres laptopa na swój publiczny adres i wysyła zapytanie do Internetu.
		Gdy serwer WWW odpowiada, router NAT tłumaczy adres z powrotem na prywatny adres laptopa i przekazuje odpowiedź.

RIP:	
	Protokół RIP (Routing Information Protocol)
	RIP to starszy protokół routingu oparty na algorytmie wektora odległości (Distance Vector), stosowany w małych i średnich sieciach. RIP jest prosty w konfiguracji i wdrożeniu, ale ma pewne ograniczenia, które sprawiają, że nie jest stosowany w bardziej złożonych sieciach.

1. Główne cechy RIP:
	Typ: Protokół wektora odległości.
	Metryka: Liczba przeskoków (hop count), maksymalnie 15. Każda trasa, której liczba przeskoków wynosi 16, jest uznawana za nieosiągalną.
	Aktualizacje: RIP wysyła aktualizacje całej tablicy routingu co 30 sekund, co zwiększa obciążenie sieci.
	Konwergencja: Stosunkowo wolna w porównaniu do nowoczesnych protokołów routingu.
	Limit skali: Ze względu na ograniczenie liczby przeskoków (max 15), RIP działa efektywnie tylko w małych sieciach.
	Wersje:
	RIP v1: Klasyczna wersja, która nie wspiera VLSM (Variable Length Subnet Masking) ani CIDR (Classless Inter-Domain Routing).
	RIP v2: Wspiera VLSM, CIDR oraz autoryzację routingu.
2. Działanie RIP:
	Metoda działania: Każdy router w sieci RIP przesyła pełną tablicę routingu do swoich sąsiadów co 30 sekund. Routery aktualizują swoje tablice na podstawie informacji otrzymanych od sąsiadów.
Algorytm: Wykorzystuje Bellmana-Forda do wyboru najlepszej trasy w oparciu o liczbę przeskoków.
Rozgłaszanie tras: RIP używa adresu multicast 224.0.0.9 (w RIP v2) do wysyłania aktualizacji routingu.
3. Ograniczenia RIP:
	Liczba przeskoków: Maksymalna liczba przeskoków wynosi 15, co ogranicza skalowalność.
Powolna konwergencja: W przypadku zmian w topologii sieci, RIP potrzebuje więcej czasu, aby zaktualizować trasy w porównaniu do nowoczesnych protokołów.
Obciążenie sieci: Regularne wysyłanie pełnych tablic routingu co 30 sekund powoduje obciążenie sieci, nawet gdy nie ma zmian w topologii.
4. Zalety RIP:
	Prostota: Łatwy do skonfigurowania i wdrożenia.
Kompatybilność: Działa na niemal każdym routerze i w małych sieciach może być efektywny.
5. Przykład konfiguracji RIP w routerze Cisco:
bash
Skopiuj kod
router rip
 version 2
 network 192.168.1.0
 network 10.0.0.0


OSPF:
	OSPF to zaawansowany protokół routingu stanu łącza (Link State), który jest powszechnie stosowany w średnich i dużych sieciach. OSPF został zaprojektowany, aby rozwiązywać ograniczenia RIP, oferując szybkie czasy konwergencji, lepszą skalowalność i większą elastyczność w zarządzaniu siecią.

1. Główne cechy OSPF:
	Typ: Protokół stanu łącza (Link State).
	Metryka: Koszt (cost), który jest oparty na przepustowości łącza. Im wyższa przepustowość, tym niższy koszt.
	Konwergencja: Bardzo szybka, ponieważ routery OSPF utrzymują pełną mapę topologii sieci, dzięki czemu mogą szybko wyznaczać nowe trasy.
	Struktura hierarchiczna: OSPF dzieli sieć na obszary (areas), co ułatwia zarządzanie dużymi sieciami. Obszar 0 jest obszarem rdzeniowym (backbone).
	Wersja: Najczęściej używaną wersją jest OSPFv2 dla IPv4 oraz OSPFv3 dla IPv6.
	Algorytm: OSPF używa algorytmu Dijkstra (SPF) do wyznaczania najkrótszej ścieżki.
2. Działanie OSPF:
	Link State Advertisement (LSA): Routery OSPF wymieniają się informacjami o stanie łączy za pomocą LSA. Każdy router wysyła informacje o swoich sąsiednich routerach do wszystkich routerów w danym obszarze.
	LSDB (Link State Database): Każdy router utrzymuje bazę danych o stanie łączy (Link State Database), która zawiera pełną mapę topologii sieci w danym obszarze.
	Obliczanie trasy: Na podstawie LSDB, każdy router uruchamia algorytm Dijkstra, aby obliczyć najkrótsze ścieżki do wszystkich celów.
3. Zalety OSPF:
	Szybka konwergencja: Zmiany w topologii są szybko propagowane, co pozwala na szybką rekonfigurację tras.
	Skalowalność: OSPF działa dobrze w dużych sieciach dzięki podziałowi na obszary i zaawansowanej strukturze hierarchicznej.
	Precyzyjna kontrola: Możliwość konfigurowania kosztów interfejsów, co pozwala na precyzyjne kontrolowanie tras.
4. Obszary w OSPF:
	Area 0 (Backbone Area): Główny obszar OSPF, który łączy wszystkie inne obszary. Każdy inny obszar musi być bezpośrednio lub pośrednio połączony z Area 0.
	Non-backbone Areas: Pozostałe obszary, które są podłączone do rdzenia (Area 0). Wśród nich mogą być:
	Stub Area: Obszar, który nie otrzymuje tras zewnętrznych spoza obszaru OSPF.
	Totally Stubby Area: Obszar, który nie otrzymuje tras zewnętrznych ani tras międzyobszarowych.
	NSSA (Not So Stubby Area): Obszar, który może importować trasy z zewnątrz, ale nadal zachowuje cechy obszaru stub.
5. Ograniczenia OSPF:
	Złożoność: W porównaniu do RIP, OSPF jest bardziej złożony i trudniejszy do skonfigurowania i zarządzania.
	Wydajność w małych sieciach: OSPF może być "przeinwestowaniem" dla bardzo małych sieci, gdzie prostsze protokoły mogą wystarczyć.