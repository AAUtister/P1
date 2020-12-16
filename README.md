# Projekt Komma

## VERSION: Early Access :shipit:

### Om
(...)

### Instrukser
Der er 2 metoder til at kompilere og køre programmet, manuelt ved gennemgang af trin og automatisk ved et simpelt script.
Programmet er testet til at virke på Linux, Mac, ~~Windows~~ og en LiveUSB af Ubuntu _(Kræver `curl`, `make`, og `gcc` installeret)._

#### Den manuelle metode
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
2. Kør `make prepare` som udpakker, konfiguerer, kompilerer og installerer Mini-XML til **./lib/** mappen.
3. Kør `make all` som kompilerer hele projektet.
4. Kør `./program.out` på en af de to følgende måder.
    - `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/lib/mxml-3.2/lib` derefter `./program.out`
    - `LD_LIBRARY_PATH=lib/mxml-3.2 ./program.out`

#### Den automatiske metode
##### Kør scriptet `./run.sh`.
Scriptet gør det samme som den manuelle metode, dvs.
1. Downloader arkivet `mxml-3.2.tar.gz` vha. cURL, hvis filen ikke eksisterer.
2. Kører `make prepare` som udpakker, konfiguerer, kompilerer og installerer Mini-XML til **./lib/** mappen, hvis det ikke allerede er udpakket til lib/
3. Kører `make all` som kompilerer hele projektet, hvis filen **program.out** ikke eksisterer
4. Kører vores program som forventet :beers:

##### Problemer?
1. Vær sikker på at scriptet er eksekverbar: `chmod u+x run.sh`, og kør igen! `./run.sh`
2. Hvis køres med WSL2 under Windows, tjek at lineendings i run.sh er sat til **LF**, ikke **CRLF**

### Regler
Programmet bruger **STARTKOMMA** i `rules.c`
