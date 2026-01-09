Testplan

Dynamic Translator Board​

Scott van der Heijden, Arda Keskin, Tijmen Groenevelt, Omar Mansour

10-10-2025

Contents

[Inleiding 3](#_Toc214627476)

[Test 1: Hot-swap sensor (plug-and-play) 4](#_Toc214627477)

[Test 2: Automatische detectie bij opstart (cold-plug) 5](#_Toc214627478)

[Test 3: Dashboard: juiste eenheden en labels 6](#_Toc214627479)

[Test 4: Waardencontrole en geldige dataweergave 7](#_Toc214627480)

[Test 5: Communicatie via I²C 8](#_Toc214627481)

[Test 6: CO₂- en deeltjesmetingen gelijktijdig 9](#_Toc214627482)

[Test 7: Sleep-modus en energieverbruik 10](#_Toc214627483)

[Changelog 12](#_Toc214627484)

# Inleiding

<br/>Dit document beschrijft de testen die zijn uitgevoerd op het Dynamic Translator Board.  
Het hoofddoel van dit verslag is om aan te tonen dat het systeem voldoet aan de gestelde requirements en acceptatiecriteria van het project.  
Daarnaast zorgt dit document ervoor dat de testen reproduceerbaar zijn, zodat toekomstige ontwikkelaars of testers dezelfde stappen kunnen volgen om de resultaten te verifiëren.

De testen zijn opgesteld op basis van de functionele en niet-functionele requirements die horen bij het project Dynamic Translator Board, onderdeel van Project 5/6 .

# Test 1: Hot-swap sensor (plug-and-play)

## Vraagstelling

Is het Dynamic Translator Board in staat om automatisch een nieuwe sensor te herkennen wanneer een aangesloten sensor wordt losgekoppeld en vervangen, zonder dat het systeem opnieuw moet worden opgestart?

Meetopstelling en meetinstrumenten  
De testopstelling bestaat uit een Pi 4 microcontroller verbonden met het Dynamic Translator Board waarop sensoren worden aangesloten.  
<br/>Meetinstrumenten:

- Raspberry Pi 4 model B
- HM3301 sensor
- SCD4x - CO₂-sensor (I²C)
- Laptop met de code

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts twee personen aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- Upload de software met automatische detectie naar de Pi.
- Sluit de SCD4x CO₂-sensor aan op de PCB.
- Start het systeem en controleer of de sensor correct wordt herkend.
- Noteer de gemeten waarden (ppm CO₂).
- Koppel de SCD4x los terwijl het systeem actief blijft.
- Sluit de HM3301 deeltjes-sensor aan op dezelfde connector.
- Observeer het gedrag van het systeem en noteer of de nieuwe sensor automatisch wordt herkend.
- Herhaal de procedure twee keer om de betrouwbaarheid te bevestigen.

## Vast te leggen data

- Sensor-ID of naam die door het systeem wordt herkend.
- Tijd (s) tussen het loskoppelen van de eerste sensor en het detecteren van de nieuwe sensor.
- Terminalmelding of log-uitvoer bij detectie.
- Meetwaarden van beide sensoren (CO₂ in ppm, PM in µg/m³).
- Aantal succesvolle herkennende pogingen (van 3 tests).

Analyse

Beschrijf of de waardes overeenkomen, of dat het te veel uitwijkt van elkaar.  
Leid hieruit af wat het resultaat van de test is.  
<br/>

# Test 2: Automatische detectie bij opstart (cold-plug)

## Vraagstelling

Worden de aangesloten sensoren automatisch herkend door het Dynamic Translator Board wanneer het systeem wordt ingeschakeld, zonder dat handmatige configuratie of herstart nodig is?  
<br/>Meetopstelling en meetinstrumenten

De opstelling bestaat uit het Dynamic Translator Board met een Pi 4 microcontroller, waarop één sensor (CO₂ of PM) is aangesloten vóór het inschakelen.  
Het systeem is verbonden met een laptop voor datalogging en observatie via de terminal.  
<br/>Gebruikte sensoren:

- SCD4x - CO₂-sensor (I²C)
- HM3301 - deeltjes-sensor (I²C)

Meetinstrumenten:

- Pi 4 met firmware voor automatische detectie
- Laptop met terminal
- Multimeter (voor spanningcontrole)

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts één persoon aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- Sluit de SCD4x-sensor aan op het Dynamic Translator.
- Observeer de terminal, noteer of de sensor automatisch wordt gedetecteerd.
- Herhaal de test met de HM3301-sensor.
- Herhaal beide tests in totaal twee keer voor betrouwbaarheid.

## Vast te leggen data

- Herkende sensortype (SCD4x of HM3301)
- Aantal keren dat automatische detectie succesvol was (van 3 pogingen per sensor)
- Log-melding of statusbericht bij detectie
- Eerste gemeten waarde (CO₂ in ppm of PM in µg/m³)

Analyse

- Controleer of het systeem consistent de juiste sensor identificeert bij elke herstart.
- Controleer dat de data onmiddellijk correct wordt weergegeven, zonder handmatige herconfiguratie.
- Evalueer of er fouten, vertragingen of verkeerde sensorlabels zijn verschenen.

Resultaten:

21-11-2025:

# Test 3: Dashboard: juiste eenheden en labels

## Vraagstelling

Toont het dashboard de gemeten waarden duidelijk en correct, met de juiste eenheden en heldere labels/legenda voor CO₂- en deeltjesmetingen?  
<br/>Meetopstelling en meetinstrumenten

Dynamic Translator Board met Raspberry Pi 4, aangesloten op:

- SCD4x - CO₂-sensor (I²C)
- HM3301 - deeltjes-sensor (I²C)

Meetinstrumenten:

- Dashboard

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts twee personen aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- Start het systeem met SCD4x + HM3301 aangesloten.
- Open dashboard en noteer labels, eenheden en grafieknamen.
- Varieer CO₂ kort (30-60 s uitademen richting sensor op ~30 cm).
- Varieer PM kort (fijn stof door papier/kaart te schuren naast sensor).
- Herhaal stappen 3-4 3 keer met korte pauzes.

## Vast te leggen data

- Labelnamen zoals getoond (bijv. _CO₂_, _PM2.5_).
- Eenheden: CO₂ in ppm, PM in µg/m³.
- Timestamps van metingen.
- Waardereeks tijdens variaties.
- Eventuele waarschuwingen/validaties.

Analyse

- Label/eenheid-check: komen label en eenheid exact overeen met specificatie (CO₂→ppm, PM→µg/m³)?
- Leesbaarheid: zijn grafiek/tiles duidelijk (sensornaam, recente waarde, timestamp)?
- Respons op variatie: stijgt CO₂ zichtbaar bij uitademen en stijgt PM zichtbaar bij stof?
- Consistentie: vergelijk 3 herhalingen.

<br/>

# Test 4: Waardencontrole en geldige dataweergave

## Vraagstelling

Geeft het Dynamic Translator Board een duidelijke foutmelding wanneer een sensor niet correct is aangesloten, losraakt tijdens gebruik, of een onbekend type is?  
<br/>Meetopstelling en meetinstrumenten

Het experiment gebruikt een Pi 4 met het Dynamic Translator Board.  
De firmware bevat foutafhandeling voor sensordetectie en communicatie.  
Tijdens de test worden zowel goedgekeurde als onjuiste of defecte sensoren aangesloten.  
<br/>Gebruikte componenten:

- SCD4x - CO₂-sensor (I²C)
- HM3301 - deeltjes-sensor (I²C)

Meetinstrumenten:

- Terminal voor foutmeldingen.

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts één persoon aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- Start het systeem met SCD4x aangesloten → controleer correcte detectie.
- Koppel de sensor los tijdens actieve meting.
- Observeer de seriële monitor en terminal → noteer melding of foutcode.
- Sluit daarna de sensor opnieuw aan → controleer herstel.
- Herhaal de stappen met de HM3301-sensor.
- Sluit vervolgens de dummy-sensor aan (onbekend type of fout ID).
- Observeer of het systeem een foutmelding of waarschuwing toont.
- Herhaal de volledige testreeks twee keer voor betrouwbaarheid.

## Vast te leggen data

- Type aangesloten sensor (of dummy)
- Moment (timestamp) van loskoppeling en foutdetectie
- Foutmeldingstekst of -code (bijv. _Sensor not detected_, _I²C timeout_)
- Tijd tussen loskoppeling en foutmelding (in seconden)
- Hersteltijd na opnieuw aansluiten
- Aantal succesvolle foutmeldingen (van 3 pogingen)

Analyse

- Foutrespons-tijd: bereken gemiddelde tijd tussen sensorverlies en foutmelding.
- Herstelgedrag: controleer of het systeem correct herstelt zodra de sensor terug is.
- Consistentie: vergelijk 3 herhalingen; beoordeel of foutmeldingen stabiel en eenduidig zijn.
- Onbekende sensor: controleer of er géén crash of verkeerde sensorherkenning optreedt.
- Interface-controle: bekijk of de terminalmelding duidelijk is voor de gebruiker (kleur, tekst, leesbaarheid).

# Test 5: Communicatie via I²C

## Vraagstelling

Kan het Dynamic Translator Board betrouwbaar communiceren met verschillende sensoren via I²C en worden de gemeten waarden correct uitgelezen en weergegeven op het terminal?  
<br/>Meetopstelling en meetinstrumenten

Het experiment wordt uitgevoerd op een Pi 4 in combinatie met het Dynamic Translator Board.  
Aan elk communicatieprotocol wordt één sensor of testmodule gekoppeld om de werking te controleren.  
<br/>Gebruikte sensoren:

- SCD4x - CO₂-sensor (I²C)
- HM3301 - deeltjes-sensor (I²C)

Meetinstrumenten:

- Pi 4
- Laptop met terminal

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts één persoon aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- - Sluit SCD4x aan op I²C-bus.
    - Start systeem en observeer data in terminal.
    - Controleer dat waarden elke 2 s worden bijgewerkt.

## Vast te leggen data

- Herkend protocol per test (I²C)
- Gemeten waarden (CO₂ in ppm, PM in µg/m³, analoge spanning in V)
- Verbindingsstatus (success/fail)
- Eventuele foutmeldingen

Analyse

- Vergelijking per protocol: controleer of elk protocol meetgegevens correct verzendt en ontvangt.
- Timinganalyse: bevestig dat datarates overeenkomen met verwachte frequentie (I²C 100-400 kHz, 9600-115200 bps).
- Nauwkeurigheid: bereken afwijking tussen analoge spanning (ADC) en gemeten digitale waarde.
- Robuustheid: beoordeel of communicatie herstelt na herstart of hot-swap.
- Stabiliteit: check of geen fouten optreden bij langere metingen (>60 s).

# Test 6: CO₂- en deeltjesmetingen gelijktijdig

## Vraagstelling

Kan het Dynamic Translator Board de CO₂-sensor (SCD4x) en de deeltjessensor (HM3301) tegelijkertijd uitlezen en de meetwaarden correct en onafhankelijk van elkaar naar het terminal sturen, zonder dataverlies of vertraging?  
<br/>Meetopstelling en meetinstrumenten

Het experiment gebruikt een Raspberry Pi 4 op het Dynamic Translator Board.  
Beide sensoren worden tegelijk aangesloten:

- SCD4x - CO₂-sensor (I²C)
- HM3301 - PM-sensor (I²C)
- De sensoren worden tijdens de test actief gehouden terwijl het terminal live meetwaarden toont.

Meetinstrumenten:

- Terminal
- Laptop
- Multimeter (controle voedingsspanning)

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts één persoon aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- Sluit beide sensoren tegelijk aan op het Dynamic Translator Board.
- Start de Raspberry Pi 4 en open het terminal of de seriële monitor.
- Observeer dat beide sensoren automatisch worden herkend (type + protocol).
- Laat het systeem gedurende 5 minuten metingen uitvoeren.
- CO₂-test: adem gedurende 30 s in de richting van de sensor om stijgende waarden te simuleren.
- PM-test: creëer licht stof (door papier te schuren) om PM-waarde te laten stijgen.
- Herhaal de gehele procedure twee keer voor betrouwbaarheid.

## Vast te leggen data

- Herkende sensortypes en protocollen
- CO₂-waarden (ppm)
- PM-waarden (µg/m³)
- Eventuele foutmeldingen of gemiste samples

Analyse

- Synchronisatiecontrole: vergelijk CO₂- en PM-metingen per tijdstempel.
- Databetrouwbaarheid: tel het aantal ontvangen samples; bereken eventuele missende percentages.
- Reactiviteit: stijgen CO₂- en PM-waarden wanneer respectievelijk adem/stof wordt toegevoegd?
- Stabiliteit: controleer of de PCB niet herstart of fouten genereert bij gelijktijdig uitlezen.
- Visuele controle: terminal toont beide sensoren met correcte labels en eenheden.

# 

Test 7: Sleep-modus en energieverbruik

## Vraagstelling

Kan het Dynamic Translator Board ongebruikte sensoren of subsystemen automatisch in sleep-modus zetten om energie te besparen, en is het verschil in stroomverbruik meetbaar?  
<br/>Meetopstelling en meetinstrumenten

Het experiment gebruikt de standaardopstelling van het Dynamic Translator Board met Raspberry Pi 4, waarop twee sensoren zijn aangesloten (CO₂ en PM).  
Het systeem is verbonden met een USB-voeding via een stroommeetinstrument (USB current meter of multimeter in serie).  
De firmware bevat een functie die niet-actieve sensoren uitschakelt of in slaapstand zet.  

Gebruikte middelen:

- Raspberry Pi 4 + Dynamic Translator Board
- SCD4x CO₂-sensor (I²C)
- HM3301 PM-sensor (/I²C)
- Laptop
- Firmware met sleepMode() functie

Meetinstrumenten:

- USB current meter met mA-nauwkeurigheid
- Seriële monitor voor statusmeldingen ("Sleep active", "Wake up")
- Stopwatch of loggingtimer

## Externe voorwaarden

- De test is uitgevoerd in een gesloten ruimte bij kamertemperatuur (tussen 18-22 °C).
- Luchtdruk en luchtstroom zijn constant gehouden.
- Slechts één persoon aanwezig tijdens de test om externe invloed (adem, beweging) te minimaliseren.

Te verrichten handelingen

- Start het systeem met beide sensoren actief.
- Laat het systeem 2 minuten draaien in actieve modus.
- Noteer de stroomafname in mA.
- Activeer daarna de sleep-modus via code (automatisch of handmatig via knop/commando).
- Wacht 30 seconden en noteer opnieuw de stroomafname.
- Herhaal de meting twee keer voor betrouwbaarheid.
- Controleer in de seriële monitor of de status "Sleep active" verschijnt.
- Schakel het systeem terug naar actieve modus en observeer of de stroom toeneemt ("Wake up").

## Vast te leggen data

| Meting | Modus | Stroomverbruik (mA) | Tijdstip | Statusmelding | Opmerking |
| --- | --- | --- | --- | --- | --- |
| 1   | Actief | ... | ... | ... | ... |
| 2   | Sleep | ... | ... | ... | ... |
| 3   | Actief | ... | ... | ... | ... |

- Gemeten spanningsniveau (V)
- Eventuele foutmeldingen of vertragingen bij terugkeer naar actieve modus

Analyse

- Gemiddelde berekenen: bereken het gemiddelde stroomverbruik voor zowel actieve als slaapmodus.
- Percentage besparing: bereken energiebesparing met:
- Controle functionaliteit: controleer dat het systeem in slaapstand geen metingen uitvoert.
- Herstelgedrag: controleer dat het systeem correct terugkeert naar actieve modus.
- Stabiliteit: bevestig dat er geen crash of reset optreedt tijdens de overgang.

# Changelog

| Wijzigingen | Versie | Datum |     |
| --- | --- | --- |     |
| Eerste versie test-plan | 1.0 | 10-10-2025 |
| Een test verwijdert en communicatieprotocollen bijgewerkt n.a.v. verandering scope | 2.0 | 21-11-2025 |