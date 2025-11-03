
1. Piramida Testowania:
	Piramida testowania to model ilustrujący różne poziomy testów, które powinny być wykonywane w projekcie oprogramowania.
	Model ten sugeruje, aby testy były organizowane w formie piramidy, 
		gdzie różne typy testów są rozmieszczone na różnych poziomach.
	Główne poziomy:
	1. Testy jednostkowe: (unit tests) - dół piramidy
	Opis:
		testy, które sprawdzają pojedyncze jednostki kodu, takie jak funkcje, metody lub klasy, w izolacji.
	Cel: Upewniamy się że komponenty oprogramowania działają poprawnie, zgodnie z ich specyfikacją
	Zalety: szybkie w wykonaniu, łatwe do zautomatyzowania. Pomagają szybko zweryfikować błędy (na wczesnym etapie)

#
	2. Testy integracyjne (integration tests): środek piramidy
	Opis:
		testowanie między różnymi komponentami lub modułami aplikacji, aby upewnić się, że współpracują one poprawnie.
	Cel: Sprawdzenie, czy różne cześci systemu współdziałające ze sobą tak jak powinny
	Zalety: Pozwalają na testowanie interakcji mniedzy różnymi komponentami, które nie są w pełni widoczne w unit testach

#
	3. Testy end-to-end: góra piramidy
	Opis: 
		Testują całe aplikacje od początku do końca, symulując rzeczywiste scenariusze użytkowników.
	Cel: Upewnienie się że aplikacja działa poprawnie w rzeczywistych warunkach, z wszystkimi komponentami w integracji
	Zalety: Pozwalają na testowanie całości systemu, błędów które trudno znaleźć na niższych poziomach testów


	Piramida jest efektywna, wychwytuje błędy na różnych etapach cyklu życia aplikacji
	Zapewnia utrzymanie odpowiedniej jakości


2. Testowanie funkcyjne:
	Skupia się na weryfikacji zgodności aplikacji z wymaganiami funkcjonalnymi:	
	Weryfikuje działanie funkcji, funkcjonalności aplikiacji.
	Weryfikuje to co aplikacja ma robić.
	Typy:
		Jednostkowe:
			Pojedyncze moduły, funkcje, metody w izolacji. Czy dany element działa poprawnie
		Integracyjne:
			Interakcja miedzy różnymi modułami/komponentami. 
		Systemowe:
			Testuje system jako całość. Upewnienie się że wszystko współdziała prawidłowo
		Akceptacyjne:
			Sprawdza czy system spełnia wymagania biznesowe i jest gotowy do wdrożenia
			Często wykonywane na podstawie scenariuszy użytkownika


3. Testowanie niefunkcyjne:
	Koncentruje się na aspektach wydajności, bezpieczeństwa i użyteczności:
	Typy:
		Wydajnościowe (Performance Tests):
			Sprawdzają czy aplikacja radzi sobie pod dużym obciążeniem
				Obejmują one testy obciążeniowe (load tests), stresowe (stress tests) 

		Bezpieczeństwa: (security)
			Oceniają, czy aplikacja jest zabezpieczona przed zagrożeniami
			Obejmuje testy podatności (vulnerability) 
			i penetracyjne (penetration) - kontrolowane ataki na system

		Użyteczności (usability tests):
			Ocenia jak łatwo user może korzystać z aplikacji
			Skupia się na doswiadczeniach usera i ich interakcji z interfacem

		Kompatybilności (compatibility):
			Sprawdza czy aplikacja działa na różnych urzadzeniach, systemach operacyjnych, przegladarkach

		Niezawodności (reliability):
			Sprawdza czy aplikacja dobrze radzi sobie z długotrwałym użytkowniem oraz w przypadku awari


4.System do śledzenia zadań  (Task managmenet System)
	 pomagają zespołom organizować, śledzić i zarządzać pracą w projektach.
	 np: Jira, Trello, Asana
	 ułatwiają zarządzanie projektami i zadaniami poprzez tworzenie i przypisywanie zadań, 
	 śledzenie postępu, ustalanie priorytetów i terminów, oraz komunikację zespołową.

	 Statusy i oznaczenia zadań:
	 	1. Ready - jest gotowe do rozpoczęcia pracy.
	 		Wszystkie informacje sa dostepne i można go wykonywać

	 	2. To Do - jest na liście do wykonania 
	 		Zostało przydzielone i zaplanowane, ale prace się jeszcze nie rozpoczeły

	 	3. In Progress:
	 		Praca nad zadaniem jest w toku.
	 		Zespół pracuje na zadaniem, podejmuje działania, aby je zakończyć

	 	4. Blocked
	 		Zadanie zablokowane i nie może być kontynuowane z powodu jakiegoś problemu
	 		(np braku informacji / zależności)

	 	5. Done/Completed:
	 		Zadanie zostało ukończone i spełnia wszystkie kryteria akceptacji
	 		Zakończone, przetestowane i zatwierdzone

5. Testowanie automatyczne:
	proces wykorzystywania narzędzi i skryptów do automatycznego wykonania testów oprogramowania 
	zamiast przeprowadzać je ręcznie. Zwiekszenie efektywności, dokładności i możliwość wielkrotnego uruchamiania

	Typy auomtayzacji:
		1.Automatyzacja potwarzalnych zadań:
			Przydatne żeby sprawdzić funkcjonalności, które musza być testowane wielokrotnie

		2. Poziomy testowania:
			Jednostkowe - pojedyncze jednostki, zazwyczaj pierwsze pisane przez programistów
			Integracyjne - interakcja modułów aplikacji, współgranie ze sobą
			Systemowe - system jako całośc, wszystkie cześci działają poprawnie
			Akceptacyjne: Czy spełniają wymagania biznesowe i czy może zostać akceptacja użytkownika końcowego

		3. automatyzacja end-to-end
			Pełne przepływy użytkowika przez system, od wejścia danych po zakończenie sesji

6. Testy regresyjne:
	sprawdzenie, czy zmiany wprowadzone w kodzie nie spowodowały wprowadzenia nowych błędów ani nie zakłóciły pracy systemu
	mają na celu upewnienie się,
		 że nowe zmiany nie wprowadziły regresji, czyli pogorszenia jakości oprogramowania.	

	Kiedy:
		Gdy błąd został naprawiony, sprawdzamy czy naprawa nie wprowadziła innych problemów w systemie

		Po dodaniu nowej funkcjonalności, może to wpłynąc nieświadomie na działanie innych funkcji

		Po aktualizacja środowiska / komponentów
			Zmiany w bazie danych, systemach operacyjnych, bibliotekach mogą wpływać na działanie aplikacji.

		Metody:
			Ręczne: recznie wykonywanie przypadków testowych 
			Automatyczne: automatyczne i szybkie testowanie dużych obszarów aplikacji

	Daje stabilność, możliwośc wczesnego wykrycia problemów, oszczednośc czasu i pieniedzy

7. Pojecia:
	Test case (przypadek testowy):
		to opis kroków, 
			danych wejściowych,
			warunków wstępnych
			oczekiwanych wyników, które są używane do testowania konkretnej funkcji lub cechy oprogramowania.

		Przykład: logowanie do aplikacji - dane wejsciowe (login, hasło), potem system sprawdza, i przekierowywuje 

	Test plan (plan testów):
		Dokument, który opisuje strategię, cele,  zasoby oraz zakres testów, które mają być wykonane w ramach projektu
		Definuje jakie metody testowania będą używane oraz jakie narzedzia potrzebne

		Przykłąd: Ecoomerce - informacje jakie testy (unit, integration itp) beda przeprowadzane 

	Test Suite (zestaw testów):
		Zestaw powiazanych testów, pogrupowanych w celu przetestowania okreslonego aspektu systemu, osiagniecie celu
		Przykłąd: Wszystkie przypadki testowe zwiazane z procesem rejestracji nowego użytkownika


	Test Script:
		Zautomatyzowany skrypt, wykonuje kroki testowe zgodnie z przypadkiem testowym
		Wprowadzanie danych do formularzy i weryfikacja czy system odpowiednio reaguje

	Bug (błąd):
		to nieprawidłowość w działaniu oprogramowania, powoduje że nie działa zgodnie z oczekiwaniami

	Testy akceptacyjne użytkownika:
		Przeprowadzone przez użytkownika końcowego lub klienta
		Weryfikacja czy spełnia ich wymagania i jest gotowy do wdrożenia

	Test eksploracyjne:
		Testerzy badają aplikacje bez wcześniejszego zdefiniowania przypadków testowych
		Improwizują na podstawie wiedzy i doświadzczenia

	Testy obciążeniowe:
		Testowanie wydajności, sprawdzenie czy system działa pod dużym obciążeniem, (dużo userów, zapytań)
