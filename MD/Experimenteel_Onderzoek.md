# Experimenteel onderzoek  
## Dynamic Translator Board

**Scott van der Heijden** (1103349) – **Arda Keskin** (1096673) –  
**Tijmen Groenevelt** (1103197) – **Omar Mansour** (1051322)

---

## Experiment protocol 1

### Vraagstelling
De vraagstelling van dit experiment luidt: Wat is de precisie van de raspberry Pi 4 model B wanneer deze voor 60 minuten onafgebroken code blijft runnen.

### Meetopstelling en instrumenten
De meetopstelling bestaat uit een Raspberry Pi 4 Model B waarop één van de twee bijgeleverde sensoren wordt aangesloten. De bijgeleverde sensoren zijn de HM3301 fijnstofsensor en een SCD4x CO₂-sensor. De Pi wordt verbonden met een laptop waar het volgende codebestand op voorbereid staat: *VOEG HIER NAAM BESTAND TOE*. Deze software bevat code voor het runnen van de pi met aangesloten sensoren.

Tijdens het experiment wordt de sensor continue getest. Er wordt gewerkt in een gesloten ruimte met een temperatuur tussen de 18 en 22 graden Celsius, waarin maximaal twee personen aanwezig zijn. Dit om invloed van omgevingstemperatuur en luchtkwaliteit zoveel mogelijk te beperken. Tijdens de softwaretest mogen er geen andere I²C-apparaten op dezelfde bus aangesloten zijn of worden dan de te testen sensor.

### Te verrichten handelingen
*VOEG HIER REFERENTIEFOTO TOE*

Het experiment start met de voorbereiding. De Raspberry Pi wordt uitgeschakeld en de sensor, zoals aangegeven op de referentiefoto, wordt aangesloten. Vervolgens wordt gecontroleerd of het eerder benoemde codebestand op de Pi aanwezig is. Als hier twijfel over bestaat, wordt de code opnieuw geüpload.

Vervolgens wordt de test uitgevoerd. De Pi wordt aangezet en de terminal wordt in de gaten gehouden om te controleren of er foutmeldingen verschijnen. Zodra de code wordt uitgevoerd, worden de resultaten van de detectie handmatig genoteerd door de observator. Dit omvat het gedetecteerde sensortype en de uitgelezen data. Het systeem draait 60 minuten zonder onderbreking achter elkaar. Daarna wordt de Pi uitgeschakeld en de sensor losgekoppeld.

### Vast te leggen data
Tijdens het experiment worden per cyclus de volgende gegevens vastgelegd:
- het gedetecteerde sensortype  
- de datatype en waarden  
- eventuele foutmeldingen zoals “no device” of “address busy”

### Analyse
De analyse richt zich op twee aspecten: nauwkeurigheid en robuustheid. De nauwkeurigheid wordt berekend als het percentage van de cycli waarin de sensor correct functioneert. Een nauwkeurigheid van minimaal 95% wordt als acceptabel beschouwd, in verhouding tot de 60 minuten cyclus betekent dit dat de pi minimaal 57 minuten foutloos moet werken. Als misdetecties optreden, worden door de observator de terminalmeldingen bekeken om te bepalen wat de oorzaak is. Vervolgens wordt nagegaan of er mogelijk een fout in de code aanwezig is of dat het bijvoorbeeld een hardware probleem zou kunnen zijn.

Het experiment wordt als geslaagd beschouwd wanneer de sensor voldoet aan de gestelde eis voor nauwkeurigheid en het systeem geen verdere fouten vertoont tijdens het uitvoeren van de wisseltest.

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 2

### Vraagstelling
De vraagstelling van dit experiment luidt: Wat zijn de gemiddelde en maximale tijd die het de Raspberry Pi kost om automatisch te detecteren welke sensor wordt aangesloten, zonder handmatige configuratie?

### Meetopstelling en instrumenten
De meetopstelling bestaat uit een Raspberry Pi 4 Model B waarop één van de twee bijgeleverde sensoren wordt aangesloten. De gebruikte sensoren zijn de HM3301 fijnstofsensor en een SCD4x CO₂-sensor. De Pi wordt verbonden met een laptop waarop de volgende software beschikbaar staat: *VOEG HIER CODEBESTAND NAAM*.

Deze software bevat code voor automatische sensorherkenning.

Tijdens het experiment worden de sensoren om de beurt op dezelfde aansluiting getest. Er wordt gewerkt in een gesloten ruimte met een temperatuur tussen de 18 en 22 graden Celsius, waarin maximaal twee personen aanwezig zijn. Dit om invloed van omgevingstemperatuur en luchtkwaliteit zoveel mogelijk te beperken. Tijdens de detectietesten mogen er geen andere I²C-apparaten op dezelfde bus aangesloten zijn dan de te testen sensor.

### Te verrichten handelingen
Het experiment start met de voorbereiding. De Raspberry Pi wordt uitgeschakeld en de eerste sensor, zoals aangegeven op de referentiefoto, wordt aangesloten. Vervolgens wordt gecontroleerd of het juiste codebestand op de Pi aanwezig is. Als hier twijfel over bestaat, wordt de code opnieuw geüpload.

Vervolgens wordt de detectietest uitgevoerd. De Pi wordt aangezet en de terminal wordt in de gaten gehouden om te controleren of er foutmeldingen verschijnen. Zodra de code wordt uitgevoerd, worden de resultaten van de detectie genoteerd. Dit omvat het gedetecteerde sensortype, de detectietijd in milliseconden en de uitgelezen data. Het systeem draait tien detectiecycli achter elkaar. Daarna wordt de Pi uitgeschakeld.

Dezelfde procedure wordt vervolgens herhaald met de andere sensor, zodat beide sensoren afzonderlijk getest worden.

Tot slot wordt een wisseltest uitgevoerd. Hierbij start de Pi zonder dat er een sensor is aangesloten. Na ongeveer vijf seconden wordt eerst de HM3301-sensor aangesloten, waarna de Pi vijf detectiecycli uitvoert. Vervolgens wordt deze sensor losgekoppeld en draait de Pi opnieuw vijf cycli zonder sensor. Daarna wordt de SCD4x CO₂-sensor aangesloten voor nogmaals vijf cycli. Dit simuleert het verwisselen van sensoren tijdens runtime en controleert of de Pi correct blijft detecteren onder wisselende omstandigheden.

### Vast te leggen data
Tijdens het experiment worden per cyclus de volgende gegevens vastgelegd:
- het gedetecteerde sensortype  
- de detectietijd (in milliseconden)  
- de datatype en waarden  
- eventuele foutmeldingen zoals “no device” of “address busy”

### Analyse
De analyse richt zich op drie aspecten: nauwkeurigheid, snelheid en robuustheid. De nauwkeurigheid wordt berekend als het percentage van de cycli waarin het juiste sensortype correct werd herkend. Een nauwkeurigheid van minimaal 95% wordt als acceptabel beschouwd. De snelheid wordt bepaald door de mediane detectietijd te berekenen. Deze mag niet hoger zijn dan 2 seconden, en de maximale detectietijd mag niet boven de 5 seconden uitkomen.

Daarnaast wordt gecontroleerd of de code tijdens de wisseltest stabiel blijft draaien, zonder crash of foutmelding. Als misdetecties optreden, worden de terminalmeldingen bekeken om te bepalen wat de oorzaak is. Vervolgens wordt nagegaan of er mogelijk een fout in de code aanwezig is of dat een regel in het detectiebestand moet worden aangepast.

Het experiment wordt als geslaagd beschouwd wanneer beide sensoren voldoen aan de gestelde eisen voor nauwkeurigheid en snelheid en het systeem geen fouten vertoont tijdens het uitvoeren van de wisseltest.

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 3

### Vraagstelling
In dit derde experiment wordt onderzocht hoeveel sensoren de Raspberry Pi in staat is om tijdens runtime automatisch te detecteren en te runnen, zonder dat een herstart nodig is.

### Meetopstelling en instrumenten
De meetopstelling bestaat uit een Raspberry Pi 4, de HM3301 fijnstofsensor, de SCD4x CO₂-sensor, de BMP180 Barometer en de MQ131 Ozon sensor. Alle sensoren worden binnen handbereik geplaatst zodat deze tijdens het experiment gemakkelijk te hanteren zijn. De Pi is verbonden met een laptop waarop het volgende codebestand klaar staat: *VOEG NAAM CODEBESTAND HIER*.

Het experiment vindt plaats in een gesloten ruimte met een temperatuur tussen de 18 en 22 graden Celsius. Er wordt gebruikgemaakt van een daarvoor geschikte connector waarop sensoren kunnen worden aangesloten zonder dat de Pi hoeft te worden uitgeschakeld. Er mag geen raam of deur openstaan om plotselinge luchtveranderingen te voorkomen, aangezien deze de stabiliteit van de meetwaarden zouden kunnen beïnvloeden.

### Te verrichten handelingen
De Pi wordt gestart met geen sensoren aangesloten. De terminal wordt gecontroleerd op eventuele foutmeldingen om te bevestigen dat de opstart correct is verlopen. Vervolgens wordt de HM3301 sensor aangesloten en gedurende twee minuten uitgelezen.

Daarna wordt de volgende sensor aangesloten, de SCD4x CO₂-sensor. De verwachting is dat de Raspberry Pi binnen vijf seconden de nieuwe sensor herkent, de juiste driver laadt en actuele uitleeswaarden toont. De combinatie van deze twee sensoren wordt wederom gedurende twee minuten uitgelezen.

Herhaal dit proces met de twee resterende sensoren, de volgorde hiervan is eerst de BMP180 Barometer en daarna de MQ131 Ozon sensor.

De terminal wordt continue in de gaten gehouden om de validiteit van data te bevestigen en eventuele foutmeldingen worden genoteerd. Als de vierde sensor succesvol is aangesloten en gedurende twee minuten uitgelezen is wordt de pi uitgeschakeld.

### Vast te leggen data
Tijdens het experiment worden per sample de volgende gegevens geregistreerd:
- het sensortype (HM3301, CO₂, etc.)  
- de gemeten waarden per sensor (zoals fijnstofconcentratie of CO₂-niveau)  
- eventuele foutmeldingen die in de terminal verschijnen  

### Analyse
De analyse richt zich op de betrouwbaarheid van het aansluitproces en de stabiliteit van de metingen.

Het doel is om de stabiliteit van het aansluitproces te beoordelen en daarbij te bepalen of sensor correct uitgelezen blijven worden bij een hoger dataverkeer van meerdere sensoren tegelijkertijd.

Het experiment wordt als geslaagd beschouwd wanneer de sensorwaarden correct uitgelezen blijven worden bij vier aangesloten sensoren gedurende de twee minuten runtime.

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 4

### Vraagstelling
De vraagstelling voor dit experiment luid als volgt: Is de Raspberry Pi in staat automatische sensordetectie uit te voeren op basis van het gebruik van de internal pull up resistors, waarbij er geen gebruik gemaakt hoeft te worden van constant polling?

### Meetopstelling en instrumenten
De meetopstelling bestaat uit een Raspberry Pi 4 Model B waarop één van de beschikbare sensoren wordt aangesloten. De gebruikte sensoren zijn de HM3301 fijnstofsensor, SCD4x CO₂-sensor, de BMP180 Barometer en de MQ131 Ozon sensor. De Pi wordt verbonden met een laptop waarop de correcte software staat, deze software bevat code voor het runnen van de pi met aangesloten sensoren.

Er wordt gewerkt in een gesloten ruimte met een temperatuur tussen de 18 en 22 graden Celsius, waarin maximaal twee personen aanwezig zijn. Dit om invloed van omgevingstemperatuur en luchtkwaliteit zoveel mogelijk te beperken. Tijdens de softwaretest mogen er geen andere I²C-apparaten op dezelfde bus aangesloten zijn dan de te testen sensor.

### Te verrichten handelingen
De Pi wordt gestart zonder een aangesloten sensor. De terminal wordt gecontroleerd op eventuele foutmeldingen om te bevestigen dat de opstart correct is verlopen. Vervolgens wordt de gekozen sensor aangesloten op de Raspberry Pi. De terminal wordt gecontroleerd op eventuele fouten en voornamelijk op een verandering in het gedrag van de pi, noteer deze eventuele veranderingen voor latere analyse.

De verwachting is dat wanneer de sensor aangesloten wordt dat de Pi dit doormiddel van de interne pull resistoren meet en de benodigde code runt om de sensor uit te gaan lezen. Belangrijk is dat de pi geen gebruikt maakt van polling in de tijd tussen aansluiten en niet aangesloten zijn.

Na het experiment wordt de sensor losgekoppeld en vervolgens de Pi uitgezet.

### Vast te leggen data
Tijdens het experiment worden de volgende gegevens geregistreerd:
- het gedetecteerde sensortype (HM3301, CO₂, BMP280 of MQ131)  
- de gemeten waarden per sensor  
- eventuele foutmeldingen die in de terminal verschijnen  

### Analyse
De analyse richt zich op de snelheid en betrouwbaarheid van het experiment. Hierbij wordt gekeken naar hoe snel de Pi in staat is de sensor te detecteren en identificeren, aangeduid in tijdseenheden.

Daarnaast wordt ook de stabiliteit gemeten van het experiment, waarbij via de terminal gecontroleerd wordt of de Pi stabiel blijft bij het verbinden en het loshalen van de sensor. Aangeduid via eventuele error handling berichten in de terminal.

### Resultaten
*In te vullen*

### Conclusie
*In te vullen*

---

## Experiment protocol 5

### Vraagstelling
De vraagstelling van experiment protocol 5 luidt als volgt: Leid het gebruik van interne resistoren voor het detecteren van sensoren tot een efficiënter stroomverbruik t.o.v. constant polling. Efficiënt wordt in deze context gemeten met behulp van de CPU-belasting tijdens het runnen van de verschillende codes.

### Meetopstelling en instrumenten
De meetopstelling begint met het aansluiten van de Raspberry PI 4 model B op een laptop of computer met de twee te runnen code bestanden. De eerste is voor het uitlezen met behulp van constant polling en de ander is met behulp van de interne pull up resistoren. Vervolgens wordt een van de volgende sensoren aangesloten op de PI: HM3301 fijnstofsensor, SCD4x CO₂-sensor en BMP280 sensor. Belangrijk is dat de gekozen sensor voor de rest van het onderzoek hetzelfde blijft.

Er wordt gewerkt in een gesloten ruimte met een temperatuur tussen de 18 en 22 graden Celsius, waarin maximaal twee personen aanwezig zijn. Dit om invloed van omgevingstemperatuur en luchtkwaliteit zoveel mogelijk te beperken. Tijdens de softwaretest mogen er geen andere I²C-apparaten op dezelfde bus aangesloten zijn dan de te testen sensor.

### Te verrichten handelingen
De Pi wordt gestart met een aangesloten sensor. De terminal wordt gecontroleerd op eventuele foutmeldingen om te bevestigen dat de opstart correct is verlopen. Vervolgens wordt het eerste codebestand geüpload, dit codebestand kan een van beide zijn. De terminal wordt gecontroleerd op eventuele fouten en voornamelijk op een verandering in het gedrag van de pi, noteer deze eventuele veranderingen voor latere analyse.

Terwijl de sensor aangesloten is wordt de terminal uitgelezen, hieruit is de belangrijkste data de CPU-belasting. De sensor wordt minimaal 60 seconden uitgelezen om eventuele plotse veranderingen te waarnemen.

Nadat de tijd verstreken is wordt de pi stopgezet en wordt het volgende codebestand klaargezet. Wanneer het volgende codebestand is geüpload op de pi worden de vorige stappen herhaald.

Na het experiment wordt de sensor losgekoppeld en vervolgens de Pi uitgezet.

### Vast te leggen data
Tijdens het experiment wordt alleen de CPU-belasting genoteerd in percentages. Ook worden eventuele foutmeldingen die in de terminal verschijnen vastgelegd.

### Analyse
De analyse richt zich op het vergelijken van twee methoden voor sensordetectie op de Raspberry Pi 4: constante polling en event-driven detectie met behulp van interne pull-up resistoren. Het doel is om vast te stellen welke methode efficiënter is, gemeten aan de hand van het CPU-verbruik tijdens het uitvoeren van de bijbehorende software.

Beide methoden zijn getest onder identieke omstandigheden. Hierbij is dezelfde sensor gebruikt, is de meetduur gelijk gehouden en zijn omgevingsfactoren zoals temperatuur constant gebleven. Hierdoor kunnen verschillen in CPU-belasting direct worden toegeschreven aan de gebruikte detectiemethode en niet aan externe invloeden.

Bij de pollingmethode controleert de Raspberry Pi continu of er een sensor aanwezig is. Dit resulteert in een constante belasting van de CPU, ook wanneer er geen verandering in de sensorstatus optreedt. De CPU blijft hierdoor actief, wat leidt tot een minder efficiënte inzet van systeemresources.

Bij gebruik van interne pull-up resistoren wordt de detectie event-driven uitgevoerd. In dit geval reageert het systeem alleen wanneer er daadwerkelijk een verandering plaatsvindt, zoals het aansluiten of loskoppelen van een sensor. Hierdoor worden onnodige CPU-cycli vermeden en blijft de CPU-belasting lager en stabieler.

Het experiment wordt als geslaagd beschouwd wanneer de gemeten CPU-belasting bij gebruik van interne pull-up resistoren aantoonbaar lager is dan bij constante polling, zonder dat dit leidt tot instabiliteit of foutmeldingen tijdens het uitvoeren van de software.

### Resultaten
Uitgevoerde meting bij gebruik van interne pull resistoren.  
Uitgevoerde meting bij gebruik van constante polling.

### Conclusie
Er zijn twee methoden vergeleken om een sensor te detecteren op een Raspberry Pi 4: de polling en event-driven (interrupt) via GPIO met de pigpio bibliotheek. Beide metingen zijn uitgevoerd over dezelfde duur van 15 seconden met pidstat. Het CPU-verbruik daalt niet tot nul omdat pigpio intern gebruikmaakt van continue sampling en DMA, wat een vaste achtergrondbelasting veroorzaakt. Desondanks vermindert de event-driven (interrupt) methode de extra belasting van polling en is zij efficiënter in CPU en energieverbruik. Voor een volledig zuivere vergelijking zou de bibliotheek overhead buiten beschouwing moeten worden gelaten, pigpio blijft echter noodzakelijk vanwege betrouwbare GPIO-interrupts en nauwkeurige timing op de Raspberry Pi 4.

---

## Changelog

| Versie | Wat | Wanneer |
|------|-----|--------|
| 1.0 | Toevoeging onderzoek 1 t/m 3 | 27/10/2025 |
| 1.1 | Aanpassing onderzoek 1 n.a.v. sprint presentatie | 31/10/2025 |
| 2.0 | Toevoeging onderzoek 4 | 13/11/2025 |
| 3.0 | Toevoeging onderzoek 5 | 21/11/2025 |
| 3.1 | Aanpassing onderzoeken n.a.v. feedback | 05/12/2025 |
| 4.0 | Uitvoering experiment 5 | 21/01/2026 |
