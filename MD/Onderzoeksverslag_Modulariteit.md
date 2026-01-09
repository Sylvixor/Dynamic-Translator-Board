Onderzoeksverslag Modulariteit

Dynamic Translator Board

Scott Van Der Heijden (1103349), Tijmen Groenevelt (1058554)  
Arda Keskin (1096673) ,Omar Mansour (1051322)

10-10-2025

Inhoud

[Samenvatting 3](#_Toc216440093)

[Inleiding 3](#_Toc216440094)

[Theoretisch kader modulariteit 4](#_Toc216440095)

[Methode toepassing modulariteit 5](#_Toc216440096)

[Resultaten implementatie project 6](#_Toc216440097)

[Conclusie 7](#_Toc216440098)

[Literatuurlijst 8](#_Toc216440099)

[Changelog 9](#_Toc216440100)

# Samenvatting

# Inleiding

Het project Dynamic Translator Board gaat om het gebruik kunnen maken van verschillende sensoren, zonder dat de gebruiker van het apparaat technische kennis nodig heeft.

Deze sensoren moeten met een "plug-and-play" principe aangesloten kunnen worden. Het magnetisch opklikken van een sensor is alles wat een gebruiker zou moeten doen om het werkend te krijgen. Verder is alles wat er vereist wordt van de gebruiker het bekijken van de informatie die de sensoren versturen.

Om dit te bereiken, moet er een bepaald niveau van modulariteit in het apparaat zitten. De vraag die hierbij komt opzetten is: Hoe valt dit te implementeren in de context van dit project?

Om het antwoord daar op te vinden moet er eerst antwoord komen op de volgende onderzoeksvragen:

- Hoe wordt modulariteit theoretisch gedefinieerd en hoe is dit van toepassing op het project?
- Waar wordt modulariteit in moderne technologie al gebruikt en heeft dit een relevante toepassing voor ons project?
- Op welke manieren wordt modulariteit zoal toegepast en welke methode is voor het project het meest van toepassing?

# Theoretisch kader modulariteit

De directe definitie van modulariteit is als volgt:

"De mate waarin een systeem of een computerprogramma is opgebouwd uit afzonderlijke eenheden (modules), die elk een eigen functie vervullen. Een modulair systeem of programma kan worden aangepast of uitgebreid met minimale aanpassingen aan het totaal." \[1\]

Uit deze definitie volgt de vraag wat het toevoegen van modulariteit bijdraagt aan dit project?

Zoals in de introductie al benoemd was, moet er een "plug-and-play" principe ontstaan. Dit principe is dus verbonden aan modulariteit, omdat de sensoren onafhankelijk van elkaar aangesloten, losgekoppeld en uitgelezen moeten kunnen worden. Dit moet kunnen gebeuren zonder dat er aan het achterliggende programma een aanpassing gemaakt hoeft te worden door de gebruiker.

# Methode toepassing modulariteit

Het principe van modulair gebruik van sensoren wordt nog niet veel toegepast, maar er zijn zeker voorbeelden te vinden van algemene toepassing modulariteit binnen moderne technologie.

Zo is er bijvoorbeeld het bedrijf Insyte Technology \[2\]. Zij hebben een framework ontworpen waar verschillende sensoren op aangesloten kunnen worden. Door gebruik van dit framework kunnen de aangesloten sensoren met elkaar communiceren en ook daarnaast ook uitgelezen worden.

Deze framework hebben ze al toegepast op verschillende situaties, zoals bij fijnstofmetingen op bouwterreinen, geurdetectie bij waterzuiveringssystemen en bodemvochtdetectie voor groenprojecten. Dit zijn een aantal voorbeelden binnen de grote hoeveelheid toepassingsmogelijkheden van het framework ontwerp.

Een ander bedrijf die zich bezighoud met modulariteit is Turck \[3\]. Zij zijn voornamelijk bezig met het modulair maken van grotere machines, zodat hierin aanpassingen gemaakt kunnen worden wanneer dit nodig is. Ook is onderhoud hiermee makkelijker, aangezien er bij problemen makkelijker geïsoleerd kan worden waar in de machine het probleem terug te vinden is. Ook gebruiken ze het om verschillende machines makkelijker te combineren en samen te laten werken.

Deze voorbeelden laat zien dat modulariteit wel al voorkomt in vergelijkbare contexten, maar dit zijn vaak relatief kleine bedrijven die zich hier mee bezig houden. Daarnaast wordt het concept modulariteit ook alleen nog in de industrie toegepast tot nu toe, waarbij het project van Cyrb de nadruk op commerciëel gebruik wil leggen.

Modulariteit wordt klaarblijkelijk over het algemeen toegepast door het juist ontwerpen van een PCB (printplaat) voor de toepassende doeleinden van een apparaat. Op deze printplaat wordt rekening gehouden met de mogelijke communicatieprotocollen van de sensoren en van de microcontroller waar het uiteindelijk aan verbonden wordt.

Ook wordt er tijdens het ontwerpen gekeken naar de gebruiksomgeving. Dit heeft te maken met de behuizing die om de PCB heen gemaakt wordt en samen met de sensoren die er op aangesloten zitten moet kunnen passen. Als het in een omgeving met gelimiteerde ruimte komt, moet het ontwerp natuurlijk hier dusdaanig op aangepast worden. Wanneer er geen eisen aan omvang hangen, kan er bijvoorbeeld meer naar efficiëntie op andere gebieden gekeken worden tijdens het ontwerpen.

# Resultaten implementatie project

Er blijken uit het onderzoek een aantal mogelijkheden te zijn om modulariteit te implementeren binnen het dynamic translator board project.

De eerste optie is het gebruik van verschillende weerstanden per sensor. Dit is een analoge methode. Deze methode vereist dat er een extra weerstand tussen twee pinnen wordt toegevoegd. Deze weerstand kan vervolgens door middel van een ADC (Analog to Digital Converter) herkent worden, waardoor het programma kan detecteren welke sensor er aanwezig is.  
Deze methode vereist een extra weerstand per sensor. Ook moeten alle sensoren correct kunnen werken met de ADC, gezien deze wel eerst in moet lezen wat er verbonden wordt. Ook is de kans op kleine meetfouten groter, omdat het een analoge oplossing is.

De tweede optie is het gebruik van interne I2C adressen. Dit is een volledig digitale methode en elimineert dus de mogelijkheid op analoge meetfouten. \[4\]  
Voor deze methode is het belangrijk dat alle sensoren via I2C communiceren. De gebruikte sensoren hebben allemaal een apart adres, en deze kan gescanned worden door de microcontroller wanneer de sensor aangesloten wordt. Hierdoor is het mogelijk om te detecteren welke sensoren er aanwezig zouden zijn, en op basis van deze informatie de juiste code te implementeren.  
De uitdaging hier in ligt dat niet alle sensoren standaard I2C gebruiken als communicatiemethode. Ook kan het zijn dat bepaalde sensoren vaste adressen hebben die mogelijk onderling overlappen, hier moet in de ontwikkelingsfase dus goed op gelet worden omdat dit anders voor problemen in de detectie kan zorgen.

# Conclusie

# Literatuurlijst

\[1\] [Nederlandse Encyclopedie](https://www.encyclo.nl/begrip/modulariteit)

\[2\] [Insyte Technology](https://insyte-technology.com/onze-aanpak)

\[3\] [Turck](https://www.turck.nl/nl/modulaire-machines-36981.php#:~:text=Het%20modulariteitsprincipe,van%20lage%20tot%20absolute%20modulariteit.)

\[4\] [Adafruit on I2C adress detection](https://learn.adafruit.com/scanning-i2c-addresses/raspberry-pi)

# Changelog

| **Datum** | **Change** |
| --- | --- |
| 10/10/25 | Document aangemaakt, begonnen met schijven |
| 27/10/25 | Impelementatie geschreven |