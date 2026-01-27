# Onderzoeksverslag Modulariteit  
## Dynamic Translator Board

---

### Groepsleden
- Scott van der Heijden (1103349)  
- Arda Keskin (1096673)  
- Tijmen Groenevelt (1103349)  
- Omar Mansour (1051322)  

*Datum: 10-10-2025*

---

## Inhoud
- Samenvatting  
- Inleiding  
- Theoretisch kader modulariteit  
- Methode toepassing modulariteit  
- Resultaten implementatie project  
- Conclusie  
- Literatuurlijst  
- Changelog  

---

## Samenvatting
Dit document focust op het onderwerp modulariteit en beaamt doormiddel van verschillende belichtingskaders te concluderen of modulariteit bruikbaar is voor het DTB (Dynamic Translator Board) project. Modulariteit wordt beschouwd vanuit een theoretisch standpunt; de definitie. Vervolgens wordt er gekeken naar de huidige implementatie van modulariteit in techniek, hierbij komt naar voren dat bedrijven zoals Turck modulariteit al implementeren in de hardware delen van grotere machines voor makkelijk onderhoud en aanpasbaarheid.

Achteraf worden de resultaten van het onderzoek vergeleken met de mogelijkheden binnen het DTB project, hieruit wordt geconcludeerd dat er twee opties mogelijk zijn qua implementatie. De eerste optie zou het gebruik zijn van pull up resistoren om te meten wat de status van sensoren is, dit brengt echter de complicatie met zich mee dat er extra hardware benodigd is binnen de behuizing. De andere meer toegankelijkere optie is het gebruik maken van interne I2C-adressen voor communicatie van sensor identiteiten, deze optie wordt uiteindelijk ook geconcludeerd het best geschikt te zijn voor het project door onder andere de schaalbaarheid van deze implementatie.

---

## Inleiding
Het project Dynamic Translator Board gaat om het gebruik kunnen maken van verschillende sensoren, zonder dat de gebruiker van het apparaat technische kennis nodig heeft.

Deze sensoren moeten met een “plug-and-play” principe aangesloten kunnen worden. Het magnetisch opklikken van een sensor is alles wat een gebruiker zou moeten doen om het werkend te krijgen. Verder is alles wat er vereist wordt van de gebruiker het bekijken van de informatie die de sensoren versturen.

Om dit te bereiken, moet er een bepaald niveau van modulariteit in het apparaat zitten. De vraag die hierbij komt opzetten is: Hoe valt dit te implementeren in de context van dit project?

Om het antwoord daar op te vinden moet er eerst antwoord komen op de volgende onderzoeksvragen:
- Hoe wordt modulariteit theoretisch gedefinieerd en hoe is dit van toepassing op het project?
- Waar wordt modulariteit in moderne technologie al gebruikt en heeft dit een relevante toepassing voor ons project?
- Op welke manieren wordt modulariteit zoal toegepast en welke methode is voor het project het meest van toepassing?

---

## Theoretisch kader modulariteit
De directe definitie van modulariteit is als volgt:

> “De mate waarin een systeem of een computerprogramma is opgebouwd uit afzonderlijke eenheden (modules), die elk een eigen functie vervullen. Een modulair systeem of programma kan worden aangepast of uitgebreid met minimale aanpassingen aan het totaal.” [1]

Uit deze definitie volgt de vraag wat het toevoegen van modulariteit bijdraagt aan dit project?

Zoals in de introductie al benoemd was, moet er een “plug-and-play” principe ontstaan. Dit principe is dus verbonden aan modulariteit, omdat de sensoren onafhankelijk van elkaar aangesloten, losgekoppeld en uitgelezen moeten kunnen worden. Dit moet kunnen gebeuren zonder dat er aan het achterliggende programma een aanpassing gemaakt hoeft te worden door de gebruiker.

---

## Methode toepassing modulariteit
Het principe van modulair gebruik van sensoren wordt nog niet veel toegepast, maar er zijn zeker voorbeelden te vinden van algemene toepassing modulariteit binnen moderne technologie.

Zo is er bijvoorbeeld het bedrijf Insyte Technology [2]. Zij hebben een framework ontworpen waar verschillende sensoren op aangesloten kunnen worden. Door gebruik van dit framework kunnen de aangesloten sensoren met elkaar communiceren en ook daarnaast ook uitgelezen worden.

Deze framework hebben ze al toegepast op verschillende situaties, zoals bij fijnstofmetingen op bouwterreinen, geurdetectie bij waterzuiveringssystemen en bodemvochtdetectie voor groenprojecten. Dit zijn een aantal voorbeelden binnen de grote hoeveelheid toepassingsmogelijkheden van het framework ontwerp.

Een ander bedrijf die zich bezighoud met modulariteit is Turck [3]. Zij zijn voornamelijk bezig met het modulair maken van grotere machines, zodat hierin aanpassingen gemaakt kunnen worden wanneer dit nodig is. Ook is onderhoud hiermee makkelijker, aangezien er bij problemen makkelijker geïsoleerd kan worden waar in de machine het probleem terug te vinden is. Ook gebruiken ze het om verschillende machines makkelijker te combineren en samen te laten werken.

Deze voorbeelden laat zien dat modulariteit wel al voorkomt in vergelijkbare contexten, maar dit zijn vaak relatief kleine bedrijven die zich hier mee bezig houden. Daarnaast wordt het concept modulariteit ook alleen nog in de industrie toegepast tot nu toe, waarbij het project van Cyrb de nadruk op commerciëel gebruik wil leggen.

Modulariteit wordt klaarblijkelijk over het algemeen toegepast door het juist ontwerpen van een PCB (printplaat) voor de toepassende doeleinden van een apparaat. Op deze printplaat wordt rekening gehouden met de mogelijke communicatieprotocollen van de sensoren en van de microcontroller waar het uiteindelijk aan verbonden wordt.

Ook wordt er tijdens het ontwerpen gekeken naar de gebruiksomgeving. Dit heeft te maken met de behuizing die om de PCB heen gemaakt wordt en samen met de sensoren die er op aangesloten zitten moet kunnen passen. Als het in een omgeving met gelimiteerde ruimte komt, moet het ontwerp natuurlijk hier dusdanig op aangepast worden. Wanneer er geen eisen aan omvang hangen, kan er bijvoorbeeld meer naar efficiëntie op andere gebieden gekeken worden tijdens het ontwerpen.

---

## Resultaten implementatie project
Er blijken uit het onderzoek een aantal mogelijkheden te zijn om modulariteit te implementeren binnen het dynamic translator board project.

De eerste optie is het gebruik van verschillende weerstanden per sensor. Dit is een analoge methode. Deze methode vereist dat er een extra weerstand tussen twee pinnen wordt toegevoegd. Deze weerstand kan vervolgens door middel van een ADC (Analog to Digital Converter) herkent worden, waardoor het programma kan detecteren welke sensor er aanwezig is.

Deze methode vereist een extra weerstand per sensor. Ook moeten alle sensoren correct kunnen werken met de ADC, gezien deze wel eerst in moet lezen wat er verbonden wordt. Ook is de kans op kleine meetfouten groter, omdat het een analoge oplossing is.

De tweede optie is het gebruik van interne I2C adressen. Dit is een volledig digitale methode en elimineert dus de mogelijkheid op analoge meetfouten. [4]

Voor deze methode is het belangrijk dat alle sensoren via I2C communiceren. De gebruikte sensoren hebben allemaal een apart adres, en deze kan gescanned worden door de microcontroller wanneer de sensor aangesloten wordt. Hierdoor is het mogelijk om te detecteren welke sensoren er aanwezig zouden zijn, en op basis van deze informatie de juiste code te implementeren.

De uitdaging hier in ligt dat niet alle sensoren standaard I2C gebruiken als communicatiemethode. Ook kan het zijn dat bepaalde sensoren vaste adressen hebben die mogelijk onderling overlappen, hier moet in de ontwikkelingsfase dus goed op gelet worden omdat dit anders voor problemen in de detectie kan zorgen.

---

## Conclusie
Uit dit onderzoek blijkt dat modulariteit een essentiële en haalbare ontwerpkeuze is voor het Dynamic Translator Board. De theoretische verkenning laat zien dat modulariteit geschikt is om een plug-and-play gebruikerservaring te realiseren, waarbij sensoren onafhankelijk van elkaar kunnen worden aangesloten en uitgelezen zonder dat extra technische kennis of handmatige software-aanpassingen vereist zijn. Dit sluit direct aan bij de doelstelling van het project om toegankelijkheid en gebruiksgemak te verbeteren.

De analyse van bestaande toepassingen in de industrie toont aan dat modulariteit elders al succesvol wordt ingezet, met name door middel van PCB-ontwerpen en gestandaardiseerde communicatieprotocollen. Hoewel deze toepassingen zich vooral richten op industriële omgevingen, bieden zij inzichten die vertaald kunnen worden naar een meer commercieel en gebruikersgericht product zoals het Dynamic Translator Board.

Binnen het project zijn twee concrete implementatiemethoden onderzocht: een analoge identificatiemethode met behulp van weerstanden en een digitale methode op basis van I2C-adresdetectie. De analoge methode is relatief eenvoudig, maar brengt wel nadelen met zich mee zoals extra hardwarevereisten. De digitale I2C-methode biedt een schaalbaardere oplossing, mits er zorgvuldig wordt omgegaan met adresconflicten en de keuze van sensoren.

Concluderend kan worden gesteld dat modulariteit technisch goed implementeerbaar is binnen het Dynamic Translator Board en een duidelijke meerwaarde biedt voor zowel de gebruiker als het ontwikkelproces. Op basis van de resultaten heeft voor dit project de I2C-gebaseerde aanpak de voorkeur, omdat deze het beste aansluit bij de gewenste uitbreidbaarheid en toekomstbestendigheid van het project en zo de extra hardwareeisen van de resistoren methode vermeden kunnen worden.

---

## Literatuurlijst
1. Nederlandse Encyclopedie  
2. Insyte Technology  
3. Turck  
4. Adafruit on I2C adress detection  

---

## Changelog

| Versie | Wat | Wanneer |
|------|-----|---------|
| 1.0 | Document aangemaakt, begonnen met schrijven | 10/10/25 |
| 2.0 | Implementatie geschreven | 27/10/25 |
