#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lukijat.h"

#define true 1
#define false 0

#define KATEISNOSTORAJA 400    // taman hetken nostoraja

// Prototyyppien esittelyt
void luepois( );
int lueTilinumero( char * tilinumero );
int tunnusluku( char * tilinumero );
void paavalikko( char * tilinumero );
int tulostaPaavalikko( );
int tulostaOttovalikko( );
int seteliotto( int nostoSumma );
void setSaldo( char * tilinumero, int nostettuSumma );    // Paivitetaan saldo
int getSaldo( char * tilinumero );     // Haetaan saldo
void talletus( char * tilinumero );
int getKateisnostovara( char * tilinumero );
void getTapahtumat( char * tilinumero );
void liittyman_lataus( char * tilinumero );
void painaENTER( );
int ohjelman_lopetus( );
void lataaLiittymaanSaldoa(int palvelunTarjoaja, char * tilinumero );
void nostettavat_Setelimaarat( int nosto, int taulu[2], int pituus );

/* main - kysyy kayttajalta tilinumeron ja tilin tunnusluvun.
 * Olemassa olevan tilin ja sen tunnusluvun antamalla ohjelman
 * aukaisee paavalikon.
*/
int main(void) {

    // Maarittelyt
    char tilinumero[20];
    int onTilinumero = false;        // Oletus etta tilinumeroa ei ole

    printf("\nTervetuloa! Syota kortti, ole hyva\n\n");

    do {
        onTilinumero = lueTilinumero( tilinumero );         // Luetaan tilinumero jota jatkossa kasitellaan
  
        if ( !onTilinumero ) {
            break;
        } 
    
        if ( tunnusluku( tilinumero )  == true)  {      // Jos tunnusluku oikein -> paavalikkoon eteneminen
            paavalikko( tilinumero );                   // Ohjelman suoritus siirtyy paavalikkoon
        } else {
            break;
        }
        
    } while ( false );

    printf("\nKiitos kaynnista\n");

    return (0);
}
/* lueTilinumero - kysyy kayttajalta tilinumeron max kolme kertaa.
 * Varmistaa tilinumeron olemassa olon avaamalla ja sulkemalla tilitiedoston.
 * Paluuarvona on tilinumeron olemassaolo tru/false.
 
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 * Paluuarvo (int): tilinumero olemassa true/false
 */
int lueTilinumero( char * tilinumero) {
    
    char formaatti[10] = ".tili";
    int tilinumeroPituus, formaattiPituus, tiliPituus;
    
    FILE * tiedostoNimi;
    int onTilinumero = false;    // Alustavasti tilöinumeroa ei ole olemassa
    int i = 0;
    
    do {
        printf("Nappaile tilinumero > ");
        fgets( tilinumero, 20, stdin );
    
        tilinumeroPituus = strlen(tilinumero) - 1;
        formaattiPituus = strlen(formaatti) - 1;
        tiliPituus = tilinumeroPituus + formaattiPituus + 1;   // formaatti[0] -> +1
    
        if ( tilinumero[strlen(tilinumero)-1] == '\n' ) { 
            tilinumero[strlen(tilinumero)-1] = '\0';      // Loppumerkki oikeaan paikkaan
        } else {
            luepois( );    // Tyhjentaa lukupuskurin
        }
    
        if ( strlen(tilinumero) != 0 ) {
            strcat( tilinumero, formaatti);               // Yhdistetaan numero + tiedostoformaatti
            tilinumero[tiliPituus] = '\0';
        
            if ( ( tiedostoNimi = fopen ( tilinumero, "r") ) != NULL ) {   
                onTilinumero = true;                                        // onTili = true
                fclose( tiedostoNimi );
                break;
            }
        } else {
            printf("\nTilinumero ei ollut oikein.");
        }
    
        printf("\nTilinumeroa ei loytynyt.\n");
        
        i = i + 1;
        if ( i == 2 ) {
            printf("Viimeinen yrityksesi nappailla tilinumero on seuraava yritys.\n");
        }
    
    } while ( i != 3 );     // Oikealla tilinumerolla poistutaan aikaisemmin
    
    return onTilinumero;
}

/* luepois - opettajan antama puskurin tyhjennysfunktio
 */
void luepois( ) {
    
    while ( getc( stdin ) != '\n' );
}
   
/* tunnusluku - kysyy kayttajalta tunnusluvun max nelja kertaa.
 * Varmistaa annetun tunnusluvun vertaamalla sita tilitiedostossa olevaan.
 * Paluuarvona on tunnusluku oikein/vaarin (=true/false)
 
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 * Paluuarvo (int): tunnusluku tru/false
 */
int tunnusluku( char * tilinumero ) {

    int i = 0;
    int tunnus_luku;
    int tilin_pin = 0;

    FILE * inTiedostoNimi;
    
    // Luetaan oikea tunnusluku tiedostosta
    if ( ( inTiedostoNimi = fopen ( tilinumero, "r") ) != NULL ) {    // Mikali tilia on
        fscanf( inTiedostoNimi, "%d", &tilin_pin );
        fclose( inTiedostoNimi );
    } else {
        printf("\nPaivitamme nostoautomaatti jarjestelmaa.");
        printf("\nKaytossa saattaa esiintya puutteita.");
        printf("\nTilitietosi ovat havinneet.");
        printf("\nPahoittelemme tilannetta.");
    }
    
    // Pyydetaan nappailemaan tiliin kuuluva tunnusluku
    do {
        printf("Nappaile tunnusluku > ");
        tunnus_luku = lueKokonaisluku( );
        //scanf("%d", &tunnus_luku);
        
        if ( tunnus_luku < 0 ) {
            printf("Annoit viallisen tunnusluvun.\n");
            printf("Syota tunnusluku uudelleen.\n");
            do {
                printf("\nNappaile tunnusluku > ");
                tunnus_luku = lueKokonaisluku( );
                //scanf("%d", &tunnus_luku);
            } while (tunnus_luku < 0 );
        }
        
        if ( tunnus_luku == tilin_pin ) {
            tunnus_luku = true;   // Nappailty oikea tunnnusluku
            break;                // Poistutaan oikealla tunnusluvulla
        }
        
        printf("\nAnnoit tiliin kuulumattoman tunnusluvun.\n");
        tunnus_luku = false;  // Ei viela nappailty oikeaa tunnuslukua
        
        i = i + 1;            // Kasvatetaan nappailykertoja
        if ( i == 3 ) {
            printf("Viimeinen yrityksesi nappailla tunnusluku on seuraava yritys.\n");
        }
    } while ( i != 4 );  // Oikealla tunnusluvulla poistutaan aiemmin

    return tunnus_luku;
}

/* paavalikko - suorittaa "paavalikon piirtofunktiosta" saadun valinnan 
 * mukaisen toiminnon:
 *   1. Seteliotto: suorittaa setelioton jos tililla on katetta summalle. Paivittaa saldon.
 *      Huom! Onnistunut seteliotto lopettaa ohjelman toiminnan.
 *   2. Saldo: tulostaa tilisaldon (ja myos kateisnostomaaran joka on tilisaldon suuruinen)
 *   3. Tapahtumat: on luonnos vaiheessa, tulostaa kuitenkin saldon ja kateisnostomaaran.
 *   4. Saldon lataus puhelinliittymaan.
 *   5. Talletus tilille.
 *
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 */
void paavalikko( char * tilinumero ) {

    int valinta = 0;
    int haluttuSumma;
    int nostettuSumma;
    int taulukko[2] = {0};     // Setelitaulukko: 0=20eur ja 1=50eur setelit
    int pituus = 2;            // Taulukon pituus
    
    do {
  
    valinta = tulostaPaavalikko( );       // Paavalikko naytolle

    switch( valinta ) {
        case 1:                     // Seteliotto
        
            // Nostomaaran verran taytyy olla tililla rahaa
            do {
                haluttuSumma = tulostaOttovalikko( );
                nostettuSumma = seteliotto( haluttuSumma );
                
                if ( nostettuSumma > getSaldo( tilinumero ) ) {
                    printf("\n  Saldosi on %d euroa. Et voi nostaa enempaa kuin tililla on rahaa\n\n", getSaldo( tilinumero ));
                }       
            } while ( nostettuSumma > getSaldo( tilinumero ) );
                
            if ( nostettuSumma == 0 ) {
                printf("\nNosto keskeytetty.");
                break;
            }
            
            setSaldo( tilinumero, nostettuSumma );    // Paivitetaan saldo
            
            nostettavat_Setelimaarat( nostettuSumma, taulukko, pituus );   // Maaritetaan nostettavat setelit (20 ja 50 euroiset)
            
            if ( nostettuSumma != 0 ) {
                printf("\nNostettu summa on %d euroa\n", nostettuSumma);
                printf("Annetaan \n");
                printf("   %2d kpl 50 eur seteleita\n", taulukko[1]);
                printf("   %2d kpl 20 eur seteleita\n", taulukko[0]);
                printf("Ota kortti, ole hyva. Rahat tulossa.\n");
                printf("Ota rahat.\n");
            }
            break;
        case 2:                     // Tilisaldo
            printf("  Tilin saldo:              %8d eur\n", getSaldo( tilinumero ) );
            printf("  Tilin kateisnostovara:    %8d eur\n", getKateisnostovara( tilinumero ) );
            painaENTER( );
            break;
        case 3:                     // Tilitapahtumat
            getTapahtumat( tilinumero );
            painaENTER( );
            break;
        case 4:                     // Liittyman lataus
            liittyman_lataus( tilinumero );
            break;     // Liittyman lataus tehty -> ohjelman lopetus
        case 5:                     // Talletus
            talletus( tilinumero );
            break;
        case 0:
            //ohjelman_lopetus( );
            break;
        default:
            break;
        }
    } while ( valinta != 0 && valinta != 1 );   // Onnistunut nosto lopettaa myos ohjelman
}

/* nostettavat_Setelimaarat - laskee parametrina saadusta nostomaarasta montako
 * 20 ja 50 euron setelia automaatin on annettava. Maksimoi 50 eur setelien maaran.
 * Tallentaa tarvittavien setelien maaran taulukkoon.
 * 
 * Parametrit:
 * - nosto (int): nostettava rahamaara
 * - taulu[2] (int): osoitin taulukkoon, johon 20 ja 50 euron setelien maara tallenetaan: taulu[0]=20setelit, taulu[1]=50 setelit
 * - pituus (int): taulukon pituus
 */
void nostettavat_Setelimaarat( int nosto, int taulu[2], int pituus ) {
    /*
    Setelimaarat talletetaan taulukkoon
        taulu[0] = 20 eur setelien maara
        taulu[1] = 50 eur setelien maara
    */
    
    int sadat = 0;
    int kymmenet = 0;
    
    sadat = nosto - ( nosto % 100 );
    kymmenet = nosto % 100;
    
    //printf("sadat %d:\n", sadat);
    //printf("kymmenet %d:\n", kymmenet);
    
    taulu[1] += (sadat/100) * 2;      // Sadoista euroista kustakin 2kpl 50eur setelia
    
    if ( kymmenet == 20 || kymmenet == 40 || kymmenet == 60 || kymmenet == 80 ) {
        taulu[0] += kymmenet/20;
        taulu[1] += 0;
    } else if ( kymmenet == 90 ) {
        taulu[0] += 2;
        taulu[1] += 1;
        } else if ( kymmenet == 70 ) {
            taulu[0] += 1;
            taulu[1] += 1;
            } else if ( kymmenet == 50 ) {
                taulu[0] += 0;
                taulu[1] += 1;
                } else if ( kymmenet == 30 ) {
                    taulu[0] += 4;
                    taulu[1] += -1;
                    } else if ( kymmenet == 10 ) {
                        taulu[0] += 3;
                        taulu[1] += -1;
                    }
}

/* painaENTER - odottaa etta kayttaja painaa ENTER-nappainta
 */
void painaENTER( ) {
    
    char ch = ' ';
    
    do {
        printf("\n  Paina ENTER > "); 
        ch = fgetc(stdin);
        
        if ( ch == 0x0A ) {
            //printf("ENTER painallus havaittu.\n");
        } else {
            //printf("%c painallus havaittu.\n", ch);
        }
        //ch = getchar();
        break;
        
    } while ( ch != 0x0A );
    
    return;
}

/* tulostaPaavalikko - tulostaa paavalikon
 * 
 * Paluuarvo (int): paavalikon toimenpiteen luku, jonka kayttaja syottaa vastauksena
 *
 */
int tulostaPaavalikko() {

    int valinta = 0;

    printf("\n  ** PAAVALIKKO **\n");
    printf("  1. SETELIOTTO\n");
    printf("  2. SALDO\n");
    printf("  3. TAPAHTUMAT\n");
    printf("  4. LIITTYMAN LATAUS, PUHEAIKA\n");
    printf("  5. TALLETUS\n");
    printf("  0. STOP -> OHJELMAN LOPETUS\n\n");
    printf("  Valitse toiminto ( 1, 2, 3, 4, 5, 0) > ");
    valinta = lueKokonaisluku( );
    //scanf("%d", &valinta);
    printf(" \n");

    return valinta;
}

/* tulostaOttovalikko - tulostaa pankkiautomaatin ottovalikon
 * 
 * Paluuarvo (int): kayttajan antama haluttu nostomaara
 *
 */
int tulostaOttovalikko() {

    int summa = 0;

    printf("       SETELI OTTO \n");
    printf("  20 euroa     90 euroa\n");
    printf("  40 euroa    140 euroa\n");
    printf("  60 euroa    240 euroa\n");
    printf("  0  STOP     Muu summa\n\n");
    printf("  Anna summa > ");
    summa = lueKokonaisluku( );
    //scanf("%d", &summa);

    return summa;
}

/* seteliotto - tarkastaa etta haluttu nostomaara on kelvollinen luku
 * ja etta automaatti sellaisen maaran kykynee antamaan. Pyytaa kayttajalta
 * antamaan sellaisen luvun.
 * Paluuarvona kelvollinen nostomaara.
 *
 * Parametrit: 
 * - nostoSumma (int): kayttajan suottama haluttu nostomaara
 * 
 * Paluuarvo: 
 * - nostoSumma (int): funktion vahvistama kelvollinen nostomaara
 */
int seteliotto( int nostoSumma ) {

    int haluttuSumma;
    
    switch ( nostoSumma ) {
        case 20:
            nostoSumma = 20;
            break;
        case 40:
            nostoSumma = 40;
            break;
        case 60:
            nostoSumma = 60;
            break;
        case 90:
            nostoSumma = 90;
            break;
        case 140:
            nostoSumma = 140;
            break;
        case 240:
            nostoSumma = 240;
            break;
        case 0:
            nostoSumma = 0;
            break;
        default:
            if ( nostoSumma < 20 || nostoSumma == 30 || nostoSumma % 10) {
                do {
                    printf("\nAnnoit kelpaamattoman luvun.\n");
                    printf("Automaatista saa 20 ja 50 euron seteleita.\n");
                    printf("Valitse nostomaara uudelleen.\n\n");
                    haluttuSumma = tulostaOttovalikko( );
                    nostoSumma = seteliotto( haluttuSumma );
                } while (nostoSumma < 0);
            }
            break;
    }
    return nostoSumma;
}

/* talletus - kysyy kayttajalta tilille talletettavan rahamaaran. Avaa tilitiedoston ja lukee 
 * tiedostosta pin-luvun ja tilin saldon, lisaa talletusmaaran saldoon, ja palauttaa uudet
 * tiedot takaisin samaan tilitiedostoon.
 *
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 */
void talletus( char * tilinumero ) {
    
    int talletusSumma = 0;
    
    int tilin_pin;
    int tilisaldo;
    
    FILE * tiedostoNimi;
    
    do {
        printf("\n  Anna talletusmaara > ");
        talletusSumma = lueKokonaisluku( );
        
        if ( talletusSumma < 0 ) {
            printf("\nTalletuksen pitaa olla positiivinen");
        }
        
    } while ( talletusSumma <= 0);
    
    
    // Luetaan tilitiedostosta tunnusluku ja saldo
    if ( ( tiedostoNimi = fopen ( tilinumero, "r") ) != NULL ) {    // Mikali tili on
        fscanf( tiedostoNimi, "%d", &tilin_pin );
        fscanf( tiedostoNimi, "%d", &tilisaldo );
        fclose( tiedostoNimi );
    } else {
        printf("\nOngelma tiedoston avaamisessa lukemista varten.");
    }
    
     // Kirjoitetaan tilitiedostoon tunnusluku ja uusi saldo takaisin
    if ( ( tiedostoNimi = fopen ( tilinumero, "w+") ) != NULL ) {    // Mikali tili on
        fprintf( tiedostoNimi, "%d\n", tilin_pin );
        fprintf( tiedostoNimi, "%d\n", ( tilisaldo + talletusSumma ) );
        fclose( tiedostoNimi );
    } else {
        printf("\nOngelma tiedoston avaamisessa kirjoitusta varten.");
    }
    
    return;
}

/* setSaldo - paivittaa tilitiedoston saldon. 
 * Talla hetkella funktio ei ole enaan kaytossa.
 
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 * - nostettuSumma (int): tilille paivitettava summa (+ pano) (- nosto)
 *
 */
void setSaldo( char * tilinumero, int nostettuSumma ) {

    int tilin_pin;   // Luetaan myos
    int tilisaldo;

    FILE * tiedostoNimi;
    
    // Luetaan tiedosto ja kirjoitetaan tiedostoon takaisin
    if ( ( tiedostoNimi = fopen ( tilinumero, "w+") ) != NULL ) {    // Mikali tili on
        rewind( tiedostoNimi );
        fscanf( tiedostoNimi, "%d", &tilin_pin );
        fscanf( tiedostoNimi, "%d", &tilisaldo );
        rewind( tiedostoNimi );
        fprintf( tiedostoNimi, "%d\n", tilin_pin );
        fprintf( tiedostoNimi, "%d\n", ( tilisaldo - nostettuSumma ) );
        
        fclose( tiedostoNimi );
    } else {
        printf("\nOngelma tiedoston avaamisessa lukemista varten.");
    }
    
    return;
}

/* getSaldo - hakee saldon tilitiedostosta.
 
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 */
int getSaldo( char * tilinumero ) {

    int tilin_pin;   // Luetaan myos
    int tilisaldo;

    FILE * inTiedostoNimi;
    
    // Luetaan oikea tunnusluku tiedostosta
    if ( ( inTiedostoNimi = fopen ( tilinumero, "r") ) != NULL ) {    // Mikali tili on
        fscanf( inTiedostoNimi, "%d", &tilin_pin );
        fscanf( inTiedostoNimi, "%d", &tilisaldo );
        fclose( inTiedostoNimi );
    } else {
        printf("\nOngelma tiedoston avaamisessa lukemista varten.");
    }
    
    return tilisaldo;
}

/* getKateisnostovara - funktio hakee ja maarittaa kateisnostovaran. 
 * Oletuskateisnostovara on 400 euroa, mutta funktio paivittaa sen tilisaldon suuruiseksi.
 * Paluuarvona kateisnostomaara.
 *
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 * Paluuarvo (int) kateisnostomaara
 */
int getKateisnostovara( char * tilinumero ) {

    int kateisnostovara = getSaldo( tilinumero );  // Toistaiseksi yhta suuri kuin tilisaldo

    return kateisnostovara;
}

/* getTapahtumat - funktio on alustava lisaominaisuus, EI KOODATTU LOPULLISEEN MUOTOON, 
 * Lopullisessa muodossaan tulostaa naytolle tilitapahtumien lisaksi myos tilin saldon, 
 * tilinta nostettavissa maaran seka kateisnostovaran.
 *
  * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 */
void getTapahtumat( char * tilinumero ) {

    printf("\n     TILITAPAHTUMAT:\n");
    printf("  Paiva        Aika     Nostomaara\n  ESIMERKKI RIVI");
    printf("  20.10.2019   19:34       100 eur\n  ESIMERKKI RIVI");
    printf("  29.10.2019   14:22        20 eur\n  ESIMERKKIRIVI");
    printf(" \n");
    printf("  Tilin saldo:            %8d eur\n", getSaldo( tilinumero ));
    printf("  Tililta nostettavissa:  %8d eur\n", getSaldo( tilinumero ));
    printf("  Kortin kateisnostovara: %8d eur\n", getKateisnostovara( tilinumero ));
}

/* liittyman_lataus - on liittyman latauksen paafunktio, joka tulostaa liittyman lataus valikon, 
 * pyytaa kayttajaa valitsemaan operaattorin ja kutsuu lisafunktioita jotka hoitavat loppuun latausasiat
 * ja tilisaldon paivittamisen.
 *
 * Parametrit:
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 */
void liittyman_lataus( char * tilinumero ) {
    
    int palvelunTarjoaja;
    int valinta;
    
    /* Naytolle liityman latauksen valikko */
    printf("Liittyman lataus\n");
    printf("\n  Valitse palvelu:\n");
    printf("  1. Saunalahti\n");
    printf("  2. DNA\n");
    printf("  3. Go Mobile\n");
    printf("  0. STOP -> PAAVALIKKOON\n\n");
    
    printf("  Valitse toiminto (1, 2, 3, 0) > ");
    valinta = lueKokonaisluku( );
    //scanf("%d", &valinta);
    printf(" \n");
    
    // Kaikki caset menevat nyt samaan lataaLiittymaanSaldoa funktioon
    switch( valinta ) {
        case 1:
            palvelunTarjoaja = 1;
            lataaLiittymaanSaldoa( palvelunTarjoaja, tilinumero );  // Saunalahti
            break;
        case 2:
            palvelunTarjoaja = 2;
            lataaLiittymaanSaldoa( palvelunTarjoaja, tilinumero );  // DNA
            break;
        case 3:
            palvelunTarjoaja = 3;
            lataaLiittymaanSaldoa( palvelunTarjoaja, tilinumero );  // GoMobile
            break;
        case 0:
            printf("Palataan paavalikkoon\n");
            break;
        default:
            printf("Hieman pieleen meni valinta.\n");
            printf("Palataan paavalikkoon.\n");
            break;
    }
    
}

/* lataaLiittymaanSaldoa - funktio saa parametrina palveluntarjoajan ja tilinumeron,
 * ja pyytaa kayttajalta puhelinnumeron, seka liittymaan ladattavan euro summan.
 * Tarkastaa halutun summan oikeellisuuden, tarkastaa etta tililla on katetta summan verran
 * ja paivittaa tilin saldon
 *
 * Parametrit:
 * - palvelunTarjoaja (int): palveluntarjoajaa kuvaa luku (1, 2, 3)
 * - tilinumero (char *): osoitin merkkijonotaulukkoon
 *
 */
void lataaLiittymaanSaldoa( int palvelunTarjoaja, char * tilinumero ) {
    /* Kasitellaan toistaiseksi puhelinnumeroa merkkijonona */
    
    char puhelinnumero[20];
    int latausSumma;
    int tilisaldo = 0;
    int latausOK = false;
    
    char ch = ' ';
    char palvelunTarjoajaNimi[4][15] = {" ", "Saunalahti", "DNA", "GoMobile"};  // 0=tyhja
  
    printf("   Syota %s puhelinnumero (esim. 0401987...) > ", palvelunTarjoajaNimi[palvelunTarjoaja]);
    scanf("%s", puhelinnumero);             // Huom! ei &-merkkia luettaessa merkkijonoja
    
    do {
        printf("\n   LIITTYMAN LATAUS\n");
        printf("   10 euroa     25 euroa\n");
        printf("   15 euroa     30 euroa\n");
        printf("   20 euroa     50 euroa\n");
        printf("   0  STOP     100 euroa\n\n");
        printf("   Anna summa > ");
        latausSumma = lueKokonaisluku( );
        //scanf("%d", &latausSumma);
    
        switch ( latausSumma ) {
            case 10:
                latausSumma = 10;
                break;
            case 15:
                latausSumma = 15;
                break;
            case 20:
                latausSumma = 20;
                break;
            case 25:
                latausSumma = 25;
                break;
            case 30:
                latausSumma = 30;
                break;
            case 50:
                latausSumma = 50;
                break;
            case 100:
                latausSumma = 100;
                break;
            case 0:
                printf("\nPalataan edelliseen valikkoon\n");
                break;
            default:
                latausSumma = 10;
                printf("\nAnnoit kelpaamattoman summan.\n");
                printf("Kaytetaan OLETUS summaa.\n");
                printf("Ladattava summa 10 eur ( ** OLETUS ** ).\n");
                break;
        }
        
        // Lataussumman verran taytyy olla tililla rahaa
        tilisaldo = getSaldo( tilinumero ); 
        if ( latausSumma <= getSaldo( tilinumero ) ) {
            setSaldo( tilinumero, latausSumma );    // Paivitetaan saldo
            latausOK = true;
        } else {
            printf("\n  Saldosi on %d euroa. Et voi ladata enempaa kuin tililla on rahaa\n\n", getSaldo( tilinumero ));
            latausOK = false;
        }
        // Kun lataus onnistuu
        if ( (latausSumma != 0) & latausOK) {  
            printf("\nLiittyman lataus\n\n");
            printf("Maksun hyvaksyminen\n\n");
            printf("   Puhelinnumero           %-17s\n", puhelinnumero);    // 15 merkkinen tulostus, vasemmalle tasaus
            printf("   Ladattava summa         %d eur\n", latausSumma);
            printf("   Otto tililta            %d eur\n", latausSumma);
        }        
    
    } while ( latausSumma > tilisaldo  );    // Pyydetaan lataussummaa kunnes se < saldo
        
        do {
            printf("\n   Hyvaksy maksu ( paina ENTER ) > "); 
            //ch = fgetc(stdin);
        
            if ( ch == 0x0A ) {
                //printf("ENTER painallus havaittu.\n");
            } else {
                //printf("%c painallus havaittu.\n", ch);
            }
            ch = getchar();
            break;
            
        } while ( ch != 0x0A );
        
        // Ottomaatissa ei ollut kuin hyvaksymismahdollisuus
        printf("\nTapahtumaasi kasitellaan.\n");    
        printf("\nOta kortti, ole hyva\n");
        printf("Puheaika maksettu\n");
        printf("\n%s latausvahvistus tekstiviestilla\n", palvelunTarjoajaNimi[palvelunTarjoaja]);
}

/* ohjelman lopetus - kutsutaan paavalikosta ja lopettaa ohjelman
 *
 */
int ohjelman_lopetus(  ) {

    bool lopetus = true;

    return lopetus;
}
