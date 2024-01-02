# c-atm-automated-teller-machine
ATM virtual cash machine created with C-language

PANKKIAUTOMAATTI

1.	ONGELMA

Tehtävän tavoitteena oli koodata C-kielellä linkin https://otto.fi/virtuaaliotto2/html01.htm  mukaisen pankkiautomaatin toiminnoista nosto, talletus ja saldon kysely. Koska eri harjoituksissa pitkin syksyä tehtiin erilaisia lisäyksiä pankkiautomaattikoodiin, niin omassa sovelluksessani on mukana myös ”Liittymän lataus, puheaika” -toiminto. Liitteen pankkiautomaatti sisältää seuraavat ”Päävalikko” toiminnot, jotka kaikki olen koodannut mukaan siten, että ainoastaan ”Tapahtumat”-toiminto on jätetty viimeistelemättä, koska se ei kuulunut lopulliseen tarvelaajuuteen ja olisi vaatinut syventymistä päiväyksen ja kellonaikojen esittämiseen.

** PAAVALIKKO **
1. SETELIOTTO
2. SALDO
3. TAPAHTUMAT
4. LIITTYMAN LATAUS, PUHEAIKA
5. TALLETUS
0. STOP -> OHJELMAN LOPETUS

Valitse toiminto ( 1, 2, 3, 4, 5, 0) > 

2.	RATKAISU
   
2.1 Ratkaisun vaiheet

Aluksi loin päävalikon toiminnot, jolla varmistin modulaarisen rakenteen. Sen jälkeen tein setelioton, liittymän latauksen, saldon ja tapahtumat funktiot, siten että ohjelma toimi oikein käynnistyksestä sammutukseen, mutta ei tallentanut mitään pysyvää tiedostoihin. Testasin kunkin luomani toiminnon ennen kuin siirryin seuraavaan. 
Kun tiedoston käsittelystä riippumaton versio oli toimiva ja testattu, lisäsin ohjelmaan tiedostotoiminnon, eli tilitiedoston avaamisen ja sen mukaisesti muutin tunnuslukutoiminnon vertaamaan käyttäjän antamaa tunnuslukua tilitiedostossa olevaan. Samoin muutin saldo -funktion lukemaan ja päivittämään tilitiedostossa olevaa saldolukua. Lisäsin myös talletus -funktion, joka päivittää tilitiedostossa olevaa saldoa. Lisäksi liittymän lataukseen päivitin sen tarkastamaan tilitiedostossa olevan saldon, ja päivittämään sitä ladatulla rahasummalla. Tässä vaiheessa myös muutin saldoon liittyvät float luvut integereiksi.

2.2 Ohjelmassa käytetyt tiedostot:

Kaikkien tiedostojen kannattaa olla samassa hakemistossa.
- pankkiautomaatti.c 	- pääohjelma
- lukijat.c		  - opettajan antamat lukijat
- lukijat.h		  - aliohjelmien prototyypit
- 12345.tili  	- tiedosto jossa tunnusluku ja saldo
  
Kääntäminen: gcc -Wall -o nostomaatti.exe nostomaatti.c lukijat.c


2.3 Pankkiautomaatin algoritmi

•	MAIN-ohjelma: 

o	lueTilinumero( ): Lukee käyttäjän antaman tilinumeron ja tarkastaa että on tili/tilitiedosto

o	tunnusluku: lukee käyttäjän antaman tunnusluvun ja vertaa sitä tilitiedostossa olevaan

  	esim. tilinumero 12345 ja tunnusluku 1234 molemmat oikein -> avaa paavalikko( )

•	paavalikko( ) funktiossa:

o	tulostaPaavalikko( ) tulostetaan näytölle

	-> 1. SETELIOTTO

	-> 2. SALDO

	-> 3. TAPAHTUMAT

	-> 4. LIITTYMÄN LATAUS, PUHEAIKA

	-> 5. TALLETUS

	-> STOP -> OHJELMAN LOPETUS

o	Lukee käyttäjän antaman luvun  -> siirtyy kyseiseen toimintoon

•	paavalikko( ) funktiossa: Suorittaa SETELIOTTO-toiminnon
o	tulostaOttovalikko( ) tulostaa näytölle seteliotto valikon
o	seteliotto( ) funktiossa tarkastetaan halutun summan oikeellisuus
o	varmistetaan nostettuSumma (mm. ei voi nostaa enempää kuin on rahaa tilillä)
o	setSaldo( ) paivitetaan saldo
o	nostettavat_Setelimaarat( ) lasketaan noston 20 ja 50 euron setelit ja tulostetaan tieto
o	 -> POISTUTAAN OHJELMASTA 
•	Huom! Oikeassa automaatissakin ohjelma lopetaan

•	paavalikko( ) funktiossa: Suorittaa SALDO-toiminnon
o	getSaldo( ) hakee tilitiedoston toiselta riviltä saldon
o	paluu -> PÄÄVALIKKOon

•	paavalikko( ) funktiossa: Suorittaa ”TAPAHTUMAT”-toiminnon
o	getTapahtumat( ) funktiota Huom! Tätä ei ole viimeistelty, koska ei kuulunut lopulliseen suoritukseen
o	Tulostaa pari kovakoodattu tapahtumariviä, sekä todelliset saldotietoidot
o	paluu -> PÄÄVALIKKOon

•	paavalikko( ) funktiossa: Suorittaa ”LIITTYMÄN LATAUS, PUHEAIKA” toiminnon
o	liittyman_lataus( ) funktiossa tulostetaan näytölle ”Liittymän lataus” valikko:
	      Valitse palvelu:
	      1. Saunalahti
	      2. DNA
	      3. Go Mobile
	      0. STOP -> PAAVALIKKOON
o	Kysytään käyttäjältä operaattori (Saunalahti, DNA, Go Mobile)
o	lataaLiittymaanSaldoa( ) funktiossa luetaan puhelinnumero ja lataussumma
	           LIITTYMAN LATAUS
	           10 euroa     25 euroa
	           15 euroa     30 euroa
	           20 euroa     50 euroa
	           0  STOP     100 euroa
o	Tarkastetaan että tilillä on katetta lataussumman verran getSaldo( )-funktiolla 
o	Päivitetään setSaldo( ) saldo tilitiedostoon
o	paluu -> PÄÄVALIKKOon
o	
•	paavalikko( ) funktiossa: Suorittaa ”TALLETUS” toiminnon
o	luetaan tilitiedostosta tunnusluku ja tilisaldo ”r” -moodissa
o	päivitetään tilisaldo lisäämällä talletusmäärä
o	kirjoitetaan tilitiedostoon tunnusluku ja päivitetty saldo ”w+” -moodissa
o	paluu -> PÄÄVALIKKOon

2.4 Ohjelmassa käytetyt funktiot

FUNKTIO	      KÄYTTÖTARKOITUS
- luepois	      - Tyhjentää näppäimistöpuskurin
- lueTilinumero	- Lukee tilinumeron
- tunnusluku	  - Lukee tunnusluvun
- paavalikko	  - Ohjelman päävalikko
- tulostaPaavalikko	  - Tulostaa päävalikon
- tulostaOttovalikko	- Tulostaa setelien ottovalikon
- seteliotto	- Tarkastaa setelinoston oikeellisuuden
- setSaldo	  - Päivittää tilisaldon tilitiedostoon
- getSaldo	  - Hakee tilisaldon tilitiedostosta
- talletus	  - Tallettaa tilille rahasumman
- getKateisnostovara	- Hakee käteisnostovaran
- getTapahtumat	- Hakee tapahtumat (Huom! kovakoodattu)
- liittyman_lataus	- Liittymän latauksen alipääohjelma
- painaENTER	- Odottaa käyttäjän painamaa Enter näppäintä
- ohjelman_lopetus	- Ohjelman lopetusfunktio
- lataaLiittymaanSaldoa	- Lataa liittymään saldoa
- Nostettavat_Setelimaarat	- Laskee 20 ja 50 euron setelimäärät nostolle
- lueKokonaisluku	- Lukee kokonaisluvun
- lueReaaliluku	- Lukee reaaliluvun
- lueRoskat	- Tyhjentää näppäimistöpuskurin
- lueMerkkijono	- Lisää merkkijonon loppuun \0 ja tyhjentää näppäimistöpuskurin

3.	KÄYTTÖOHJEET
   
Ohjelma käännetään käskyllä: gcc -Wall -o nostomaatti.exe nostomaatti.c lukijat.c

Kaikki nämä tiedostot suosittelen olevan myös samassa hakemistossa jossa käännös tehdään: pankkiautomaatti.c, lukijat.c, lukijat.h, 12345.tili

Käynnistä nostomaatti.exe komennolla. 

Anna tilinumero 12345 ja anna tunnusluku 1234. Voit luoda muitakin tilitiedostoja esim. 67890.tili tiedoston. Tilitiedoston nimi on char tekstimuodossa (sallii kirjaimet, ei skandeja). Tilitiedostossa rivillä 1 on tunnusluku ja rivillä 2 on tilisaldo, 3 rivillä <EOF>. Katso tiedostosta 12345.tili tarkemmin. Tunnusluku on integer tyyppinen. Negatiivistä tai merkkejä sisältävää tunnuslukua ei ohjelma hyväksy.

Antamalla oikean tilinumeron ja oikean tunnusluvun eteesi avautuu päävalikko, josta voit valita SETELIOTON (syötä numero 1). Automaatissa on vain 20 ja 50 eur seteleitä, joten sen mukaan ohjelma hyväksyy nostomäärän. Nostomäärän verran pitää tilillä olla myös katetta/saldoa. Tililtä voi nostaa siellä olevan rahamäärän verran. Syötä haluamas nostomäärä, joka on integer tyyppinen. Ohjelma ei hyväksy miinusmerkkistä nostoa, eikä merkkejä sisältävää nostoa. Noston jälkeen saldo päivitetään tilitiedostoon. Seteliotto päättyy aina ohjelman päättymiseen kuten oikeassakin pankkiautomaatissa. Voit käynnistää ohjelman aina uudelleen nostomaatti.exe komennolla.

Päävalikosta voit valita SALDO -toiminnon (syötä numero 2). Ohjelma käy lukemassa tilitiedostosta saldon. Ohjelma jää odottamaan (Paina ENTER) enter painallusta, joten tee se, jotta pääset takaisin päävalikkoon.

Päävalikosta voit valita TAPAHTUMAT -toiminnon (syötä numero 3). Tätä ei ole valitettavasti viimeistelty, vaan osa on kovakoodattu. Saldoon liittyvät rivit ovat kuitenkin oikein. Tätä toimintoa ei vaadittu tähän harjoitustyöhön. Ohjelma jää odottamaan (Paina ENTER) enter painallusta, joten tee se, jotta pääset takaisin päävalikkoon.

Päävalikosta voit valita LIITTYMÄN LATAUS, PUHEAIKA -toiminnon (syötä numero 4). Valitse operaattori syöttämällä numero 1, 2 tai 3 sen mukaan kenen operaattorin liittymä sinulla on. Negatiivisella luvulla, 0:lla ja muilla kokonaisluvuilla palataan päävalikkoon, mutta merkeillä ja reaaliluvuilla kysytään uudelleen operaattoria. Syötä puhelinnumero muodossa 04012345678. Puhelinnumero syötetään tekstimuotoisena, eikä sen oikeellisuutta tässä vaiheessa tarkasteta !!! Ole erittäin tarkkana puhelinnumeron kanssa. Liittymään voi ladata 10, 15, 20, 25, 30, 50 tai 100 euroa antamalla kyseisen luvun. Tässä vaiheessa voit vielä syöttämällä 0-luvun lopettaa liittymän lataus toiminnon. Ohjelma ei hyväksy summaan kirjaimia eikä reaalilukuja vaan pyytää uuden syötön. Mikäli annat minkä tahansa muun kokonaisluvun niin ohjelma lataa liittymään OLETUS määrän 10 eur. Tilillä pitää olla katetta/saldoa ladattavan summan verran. Lopuksi pyydetään painamaan (Hyväksy maksu ( paina ENTER) enteriä, ja tässä vaiheessa maksua ei voi enään perua. 

Päävalikosta voit valita TALLETUS -toiminnon (syötä numero 5). Ohjelma kysyy talletusmäärän, johon kelpaa positiivinen kokonaisluku. Merkkiluvun, negatiivisen tai reaaliluvun syötön ohjelma pyytää korjaamaan uudella syötöllä. Talletuksen onnistumisen voit halutessasi tarkastaa saldo-toiminnolla.

Päävalikosta voit valita LOPETUS -toiminnon (syötä numero 0). Virhesyötöllä eli negatiivisella luvulla, reaaliluvulla, merkkiluvulla tai muilla kokonaisluvuilla ohjelma pyytää syöttämään uudelleen.

4.	TESTAUS

Testaussuunnitelma on periaatteessa yksinkertainen. Kaikki käyttäjän näppäimistöltä antamat kohdat testasin positiivisilla ja negatiivisilla kokonaisluvuilla, positiivisilla reaaliluvuilla ja numero-merkkiyhdistelmillä ja merkkijonoilla, ja syötteeksi ohjelma hyväksyy vain oikean formaatin syötön. Ohjelma ei pääty virheeseen vääränlaisella syötöllä.

Kaikki päävalikon moduulit/funktiot testasin erikseen. Seteliotosta testasin, että automaatti antaa oikean määrän seteleitä, joissa max määrä 50 eur seteleitä. Lisäksi testasin, että ei anneta esimerkiksi 10 tai 30 euron summaa, joka on mahdoton. Testasin myös, että saldon ylittävää summaa ei hyväksytä. Testasin että saldo päivittyy tulitiedostoon oikein.

Saldo toiminnosta testasin, että hakee tilitiedostosta oikean saldon.

Tapahtumat näytöltä testasin, että siellä oleva saldo on oikein.

Liittymän lataus toiminnosta testasin, että kysyy puhelinnumeron, joka hyväksytään tekstimuotoisena. Tässä puhelinnumeroon pystyy antamaan myös merkkejä, mutta oletin, että jos syöttää kelpaamattoman puhelinnumeron, niin pankki/operaattori rajapinnassa on tarkastus, että latausta ei veloiteta. Testasin myös, että vain latausvalikossa olevat summat hyväksytään, ja muilla annetuilla summilla ladataan oletussumma 10 eur. 

Talletus -toiminnosta testasin, että talletettu summa tallentuu tilitiedostoon oikein.

Tilitiedostosta testasin, että se aukeaa ja sulkeutuu kuten pitääkin, ja sitä voi käsitettä samassa ajossa loputtomasti. Käynnistettäessä ohjelma uudelleen tilitiedosto avautuu ja sulkeutuu myös normaalisti.

5.	KOKEMUKSET
   
Itselle vaikeimpia asioita olivat pointterit ja tiedostojen käsittely. Näitä piti testata koodin luontivaiheessa, jotta sain aikaiseksi oikeanlaisen toiminnon. Edelleen pointterit tuottavat hieman tuskaa.

Lähdin liikkeelle siten, että suunnittelin ensin päävalikko-funktion, sen perusteella tein aina yhden moduulin kerralla valmiiksi. Sopivissa väleissä lisäsin syötteiden virheenkäsittelyt.

Sain aikaiseksi moduulirakenteen, joka oli tarkoituksena.
