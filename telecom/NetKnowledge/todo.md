
## Tydzień 1: **Podstawy programowania i narzędzi**
### Elixir
- [ ] Zapoznanie się z podstawami składni (moduły, funkcje, typy danych)
- [ ] Zrozumienie pattern matching w Elixir
- [ ] Procesy i współbieżność w Elixir
- [ ] Praktyczne ćwiczenia: napisz prosty program (np. kalkulator)

### Python
- [ ] Powtórka z podstaw: zmienne, funkcje, pętle, wyjątki
- [ ] Testowanie w Pythonie (`unittest`, `pytest`)
- [ ] Praktyczne ćwiczenie: napisz testy dla prostej funkcji

### Linux i Bash
- [ ] Nauka podstawowych komend terminala: `ls`, `cd`, `cp`, `mv`, `chmod`, `ps`, `kill`, `top`
- [ ] Tworzenie prostych skryptów bash: zmienne, pętle, warunki (`if`, `for`, `while`)
- [ ] Praktyczne ćwiczenie: napisz skrypt automatyzujący np. uruchamianie testów

---

## Tydzień 2: **Sieci i CI/CD**
### Sieci IP
- [ ] Zrozumienie podstawowych protokołów: TCP, UDP, IP, DNS
- [ ] Jak działa NAT, routing, podział na sieci, IP (IPv4 vs IPv6)
- [ ] Praktyczne ćwiczenie: opisz, jak działa proces komunikacji przez sieć IP (np. otwarcie strony WWW)

### Sieci mobilne (opcjonalnie)
- [ ] Zapoznanie się z podstawami LTE/5G
- [ ] Zrozumienie działania komórek, przepustowości i połączeń

### Jenkins (CI/CD)
- [ ] Zrozumienie pipeline'ów CI/CD
- [ ] Tworzenie prostych pipeline'ów w Jenkinsie (build, test, deploy)
- [ ] Praktyczne ćwiczenie: zaprojektuj przykładowy pipeline dla aplikacji

---

## Tydzień 3: **Procesy rozwoju oprogramowania i praca zespołowa**
### Agile/Scrum
- [ ] Podstawy Agile i Scrum (sprinty, retrospektywy, daily stand-up)
- [ ] Praktyczne ćwiczenie: opisz, jak wyglądał Twój udział w projektach Agile

### GIT
- [ ] Podstawowe komendy: `git clone`, `git pull`, `git commit`, `git push`, `git branch`, `git merge`, `git rebase`
- [ ] Praktyczne ćwiczenie: utwórz repozytorium, zrób branch, dokonaj zmian i wykonaj merge

### Komunikacja i praca zespołowa
- [ ] Przygotowanie przykładów pracy w zespole (rozwiązywanie konfliktów, dzielenie się zadaniami)
- [ ] Praktyczne ćwiczenie: opisz przykład, jak rozwiązałeś problem w projekcie zespołowym

---

## Dodatkowe zasoby
### Elixir
- [Elixir Official Documentation](https://elixir-lang.org/docs.html)
- [Elixir School](https://elixirschool.com/en/)

### Python
- [Python Docs](https://docs.python.org/3/)
- [Pytest](https://docs.pytest.org/en/6.2.x/)

### Linux/Bash
- [Linux Journey](https://linuxjourney.com/)
- [Bash Guide](https://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html)

### Jenkins CI/CD
- [Jenkins Documentation](https://www.jenkins.io/doc/)


#------------------------
Sieci:
	1. Podstawowe protokoły sieciowe:
		TCP/IP i UDP: Zrozumienie, jak TCP i UDP są używane w kontekście sieci telekomunikacyjnych. Jak działa mechanizm retransmisji, jak realizowane jest zestawienie połączeń w TCP (3-way handshake), oraz kiedy i dlaczego UDP jest używany w telekomunikacji.
		DNS: Jak działają zapytania DNS, różnice między DNS A, CNAME, MX itp.
		ICMP: Do czego służy (np. ping, traceroute).
	➜ Przykładowe pytanie: Jak wygląda komunikacja przy otwieraniu strony WWW od zapytania DNS po zestawienie sesji TCP?

	2. IP i sieci:
		Adresacja IPv4 i IPv6: Jak działa adresacja, maski podsieci, podstawy routingów.
		NAT (Network Address Translation): Jak sieci prywatne są tłumaczone na publiczne adresy IP.
		Routing: Podstawowe mechanizmy routingowe, tablice routingu, różnice między routingiem statycznym a dynamicznym.
	➜ Przykładowe pytanie: Jak działa NAT i dlaczego jest niezbędny w sieciach IPv4?

	3. Telekomunikacja i sieci komórkowe:
		LTE / 5G: Zrozumienie architektury sieci RAN (Radio Access Network), podstawowych pojęć jak eNodeB, gNodeB, EPC (Evolved Packet Core), NG Core.
		VoLTE i VoIP: Jak działa transmisja głosu w sieciach LTE? Zrozumienie protokołów SIP (Session Initiation Protocol) i RTP (Real-Time Protocol).
		QoS (Quality of Service): Jak priorytetyzowane są różne typy ruchu (np. dane, głos, wideo).
	➜ Przykładowe pytanie: Jak działa połączenie VoLTE i jakie są główne różnice między VoLTE a tradycyjnymi połączeniami głosowymi?

	4. Bezpieczeństwo sieci:
		SSL/TLS: Zrozumienie podstaw szyfrowania komunikacji.
		IPSec, VPN: Jak działają wirtualne sieci prywatne oraz szyfrowanie ruchu w IPSec.
		Firewall, ACL (Access Control Lists): Jak zarządzać regułami ruchu w sieci.
	➜ Przykładowe pytanie: Jak działa protokół IPSec i do czego służy?

	5. Systemy operacyjne:
		Linux: Przygotuj się na pytania dotyczące podstawowych komend Linux, jak zarządzać użytkownikami, procesami, oraz jak monitorować sieć i serwisy (komendy typu netstat, iptables, tcpdump, ss, ip route).
		Skrypty Bash: Pisanie prostych skryptów, które mogą zarządzać siecią (np. automatyzowanie konfiguracji, sprawdzanie połączeń).
	➜ Przykładowe pytanie: Napisz skrypt w Bashu, który pinguje wybrany serwer co 5 sekund i zapisuje wyniki do logu.

	6. Narzędzia sieciowe:
	Wireshark, tcpdump: Jak przechwytywać i analizować ruch sieciowy.
	Ping, traceroute: Narzędzia diagnostyczne do sprawdzania połączeń.
	➜ Przykładowe pytanie: Jak za pomocą tcpdumpa przechwycić ruch na porcie HTTP (