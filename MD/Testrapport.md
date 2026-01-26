# Testplan  
## Dynamic Translator Board

**Scott van der Heijden** (1103349)  
**Arda Keskin** (1096673)  
**Tijmen Groenevelt** (1103349)  
**Omar Mansour** (1051322)  

*Datum: 10-10-2025*

---

## Inhoud
1. Inleiding  
2. Test 1: Hot-swap sensor (plug-and-play)  
3. Test 2: Automatische detectie bij opstart (cold-plug)  
4. Test 3: Waardencontrole en geldige dataweergave  
5. Test 4: Communicatie via I²C  
6. Test 5: CO₂- en deeltjesmetingen gelijktijdig  
7. Changelog  

---

## Inleiding
Dit document beschrijft de testen die zijn uitgevoerd op het Dynamic Translator Board. Het hoofddoel van dit verslag is om aan te tonen dat het systeem voldoet aan de gestelde requirements en acceptatiecriteria van het project.

Daarnaast zorgt dit document ervoor dat de testen reproduceerbaar zijn, zodat toekomstige ontwikkelaars of testers dezelfde stappen kunnen volgen om de resultaten te verifiëren. De testen zijn opgesteld op basis van de functionele en niet-functionele requirements van Project 5/6.

---

## Test 1: Hot-swap sensor (plug-and-play)

### Vraagstelling
Is het Dynamic Translator Board in staat om automatisch een nieuwe sensor te herkennen wanneer een aangesloten sensor wordt losgekoppeld en vervangen, zonder dat het systeem opnieuw moet worden opgestart?

### Meetopstelling en meetinstrumenten
**Meetinstrumenten:**
- Raspberry Pi 4 Model B  
- HM3301 deeltjes-sensor  
- SCD4x CO₂-sensor (I²C)  
- Laptop met testsoftware  

### Externe voorwaarden
- Gesloten ruimte (18–22 °C)  
- Constante luchtdruk en luchtstroom  
- Maximaal twee personen aanwezig  

### Te verrichten handelingen
1. Upload software met automatische detectie naar de Pi.
2. Sluit de SCD4x CO₂-sensor aan.
3. Start het systeem en controleer detectie.
4. Noteer gemeten waarden.
5. Koppel de sensor los tijdens runtime.
6. Sluit de HM3301-sensor aan.
7. Observeer automatische detectie.
8. Herhaal de procedure tweemaal.

### Vast te leggen data
- Gedetecteerde sensor-ID  
- Detectietijd (s)  
- Terminalmeldingen  
- Meetwaarden (CO₂ ppm, PM µg/m³)  
- Aantal succesvolle detecties  

### Resultaten
25-12-2025: Beide sensoren werden consequent herkend na loskoppelen en opnieuw aansluiten. Het systeem gaf duidelijke meldingen bij ontkoppeling en hervatte automatisch het uitlezen.

### Conclusie
De test is succesvol: hot-swapping werkt stabiel en betrouwbaar.

---

## Test 2: Automatische detectie bij opstart (cold-plug)

### Vraagstelling
Worden aangesloten sensoren automatisch herkend bij het opstarten van het systeem?

### Meetopstelling
- Raspberry Pi 4 met DTB  
- SCD4x en HM3301 sensor  

### Te verrichten handelingen
1. Sluit sensor aan vóór opstart.
2. Start systeem.
3. Observeer detectie.
4. Herhaal voor beide sensoren.

### Vast te leggen data
- Herkend sensortype  
- Aantal succesvolle detecties  
- Eerste meetwaarde  

### Resultaten
25-12-2025: Beide sensoren werden bij opstart direct correct herkend zonder fouten.

### Conclusie
Cold-plug detectie functioneert correct.

---

## Test 3: Waardencontrole en geldige dataweergave

### Vraagstelling
Geeft het systeem duidelijke foutmeldingen bij sensorproblemen?

### Te verrichten handelingen
1. Start systeem met aangesloten sensor.
2. Koppel sensor los tijdens meting.
3. Observeer foutmelding.
4. Sluit sensor opnieuw aan.
5. Test met onbekende sensor.

### Vast te leggen data
- Type sensor  
- Foutmelding  
- Detectietijd  
- Hersteltijd  

### Resultaten
25-12-2025: Het systeem gaf duidelijke visuele en tekstuele feedback zonder crashes.

### Conclusie
Foutafhandeling is duidelijk, stabiel en gebruikersvriendelijk.

---

## Test 4: Communicatie via I²C

### Vraagstelling
Is de I²C-communicatie betrouwbaar en stabiel?

### Te verrichten handelingen
- Sluit sensor aan op I²C
- Observeer terminal-output
- Controleer update-interval (2 s)

### Resultaten
25-12-2025: Sensorwaarden werden correct en stabiel uitgelezen.

### Conclusie
I²C-communicatie werkt betrouwbaar.

---

## Test 5: CO₂- en deeltjesmetingen gelijktijdig

### Vraagstelling
Kunnen beide sensoren tegelijk worden uitgelezen zonder dataverlies?

### Te verrichten handelingen
1. Sluit beide sensoren tegelijk aan.
2. Start systeem.
3. Simuleer CO₂- en PM-verhoging.
4. Observeer meetwaarden.

### Vast te leggen data
- CO₂-waarden (ppm)  
- PM-waarden (µg/m³)  
- Eventuele fouten  

### Resultaten
25-12-2025: Beide sensoren functioneerden gelijktijdig zonder verlies van data.

### Conclusie
Gelijktijdige metingen verlopen stabiel en correct.

---

## Changelog

| Versie | Datum | Wijziging |
|------|------|----------|
| 1.0 | 10-10-2025 | Eerste versie testplan |
| 2.0 | 21-11-2025 | Scope aangepast |
| 3.0 | 25-12-2025 | Testen uitgevoerd en resultaten toegevoegd |
