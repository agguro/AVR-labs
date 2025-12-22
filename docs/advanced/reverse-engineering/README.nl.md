[Home](../../../README.md)  -  [Docs index](../../index/README.md)
[🇬🇧](README.md)  -  [🇳🇱](README.nl.md)  -  [🇨🇴](README.es-co.md)  -  [🇵🇹](README.pt.md)

# Bestuderen van gecompileerde firmware (gevorderd)

Dit document introduceert het bestuderen van gecompileerde firmware voor educatieve doeleinden.  
Het is bedoeld voor gevorderde leerlingen die willen begrijpen wat er overblijft van een programma wanneer de broncode niet beschikbaar is.

Dit onderwerp is optioneel en niet vereist om de hoofdleertrajecten te volgen.

---

## Wat wordt hier bedoeld met “reverse engineering”

In deze context betekent reverse engineering het analyseren van gecompileerde firmware om structuur, gedrag en beperkingen te begrijpen.  
Het doel is **niet** om broncode te reconstrueren of beveiligingen te omzeilen.

De focus ligt op inzicht in de uitvoering van machine-instructies door een microcontroller.

---

## Wat kan geanalyseerd worden

Leerlingen kunnen onder meer analyseren:

- `.elf`-bestanden, met of zonder debug-symbolen  
- `.hex`-bestanden die ruwe firmware voorstellen  

Deze bestanden kunnen afkomstig zijn van:
- firmware gebouwd binnen deze repository  
- vrij beschikbare voorbeelden  
- eigen projecten van de leerling  

---

## Educatieve doelen

Door gecompileerde firmware te analyseren leren leerlingen:

- hoe code wordt vertaald naar instructies  
- hoe geheugen en uitvoeringsflow zijn opgebouwd  
- wat het effect is van compileroptimalisaties  
- waarom debug-symbolen belangrijk zijn  

---

## Vragen om te onderzoeken

Voorbeelden van onderzoeksvragen:

- Kun je lussen of vertragingen herkennen?  
- Kun je I/O-operaties identificeren?  
- Welke informatie verdwijnt zonder debug-symbolen?  
- Waarom is broncode moeilijk te herleiden uit firmware?  

---

## Hulpmiddelen en aanpak

Verschillende hulpmiddelen kunnen hierbij gebruikt worden, zoals:

- disassemblers  
- tools voor symbolenanalyse  
- simulators  
- eigen analysetools  

De nadruk ligt op **observatie en interpretatie**.

---

## Afbakening en beperkingen

Deze activiteit richt zich op begrip, niet op reconstructie.  
Het terughalen van originele broncode uit firmware is doorgaans niet mogelijk.

Conclusies blijven interpretaties op basis van observatie.

---

## Ethische en juridische noot

Dit onderwerp is uitsluitend bedoeld voor educatief gebruik.  
Werk met eigen firmware of met vrij beschikbare voorbeelden, en respecteer altijd softwarelicenties.

---

## Wanneer dit onderwerp te verkennen

Dit onderwerp is geschikt:

- na het doorlopen van de kerntrajecten  
- bij voldoende kennis van assembly en microcontrollerarchitectuur  
- onder begeleiding in een onderwijscontext  

Deze sectie bestaat om inzicht te verdiepen en nieuwsgierigheid te ondersteunen.

