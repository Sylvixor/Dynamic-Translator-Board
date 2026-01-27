# Cyrb  
# Kapstokdocument  
## Dynamic Translator Board

### Groepsleden
- Scott van der Heijden (1103349)  
- Arda Keskin (1096673)  
- Tijmen Groenevelt (1103349)  
- Omar Mansour (1051322)  

*Datum: 26-1-2026*

---

## Contents
- Inleiding  
- Doel & scope  
- Beslislogboek  
- Projectterminologie  
- Documentstructuur  
- Changelog  

---

## Inleiding
Het beaamde doel van dit document is om de overdracht van het Dynamic Translator Board project zo efficiënt mogelijk te laten verlopen. In dit document zijn verschillende aspecten van de documentatie in behandeling genomen met als doel extra verduidelijking te verschaffen waar nodig. Er wordt onder andere meer duidelijkheid gegeven over het doel van het project en de scope van de werkzaamheden daarbinnen. Het beslissingslogboek noteert de verschillende keuzes die gemaakt zijn tijdens het project en de motivatie daarachter. Bij de projectterminologie worden veelgebruikte woorden en concepten behandeld die niet altijd vanzelfsprekend zijn. Tot slot bekommert de documentstructuur zich over de verschillende documenten die te vinden zijn in de oplever set, hoe deze documenten te gebruiken zijn en wat de toegevoegde waarde van deze documenten is.

---

## Doel & scope
Het doel van het Dynamic Translator Board (DTB) project is tijdens het traject vrijwel altijd hetzelfde gebleven en kwam neer op het volgende: Breid de bestaande software, en optioneel hardware, uit van de DTB zodat deze gebruikt kan worden met een modulair sensorsysteem. Vertaald komt dit erop neer dat de DTB al sensoren kon uitlezen en gebruiken, maar dat het wisselen van deze sensoren niet snel, efficiënt of intuïtief gedaan kon worden door de gebruiker. De bedachte oplossing hiervoor was het implementeren van een concept genaamd modulariteit, het systeem onderverdelen in individueel aanpasbare en functionerende aspecten. Om het project binnen de gegeven tijd succesvol af te kunnen sluiten werd er een scope bepaald, hierbinnen werden de taken bedacht en verdeeld.

Ondanks opdoemende problemen en alternatieve gevonden oplossingen is het doel van project uiteindelijk nooit veranderd, wel is de scope aangepast gebaseerd op de tijd en mogelijkheden binnen het project. De scope van dit project is een combinatie van de uitgevoerde taken en gehaalde requirements en is terug te vinden in het document: “UserStories + Requirements”.

---

## Beslislogboek
Tijdens de loop van het project zijn er meerdere beslissingen gemaakt, ten alle tijden in overleg met het projectteam en waar nodig met de producteigenaar (Cyrb). Hieronder staan een aantal van deze grotere keuzes gedetailleerd en onderbouwd.

- **Verwijdering van een groepslid:**  
Het DTB-project begon met een groepsgrootte van vijf man sterk, echter is dit aantal vermindert naar vier in het verloop van het project. De keuze om het vijfde groepslid achterwege te laten was in overleg met meerdere instanties, waaronder de resterende groepsleden en de betrokken leraren. De motivatie achter deze beslissing was gebaseerd op een gebrek aan aantoonbare contributies aan het project.

- **Gebruik van GitHub als primair documentatieplatform:**  
Er is binnen het project gekozen voor GitHub als voornaamste documentatieplatform, deze keuze is gebaseerd op een aantal voordelen die het platform met zich mee brengt. Het feit dat GitHub open source is sluit goed aan bij de ideologie van Cyrb, dit is iets wat eerder naar voren kwam als een belangrijk aspect van gebruikte software binnen dit project. Ook is GitHub zeer overzichtelijk en een algemeen prettige werkomgeving voor groepsprojecten.

- **Gebruik van exclusief I2C sensoren:**  
Aan het begin van het project waren er een aantal verschillende sensoren in beschouw, waaronder sensoren met verschillende communicatieprotocollen zoals bijvoorbeeld SPI. In de originele scope was het ook de bedoeling dat deze variabele communicatieprotocollen gebruikt konden worden binnen de DTB, echter bleek dit al relatief vroeg een obstakel te zijn waar tegenaan gelopen werd. In overleg met de producteigenaar is er besloten dat rekening houdend met de scope en beschikbare tijd het logischer zou zijn om alleen verder te gaan met I2C gebaseerde sensoren.

- **Gebruik van continuous polling voor I2C adresdetectie.**  
Voor het implementeren van modulariteit werd er gerealiseerd dat er een manier moest zijn om te detecteren wanneer er een sensor ontkoppeld of aangekoppeld werd. Na onderzoek over de mogelijkheden hiervan, terug te vinden in het document “Modulariteitsonderzoek”, kwam er naar boven dat er twee opties rendabel waren. Een continuous polling methode en een internal resistor methode, beide opties konden effectief gebruikt worden voor de doeleinden van dit project. Uiteindelijk is er gekozen voor de eerste optie, het continue pollen voor een adres van een sensor. Deze keuze is gemaakt in overleg met de producteigenaar en is gebaseerd op de huidige hardware limitatie binnen de DTB. Voor verdere uitleg over de gevonden opties, zie het eerder benoemde document: “Modulariteitsonderzoek”.

---

## Projectterminologie
In de documenten van de DTB wordt een groot aantal onderwerpen besproken, hierbij is de mogelijkheid dat er termen en concepten gebruikt worden die niet altijd vanzelfsprekend zijn. Zulke taalkeuzes worden in onderdeel genoteerd en belicht.

- **Dynamic Translator Board (DTB)**  
Verwijst naar het project waar de documentatie voor geschreven is en wordt in de documentatie uitbundig benoemd vanwege dit feit. Met DTB wordt vaak of de daadwerkelijke hardware bedoeld die gebruikt wordt of het project als geheel wat dezelfde naam deelt als de hardware, het verschil hiertussen zal uit de context van de tekst om de term heen duidelijk worden.

- **Modulariteit**  
Het concept modulariteit wordt uitgebreid uitgelegd in het document: “Modulariteitsonderzoek”.

- **Polling**  
Continuous polling is het doorlopend en automatisch verzamelen van informatie door steeds opnieuw dezelfde vraag te stellen aan een systeem, apparaat of doelgroep. Dit gebeurt vaak met korte tussenpozen en wordt in de DTB gebruikt om te detecteren wanneer er een sensor beschikbaar wordt of verdwijnt.

- **Pull up resistor**  
Een pull up resistor is een onderdeel binnen het stroomcircuit dat gebruikt kan worden om de bekende status van een signaal te garanderen. Binnen dit project had dat gebruikt kunnen worden om specifieke sensoren aan specifieke signaalsterktes te kunnen koppelen.

---

## Documentstructuur
De bijgeleverde oplever set bestaat uit een verzameling documenten die elk een bijdrage leveren aan het eindproduct. Het grootste deel van de schriftelijke documentatie heeft een samenvatting aan het begin voor makkelijke verwijzing naar belangrijke informatie, hieronder echter worden de documenten allemaal nog een keer uitgelegd. De documentatie is verdeeld in de volgende mappen:

- **Schriftelijke documentatie**
  - Testen
  - Onderzoeken
  - Planningen
- **Visuele documentatie**
  - FotosEnVideos
  - Ontwerpen
  - Presentaties
- **Software**
  - Codebestanden

De volledige verzameling documentatie wordt hieronder verder uitgelegd voor extra verduidelijking.

### Schriftelijke documentatie:
- **Testen**
  - **Testrapport:** Het testrapport bevat een aantal testen dusdanig opgebouwd en uitgevoerd voor een makkelijk reproduceerbaar effect. De opbouw detailleert onder andere de meetopstelling, teststappen en gewenste omstandigheden. Het doel van dit document is om de testen uit te leggen en de resultaten te onderbouwen, daarnaast kan het document later gebruikt worden om testen te herhalen na eventuele veranderingen binnen het project.

- **Onderzoeken**
  - **Experimenteel onderzoek:** Het experimenteel onderzoek is gebruikt als gidslijn voor het verzamelen van informatie over het project via experimenten. Een aantal experimenten staan gedetailleerd in het onderzoek en dienen als onderbouwing van vergaarde informatie en verduidelijking van de methode tot vergaring. Een voorbeeld uit dit document is het experimenteel protocol: “Is de Raspberry Pi in staat automatische sensordetectie uit te voeren op basis van het gebruik van de internal pull up resistors, waarbij er geen gebruik gemaakt hoeft te worden van constant polling?”
  - **Gebruikersonderzoek:** Het gebruikersonderzoek stelt de context op van een onderzoek wat uitgevoerd wordt binnen een doelgroep gebruikers. Dit onderzoek focust op de ervaring van potentiële gebruikers van de DTB met het opgeleverde materiaal. Het document is makkelijk uit te breiden voor het huidige project of te reproduceren voor een ander project. Er wordt uitgelegd wat de gekozen doelgroepen zijn, welke vragen er gesteld worden en uiteraard wat het resultaat is.
  - **Modulariteitsonderzoek:** Dit onderzoek dient als een literatuuronderzoek, met als doel het concept van modulariteit verder te begrijpen en een begin te maken aan de toepassing hiervan op het project.
  - **Probleemomschrijving:** Een kort document die de achterliggende context van het project onderbouwt. Het bedrijf achter het DTB project, de context van het probleem dat de DTB moet oplossen en een aantal onderzoeksvragen komen hier naar voren.
  - **Requirements analyse:** Gebaseerd op de wensen van de producteigenaar is er een document opgesteld met als doel een overzicht te creëren van de verschillende eisen binnen het DTB project. Dit document noteert die eisen en verdiept de achterliggende redenering en prioritering hiervan.
  - **Risicoanalyse:** Het doel van deze analyse is om potentiële risico’s te identificeren binnen het DTB project, hierbij wordt er gekeken naar zowel risico’s binnen bijvoorbeeld de planning als de daadwerkelijke hardware/software ontwikkelingen. Het document is kleur gecodeerd en hanteert simpele maar effectieve meetstaven voor de verschillende behandelde risico’s.

- **Planningen**
  - **Userstories + Requirements:** Dit bestand is een uitbreiding op het eerder benoemde bestand “Requirements analyse”, het detailleert wederom de gestelde eisen en voegt hier een aantal essentiële dingen aan toe. Ten eerste worden er user stories toegevoegd aan de eisen, deze motiveren de redenering achter waarom de eis bestaat en zijn vaak afkomstig vanuit het oogpunt van een gebruiker. Daarnaast wordt hier ook elke eis onderverdeeld in taken, deze taken representeren het daadwerkelijke werk dat verricht moest worden.

### Visuele documentatie:
- **FotosEnVideos**
  - **BMPdemo:** Een korte video van de resultaten van een test over de BMP, deze toont aan succesvol aangesloten te zijn aan de Raspberry PI.
  - **Demovideo:** Een video met commentaar, geeft de volledige werking van de DTB weer en onderbouwt daarmee hoe er aan de eisen van het project voldaan is.
  - **Onderdelen:** Een foto met de verschillende onderdelen van de DTB en de gebruikte benamingen daarvoor.

- **Ontwerpen**
  - **Architectuurontwerp(begin):** Een architectuurontwerp dat gemaakt was aan het begin van het project met als doel het beter begrijpen van de bestaande structuur.
  - **Architectuurontwerp(eind):** Een architectuurontwerp dat aan het eind van het project gemaakt is, gebaseerd op de veranderingen die tijdens het project aangebracht zijn.
  - **Flowchart(begin):** Een flowchart van de al bestaande code bij oorspronkelijke aanlevering van het project. Deze flowchart was gemaakt om een beter overzicht te krijgen van de code en de logica daarachter.
  - **Flowchart(eind):** Een flowchart gemaakt tijdens het project, gebaseerd op de verwachtingen van hoe de code zou veranderen en waar een deel van de code uiteindelijk op gebaseerd is.
  - **Presentaties:** Alle gemaakte sprintreview presentaties, inclusief de 50% presentatie.

### Software:
- **Codebestanden**
  - **Readme:** Een uitleg van de gemaakte veranderingen binnen de code en waar deze gevonden kunnen worden.
  - -

---

## Changelog

| Versie | Wat | Wanneer |
|------|-----|---------|
| 1.0 | Document aangemaakt | 27-01-2026 |
