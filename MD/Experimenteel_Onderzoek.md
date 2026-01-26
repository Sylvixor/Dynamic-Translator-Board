# Experimenteel onderzoek

## DYNAMIC TRANSLATOR BOARD

**SCOTT VAN DER HEIJDEN** (1103349)  
**ARDA KESKIN** (1096673)  
**TIJMEN GROENEVELT** (1103197)  
**OMAR MANSOUR** (1051322)


## Experiment protocol 1 – Stabiliteit en precisie

### Vraagstelling
Wat is de precisie van de Raspberry Pi 4 Model B wanneer deze gedurende 60 minuten onafgebroken code blijft uitvoeren?

### Meetopstelling en instrumenten
De meetopstelling bestaat uit een Raspberry Pi 4 Model B waarop één van de twee bijgeleverde sensoren wordt aangesloten:  
- HM3301 fijnstofsensor  
- SCD4x CO₂-sensor  

De Raspberry Pi is verbonden met een laptop waarop het volgende codebestand is voorbereid:  

Het experiment vindt plaats in een gesloten ruimte met een temperatuur tussen de 18 en 22 °C, met maximaal twee personen aanwezig. Tijdens de test mogen geen andere I²C-apparaten op dezelfde bus zijn aangesloten dan de te testen sensor.

### Te verrichten handelingen
![Referentiefoto aansluiting sensor]

1. De Raspberry Pi wordt uitgeschakeld.
2. De sensor wordt aangesloten volgens de referentiefoto.
3. Er wordt gecontroleerd of het juiste codebestand op de Pi aanwezig is.
4. De Pi wordt gestart en de terminal wordt gemonitord op foutmeldingen.
5. Het systeem draait 60 minuten onafgebroken.
6. Gedurende de test worden detectieresultaten handmatig genoteerd.
7. Na afloop wordt de Pi uitgeschakeld en de sensor losgekoppeld.

### Vast te leggen data
Per cyclus worden de volgende gegevens vastgelegd:
- Gedetecteerd sensortype  
- Uitgelezen data (datatype en waarden)  
- Eventuele foutmeldingen (bijv. *no device*, *address busy*)

### Analyse
De analyse richt zich op:
- **Nauwkeurigheid:** percentage foutloze cycli (minimaal 95%)
- **Robuustheid:** stabiliteit van het systeem tijdens langdurige runtime

Het experiment is geslaagd wanneer de Pi minimaal 57 minuten foutloos functioneert.

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 2 – Detectietijd sensoren

### Vraagstelling
Wat zijn de gemiddelde en maximale tijd die de Raspberry Pi nodig heeft om automatisch te detecteren welke sensor is aangesloten?

### Meetopstelling en instrumenten
De meetopstelling bestaat uit een Raspberry Pi 4 Model B met:
- HM3301 fijnstofsensor  
- SCD4x CO₂-sensor  

De gebruikte software:  
**[VOEG HIER CODEBESTAND NAAM TOE]**

De test wordt uitgevoerd in een gesloten ruimte (18–22 °C). Er mogen geen andere I²C-apparaten aangesloten zijn.

### Te verrichten handelingen
1. Pi uitschakelen en sensor aansluiten.
2. Controleren of het juiste codebestand aanwezig is.
3. Pi starten en detectieresultaten noteren.
4. Tien detectiecycli uitvoeren.
5. Procedure herhalen voor de andere sensor.
6. Uitvoeren van een wisseltest (sensor aansluiten en loskoppelen tijdens runtime).

### Vast te leggen data
Per cyclus:
- Gedetecteerd sensortype  
- Detectietijd (ms)  
- Uitgelezen data  
- Eventuele foutmeldingen  

### Analyse
Beoordeling op:
- **Nauwkeurigheid:** ≥ 95%
- **Snelheid:** mediane detectietijd ≤ 2 s, max. ≤ 5 s
- **Robuustheid:** stabiele werking tijdens wisseltest

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 3 – Meerdere sensoren tijdens runtime

### Vraagstelling
Hoeveel sensoren kan de Raspberry Pi tijdens runtime automatisch detecteren en uitlezen zonder herstart?

### Meetopstelling en instrumenten
- Raspberry Pi 4  
- HM3301 fijnstofsensor  
- SCD4x CO₂-sensor  
- BMP180 barometer  
- MQ131 ozonsensor  

### Te verrichten handelingen
1. Pi starten zonder sensoren.
2. Sensoren één voor één aansluiten.
3. Elke configuratie 2 minuten laten draaien.
4. Terminal monitoren op foutmeldingen.

### Vast te leggen data
- Sensortype  
- Gemeten waarden  
- Eventuele foutmeldingen  

### Analyse
Beoordeling van stabiliteit en betrouwbaarheid bij toenemend aantal sensoren.

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 4 – Detectie via interne pull-up resistors

### Vraagstelling
Kan automatische sensordetectie plaatsvinden via interne pull-up resistors zonder constant polling?

### Analyse
Beoordeling van:
- Detectiesnelheid  
- Stabiliteit bij aansluiten en loskoppelen  
- Afwezigheid van polling  

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 5 – CPU-belasting: polling vs interrupt

### Vraagstelling
Leidt het gebruik van interne pull-up resistors tot efficiënter stroomverbruik dan constant polling?

### Analyse
Vergelijking van CPU-belasting bij:
- Polling  
- Event-driven detectie (interrupts)

### Resultaten
- Meting interne pull-up resistors  
- Meting constante polling  

### Conclusie
De event-driven methode is efficiënter in CPU- en energieverbruik, ondanks vaste overhead van pigpio.

---

## Changelog

| Versie | Wijziging | Datum |
|------|---------|-------|
| 1.0 | Toevoeging experiment 1 t/m 3 | 27-10-2025 |
| 1.1 | Aanpassing experiment 1 | 31-10-2025 |
| 2.0 | Toevoeging experiment 4 | 13-11-2025 |
| 3.0 | Toevoeging experiment 5 | 21-11-2025 |
| 3.1 | Feedbackverwerking + resultaten | 05-12-2025 |
| 4.0 | Uitvoering experiment 5 | 21-01-2026 |
