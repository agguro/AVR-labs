[🇬🇧](README.md)  -  [🇳🇱](README.nl.md)  -  [🇨🇴](README.es-co.md)  -  [🇵🇹](README.pt.md)

# Leertrajecten

Deze repository ondersteunt meerdere leertrajecten, afhankelijk van voorkennis, beschikbare middelen en leerdoelen.  
Alle trajecten hebben uiteindelijk hetzelfde doel: begrijpen hoe microcontrollers écht werken.

Niet iedereen start op hetzelfde punt, en dat is bewust zo ontworpen.

---

## 🟢 Traject 1 — Geleide instap (Arduino-brug)

**Voor wie:**  
- beginners  
- jongere leerlingen  
- studenten zonder volledige toolchain  
- eerste kennismaking met microcontrollers  

**Middelen:**  
- Arduino IDE  
- Arduino-sketches (in de map `arduino/`)  

**Focus:**  
- basis I/O  
- observeren van gedrag  
- eenvoudige experimenten  

**Wat doe je in dit traject:**  
- een bestaande sketch openen  
- deze uploaden naar een Arduino-bord  
- LEDs, knoppen en timing observeren  

**Wat leer je:**  
- dat code hardware aanstuurt  
- dat pinnen een betekenis hebben  
- dat timing een rol speelt  

**Belangrijke opmerking:**  
Dit traject is een instap, niet het eindpunt.  
Leerlingen worden aangemoedigd om door te groeien naar Traject 2.

---

## 🟡 Traject 2 — Simulatie eerst (kerntraject)

**Voor wie:**  
- studenten die willen begrijpen  
- omgevingen zonder hardware  
- onderwijs met beperkte middelen  

**Middelen:**  
- `virt-atmega328p`  
- per lab een `simulate`-programma  
- Meson buildsysteem  

**Focus:**  
- interne werking van de microcontroller  
- registers en poorten  
- timing en uitvoering  

**Wat doe je in dit traject:**  
- firmware bouwen als `.elf`  
- deze uitvoeren in simulatie  
- interageren met virtuele componenten  

**Wat leer je:**  
- hoe firmware wordt uitgevoerd  
- hoe poorten echt werken  
- het verschil tussen simulatie en hardware  

👉 **Dit is het aanbevolen leertraject.**

---

## 🔵 Traject 3 — Firmware en flashen (hardwarebewust)

**Voor wie:**  
- studenten die klaar zijn voor echte hardware  
- wie wil begrijpen wat “uploaden” werkelijk betekent  

**Middelen:**  
- `.hex` firmware  
- `flash`-tool  
- ATmega328P (met of zonder Arduino-bord)  

**Focus:**  
- flashen versus uploaden  
- geheugenstructuur  
- seriële communicatie  

**Wat doe je in dit traject:**  
- firmware rechtstreeks flashen  
- baudrate en poorten instellen  
- gedrag op echte hardware observeren  

**Wat leer je:**  
- hoe code in de microcontroller terechtkomt  
- wat een bootloader doet  
- hoe tools met hardware communiceren  

---

## 🔴 Traject 4 — Verdieping (voorbij Arduino)

**Voor wie:**  
- gevorderde studenten  
- zelflerenden  
- geïnteresseerden in embedded systemen  

**Middelen:**  
- uitbreidingen op `virt-atmega328p`  
- virtuele componenten  
- low-level debugging  

**Focus:**  
- systeemontwerp  
- randapparatuur  
- architectuur  

**Wat doe je in dit traject:**  
- virtuele hardware uitbreiden  
- eigen componenten ontwerpen  
- timing, interrupts en geheugen onderzoeken  

**Wat leer je:**  
- hoe embedded systemen zijn opgebouwd  
- hoe hardware en software samenwerken  
- hoe abstracties ontstaan  

---

## 🔁 Trajecten zijn niet strikt gescheiden

Leerlingen kunnen vrij bewegen tussen trajecten.  
Iemand kan starten met Arduino, overstappen naar simulatie en later terugkeren naar hardware met meer inzicht.  

Het doel is vooruitgang, niet beperking.

---

## 🎯 Gedeeld einddoel

Niet alleen iets laten werken,  
maar begrijpen **waarom** het werkt.

---

## Opmerking voor leerkrachten

Deze leertrajecten zijn bewust ontworpen om te werken zonder verplichte hardware.  
Ze maken gelijkekansenonderwijs mogelijk in contexten waar middelen beperkt zijn, zonder in te boeten aan technische diepgang.

