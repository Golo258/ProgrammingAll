
"""
    Wyjaśnienie:
        Obraz - image
            szablon do odczytu (read only)
            zbiór plików i ustawień (co zainstalować, jaki program uruchomić na starcie)
            zazwyczaj ma specyficzny tak np mysql:7.4 
            jest złożony z warstw (layerts)
            warstwy są cashgowane, dziieki czemu pobieranie / budowanie jest szybsze
            nie uruchamia sie sam, to jest tylko przepis

            Do czego on jest:
                aby wszedzie było to samo środowiska
                można zrobić wiele kopii tej samej aplikacji bez instalowania jej od zera
                żeby łatwo wersjonizować app1.0 app1.1

        Kontener - 
            -to uruchomiona instancja obrazu, czyli już upieczone ciasto z przepisu
            to proces działający w odizolowanym pudełku
                ( ma własny pid, sieć, system plików)
            ma dodatkową warstwe zapisu (writable). wszystko co zmieniasz w trakcie działania
                trafia do tej warstwy, obraz pod spodem jest nadal niezmieniony
            
            kontener żyje dopóki działa proces. możesz go 
                zatrzymąć(stop)
                wystartować(start)
                skaskować
                nadać mu nazwe
            
            Używamy do:
                uruchmaiania aplikacji /usług z obrazow 
                do skalowania: z jednego obrazu odpalasz 5 takich samych kontenerów
                do izolacji: każdy kontener ma swoje biblioteki, porty, zmienne 

    Czyli:
        Obraz- niezmienony szablon - gwarancja powtarzalności
        Kontener - stan uruchomienia - ma swoje dane zmiany, znikną gdy skasuje 
    
        Obraz → jak klasa w programowaniu.
        Kontener → jak obiekt tej klasy.
        Możesz mieć 10 obiektów z tej samej klasy — tak samo możesz mieć 10 kontenerów z jednego obrazu

"""
1. Zaciągnie obrazu
    docker pull nazwa_obrazu:tag(wersja) -- jak nie podasz wersji to zrobi latests
        np: docker pull mysql:8.4

2. Jakie masz obrazy i kontenery:
    docker images - pokazuje wszystkie obrazy 
    docker ps - jakie mamy kontenery  
        -a --all - wszystkie 
        -q --quiet - tylko id kontenerów
        -l --latest - ostatnio utworzony 
        -n - x utworzonych kontentórw
        -f --filter - filtruje po danym atrybucie
        --format - własny sposób wyświetlania

3. Jak zrobić kontener z obrazu:
    - tworzy  kontener na podstawie obrazu i od razu uruchamia kontener.
    docker run -d --name db1 mysql:8.4
        -d (detached czyli leci w tle)
        --name db1 - nadajem mu nazwe, żeby było łątwiej znaleźć
        - mysql:7.4 - z jakiego obrazu tworzymy 
        -przydantne flagi
            porty:               -p 3306(host):3306(container) - wystaw port z kontenera na hosta
            dane trwałem:        -v mysql_data:/var/lib/mysql - volumen named
            zmienna środowiska:  -e MYSQL_PASS=secret
            automatyczny reset:  --reset unless-stopped
            usuwanie po wyjściu: --rm
            sieć:                --network bridge|host|nazwa_sieci
            plik env:            --env-file .env
            limit zasobów:       --cpus 1.5 --memory 1g
                docker run -d --name db1 \
                -e MYSQL_PASS=secret_pass \
                -v mysql_data:/var/lib/mysql \
                -p 3306:3306 \
                --reset --unless-stopped \
                mysql:8.4

4. Tworzenie bez startu
    docker create --name db2 mysql:8.4
    docker start db2 -- start kontenera


5. Sterowanie życiem kontenra
    docker stop db1
        -t 120 - można dodać ile czasu ma przed zamknieciem
    docker start db1
    docker reset db1
    docker rm db1     -- usuń ( musi być zatrzymany)
    docker rm -f db1  -- usuń na siłe (kill + rm)


6. Interakcja z kontenerem: 
    docker exec -it <nazwa kontenera> bash
        exec - wykonaj polecenie na działającym kontenerze
        -i --interactive - tryb interakyny (stdin otwarty)
        -t --tty - terminal 
        bash sh - powłoka na jakiej otwieramy terminal

    docker logs -f --tail 20 <kontener>  
        logs - podgląd logów z kontenera
        -f --folow = na żywo (jak tail -f )
        --tail x - pokaze ylko x lini

    docker top <kontener>
        - top jakie procesy działają wewnątrz kontenera

    docker stats -  statystuki kontenra CPU / RAM / IO itp

    docker cp 
        ./plik.txt <nazwa_kontenera>:/sciezka
             - kopiowanie plików z hosta do kontenera
        <nazwa_kontenera>:/sciezka ./sciezka
             - kopiowanie plików z kontenera do hosta

    docker inspect - szczegółowe informacje o kontenerze
    
7. Czyszczerenie śmeici
    docker system prune  - usuwa zatrzymane kontenery, sieci itp
    docker system prune -a - to samo tylko wszystkie --all

8. Budowanie obrazu:
    docker build -t nazwa/aplikacja:tagi .
        -t - tag (repo/nazwa:wersja)
        . - kontekst buildu wszystkoco nie jest w .dockerignore leci do 
            demona Dockera  

9. Wypychanie obrazu:
    docker login - logowanie na dockera
    docker push repo/nazwa:wersja
    potem 
    docker pull  repo/nazwa:wersja
    docker run -p 8000:8000 repo/nazwa:wersja

10. Po co pliczki:
    Dockerfile:
        przepis na zbudowanie obrazu 
        mówi nam co mamy zrobić, wziąśc odpalić, skopiować, żeby zbudować nowy obraz
    
    docker-compose.yml
        przepis na uruchomienie wielu kontenerów razem
            (np: aplikacja pythonowa, baza danych, panel admina itp)
        zamiast pisać 5 razy docker run, mamy 1 plik z definicją wszystkiego 

        odpalamy poprzez docker compose up
    
    Makefile:
        zbiór skrótów/aliasów do czesto powtarzanych komend 
            zamiast pisać: docker build / puish - robimy make build, make push 
            
10.1
    Dockerfile: - lsita kroków  jak zbudować obraz 
        kadza linijka to instrukcja jak robimy warstwy obrazu
    Najważniejsze klocki:
        FROM - z czego startujemy - wybiera bazowy obraz z jakąś zawartością
            (System narzedzia, programy jezyki ) 
            FROM python:3.12-slim ( splim małe bazy danynch | alpine duze)

        WORKDIR - katalog roboczy w dla wszystkich dalszych instrukcji w Dockerfile
            i dla domyślnego startu kontenera - exec- it kontener bash - wejdzie do danego katalogu 
            ustala cd na reszte instrukcji 
            WORKDIR /app
        COPY - kopiujemy pliki z kontekstu buildu do obrazu
            COPY requirements.txt .
            COPY . .
                - source | target 
                - jestli target to . - to kopiuje do bieżacego workdir 

        RUN - wykonaj komende w czasie budowania
            a wynik zapisuje w obrazie jako warstwa
            np tutaj: instaluje biblioteki w obrazie
            RUN pip install --no-cache-dir -r requirements.txt

        ENV -zmienne środowiskowe w obrazie / zostaja na stałe w obrazie
            ENV PYTHONUNBUFFERED=1
        ARG - zmienne na czas budowania
            dostpene tylko  w buldzie można nadpisać --build-arg
            ARG APP_VERSION=dev
            LABEL version=$APP_VERSION
        EXPOSE - informacje o porcie, dokumentacja w obrazie 
            EXPOSE 8000

        CMD vs ENTRYPOINT - co startuje kontener 
            CMD - domyślna komenda  argumenty , łątwo nadpisać w rocker run 
            ENTRYPOINT - twarda komenda - trudniej nadpisać
            np: CMD ["uvicorn", "app:app", "--host", "0.0.0.0", "--port", "8000"]
            -- komenda która urchamia sie gdy odpalasz kontener 

        VOLUME: deklaracje miejsca na dane
            VOLUME ["/data"]
    Jak odpalać:
        docker build -t repo/app:wersja
        docker push repo/app:wersja

10.2 - docker-compose.yaml
    -- definiuje nam jak uruchomić jedną albo kilka aplikacji w kontenerze
        -- może on zbudować obrazy (sekcja build) i od razu urchomić z nich kontenery

    scenarisuz uruchamiania dla wielu kopntenerów naraz
        services - lista usług/kontenerówJ jakie mają powstać
            - (każdy wpis to osobny kontener)
        image/build - skąd wziąć obraz 
            image - nazwa obrazu z którego bedzie kontener
            build: info skad zbudować obraz -( dockerfile)
                context: precyzujemy na przykąłd 
                context: . - czyli wszystko gdzie jesteśmy jest kontekstem buildu

        env_file - wskazuej plik .env - w którym są zmienne środowiskowe
        environment - lsita zmiennych środowiskowych
            albo DB_HOST: db 
            albo - DB_USER=app
        ports: mapowanie portów host<->kontener np 8000:8000
            host - VM / PC, na któym działą docker
            kontener - wewnętrzny port na którym aplikacja nasłuchuje 

        volumes: dane trwałem named volume lub mount kodu dev
            named volumes - trwałe dane, które zostają 
            bind mounts- mapowanie katalogu z hosta
                :/app:/app
        command: 
            nadpsiuej cmd z Dockerfile
            komenda która uruchomi sie po starcie kontenera
        depends_on: kolejność startu
        restart: polityka restartu
            np: always -jesli padnie kontener to Docker go uruchomi automatycznie
        expose: informacja że ten port jest używany w sieci Dockera
        networks: zwykle domyslny bridge
            tworzymy daną sieć, i nadajemy jej drivera np:
            networks:
             nginxphp:
                driver: bridge



    Jak odpalać:
        - start wszystkich usług
            docker compose up -d 
        - logi konkretnego serwisu
            docker compose logs -f (-- follow) db
        - stan usług
            docker compose ps
        - wejscie do kontenera 
            docker compose exec app bash 

        - restart/stop/start danej usługi
            docker compose restart app
            docker compose stop app
            docker compose start app

        - zatrzymanie i usunięcie kontenerów
            docker compose down
        
        - zatrzymanie + czyszczenie volumenów
            docker compose down -v

        - walidacja i podgląd tego co compose widzi
            docker compose config 


11. Tagowanie:
    nadawnaie obrazowi adresu pod którym jest znany
    Nazwa obrazu w dockerze
    [registry]/namespace/repo:tag
        docker.io/golo258/myapp:1.0
        registry - gdzie to leży - na jakim hubie 
        namespace - konto, organizacja w rejestrze
        repo - nazwa projektu/obrazu
        tag - wersja 

    dziąła to jak alias  - nie kopiuejmy danego obrazu tylko nadajemy etykeite
            zbudowana aplikacja   na realny namespace 
    docker tag grzesio/myapp:1.0 golo258/myapp:1.0
    


12. Sieci:
    docker daje nam prywante LANY wirtualne 
    prywatny pokój dla wybranych kontenerów
    kontenery w sieci widzą sie po nazwie, gadaja po wewnętrznych portach
    są odciete od innych poza siecią

    -p - portów - używamy tylko z zewnątrz do kontenera,

    Tworzenie:
        docker network create appnet
        docker network ls
    Dodawanie kontenera do sieci:
        docker run -d --name web --network appnet nginx:slim

        docker run --rm curlimages/curl echo "Siemano kolano" 
            pobiera obraz 
            uruchamia od razu komende 
            po zakończeniu, usuwa kontener  

        # kto sie dzici w danej sieci
        docker network inspect <nazwa_sieci> | jq '.[0].Containers'
        #odłączanie kontenera od sieci
        docker network disconnect <siec> <kontener>
    
    Jak definiujemy sieci w compose:
        networks:
            nginxphp:
            driver: bridge
        to potem nie tworzy sie sieć dokładnie o takiej samej nazwie tylko
            nazwa_kontener_nazwa_sieci
            
13: Volumeny:
    Kontener ma system plików któy znika w momencie usunięcia
    Wlumen to trwały magazyn danych
        żyje poza kontenerem
        może być podłączony do wielu kontenerów
            odłączyć i dać do innego
    
    #tworzenie 
        docker volume create <nazwa>
        docker volume ls - jakie są
    
    # dodawanie danych do volumenu
        1.Named volume: zarzadzany przez dockera
        docker run -v <nazwa>:/jakie_dane <kontener>
            -v --volume 
        2.Bind mount: mapujesz katalog z hosta:
                            (host dir) : (container dir)
            docker run -v $PWD/data:/app/data ...
                jeśli zmienisz na hoście albo na contenerze to bedzie miało wpływ na drugie

14. Env w kontenterach: - środowisko uruchomieniowe
    zmienne środowiskowe
        konfguracja bez zmiany obrazu   
        bezpieczniejsze niż wypisywanie haseł
        łatwe zmiany w docker run i compose

    # ustawianie env
        docker run -t --rm \
            -e VAR=sifmap \
            -e PASS=secret \
            ubuntu bash

        # potem można zrobić
            echo $VAR
    # wczytywanie z pliku .env
        docker run - --rm --env-file .env ubuntu bash
        

wejście na dockera i sprawdwzenie co sie tam dzieje
    docker ps - bierzesz sobie id contenera
    docker exec -it <id_contenera> /bin/bash
        wejdzie ci do powłoki szelowej i można lecieć

#-------------------------------------
Inna wersja podsumowania
Docker:
		Rejest- np: Docker Hub: 
			przechowuje w sobie obrazy  
		Obraz - coś jak klasa
		Container - coś jak instancja tej klasy(obrazu)
			Na bazie jednego obrazu, możemy uruchomić sobie wiele kontenerów 

przykładowe uruchomienie kontenera:
	docker run -d -p 80:80 docker/getting-started
	-d - run container in detached mode
	-p - map port 80 to host port 80
	docker/getting-started - the image to use 

docker run image - running the image
docker images -> show our images 
docker container ls -a -> list our containeres
docker stop ContinerPort

images are readonly, cannot modified 
container is writable, can be modified 

docker run: pobiera obraz, cashuje go w pamieci, potem go uruchamia

docker pull - pobiera obraz, cashuje go, bez uruchamiania	

docker pull image - pobieranie obrazu 
	bez podawania wersji pobiera nam latests
	podanie wersji to
		image:wersja np : httpd:2.4.58-alpine

	its loading our image and its layers and then its cashing it in our memory

Docker hub to jest jak github:
	możemy wysłać obrazy do repozytorium, obrazy mogą zawierać różne rzeczy, kod, aplikacje, serwery itp

Potem aby uruchomić to:
	to runujemy sobie kontener na podstawie obrazów
np;
	runowanie serwera apache
	docker run -d --name apache-app nasz_port(8080):port apache(80) image:version

version:
	Każdy obraz ma jakąś wersje
		Obraz ma wiele warstw 
		Alpine - najniższy 
docker rm container - remove container by its id
docker rmi image - remove image by its id 

Wejscie do kontenera:
	docker exec -it idContainer /bin/sh

	-it - interactive tty

Po zmianach wprowadzonych na kontenerze możemy zapisać je poprzez commit obrazu

docker commit identyfikator nazwa_zmienionego_obrazu
po commicie możemy zobaczyć historie jakie zmiany zroibliśmy
	docker history obraz:wersja

Budowanie obrazów DockerFile:
	dockerfile references - dokumentacja

ADD
 przenoszenie plików z komputera hosta do obrazu

COPY-
 przenoszenie plików z komputera hosta do contenera

ENV- zmienne środowiskowe

EXPOSE - określenie portu uruchamianej aplikacji

FROM - mówimy z jakiego obrazu rodzica chcemy skorzystać
 
Budowanie instrukcji za pomocą DockerFile:
	docker build -t nazwa_obrazu/autor:versja ./
	./ ( katalog gdzie jest DockerFile)

Plik Dockerignore:
	 Ignorowanie plików, katalogów które sa niechciane w repo 

Tagi:
	Możemy nadawać tagi podczas budowania obrazu
		docker build -t 
			-t - inaczej tag 
			-t nazwa/cos:tagName

	Zmienianie tagu
		docker tag imageName changedImageName

	Usuwanie starego image:
		docker rmi imageID

Volumeny:
	Zapisywanie danych na stałe  
	Tworzenie:
		docker volume create volumeName
		Tworzenie przy uruchamianiu contenera:
			docker run -d --name nazwa -p porty -v Nazwa volumenu/workdirName  imageName

			np: 
			docker run -d --name course-cont-vol -p 81:80 -v app_volume:/app 64aa05b3f830

			wolumen teraz ma współdzielony folder /app
			który został utworzyony w DockerFile:
				WORKDIR /app
		
	Listowanie:
		docker volume ls 
	Usuwanie:
		docker volume rm volumeName

W momencie gdy tworzymy nowe kontenery na danym obrazie to gdy damy tam ten sam wolumen to jest on wspóldzielony z wszystkimi kontenerami dla danego obrazu 
	Możemy też podpiąć volumen z dysku lokalnego
		dajemy -v C:/Users:/katalog

Tworzenie bazy danych na kontenerze dockerowym:
	docker pull mariadb
		sprawdzamy czy jest taka sama wersja jak chcemy miec w aplikacji i potem
		docker run -d --name grzesiu-database 
		--env MARIADB_USER=golo258 
		--env MARIADB_PASSWORD=asd 
		--env MARIADB_ROOT_PASSWORD=asd 
		--env MARIADB_DATABASE=pslab
		-p 3307:3306 mariadb

	Mapujemy porty na jeden lokalny:port maridb czyli 3306

	Przywracanie danych na kontenerze bazy danych:
		jeśli nie ma tam zainstlowanego mysql to robimy:
			apt update 
			apt-get install mysql-client
		mysql -u nazwa_user -p
			hasło wpisujemy
		use nasza baza danych

		source sciezka_do_pliku_skopionanego
Docker sieci:
	docker network ls 
	Tworzenie sieci:
		docker network create --driver options nazwa

		options:
			bridge
			host
			overlay
			ipvlan
			macvlan
			none

	Usuwanie sieci:
		docker network rm id_sieci

	Domyślnie kontener jest podpięty do sieci bridge
	Sprawdzanie sieci na kontenerze:
		docker network inspect nazwa_sieci
			pokazuje jakie kontenery są podpiete do sieci i ich adresy ip 
	Kontenery w tej samej sieci widzą siebie

	Przypisywanie sieci do kontenera:
		docker run -d --name nazwa --network nazwa_sieci -p port1:port2 obraz

	Podłączanie kontenera do innej sieci:
		rozłaczamy z poprzednią:
		docker network disconnect nazwa_sieci kontener_id
		docker network connect 

