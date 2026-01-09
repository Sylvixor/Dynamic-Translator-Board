| Cyrb |
| --- |
| Risicoanalyse |
| Dynamic Translator Board |

13-11-2025

Scott Van Der Heijden (1103349), Tijmen Groenevelt (1058554)  
Arda Keskin (1096673) ,Omar Mansour (1051322)

# Risicoanalyse (Dynamic Translator Board)

Het doel van deze risicoanalyse is om mogelijke risico's te identificeren die de ontwikkeling, functionaliteit of planning van het Dynamic Translator Board-project kunnen beïnvloeden. De risico's worden beoordeeld op kans (1-10) en impact (1-10), waarbij de risicoscore berekend wordt met de formule: Risico = Kans × Impact.

## Schaal voor Kans en Impact (1-10)

De onderstaande tabel geeft de beschrijvende schaal weer die wordt gebruikt om de kans en impact te beoordelen:  
<br/>1-2 = Zeer laag (nauwelijks mogelijk, minimale impact)  
3-4 = Laag / Beperkt (onwaarschijnlijk, kleine vertraging of lichte schade)  
5-6 = Middel / Merkbaar (kan voorkomen, merkbare gevolgen op planning of kwaliteit)  
7-8 = Hoog (waarschijnlijk, grote vertraging of kwaliteitsverlies)  
9-10 = Zeer hoog (vrijwel zeker, projectdoelen in gevaar)

## Risicomatrix

| Nr  | Risico | Kans (1-10) | Impact (1-10) | Risicoscore (K×I) | Beheersmaatregelen |
| --- | --- | --- | --- | --- | --- |
| 1   | Hot-swap mechanisme veroorzaakt kortsluiting of beschadiging bij sensorwissel | 6   | 9   | 54  | Beveiligingsweerstanden en detectielogica toevoegen, testen met dummy-modules, duidelijke gebruikersinstructie. |
| 2   | Communicatieproblemen tussen PCB en Raspberry Pi (I²C) | 7   | 8   | 56  | Gebruik van pull-up/pull-down weerstanden controleren; protocollen testen met meerdere sensoren. |
| 3   | Foutdetectie werkt niet goed - systeem herkent defecte sensor niet | 7   | 8   | 56  | Unit-tests en integratietests uitvoeren, foutafhandeling simuleren. |
| 4   | Onvoldoende versiebeheer of documentatie op GitHub | 6   | 6   | 36  | Teamregels opstellen voor commits en changelogs; automatische back-ups. |
| 5   | Verkeerde weergave van sensorwaarden of eenheden | 6   | 8   | 48  | Validatie met bekende referentiewaarden, gebruikersinterface testen, kalibratiehandleiding toevoegen. |
| 6   | Energiebeheer werkt niet - systeem verbruikt te veel stroom | 3   | 6   | 18  | Sleepmodus testen met verschillende sensoren, stroomverbruik loggen, energie-efficiëntie verbeteren in code. |
| 7   | Teamleden vallen uit of er zijn communicatieproblemen binnen het projectteam | 6   | 6   | 36  | Taken verdelen via Discord, wekelijkse voortgangsmeetings. |
| 8   | Software-bug veroorzaakt crash of verkeerde metingen | 7   | 8   | 56  | Debugging, versiebeheer met rollback-mogelijkheid. |

Kleurcodering Risico's

| Risicoscore | Kleur | Betekenis |
| --- | --- | --- |
| 50 - 100 | Rood | Hoogl risico |
| 25 - 49 | Oranje | Middel risico |
| 1 - 24 | Groen | Laag risico |

## 

<br/>Risico-evaluatie (topprioriteiten)

Hoog risico (≥50): Hot-swap schade, Communicatieproblemen, Foutdetectie, Software-bugs.  
Aanpak: Technische mitigatie via hardware-beveiliging, robuuste softwaretests, simulaties.  
<br/>Middel risico (20-49): GitHub/documentatie, PCB, Weergave van sensorwaarden, Teamcommunicatie.  
Aanpak: Planning, teamafspraken en teststrategie versterken.  
<br/>Laag risico (<20): Energiebeheer.  
Aanpak: Monitoren tijdens testfase.

## Calamiteitenplan

Indien zich een kritisch risico voordoet:  
1\. Projectteam rapporteert incident in Discord.  
2\. Analyse door verantwoordelijke leden (hardware/software).  
3\. Tijdelijke oplossing of rollback toepassen.  
4\. Evaluatie en update van risicoanalyse voor toekomstige iteraties.  
Relatie tussen risico's en projectsucces

De geïdentificeerde risico's hebben directe invloed op de succesfactoren van het project:

- Gebruiksvriendelijkheid**:**  
    Risico's zoals foutdetectie (nr. 3) en verkeerde weergave van sensorwaarden (nr. 5) kunnen leiden tot onbetrouwbare informatie voor de gebruiker en verminderen de gebruiksvriendelijkheid.
- Modulariteit**:**  
    Hot-swap risico's (nr. 1) en communicatieproblemen via I²C (nr. 2) kunnen de verwisselbaarheid van sensormodules beperken, wat de modulariteit van het systeem onder druk zet.
- Betrouwbaarheid**:**  
    Software-bugs (nr. 8) en energiebeheer (nr. 6) beïnvloeden direct de stabiliteit en bedrijfszekerheid van het systeem.

Door deze risico's actief te beheersen, wordt een stabiel, gebruiksvriendelijk en modulair eindproduct gewaarborgd.

## Conclusie

Deze risicoanalyse geeft een gestructureerd overzicht van de belangrijkste technische en organisatorische risico's binnen het Dynamic Translator Board-project. Door het gebruik van kans-, impact- en kleurcodering zijn prioriteiten in één oogopslag zichtbaar. Daarnaast is de samenhang tussen risico's en projectsuccesfactoren zoals gebruiksvriendelijkheid, modulariteit en betrouwbaarheid duidelijk gelegd. Hiermee vormt dit document een praktisch sturingsinstrument voor het projectteam.

Changelog

| **Wat:** | **Versie:** | **Wanneer:** |
| --- | --- | --- |
| Eerste versie. | 1.0 | 31-10-2025 |
| Aanpassingen kans en impact bij nr. 1 | 1.1 | 13-11-2025 |
| Toevoeging kleurcodering en relatie met projectsucces | 1.2 | 08-12-2025 |