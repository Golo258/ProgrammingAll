
Dispatcher co robi i jak:
    Docker Compose, który uruchamia 3 usługi:
    web → Twoja aplikacja Pythonowa
    mysqldb → Baza danych MySQL
    phpmyadmin → Panel webowy do bazy (dla ludzi)

    aplikacja start: CMD [ "python3", "wts_ute_cloud_interface/cli_interface.py", "-l", "info" ]


    sh "sudo docker run -d -v /home/ute/workspace-jenkins/...:/wts_ute_cloud_interface/logs --network testline_dispatcher_nginxphp -p 5000:5000 --name cus_dispatcher cus_dispatcher:${DISPATCHER_VERSION}"
        odpal kontent cus_dispatcher z wcześniej zbudowanego brazu
        podłącz go do seici nginxphp
        przekieruj port 5000
        dodaj volumy z logami 


        pliki YAML są kopiowane do kontenera do katalogu
             wts_ute_cloud_interface/wts_ute_cloud_interface/data


Reprodukcja na debugowanie pythonowe:
    potrzebne - środowisko pythonowe
    pliki .yaml w wts_ute_cloud_interface/data
    lokalny MySQL z tym samym hasłem 


tokens_to_spare.yaml
    []

tl_for_retry.yaml
    default: 1
    CLOUD_R4A_CUS: 2
    CLOUD_R4BANO_CUS: 2
    CLOUD_R4LAPO_CUS: 2
te pliki wpierdalamy w ścieżke /wts_ute_cloud_interface/wts_ute_cloud_interface/data/
absolutną !! - nie w projekcie 

docker-compose-mysql.yaml
    version: '3.8'
    services:
    phpmyadmin:
    depends_on:
    - mysqldb
    image: phpmyadmin
    restart: always
    ports:
    - '9000:80'
    expose:
    - 80
    environment:
    PMA_HOST: mysqldb
    MYSQL_ROOT_PASSWORD: 'relsup2018'
    networks:
    - nginxphp

    mysqldb:
    image: mysql
    restart: always
    ports:
    - 3306:3306
    environment:
    - MYSQL_DATABASE=relsup
    - MYSQL_ROOT_PASSWORD=relsup2018
    - MYSQL_HOST=localhost
    volumes:
    - mysql:/var/lib/mysql
    - mysql_config:/etc/mysql
    networks:
    - nginxphp

    volumes:
    mysql:
    mysql_config:

    networks:
    nginxphp:
    driver: bridge

i komenda do odpalenia mysql i phpadmin
    docker-compose -f docker-compose-mysql.yml up -d

    wbijasz na http://localhost:9000
        root i hasło relsup2018

wejście na dockera i sprawdwzenie co sie tam dzieje
    docker ps - bierzesz sobie id contenera
    docker exec -it <id_contenera> /bin/bash
        wejdzie ci do powłoki szelowej i możesz jechać z kurwami

