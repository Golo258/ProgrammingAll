
"""
    Tworzenie nowego projektu od zera
        Struktura itp:

    flow_tracker - nazwa_projektu


    flow_tracker/
    ├── docs/                # dokumentacja, notatki
    ├── src/                 # kod źródłowy (dobrze!)
    │   ├── common/          # moduły współdzielone — logger, utils itd.
    │   │   ├── __init__.py
        │   ├── flow_tracker     # główny pakiet (entrypoint)
    │   │   ├── __init__.py
    │   │   └── __main__.py
    │   ├── models/          # modele danych (np. Pydantic)
    │   │   ├── __init__.py
    │   └── services/        # logika biznesowa / moduły akcji
    │   │   ├── __init__.py
    |   ├── static/              # dane, szablony, konfiguracje
    |   │   └── dummy_data.json
    ├── tests/               # testy jednostkowe
    └── README.md

    __main__.py 
        specjalny plik python automatycznie uruchamia
        kiedy odpalamy dany pakit komenda
        python -m <pakiet>
            python -m flow_tracker
        wtedy odpalasz cały pakiet
        a nie tylko pojedynczy plikk
        

    Jeśli mamy projekt z src/
    to wtedy debuger nie łapie nam poprawnie modułów
    Konfiguracja launcher
        {
        "version": "0.2.0",
        "configurations": [
            {
                "name": "Python: Run flow_tracker CLI",
                "type": "debugpy",
                "request": "launch",
                "module": "flow_tracker.cli",
                "console": "integratedTerminal",
                "justMyCode": true,
                "cwd": "${workspaceFolder}/src"
            }
        ]
    }
"""

