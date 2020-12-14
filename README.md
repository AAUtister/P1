# Projekt Komma

## VERSION: Early Access :shipit:

### Om
Finder udsagnsord i txt. Markerer med CAPS.
Vildt nok (...)

### Instrukser
Der er 2 metoder til at kompilere og køre programmet, den nemme og den mindre nemme.
Programmet er testet til at virke på Linux, ~~Mac og en LiveUSB af Ubuntu~~
#### Den nemme metode
1. Kør scriptet `./run.sh`.
    - Hvis det ikke virker, så hver sikker på at scriptet er eksekverbar `chmod u+x run.sh`, og kør igen!

#### Den _mindre_ nemme metode
1. Sørg for at manuelt hente Mini-XML biblioteket [minixml-3.2.tar.gz](https://github.com/michaelrsweet/mxml/releases/download/v3.2/mxml-3.2.tar.gz) og placér i roden af projektets mappe.
    - Projekt mappen skal se således ud efter.
    ```
    .
    ├── data
    ├── lib
    ├── src
    ├── Makefile
    ├── README.md
    ├── mxml-3.2.tar.gz
    └── run.sh
    ```
2. Kør `make prepare` som udpakker, konfiguerer og installerer Mini-XML til **lib/** mappen.
3. Kør `make all` som kompilerer hele projektet.
4. Kør `./program.out` på en af de to følgende måder.
    - 
    ```
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/lib/mxml-3.2/lib
    ./program.out
    ```
    - 
    ```
    LD_LIBRARY_PATH=lib/mxml-3.2 ./program.out
    ```

### Regler
Programmet bruger **STARTKOMMA** i `rules.c`
