# Onderzoeksverslag Modulariteit  
## Dynamic Translator Board

**Scott van der Heijden** (1103349)  
**Arda Keskin** (1096673)  
**Tijmen Groenevelt** (1103349)  
**Omar Mansour** (1051322)  

*Datum: 10-10-2025*

---

## Inhoud
1. Samenvatting  
2. Inleiding  
3. Theoretisch kader modulariteit  
4. Methode toepassing modulariteit  
5. Resultaten implementatie project  
6. Conclusie  
7. Literatuurlijst  
8. Changelog  

---

## Samenvatting
Dit document richt zich op het concept modulariteit en onderzoekt, vanuit verschillende invalshoeken, of modulariteit geschikt is voor het Dynamic Translator Board (DTB) project. Modulariteit wordt eerst benaderd vanuit een theoretisch perspectief, waarna wordt gekeken naar bestaande toepassingen binnen de techniek. Hierbij komen bedrijven zoals Turck naar voren, die modulariteit toepassen in hardwarecomponenten van grotere machines om onderhoud en aanpasbaarheid te verbeteren.

De onderzoeksresultaten worden vervolgens vergeleken met de mogelijkheden binnen het DTB-project. Hieruit volgen twee mogelijke implementatiestrategieën. De eerste optie maakt gebruik van pull-up resistors om de status van aangesloten sensoren te bepalen, wat echter extra hardware binnen de behuizing vereist. De tweede, meer toegankelijke optie is het gebruik van interne I²C-adressen voor het identificeren van sensoren. Deze methode wordt als meest geschikt beschouwd vanwege de schaalbaarheid en digitale betrouwbaarheid.

---

## Inleiding
Het project Dynamic Translator Board heeft als doel het mogelijk maken om verschillende sensoren te gebruiken zonder dat de gebruiker over technische kennis hoeft te beschikken. De sensoren moeten volgens een *plug-and-play* principe aangesloten kunnen worden, waarbij het magnetisch opklikken van een sensor voldoende is om deze operationeel te maken.

Om dit te realiseren is een bepaald niveau van modulariteit binnen het systeem noodzakelijk. Dit leidt tot de centrale onderzoeksvraag:  
**Hoe kan modulariteit effectief worden geïmplementeerd binnen de context van het Dynamic Translator Board project?**

Om deze vraag te beantwoorden zijn de volgende deelvragen opgesteld:
- Hoe wordt modulariteit theoretisch gedefinieerd en hoe is dit toepasbaar op het project?
- Waar wordt modulariteit in moderne technologie toegepast en is dit relevant voor het DTB-project?
- Welke vormen van modulariteit zijn mogelijk en welke methode sluit het best aan bij dit project?

---

## Theoretisch kader modulariteit
Modulariteit wordt gedefinieerd als:  

> “De mate waarin een systeem of computerprogramma is opgebouwd uit afzonderlijke eenheden (modules), die elk een eigen functie vervullen. Een modulair systeem kan worden aangepast of uitgebreid met minimale aanpassingen aan het geheel.” [1]

Deze definitie sluit nauw aan bij de doelstelling van het DTB-project. Om een *plug-and-play* ervaring te realiseren moeten sensoren onafhankelijk van elkaar kunnen worden aangesloten, losgekoppeld en uitgelezen, zonder dat wijzigingen in de software nodig zijn door de gebruiker.

---

## Methode toepassing modulariteit
Hoewel modulair gebruik van sensoren nog beperkt wordt toegepast, zijn er wel bestaande voorbeelden binnen de technologie. Zo heeft Insyte Technology [2] een framework ontwikkeld waarop verschillende sensoren aangesloten kunnen worden die onderling communiceren en centraal uitgelezen worden. Dit framework wordt onder andere toegepast bij fijnstofmetingen, geurdetectie en bodemvochtmetingen.

Een ander voorbeeld is het bedrijf Turck [3], dat zich richt op modulariteit binnen industriële machines. Door modulaire ontwerpen wordt onderhoud vereenvoudigd en kunnen machines flexibeler gecombineerd worden.

Deze voorbeelden tonen aan dat modulariteit vooral via doordacht PCB-ontwerp wordt gerealiseerd, waarbij rekening wordt gehouden met communicatieprotocollen, microcontrollers en de fysieke gebruiksomgeving. Factoren zoals beschikbare ruimte en efficiëntie spelen hierbij een belangrijke rol.

---

## Resultaten implementatie project
Uit het onderzoek komen twee mogelijke methoden naar voren om modulariteit binnen het Dynamic Translator Board te implementeren.

De eerste methode is een analoge oplossing waarbij per sensor een unieke weerstand wordt toegevoegd. Via een ADC kan deze weerstand worden uitgelezen, waardoor het systeem kan bepalen welke sensor is aangesloten. Deze methode vereist extra hardware en is gevoelig voor meetafwijkingen.

De tweede methode is een digitale oplossing op basis van I²C-adresdetectie [4]. Hierbij worden aangesloten sensoren automatisch herkend door hun unieke I²C-adressen. Deze methode is minder foutgevoelig en beter schaalbaar. Een aandachtspunt hierbij is dat niet alle sensoren standaard I²C gebruiken en dat adresconflicten kunnen optreden.

---

## Conclusie
Uit dit onderzoek blijkt dat modulariteit een haalbare en waardevolle ontwerpkeuze is voor het Dynamic Translator Board. Modulariteit maakt een *plug-and-play* gebruikerservaring mogelijk en sluit direct aan bij de doelstelling om het systeem toegankelijk en gebruiksvriendelijk te maken.

Hoewel een analoge identificatiemethode met weerstanden technisch uitvoerbaar is, brengt deze extra hardware-eisen en potentiële meetfouten met zich mee. De digitale I²C-gebaseerde methode biedt een schaalbaardere en toekomstbestendige oplossing, mits er zorgvuldig wordt omgegaan met adresbeheer en sensorselectie.

Op basis van de onderzoeksresultaten wordt geconcludeerd dat de I²C-gebaseerde aanpak het meest geschikt is voor het Dynamic Translator Board project.

---

## Literatuurlijst
1. Nederlandse Encyclopedie – Modulariteit  
2. Insyte Technology  
3. Turck  
4. Adafruit – I²C address detection  

---

## Changelog

| Datum | Wijziging |
|------|---------|
| 10-10-2025 | Document aangemaakt, start onderzoek |
| 27-10-2025 | Implementatie uitgewerkt |
