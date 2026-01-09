| Cyrb |
| --- |
| Requirementsanalyse |
| Dynamic Translator Board |

13-11-2025

Scott Van Der Heijden (1103349), Tijmen Groenevelt (1058554)  
Arda Keskin (1096673) ,Omar Mansour (1051322)  

**1\. Inleiding**

Dit document beschrijft en analyseert de eisen (requirements) die van toepassing zijn op het Dynamic Translator Board-project. Het projectdoel is het realiseren van een modulair systeem dat verschillende sensoren kan uitlezen, automatisch kan herkennen en foutmeldingen kan genereren wanneer er problemen optreden. De hardware bestaat uit een Raspberry Pi 4 in combinatie met een printplaat (PCB) waarop diverse sensormodules aangesloten kunnen worden.

Deze analyse legt een duidelijke basis voor de vervolgfases (ontwerp, implementatie en testen) en fungeert als referentie voor toekomstige uitbreidingen.

**2\. Functionele requirements**

Functionele requirements beschrijven wat het systeem moet doen - de zichtbare functies en het gedrag dat de gebruiker ervaart.

| **Nr** | **Requirement** | **Beschrijving** | **Prioriteit** | **Toelichting** |
| --- | --- | --- | --- | --- |
| 1   | Sensoren moeten eenvoudig verwisselbaar zijn (hot-swappable). | De hardware is modulair ontworpen. Sensoren kunnen worden gewisseld zonder het systeem uit te schakelen. | Must have | Belangrijk voor onderhoud en flexibiliteit. |
| 2   | De vergaarde informatie is duidelijk en nuttig voor de gebruiker. | Sensordata wordt begrijpelijk gepresenteerd (dashboard, juiste eenheden en context). | Must have | Zorgt dat ook niet-technische gebruikers de data begrijpen. |
| 3   | Ondersteuning  <br>voor (I²C) communicatieprotocol. | Het systeem ondersteunt  <br>(I²C) communicatieprotocol. | Must have | Zorgt voor stabiele communicatie tussen sensoren en microcontroller. |
| 4   | Foutmeldingen bij niet-herkende of verkeerd aangesloten sensoren. | Detectie van fouten met duidelijke melding aan de gebruiker/logs. | Must have | Verhoogt betrouwbaarheid en gebruikerservaring. |
| 5   | Verplichte sensoren: CO₂-sensor en deeltjes-sensor (PM). | Prototype wordt minimaal getest met CO₂ en fijnstof (PM). | Must have | Kern van het projectdoel: luchtkwaliteit meten. |
| 6   | Ondersteuning voor meerdere communicatieprotocollen (SPI/UART/GPIO/ADC). | Het systeem biedt uitbreidbare ondersteuning voor extra communicatieprotocollen zoals SPI, UART, GPIO en ADC. | Could have | Verbetert de uitbreidbaarheid en compatibiliteit met verschillende modules. |
| 7   | Energiebeheer via sleepfunctie. | Niet-gebruikte sensoren/modules kunnen tijdelijk worden uitgeschakeld. | Could have | Belangrijk voor energie-efficiëntie, niet cruciaal voor basisfunctionaliteit. |

**3\. Niet-functionele requirements**

Niet-functionele requirements beschrijven kwaliteitseisen en randvoorwaarden, zoals onderhoudbaarheid, documentatie en ontwikkelproces.

| **Nr** | **Requirement** | **Beschrijving** | **Type** | **Toelichting** |
| --- | --- | --- | --- | --- |
| 8   | Versiebeheer met GitHub en changelogs. | Alle aanpassingen aan code en PCB worden bijgehouden met commits en changelogs. | Onderhoudbaarheid | Zorgt voor transparantie en samenwerking. |
| 9   | Actuele documentatie. | Wijzigingen in code of hardware worden direct verwerkt in de documentatie. | Onderhoudbaarheid | Essentieel voor traceerbaarheid en overdraagbaarheid. |
| 10  | PCB-ontwerp in KiCad. | Alle PCB-wijzigingen worden uitsluitend in KiCad uitgevoerd. | Ontwikkelstandaard | Garandeert consistentie met bestaande ontwerpen. |

**4\. Analyse en motivatie**

De requirements zijn gebaseerd op:

- De projectomschrijving van Cyrb (geluid- en luchtkwaliteitsmeting met privacy-by-design).
- De gebruikersbehoefte aan een modulair, uitbreidbaar sensorsysteem.
- Technische vereisten vanuit de PCB- en Raspberry Pi 4-architectuur.

De nadruk ligt op betrouwbaarheid, modulariteit, uitbreidbaarheid en gebruiksvriendelijkheid. Daarnaast zijn onderhoudbaarheid en versiebeheer cruciaal in verband met teamwerk en een open benadering van het ontwikkelproces.

**5\. MoSCoW-prioritering**

| **Prioriteit** | **Beschrijving** | **Toegepaste requirements** |
| --- | --- | --- |
| Must have | Essentieel voor een werkend prototype | 1, 2, 3, 4, 5 |
| Should have | Belangrijk voor verbetering (kwaliteitsborging) | 8, 9, 10 |
| Could have | Toegevoegde waarde, optioneel | 6,7 |

**  
6\. Conclusie**

De requirementsanalyse vormt de basis voor de verdere ontwikkeling van het Dynamic Translator Board. Met deze eisen kan het team gericht werken aan een betrouwbaar, uitbreidbaar en energiezuinig systeem dat verschillende sensoren ondersteunt en begrijpelijke data levert. Het gebruik van GitHub voor versiebeheer en KiCad voor PCB-ontwerp waarborgt een professioneel en herhaalbaar ontwikkelproces. Deze requirementsanalyse dient als referentie voor ontwerp, implementatie en validatie en vormt de basis voor toekomstige uitbreidingen.  
<br/>

# Changelog

| **Wijzigingen** | **Versie** | **Datum** |
| --- | --- | --- |
| Eerste versie requirementsanalyse | 1.0 | 27-10-2025 |
| Het systeem ondersteunt voortaan uitsluitend sensoren met een I²C-verbinding. | 1.1 | 31-10-2025 |
| Titel aangepast naar een beschrijvende titel. Namen toegevoegd bij auteurs. | 1.2 | 08-12-2025 |

<br/>