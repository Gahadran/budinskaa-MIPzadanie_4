// projekt1.c -- Projekt1 - Snehulienka
// Alzbeta Budinska, 2.3.2017 11:25:16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// globalne premenne
char rolkaA[10000]; // ukladame v nej iba znaky (nazvy ovocia oddelene '\0') neupratujeme ju, ked raz nieco zapisem, nikdy to nemazem
int rolkaB[10000]; // v prijem_ovocia do nej zapisujeme prijate ovocie vo vydaj_ovocia z nej mazeme vydane ovocie a upratujeme ju
int **sklad; // aktualny stav skladu
int sirka; // pre sirku skladu
int vyska; // pre vysku skladu
int noveA; // prva volna pozicia v rolke A = id noveho ovocia
int noveB; // nasledujuca volna pozicia v rolke B (pre najnovsie ovocie v rolkeB)

// Pouzitim tejto funkcie vypiseme aktualny stav skladu.
// zaplnena pozicia v sklade sa vypise ako id ovocia, ktore sa na pozicii nachadza
// "-" je pre prazdnu poziciu v sklade
// k rozmerom skladu pristupujeme pomocou globalnej premennej sirka a vyska
void vypis_sklad()
{
  int i, j; // pomocna premenna i pre riadky/police, j pre stlpce/pozicie na policiach
  
  for(i=0; i < vyska; i++) // pokial zodpoveda zadanej vyske skladu
  {
    for(j=0; j < sirka; j++) // pokial zodpoveda zadanej sirke skladu
    {
      if(sklad[i][j] == -1) // ak je na danom mieste sklad prazdny vypise '-'
        printf("- ");
      else
        printf("%d ", sklad[i][j]); // ak je na danom mieste sklad zaplneny, vypise id ovocia ktore sa tam nachadza
    }
    putchar('\n');
  }
  putchar('\n');
}

// Pouzitim tejto funkcie vytvorime pomocou funkcie malloc() novy sklad podla zadanych hodnot 
// a nastavime vsetky hodnoty v rolke B na -2
// ak niektora alebo obe zo zadanych rozmerov su zaporne, zmenime ich na kladne a vypiseme 
// hlasenie o zmene
// rozmery skladu si ulozime do globalnych premennych sirka a vyska aby sme vedeli 
// vypisat aktualny stav skladu pomocou funkcie vypis_sklad
// alokujeme pole a nastavime vsetkych jeho miesta na prazdne (-1)
void novy_sklad(int n, int m)
{
  int i, j, r; // pomocne premenne i=riadky, j=pozicie v riadkoch/policiach, r=posun v rolkeB
  
  for(r=0; r < 10000; r++)
    rolkaB[r]=-2; // nastavime si vsetky hodnoty v rolke B na -2 aby sa nam s nou neskor lepsie pracovalo
  
  if(n < 0) // ak sme dostali zapornu hodnotu pre vysku skladu
  {
    n=n*(-1); // zmenime vysku na kladnu
    printf("Hodnota pre vysku skladu bola zmenena na kladnu.\n"); // hlasenie o zmene
  }
  
  if(m < 0) // ak sme dostali zapornu hodnotu pre sirku skladu
  {
    m=m*(-1); // zmenime sirku na kladnu
    printf("Hodnota pre sirku skladu bola zmenena na kladnu.\n"); // hlasenie o zmene
  }
  
  vyska=n; // ulozime vysku skladu do globalnej premennej
  sirka=m; // ulozime sirku skladu do globalnej premennej
  
  sklad=(int**)malloc(n*sizeof(int*)); // pomocou funkcie malloc() vytvorime sklad podla zadanych rozmerov
  
  for (i=0; i < n; i++) // police v sklade
  {
    sklad[i]=(int*)malloc(m*sizeof(int));
    for(j=0; j < m; j++) // pozicie v sklade
      sklad[i][j] = -1; // kedze je sklad prazdny, nastavime hodnotu na kazdom mieste na -1
  }
}

// Pouzitim tejto funkcie vypiseme hlasenia v zavislosti od zadaneho id.
// ak zadane id zodpoveda id nejakeho ovocia v rolke A, vypise jeho nazov aj s tymto id
// ak zadane id nezodpoveda id nejakeho ovocia v rolke A, vypise hlasenie podla stavu 
// rolky A a pozicie zadaneho id
void vypis_id(int id)
{
  int i; // pomocna premenna pre posun v rolke A
  
  if(id > 10000 || id < 0) // ak je zadane id vacsie alebo mensie ako kapacita rolkyA
    printf("Zadane ID nezodpoveda kapacite rolky.\n");

  else if(id == 10000) // ak zadane id zodpoveda koncu rolky A
  {
    if (rolkaA[id] == '\0') // ak sa tu nachadza koncovy znak, znamena to, ze rolka A je zaplnena
      printf("Ste na konci zaplnenej rolky.\n");
    else
      printf("Ste na konci rolky.\n"); // ak rolka A nie je uplne zaplnena
  }
  
  else if(rolkaA[id-1]=='\0' && rolkaA[id]!='\0') // ak sa nachadzame na id pozicii ovocia
  {
    for(i=0; i > -1; i++)
    {
      if(rolkaA[id+i] != '\0') // pokial nie sme na konci nazvu ovocia
        printf("%c", rolkaA[id+i]); // po znakoch ho vypiseme
      else 
        break; // nachadzame sa na konci nazvu, tak prestaneme vypisovat
    }
    printf(" ma ID %d\n", id); // vedla nazvu vypiseme aj id ovocia
  }
  
  else if(rolkaA[id-1]>'\0' && rolkaA[id]>='\0') // ak sa nenachadzam na id pozicii ovocia, ale v rolke A je tato pozicia zaplnena
  {
    printf("Zadane cislo nie je ID ovocia.\n"); 
  }
  
  else // ak je na zadanej pozicii rolka A prazdna
    printf("Rolka tu nie je zaplnena\n");
}

// Pouzitim tejto funkcie zapisujeme do rolky A a vraciame id zadaneho ovocia.
// ak sa ovocie v rolke A uz nachadza, vratime a vypiseme jeho id
// ak sa ovocie v rolke A nenachadza a uz sa do rolky A nezmesti, vrati hodnotu -1 
// a vypise hlasenie o tom, ze sa uz nezmesti
// ak sa ovocie v rolke A nenachadza a zmesti sa do rolky A, zapiseme ho do nej, 
// vratime hodnotu jeho id a vypiseme jeho nazov a pridelene id
int zisti_id(char *meno)
{
  int i; // pomocna premenna pre posun v rolke A
  int k; // pomocna premenna pre posun v zadanom nazve ovocia
  int id; // premenna, ktorej hodnotu na konci funkcie vratime. 
  
  for(i=0; i < 10000; i++) // prechadzame celu rolku A
  {
    for(k=0; k < strlen(meno)+1; k++) // prechadzame zadany nazov a tie v rolkeA
    {   
      if(meno[k] != rolkaA[i+k]) // ak sa nazov nerovna s tym v rolke A
        break; 
    }
    
    if(strlen(meno)+1 == k) // ak ovocie v rolke A uz zapisane je
    {
      //printf("%d\n", i); // vypiseme iba jeho id
      return i; // vratime hodnotu jeho id 
    }
  }
    
  if(i != -1) // ak sa ovocie v rolke A este nenachadza
  {
    if(strlen(meno)+noveA > 10000) // ak sa nazov noveho ovocia uz do rolky A nezmesti
    {
      printf("Nazov sa uz nezmesti\n"); // vypise o tom hlasenie
      return -1; // vratim chybne id (id moze byt len kladne)
    }
    
    else // zapiseme ho do rolky A
    {
      for(i=0; i < strlen(meno)+1; i++) // posuvame sa v nazve a rolke A
      {
        if(i==strlen(meno)) // ak sme na konci nazvu
        {
          rolkaA[noveA+i]='\0'; // pridame zan v rolke A koncovy znak
          break; // prestaneme zapisovat do rolky A
        }
        rolkaA[noveA+i]=meno[i]; // po znakoch zapisujeme do rolky A nove ovocie
        //printf("%c", meno[i]); // po znakoch vypiseme nazov noveho ovocia
      }
      //printf(" %d\n", noveA); // za nazvom vypiseme aj id tohoto noveho ovocia
      id=noveA; // vratime id noveho ovocia
      noveA=noveA+strlen(meno)+1; // pre nove ovocie nastavime id na prvu volnu poziciu po poslednom zapisanom ovocii 
    }
  }
  return id; // vraciame hodnotu id zadaneho ovocia
}

// Pouzitim tejto funkcie prijmame ovocie do skladu (nastavujeme prazdne miesta -1 na id prijateho ovocia).
// pomocou funkcie zisti_id zistime, ci uz mame zaznam o ovoci v rolke A
// ak zaznam o ovoci v rolke A nemame, a este sa do nej zmesti, zapiseme ho a ovocie skusime uskladnit 
// ak sa do rolky A uz nezmesti nove ovocie, tak ovocie neprijmeme
// vraciame hodnotu premennej prijatych, ktora nas informuje o pocte prijatych ks ovocia
int prijem_ovocia(char *meno, int ks, int velkost)
{
  int i; // posun v policiach skladu=vyska 
  int j; // posun po miestach v policiach skladu=sirka
  int k; // premenna ktora prechadza kusy ovocia
  int x; // pomocna premenna pre zistenie dostatku miesta v polici a pri zapise ovocia do police
  int napln=0; // premenna ktora nam urci, ci sa nam ovocie do skladu zmesti
  int prijatych=0; // premenna v ktorej vraciame pocet prijatych kusov ovocia
  int id; // premenna ktora si zapamata id uskladnovaneho ovocia
  
  if(ks < 1 || velkost < 1) // ak je pocet kusov alebo velkost ovocia na prijem 0 a menej
  { 
    printf("Chybny pocet kusov alebo velkost ovocia.\n");
    return prijatych; // nic neprijme
  }
  
  if(velkost > sirka) // ak je velkost ovocia vacsia nez miest na polici
  { 
    printf("Ovocie je prilis velke na uskladnenie v tomto sklade.\n");
    return prijatych; // nic neprijme
  }
  
  id=zisti_id(meno); // ulozime si id ovocia pre neskorsie pouzitie
  
  if(id > -1) // ak ovocie je v rolke A alebo sa tam da este zapisat
  {
    for(k=1; k <= ks+1; k++) // snazime sa uskladnit kazdy kus ovocia
    {
      if(k == ks+1) // ak sme skusili uz vsetky kusy ovocia
        return prijatych; // vratime hodnotu kolko kusov sme prijali
    
      for(i=0; i <= vyska; i++) // prechadzame police v sklade
      {
        if(i == vyska) // ak sme presli vsetky police
          break;
    
        for(j=0; j <= sirka; j++) // kontrolujeme miesta v policiach
        {
          if(j == sirka) // ak sme na konci police
            break;
        
          if(sklad[i][j] >= 0) // ak je miesto v polici zaplnene
            continue;
        
          if(sklad[i][j] == -1) // ak je miesto v polici prazdne
          {
            for(x=j; x <= velkost+j; x++) // skontrolujeme ci je od tej pozicie v polici miesto pre ovocie
            {
              if(x == velkost+j) // ak sa ovocie do skladu zmesti
              {
                napln=1; // nech vieme ze mozeme ovocie uskladnit
              }
              else if(sklad[i][x] == -1) // ak je miesto v sklade prazdne
                continue;
              else
                break;
            }
          }
          
          if(napln == 1) // ak sa ovocie do skladu zmesti
          {
            if(noveB > 9999) // ak je rolka B plna
            {
              printf("Rolka B je plna");
              return 0; // nic neprijme
            }
            
            rolkaB[noveB] = velkost; // zapiseme do rolky B velkost prijateho ovocia
            rolkaB[noveB+1] = i; // policu v sklade
            rolkaB[noveB+2] = j; // pociatocne miesto na polici v sklade
            rolkaB[noveB+3] = -1; // ze je posledne prijate
            noveB+=4; // nastavime na nasledujuce volne miesto v rolkeB 
   
            for(x=j; x < velkost+j; x++)
            {
              sklad[i][x]=id; // zapiseme id ovocia do skladu
            }
            break;
          }
        }
        
        if(napln == 1)
        {
          napln=0; // vratime na povodnu hodnotu
          prijatych++; // navysime pocet prijatych kusov ovocia
          break;
        }
      }
    }
  }
  else
  {
    printf("Uz sa neda prijat novy druh ovocia, rolkaA je plna.");
    return prijatych; // nic neprijme
  }
  return prijatych; // vrati pocet pridanych ovocii do skladu (moze by odlisny od poctu ktory chceme pridat)
}

// Pouzitim tejto funkcie sa snazime vydat ovocie zo skladu
// prechadzame rolkuB od zaciatku aby sme isli od najstarsie prijatych ovocii
// vydame prve vyhovujuce ovocie a zmazeme zaznam o nom v rolke B, ktoru nasledne upraceme
// aby sa zachovali zaznamy ovocia od najstarsieho
// vraciame hodnotu premennej vydanych, ktora nas informuje kolko ks ovocia uspesne vydalo
int vydaj_ovocia(char *meno, int ks, int velkost_aspon)
{
  int j, r;  // premenne pouzite v cykloch j=miesto na polici pouzite, r=pozicia v rolke
  int id=-1; // premenna na ulozenie hodnoty id ovocia
  int aktualna=0;  // aktualna pozicia v rolke B
  int vydanych=0; //hodnota ktorou vraciame pocet vydanych ks ovocia
  
  if(ks < 1 || velkost_aspon < 1) // ak je pocet ks alebo velkost ovocia 0 a menej
  {
    printf("Chybny pocet kusov alebo velkost ovocia.\n");
    return vydanych; // nic nevyda
  }
 
  for(vydanych=0; vydanych < ks;)  // snazime najst a vydat pozadovany pocet ovocia
  {
    if(rolkaB[aktualna] == -2) // ak sme na konci rolky B, prestaneme hladat ovocie na vydaj
      break;
    
    if(rolkaB[aktualna] >= velkost_aspon)  // ak ovocie v rolke B splnuje pozadovanu velkost
    {
      if((sklad  [rolkaB[aktualna + 1]]  [rolkaB[aktualna + 2]] > -1)  &&  
         (sklad  [rolkaB[aktualna + 1]]  [rolkaB[aktualna + 2]] == (id = zisti_id(meno)))) // zistime ci sa tam nachadza pozadovane ovocie
      {     // ...
        vydanych++;  // zvysi pocet vydanych kusov ovocia
        
        for(j=0; j < rolkaB[aktualna]; j++)
          sklad[rolkaB[aktualna+1]][rolkaB[aktualna+2]+j] = -1; // vymaze ovocie zo skladu
        
        for(r=aktualna; r < 10000; r++) // vymazeme zaznam o vydanom ovoci z rolky B
        {
          if(-2 == rolkaB[r]) // ak uz sme upratali rolku B a sme na prazdnom mieste
            break;
          rolkaB[r]=rolkaB[r+4];
        }
        noveB-=4; // aktualizujeme posledne volne miesto v rolke B
        continue; // ostaneme na aktualnom mieste v rolke B
      }
    }
    aktualna+=4; // ak sme ovocie nevydali, posunieme sa v rolke B
  }
  
  if(vydanych == 0)  // ak sa nenaslo ovocie s pozadovanou velkostou
  { 
    printf("Pozadovane ovocie nemame na sklade.\n");
    return vydanych; // nic nevyda
  }
  
  if(id == -1) //  ak sa v sklade nenaslo ziadne take ovocie a neda sa uz zapisat do rolky A
  {
    printf("Ovocie nemame a ani nebudeme mat na sklade.\n");
    return vydanych; // nic nevyda
  }
  return vydanych; // vrati pocet uspesne vydanych ks ovocia
}

int main()
{

novy_sklad(1,1);
vypis_sklad();

printf("%d\n", zisti_id("abcdefghijklmnopqrstuvwxyz"));
vypis_id(0);
vypis_id(10);
vypis_sklad();

printf("%d\n", prijem_ovocia("abcde",1,1));
vypis_sklad();

  /*
  int r;
  
  novy_sklad(10,20);
  prijem_ovocia("mango", 1, 20);
  prijem_ovocia("mango", 1, 20);
  prijem_ovocia("kivi", 1, 2);
  prijem_ovocia("mango", 1, 2);
  vydaj_ovocia("mf", 1, 1);
  vydaj_ovocia("kivi", 1, 2);
  prijem_ovocia("mango", 1, 2);
  prijem_ovocia("kivi", 1, 2);
  prijem_ovocia("mango", 1, 2);
  vydaj_ovocia("kivi", 1, 2);
  vydaj_ovocia("kivi", 1, 2);
  prijem_ovocia("kivi", 1, 2);
  vypis_sklad();
  
  for(r=0; r<=10000; r++)
  {
    printf("%d", rolkaB[r]);
  }
  printf("\n");
  
  for(r=0; r<=10000; r++)
  {
    printf("%c", rolkaA[r]);
  }
  printf("\n");
  */
  
  free(sklad);
  return 0;
}
