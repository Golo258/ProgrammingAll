def call() {
    // 1. Zwykły log
    echo "Uruchamiam przykładowy skrypt..."

    // 2. Krok withEnv (na którym wcześniej był błąd)
    // Przyjmuje listę zmiennych i blok kodu (closure)
    withEnv(["PYTHONPATH=/home/ute/.pyenvs/"]) {

        echo "Jestem wewnatrz srodowiska"

        // 3. Wywołanie shella (które sprawdzamy w teście)
        sh('git status')

        // Przykładowy etap
        stage('build') {
            sh(script: 'mvn clean install', returnStdout: true)
        }
    }

    echo "Koniec skryptu."
}