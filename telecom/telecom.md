#1. -------------------------
## 1. Stacje Bazowe (BTS) i RAN (Radio Access Network)

Stacje bazowe (BTS) są odpowiedzialne za bezpośrednią komunikację z telefonem komórkowym. W skrócie, BTS to „pośrednik” między urządzeniem użytkownika (telefonem) a siecią szkieletową (Core Network). 

### Główne zadania BTS:

- **Odbieranie i wysyłanie sygnałów radiowych** z telefonem użytkownika. Telefon komunikuje się bezpośrednio z najbliższą stacją bazową.
- **Monitorowanie siły sygnału użytkownika**. Kiedy sygnał staje się zbyt słaby, BTS inicjuje **handover** – proces przekazania połączenia do innej stacji bazowej z lepszym sygnałem.
- **Przesyłanie danych** z telefonu do rdzenia sieci (połączenia głosowe, wiadomości, dane internetowe).
- **Kontrolowanie zasobów radiowych**, przydzielanie częstotliwości i kanałów radiowych, potrzebnych do przesyłania danych między telefonem a siecią.

Stacje bazowe są częścią **RAN** (Radio Access Network) – sieci dostępowej, która obsługuje wszystkie urządzenia mobilne w zasięgu danej stacji.

---

## 2. MME (Mobility Management Entity)

MME to kluczowy element rdzenia sieci LTE, zarządzający mobilnością użytkowników oraz sesjami. 

### Główne zadania MME:

- **Rejestracja użytkownika**: Gdy telefon łączy się z siecią, MME sprawdza, czy użytkownik ma prawo do korzystania z usług. Komunikuje się w tym celu z **HSS** (Home Subscriber Server), który przechowuje dane abonenta (np. uprawnienia, abonament).
  
- **Zarządzanie mobilnością**: Kiedy użytkownik przemieszcza się, MME zarządza **handover** między stacjami bazowymi, zapewniając płynne przekazywanie połączeń.
  
- **Przydzielanie adresów IP**: MME przydziela adres IP użytkownikowi, gdy ten korzysta z danych pakietowych (internet). Komunikuje się w tym celu z bramkami SGW i PGW.

- **Zarządzanie sesjami**: MME monitoruje aktywne połączenia użytkownika i kontroluje przesył danych, zarówno głosowych, jak i internetowych.

---

## 3. Serving Gateway (SGW)

SGW (Serving Gateway) odpowiada za przesyłanie danych pakietowych w rdzeniu sieci. To „punkt przekaźnikowy”, który odbiera dane od stacji bazowych i przekazuje je dalej do bramki PGW.

### Główne zadania SGW:

- **Przekazywanie danych**: SGW przesyła dane między stacją bazową a PGW. Obsługuje zarówno transmisję danych od użytkownika (np. przeglądanie internetu), jak i do użytkownika (np. pobieranie plików).
  
- **Handover**: SGW obsługuje handover, utrzymując sesję użytkownika i przesyłając dane do nowej stacji bazowej, gdy użytkownik zmienia swoją lokalizację.

Oba:
Wykorzystują TCP i UDP do zapewnienia różnych usług przesyłania danych. TCP może być używane do aplikacji, które wymagają niezawodnego połączenia, natomiast UDP może być stosowane do strumieniowania mediów (np. VoIP).

---

## 4. Packet Data Network Gateway (PGW)

PGW (Packet Data Network Gateway) to bramka, która łączy sieć komórkową z zewnętrznymi sieciami, takimi jak internet.

### Główne zadania PGW:

- **Połączenie z internetem**: PGW przekazuje dane między siecią LTE a zewnętrznymi sieciami pakietowymi, takimi jak internet, prywatne sieci korporacyjne, czy serwisy OTT (np. streaming wideo).

- **Zarządzanie jakością usług (QoS)**: PGW kontroluje priorytety w przesyle danych, zapewniając lepszą jakość usług, np. VoIP (rozmowy przez internet) lub strumieniowanie wideo.

- **Zarządzanie adresem IP**: PGW przydziela adresy IP dla urządzeń mobilnych i zarządza routingiem danych do internetu.

---

## Podsumowanie:

- **Stacja bazowa (BTS)** i **RAN** odpowiadają za bezpośrednią komunikację z telefonem użytkownika i przesyłanie sygnałów radiowych.
- **MME** zarządza sesjami użytkowników, rejestracją w sieci i mobilnością (handover).
- **SGW** przesyła dane między stacjami bazowymi a **PGW**, a także obsługuje handover.
- **PGW** łączy sieć komórkową z internetem i innymi zewnętrznymi sieciami.

#2. -------------------------
# Proces Łączenia Użytkownika z Siecią Komórkową

## 1. Włączenie Urządzenia:
- Użytkownik włącza telefon komórkowy, który zaczyna skanować dostępne sieci komórkowe.

## 2. Skanowanie Sieci:
- Telefon wyszukuje sygnały od pobliskich stacji bazowych (BTS), które są częścią Radio Access Network (RAN).
- Po zidentyfikowaniu dostępnych sieci, telefon wyszukuje sieć operatora, z którym jest zarejestrowany.

## 3. Rejestracja w Sieci:
- Gdy telefon wybierze odpowiednią stację bazową, rozpoczyna proces rejestracji. Telefon wysyła do stacji bazowej sygnał rejestracyjny (np. żądanie dostępu).
- Stacja bazowa przesyła to żądanie do **Mobility Management Entity (MME)** w Evolved Packet Core (EPC).

## 4. Autoryzacja:
- MME sprawdza, czy użytkownik ma prawo dostępu do sieci (czy jest zarejestrowany, czy ma aktywny abonament).
- MME komunikuje się z **Home Subscriber Server (HSS)**, gdzie są przechowywane dane abonenta, aby potwierdzić autoryzację.

## 5. Utworzenie Sesji:
- Po pomyślnej autoryzacji MME tworzy sesję w **Serving Gateway (SGW)**. SGW odpowiedzialny jest za przekazywanie danych do użytkownika i między różnymi stacjami bazowymi.
- SGW przekazuje dane do **Packet Data Network Gateway (PGW)**, co umożliwia połączenie z Internetem lub innymi sieciami.

## 6. Nawiązanie Połączenia:
- Po nawiązaniu sesji MME wysyła potwierdzenie do stacji bazowej, która następnie informuje telefon o możliwości korzystania z sieci.
- Użytkownik jest teraz połączony i może przesyłać dane, dzwonić lub korzystać z innych usług.

---

# Dalsze Etapy Komunikacji

## 1. Przesyłanie Danych:
- Po nawiązaniu połączenia, dane (np. wiadomości, strumieniowanie wideo) są przesyłane w formie pakietów.
- Każdy pakiet zawiera informacje o porządku, dzięki czemu SGW i PGW mogą zidentyfikować, do którego użytkownika są kierowane.

## 2. Mobilność:
- Gdy użytkownik porusza się, jego telefon może łączyć się z innymi stacjami bazowymi. W tym celu:
  - Telefon monitoruje siłę sygnału z pobliskich BTS.
  - Gdy siła sygnału z nowej stacji bazowej jest wystarczająco silna, telefon wykonuje **handover** (przełączenie).
  - Nowa stacja bazowa informuje MME o przełączeniu, a MME zarządza transferem sesji, aby zapewnić ciągłość komunikacji.

## 3. Zakończenie Połączenia:
- Gdy użytkownik kończy korzystanie z usługi (np. kończy rozmowę lub przestaje korzystać z internetu), telefon wysyła sygnał zakończenia.
- MME aktualizuje status użytkownika i zwalnia zasoby sieciowe.

---

# Kluczowe Elementy do Zapamiętania
- **Stacja Bazowa (BTS)**: Umożliwia połączenie telefonu z siecią.
- **MME**: Zarządza sesjami użytkowników i ich mobilnością.
- **SGW i PGW**: Zarządzają transferem danych i połączeniem z Internetem.
- **Handover**: Proces przełączania między stacjami bazowymi, zapewniający ciągłość komunikacji podczas ruchu.

#3.-----------------------------------
# Proces Funkcjonowania Sieci Komórkowej po Nawiązaniu Połączenia

## 1. Stan Połączenia (Connected Mode)
- Gdy telefon jest już połączony z siecią, działa w trybie połączenia (**Connected Mode**). Oznacza to, że sesja użytkownika jest aktywna, a wszystkie potrzebne zasoby sieciowe są już przydzielone (np. kanały radiowe, adres IP).
- Telefon może teraz swobodnie przesyłać dane (np. przeglądać internet, wysyłać wiadomości, dzwonić) poprzez połączenie z **BTS** i rdzeniem sieci (**Core Network**). Proces wygląda następująco:
  1. Dane (np. wiadomości, pakiety internetowe, połączenia głosowe) są przesyłane między telefonem a stacją bazową (BTS).
  2. BTS przekazuje te dane do sieci radiowej (**RAN**), a stamtąd do **EPC** (rdzenia sieci).
  3. W rdzeniu EPC, dane są przetwarzane przez **SGW** (Serving Gateway), a następnie przekazywane do **PGW** (Packet Data Network Gateway), który obsługuje połączenie z internetem lub innymi sieciami.

## 2. Mobilność Użytkownika (Handover)
- Kiedy użytkownik porusza się (np. chodzi po domu, podróżuje samochodem), jego telefon musi dynamicznie przełączać się między stacjami bazowymi. Proces ten nazywa się **handover** (przekazanie połączenia) i jest kluczowy dla zapewnienia ciągłości połączeń i transmisji danych bez przerw.
  1. Telefon monitoruje siłę sygnału z najbliższej stacji bazowej. Gdy siła sygnału spada poniżej pewnego progu, telefon zaczyna szukać innych, silniejszych sygnałów.
  2. Handover następuje, gdy telefon przełączy się z jednej stacji bazowej do innej, bez przerywania trwającego połączenia (np. połączenia głosowego lub transmisji danych).
  3. Cały proces jest zarządzany przez **MME** i BTS. MME decyduje, do której stacji bazowej telefon powinien się przełączyć, a BTS zarządza alokacją zasobów radiowych.
- Dzięki handover, telefon może się przemieszczać między różnymi stacjami bazowymi bez zauważalnych przerw w działaniu aplikacji, rozmowach czy połączeniach internetowych.

## 3. Idle Mode (Tryb Czasowego Spoczynku)
- Gdy telefon nie jest aktywnie używany (np. nie przeglądasz internetu ani nie dzwonisz), ale pozostaje podłączony do sieci, przechodzi w **Idle Mode** (tryb uśpienia/spoczynku). W tym trybie:
  - Telefon ciągle monitoruje sygnały z sieci, ale nie przesyła aktywnie danych ani nie używa pełnych zasobów radiowych.
  - Telefon utrzymuje połączenie sygnalizacyjne z siecią, aby móc szybko aktywować połączenie, gdy użytkownik zacznie np. dzwonić lub przeglądać internet.
  - Jeśli telefon wykryje, że użytkownik zaczyna korzystać z aplikacji lub wykonywać połączenie, szybko przechodzi z Idle Mode do **Connected Mode**, aby nawiązać pełne połączenie z siecią.

## 4. Transmisja Danych i Głosowych
- Kiedy telefon jest już połączony, transmisja danych (internet) i połączenia głosowe przebiegają przez te same elementy sieci, ale są przetwarzane w różny sposób:
  1. **Dane internetowe** (np. przeglądanie stron) są przesyłane w pakietach IP, które są zarządzane przez **EPC** (SGW i PGW).
  2. **Połączenia głosowe** mogą być obsługiwane przez różne technologie w zależności od rodzaju sieci. W LTE, głos może być przesyłany za pomocą technologii **VoLTE** (Voice over LTE), gdzie dźwięk jest przesyłany w formie pakietów danych.

## 5. Wylogowanie i Zakończenie Sesji
- Kiedy użytkownik kończy korzystanie z sieci (np. rozłącza się, kończy korzystanie z internetu lub wyłącza telefon):
  1. Telefon wysyła sygnał zakończenia sesji do **MME**, który zwalnia zasoby radiowe i odłącza użytkownika od rdzenia sieci.
  2. Zasoby są zwalniane, aby mogły być użyte przez innych użytkowników.

---

# Podsumowanie
- Gdy użytkownik jest już połączony z siecią komórkową:
  - Telefon utrzymuje sesję z siecią i może przesyłać dane bez konieczności ponownej rejestracji.
  - **Handover** zapewnia ciągłość połączeń, gdy użytkownik się przemieszcza.
  - Telefon przechodzi w **Idle Mode**, gdy nie jest aktywnie używany, aby oszczędzać zasoby.
  - Po zakończeniu połączenia telefon wylogowuje się z sieci, zwalniając zasoby.
