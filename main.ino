#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32)
#define TFT_CS 14
#define TFT_RST 15
#define TFT_DC 32

#elif defined(ESP8266)
#define TFT_CS 4
#define TFT_RST 16
#define TFT_DC 5

#else
// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8
#endif
// nasze bitmapy
//  bell
const unsigned char bell[] PROGMEM = {
    0x03, 0xc0, 0x07, 0xe0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0,
    0x0f, 0xf0, 0x1f, 0xf8, 0x3f, 0xfc, 0x7f, 0xfe, 0x00, 0x00, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80};
// bell
const unsigned char wisnie[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x7e, 0x7e, 0x7e, 0x7e,
    0x7e, 0x7e, 0x7e, 0x7e, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// łodyga
const unsigned char lodyga[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x01, 0xc0, 0x01, 0x40, 0x02, 0x40,
    0x04, 0x20, 0x04, 0x20, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// liść
const unsigned char lisc[] PROGMEM = {
    0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x00};
// siedem
const unsigned char siedem[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0c, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x30, 0x1c, 0x00, 0x3c, 0x00, 0x78,
    0x00, 0xf8, 0x01, 0xf0, 0x03, 0xe0, 0x03, 0xc0, 0x03, 0x80, 0x07, 0x80, 0x07, 0x00, 0x07, 0x00,
    0x00, 0x00};
const unsigned char siedem_obr[] PROGMEM = {
    0x30, 0x0c, 0x4f, 0xf2, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x4f, 0xe2, 0x30, 0x42, 0x00, 0x84,
    0x01, 0x04, 0x02, 0x08, 0x00, 0x10, 0x04, 0x20, 0x04, 0x40, 0x08, 0x40, 0x08, 0x80, 0x08, 0x80,
    0x07, 0x00};
// dolar
const unsigned char dolar[] PROGMEM = {
    0x00, 0x00, 0x0e, 0x70, 0x3e, 0x7c, 0x7e, 0x7e, 0x70, 0x0e, 0x70, 0x06, 0x7e, 0x00, 0x3f, 0xe0,
    0x1f, 0xfc, 0x07, 0xfe, 0x60, 0x0e, 0x70, 0x0e, 0x78, 0x0e, 0x7e, 0x7e, 0x3e, 0x7c, 0x0e, 0x70,
    0x00, 0x00};
const unsigned char dolar_krecha[] PROGMEM = {
    0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
    0x01, 0x80};
// diax
const unsigned char diax[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x1f, 0xf8, 0x60, 0x06, 0x77, 0xee, 0x6f, 0xf6, 0x6f, 0xf6,
    0x6f, 0xf6, 0x47, 0xe2, 0x38, 0x1c, 0x1b, 0xd8, 0x07, 0xe0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80,
    0x00, 0x00};
const unsigned char diax_d[] PROGMEM = {
    0x00, 0x00, 0x1f, 0xf8, 0x20, 0x04, 0x60, 0x06, 0x9f, 0xf9, 0x88, 0x11, 0x90, 0x09, 0x90, 0x09,
    0x90, 0x09, 0xb8, 0x1d, 0x47, 0xe2, 0x24, 0x24, 0x18, 0x18, 0x08, 0x10, 0x04, 0x20, 0x02, 0x40,
    0x01, 0x80};

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int BUTTON_G = 2; // pin do któego podpiety jest przycisk główny
const int BUTTON_L = 3; // pin do któego podpiety jest przycisk lewy
const int BUTTON_P = 4; // pin do któego podpity jest przycisk prawy
uint16_t time;

int punkty = 300; // punkty początkowe
int Los_1;        // zmienne do których bedziemy przypisywać losy
int Los_2;
int Los_3;

int MAX = 6;
int bid = 30; // bid początkowy
int menu = 1; // poczatkowa wartość menu
bool FLAGA = 1;
void setup(void)
{
  Serial.begin(9600);
  pinMode(BUTTON_G, INPUT); // przypisanie pinów jako wejście
  pinMode(BUTTON_L, INPUT);
  pinMode(BUTTON_P, INPUT);

  tft.initR(INITR_GREENTAB);
  // Los_1 = random(1, MAX);
  // Los_2 = random(1, MAX);
  // Los_3 = random(1, MAX);

  int los = 1;

  Ekran_startowy(); // włączenie funkcji odpowiedzialnej za animacje początową
                    // tft.fillScreen(ST77XX_BLACK);
}
void loop()
{

  display_punkty(punkty);            // aktualizacja punktów
  if (digitalRead(BUTTON_L) == HIGH) // jeżeli przycisk lewy jest wciśniety
  {
    if (menu > 1) // jezeli wartość zmiennej obsługującej menu >1
      menu--;     // zmniejsz jej wartość o jeden
    else
      menu = 5;
    display_menu(); // zaktualizuj menu
    delay(300);     // poczekaj 0.3s
  }
  if (digitalRead(BUTTON_P) == HIGH) // analogicznie tylko w druga strone
  {
    if (menu < 5)
      menu++;
    else
      menu = 1;
    display_menu();
    delay(300);
  }
  if (digitalRead(BUTTON_G) == HIGH) // jeżeli jest wciśniety przycisk główny
  {
    switch (menu) // w zaleźnosci od stanu menu
    {
    case 1: // jednoręki bandyta
    {
      if (punkty - bid >= 0) // sprawdzenie czy użytkownika stać na gre
      {
        FLAGA = 0;
        punkty = punkty - bid;        // odebanie punktów na poczet gry
        tft.fillScreen(ST77XX_BLACK); // wypełnienie ekranu
        display_punkty(punkty);       // wyświetlanie punktów
        display_bid();                // wyświeltanie bidu
        display_menu();               // wyświeltanie menu
        FLAGA = 1;
        time = millis() * 12.23456l; // podpisanie pod zmienna time czasu włączenia gry pomnożonego przez stała
        randomSeed(time);            // stworzenie losowego seedu na podstawie czas

        Los_1 = random(1, MAX); // pierwszy los
        Los_2 = random(1, MAX); // drugi los
        Los_3 = random(1, MAX); // trzeci los

        animacja(-35);      // aniamcja na pozycji nr.1
        figury(-35, Los_1); // pokazanie losu nr 1 na odpowiednim miejscu
        delay(300);         // poczekanie 0.3s

        animacja(0);      // animacja na pozycji nr. 2
        figury(0, Los_2); // pokazanie losu nr 2 na odpowiednim miejscu
        delay(300);       // poczekanie 0.3s

        animacja(35);      // animacja na pozycji nr. 3
        figury(35, Los_3); // pokazanie losu nr 3 na odpowiednim miejscu
        delay(300);        // animacja na pozycji nr. 3

        wygrana(Los_1, Los_2, Los_3, bid); // sprawdzenie czy użytkownik coś wygrał, dodanie punktów, wyświetlenie ile wygrał
        delay(600);                        // poczekaj 0.6s
        tft.fillRect(85, 10, 30, 10, ST77XX_BLACK);
      }
      else
      {
      }
      break;
    }
    case 2: // zwiekszenie bidu
    {
      if (bid < 99995) // jezeli bid nie przegracza maxa
      {
        bid = bid + 5;    // dodaj 5 do bidu
        if (bid > punkty) // jezeli po dodaniu wartość bidu bedzie wieksza niż punktów
        {
          bid = bid - 5; // zmniejsz o 5 oraz wyświelt tekst
          tft.setCursor(15, 30);
          tft.setTextSize(1);
          tft.println("Bid nie moze byc");
          tft.setCursor(13, 40);
          tft.println("wiekszy niz saldo");
        }
        display_bid(); // aktualizuj bid
        delay(300);    // poczekaj 0.3s
      }
      else // jeżeli bid jest wiekszy od możliwego
      {
        tft.setCursor(15, 30);
        tft.setTextSize(1);
        tft.println("Maksynalny bid to");
        tft.setCursor(50, 40);
        tft.println("99995$");
      }
      break;
    }
    case 3: // zmniejszenie bidu
    {
      if (bid > 0) // jeżeli bid jest wiekszy od zera (tak naprawde wiekszy od 4)
      {
        bid = bid - 5; // zmniejszenie bidu o 5
        display_bid(); // zaktualizowanie bidu
        delay(300);    // poczekaj 0.3s
      }
      break;
    }
    case 4: // wyświetlanie instrukcji
    {       // wyswietlanie tekstu

      instrukcja();

      menu = 1;       // ustaw menu na gre w jednorękiego
      display_menu(); // wyświetl menu
      display_bid();  // wyświetl bid

      figury(-35, 3); // pokaż figure nr 3 (liczbe siedem) na pozycji nr 1
      figury(0, 3);   // pokaż figure nr 3 (liczbe siedem) na pozycji nr 2
      figury(35, 3);  // pokaż figure nr 3 (liczbe siedem) na pozycji nr 3
      break;
    }
    case 5: // sposob na zarobienie pieniedzy gdy szczęście nam nie dopisuje.
    {
      delay(300); // poczekaj 0.3s
      tft.fillRect(0, 20, 150, 150, ST77XX_BLACK);
      tft.setCursor(35, 130);
      tft.setTextSize(1);
      tft.println("KONTYNUUJ");

      int i = 1;
      int j = 1;
      int flaga = 0;
      int TIME = 30000;
      time = millis() * 12.234561; // czas włączeia jednorękiego pomnozony przez stała
      randomSeed(time);            // na podstawie niego tworzenie seedu
      // pierwsza figura
      while (true)
      {

        tft.fillRect(20, 73, 18, 18, ST77XX_BLACK); // czarny ekran zasłąniajacy figure któa znajduje sie na pozycji nr1
        Los_1 = random(1, MAX);                     // losowanie liczby od 1 do 5
        figury(-35, Los_1);                         // wyświetlanie wylosowanej figury na pozycji nr.1
        j = 0;

        while (j < TIME) // pętla obsługująca czas jaki użytkowynik ma na zareagowanie
        {
          j++;
          if (digitalRead(BUTTON_G) == HIGH) // jeżeli zostaie klikniety przycisk główny
          {
            flaga = 1;  // ustaw falge na 1
            delay(200); // poczekaj 0.2s
            break;      // wyjdz z petki reakcji
          }
        }

        if (flaga)                   // jeżeli flaga została ustawiona na 1
          break;                     // wyjdz z petli pierwszego losu
        time = millis() * 12.234561; // czas włączeia jednorękiego pomnozony przez stała
        randomSeed(time);            // na podstawie niego tworzenie seedu
      }

      while (true) // los nr 2
      {

        tft.fillRect(55, 73, 18, 18, ST77XX_BLACK); // czarny ekran zasłąniajacy figure któa znajduje sie na pozycji nr 2
        Los_2 = random(1, MAX);                     // losowanie liczby od 1 do 5
        figury(0, Los_2);                           // wyświetlanie wylosowanej figury na pozycji nr.2
        j = 0;
        flaga = 0;
        while (j < TIME) // pętla obsługująca czas jaki użytkowynik ma na zareagowanie
        {
          j++;
          if (digitalRead(BUTTON_G) == HIGH) // jeżeli zostaie klikniety przycisk główny
          {
            flaga = 1;  // ustaw falge na 1
            delay(200); // poczekaj 0.2s
            break;      // wyjdz z petki reakcji
          }
        }
        if (flaga)                   // jeżeli flaga została ustawiona na 1
          break;                     // wyjdz z petli pierwszego losu
        time = millis() * 12.23456l; // czas włączeia jednorękiego pomnozony przez stała
        randomSeed(time);            // na podstawie niego tworzenie seedu
      }
      // 3
      while (true)
      {

        tft.fillRect(90, 73, 18, 18, ST77XX_BLACK); // czarny ekran zasłąniajacy figure któa znajduje sie na pozycji nr 2
        Los_3 = random(1, MAX);                     // losowanie liczby od 1 do 5
        figury(35, Los_3);                          // wyświetlanie wylosowanej figury na pozycji nr.2
        j = 0;
        flaga = 0;
        while (j < TIME) // pętla obsługująca czas jaki użytkowynik ma na zareagowanie
        {
          j++;
          if (digitalRead(BUTTON_G) == HIGH) // jeżeli zostaie klikniety przycisk główny
          {
            flaga = 1;  // ustaw falge na 1
            delay(200); // poczekaj 0.2s
            break;      // wyjdz z petki reakcji
          }
        }
        if (flaga)                   // jeżeli flaga została ustawiona na 1
          break;                     // wyjdz z petli pierwszego losu
        time = millis() * 12.23456l; // czas włączeia jednorękiego pomnozony przez stała
        randomSeed(time);            // na podstawie niego tworzenie seedu
      }

      wygrana(Los_1, Los_2, Los_3, bid); // sprawdzenie czy wysolowanie i zatwierdzone liczby dadza punkty
      tft.fillRect(85, 10, 30, 10, ST77XX_BLACK);
      break;
    }
    }
  }
}
//-----------------------------
void display_punkty(int p) // funkcja wyświetlająca punkty
{                          // w zależnościod tego jak duze one sa beda one dobrze układane na ekranie
  int i = 0;
  if (punkty < 10)
    i = -1;
  else if (punkty < 100)
    i = 0;
  else if (punkty < 1000)
    i = 1;
  else if (punkty < 10000)
    i = 2;
  else
    i = 3;
  tft.setCursor(90, 0);
  tft.setTextSize(1);
  tft.println("Saldo: ");
  tft.setCursor(97 - 3 * i, 10);
  tft.println(p);
  tft.setCursor(110 + 3 * i, 10);
  tft.println("$");
}
//-----------------------------
void display_bid() // funkcja wyświetlająca wartość BIDu w odpowiednim miejscu
{                  // w zależnościod tego jak duze on jest bedzie on dobrze y na ekranie
  int i = 0;
  tft.fillRect(0, 0, 40, 18, ST77XX_BLACK);
  if (bid <= 9)
    i = 0;
  else if (bid <= 99)
    i = 1;
  else if (bid <= 999)
    i = 2;
  else if (bid <= 9999)
    i = 3;
  else
    i = 4;
  tft.setCursor(10, 0);
  tft.setTextSize(1);
  tft.println("Bid: ");
  tft.setCursor(14 - 3 * i, 10);
  tft.println(bid);
  tft.setCursor(20 + 3 * i, 10);
  tft.println("$");
}
//-----------------------------
void display_menu()
{                                             // funkcja wyświetlająca menu dolne
  tft.fillRect(0, 20, 140, 40, ST77XX_BLACK); // wyczyszczenie obszaru menu dolnego
  tft.fillRect(0, 130, 130, 130, ST77XX_BLACK);
  switch (menu) // w zależności jaka wartość ma zmienna globalna "menu"
  {
  case 1: // wyświelta nam informacje o tym ze klikniecie przycisku głównego pozwoli nam zagrać w jednorękiego
    tft.setCursor(53, 130);
    tft.setTextSize(1);
    tft.println("GRAJ");
    if (FLAGA)
    {
      tft.setCursor(4, 35);
      tft.println("Kliknij przycisk aby");
      tft.setCursor(38, 43);
      tft.println("zagrac w");
      tft.setCursor(0, 52);
      tft.println("Jedno Rekiego Bandyte");
    }
    break;

  case 2: // wyświelta nam informacje o tym ze klikniecie przycisku głównego pozowoli nam zwiększyć BID o 5$
    tft.setCursor(32, 130);
    tft.setTextSize(1);
    tft.println("ZWIEKSZ BID");

    tft.setCursor(4, 35);
    tft.println("Kliknij przycisk aby");
    tft.setCursor(10, 43);
    tft.println("zwiekszyc BID o 5$");
    break;
  case 3: // wyświelta nam informacje o tym ze klikniecie przycisku głównego pozowoli nam zmniejszyć BID o 5$
    tft.setCursor(28, 130);
    tft.setTextSize(1);
    tft.println("ZMNIEJSZ BID");

    tft.setCursor(4, 35);
    tft.println("Kliknij przycisk aby");
    tft.setCursor(7, 43);
    tft.println("zmniejszyc BID o 5$");
    break;
  case 4: // wyświelta nam informacje o tym ze klikniecie przycisku głównego pozowoli nam wyświetlić instrukcje
    tft.setCursor(35, 130);
    tft.setTextSize(1);
    tft.println("INSTRUKCJA");

    tft.setCursor(4, 35);
    tft.println("Kliknij przycisk aby");
    tft.setCursor(2, 43);
    tft.println("wyswietlic instrukcje");
    break;
  case 5: // wyświelta nam informacje o tym ze klikniecie przycisku głównego pozowoli nam spróbować zdobyć $
    tft.setCursor(38, 130);
    tft.setTextSize(1);
    tft.println("ZDOBADZ $");

    tft.setCursor(4, 35);
    tft.println("Kliknij przycisk aby");
    tft.setCursor(11, 43);
    tft.println("sprobowac zdobyc $");

    break;
  }
}
//-----------------------------
void wygrana(int j, int d, int t, int b) // funkcja sprawdzająca czy trzy podane wartości są takie same
{                                        // bedzie także zmieniał wartość punktów które posiadamy
  int i = 0;                             // i wyświetlał napis ile wygraliśmy
  int w = 0;
  int flaga = 1;
  if (j != d && d != t && j != t) // jeżeli wszystkie trzy zmienne są różne
  {
    tft.setCursor(5, 40);
    tft.setTextSize(1);
    tft.setTextWrap(true);
    tft.fillRect(0, 20, 140, 40, ST77XX_BLACK);
    tft.println("Moze nastepnym razem");
  }
  // jeżeli dwa losy są takie same
  else if ((j == d && j != t && d != t) || (j != d && d == t && j != t) || (j != d && d != t && j == t))
  {
    if ((j == d) || (j == t)) // jeżeli pierszy los jest taki sam jak drugi lub trzeci
      w = j;
    else // else bedzie sie wykonywać tylko  w tedy gdy los nr 2 jest taki sam jak los nr 3
      w = d;

    switch (w) // w zależności od tego która figura sie powtarza
    {          // nadajemy zmiennej "w" odpowiednią wartość
    case 1:
      w = 2 * b; // jeżeli trafimy bell to wartość wygranej to 2 razy wartość BID
      break;
    case 2:
      w = 2.5 * b; // jeżeli trafimy wiśnia to wartość wygranej to 2.5 razy wartość BID
      break;
    case 3:
      w = 5 * b; // jeżeli trafimy siedem to wartość wygranej to 2 razy wartość BID
      break;
    case 4:
      w = 3.5 * b; // jeżeli trafimy dolar to wartość wygranej to 2 razy wartość BID
      break;
    case 5:
      w = 4 * b; // jeżeli trafimy diax to wartość wygranej to 2 razy wartość BID
      break;
    }

    if (menu == 5) // jeżeli menu jest równe 5 (Zdobywanie pieniędzy)
    {
      w = w / b * 20; // wartość wygranej jest dzielona przez BID żeby nie była zależna od niej oraz mnożona przez 20
    }

    if ((w < 10) && flaga) // sprawdzamy jak duża jest wygrana żeby poprawnie wyświetlić ją na ekranie
    {
      i = 0;
      flaga = 0;
    }
    else if ((w < 100) && flaga)
    {
      i = 1;
      flaga = 0;
    }
    else if ((w < 1000) && flaga)
    {
      i = 2;
      flaga = 0;
    }
    else if ((w < 10000) && flaga)
    {
      i = 3;
    }
    tft.setCursor(0, 35);
    tft.setTextSize(1);
    tft.setTextWrap(true);
    tft.fillRect(0, 20, 140, 40, ST77XX_BLACK);
    tft.println("Gratulacje!Wygrywasz:");
    tft.setCursor(58 - 3 * i, 45);
    tft.println(w);
    tft.setCursor(65 + 3 * i, 45);
    tft.println("$");
    punkty = punkty + w; // dodanie wygranej do punktów;
  }

  else if (j == d && d == t && j == t) // jezeli wszystkie trzy losy są takie same
  {
    tft.setCursor(20, 40);
    tft.setTextSize(2);
    tft.fillRect(0, 20, 100, 40, ST77XX_BLACK);
    tft.println("JACKPOT"); // użytkownik zdobywa jackpot!

    for (int i = 400; i <= 500; i = i + 49) // wyświela sie prosta Animacja

    {
      tft.fillRect(20, 73, 90, 18, ST77XX_BLACK); // usuwa z ekranu aktulane figury
      delay(i / 2);                               // po poczekaniu 0.i/2 s ktore bedzie sie zwiększać z każdą iteracją
      figury(-35, Los_3);                         // wyświetla figury które wygrały
      figury(0, Los_3);
      figury(35, Los_3);
      delay(i / 2); // następnie znowu czeka 0.i/2s
    }

    punkty = punkty + b * 11;
  }
  //???????????????????????????????
  delay(1700);    // po pokażej grze czeka 1.7s
  display_menu(); // wyświetla menu
}
//-----------------------------
void animacja(int p) // aniamcja polegająca na miganiu danej pozycji
{
  tft.fillRect(55 + p, 73, 17, 18, ST77XX_BLACK); // czyści pola figur
  int Los_poprzedni = 0;
  int Los_s = 0;
  for (int i = 50; i <= 160; i = i + 8) // pętla odpowiedzalna za miganie
  {
    time = millis() * 12.234561; // czas włączenia jednorękiego pomnożony przez stała
    randomSeed(time);            // na podstawie tego tworzenie seedu
    Los_s = random(1, MAX);      // losowanie figury

    if (Los_s == Los_poprzedni) // jeżeli wylosowana figura jest taka sama jak poprzednia
    {
      time = millis() * 986; // ustalamy seed za pomocy innej stałej
      randomSeed(time);
      Los_s = random(1, MAX);
    }

    figury(p, Los_s);                               // wyświetlamy ten los na danej pozycji
    Los_poprzedni = Los_s;                          // podpisujemy go jako poprzedni
    delay(i);                                       // czekamy 0.i s
    tft.fillRect(55 + p, 73, 18, 18, ST77XX_BLACK); // czyścimy tą pozycje
  }
}
//-----------------------------
void figury(int p, int f) // wyświeltanie figury w danym miesjcu
{
  p = p + 7;
  // jeżeli los jest równy jeden to wyświtlamy bell
  if (f == 1)
  {
    tft.drawBitmap(50 + p, 75, bell, 16, 16, ST77XX_YELLOW);
  }

  // jeżeli los jest równy jeden to wyświtlamy wisnia
  if (f == 2)
  {
    tft.drawBitmap(50 + p, 77, wisnie, 16, 16, ST77XX_BLUE);
    tft.drawBitmap(50 + p, 72, lodyga, 16, 16, 0x4861);
    tft.drawBitmap(58 + p, 75, lisc, 3, 3, 0x07B0);

    tft.drawPixel(55 + p, 85, ST77XX_WHITE);
    tft.drawPixel(55 + p, 84, ST77XX_WHITE);
    tft.drawPixel(54 + p, 83, ST77XX_WHITE);

    tft.drawPixel(60 + p, 85, ST77XX_WHITE);
    tft.drawPixel(61 + p, 86, ST77XX_WHITE);
    tft.drawPixel(62 + p, 86, ST77XX_WHITE);
  }
  // jeżeli los jest równy jeden to wyświtlamy siedem
  if (f == 3)
  {
    tft.drawBitmap(50 + p, 73, siedem, 16, 17, 0x9190);
    tft.drawBitmap(50 + p, 73, siedem_obr, 16, 17, ST77XX_WHITE);
  }
  // jeżeli los jest równy jeden to wyświtlamy dolar
  if (f == 4)
  {
    tft.drawBitmap(50 + p, 73, dolar, 16, 17, 0x4760);
    tft.drawBitmap(50 + p, 73, dolar_krecha, 16, 17, 0x3590);
  }
  // jeżeli los jest równy jeden to wyświtlamy diax
  if (f == 5)
  {
    tft.drawBitmap(50 + p, 73, diax, 16, 17, ST77XX_RED);
    tft.drawBitmap(50 + p, 73, diax_d, 16, 17, ST77XX_WHITE);
  }
}
//-----------------------------

void instrukcja()
{
  tft.fillScreen(ST77XX_BLACK);
  // kolejna czesc instruckji
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(4, 0);
  tft.setTextSize(2);
  tft.println("INSTRUKCJA");
  tft.setCursor(0, 20);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.println(" Aby poruszac sie po menu, uzyj strzalek, a swoj wybor zatwierdzaj klikajac X. Zmniejsz lub zwieksz wysokosc bidu, zagraj i daj szanse szczesciu!");
  tft.setCursor(50, 80);
  tft.println(" :)");
  tft.setCursor(35, 130);
  tft.setTextSize(1);
  tft.println("KONTYNUUJ");

  while (true) // pętla odpowiedzialna na czekanie na wciśniecie przycisku
  {
    if (digitalRead(BUTTON_G) == HIGH) // gdy zotsanie wciśniety przucisk główny
    {
      delay(100); // poczkeaj 0.1s
      break;      // wyjdz z petli
    }
  }

  // wyświeltanie mnożnika - wyświelanie danej figury a obok niej napisu.
  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(15, 0);
  tft.setTextSize(2);
  tft.println("Mnozniki:");
  tft.setTextSize(1);

  // bell
  tft.drawBitmap(5, 30, bell, 16, 16, 0x2679);
  tft.setCursor(25, 35);
  tft.println("X2");

  // wisnia
  int p = 2;
  tft.drawBitmap(4, 62 + p, wisnie, 16, 16, ST77XX_BLUE);
  tft.drawBitmap(4, 57 + p, lodyga, 16, 16, 0x4861);
  tft.drawBitmap(12, 60 + p, lisc, 3, 3, 0x07B0);

  tft.drawPixel(9, 70 + p, ST77XX_WHITE);
  tft.drawPixel(9, 69 + p, ST77XX_WHITE);
  tft.drawPixel(18, 68 + p, ST77XX_WHITE);

  tft.drawPixel(14, 70 + p, ST77XX_WHITE);
  tft.drawPixel(15, 71 + p, ST77XX_WHITE);
  tft.drawPixel(15, 71 + p, ST77XX_WHITE);

  tft.setCursor(25, 66);
  tft.println("X2.5");

  // dolar
  tft.drawBitmap(75, 30, dolar, 16, 17, 0x4760);
  tft.drawBitmap(75, 30, dolar_krecha, 16, 17, 0x3590);
  tft.setCursor(97, 35);
  tft.println("X3.5");

  // 7
  tft.drawBitmap(45, 93, siedem, 16, 17, 0x9190);
  tft.drawBitmap(45, 93, siedem_obr, 16, 17, ST77XX_WHITE);
  tft.setCursor(67, 98);
  tft.println("X5");

  // diax
  tft.drawBitmap(75, 59, diax, 16, 17, ST77XX_RED);
  tft.drawBitmap(75, 59, diax_d, 16, 17, ST77XX_WHITE);
  tft.setCursor(97, 65);
  tft.println("X4");

  tft.setCursor(35, 130);
  tft.setTextSize(1);
  tft.println("KONTYNUUJ");

  while (true) // pętla odpowiedzialna na czekanie na wciśniecie przycisku
  {
    if (digitalRead(BUTTON_G) == HIGH) // gdy zotsanie wciśniety przucisk główny
    {
      delay(100); // poczekaj 0.1s
      break;      // wyjdz z petli
    }
  }

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(4, 0);
  tft.setTextSize(2);
  tft.println("INSTRUKCJA");
  tft.setCursor(5, 20);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.println("Jezeli szczescie ci nie dopisuje, mozesz zawsze udac sie do ostatniej opcji w menu, w niej mozesz sprobowac zdobyc minimum dwie takie same figury aby zyskać troche waluty na gre, jednak miej pewnosc ze nie to takie proste ");

  tft.setCursor(35, 130);
  tft.setTextSize(1);
  tft.println("KONTYNUUJ");

  while (true) // pętla odpowiedzialna na czekanie na wciśniecie przycisku
  {
    if (digitalRead(BUTTON_G) == HIGH) // gdy zotsanie wciśniety przucisk główny
    {
      delay(100); // poczekaj 0.1s
      break;      // wyjdz z petli
    }
  }
  tft.fillScreen(ST77XX_BLACK);
}
//-------------
void Ekran_startowy() // funkcja odpowiedzialna za wyświtlanie poczatkowej animacji
{
  // Ekran startowy
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(5, 5);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Projekt SM ");
  // nazwa projektu
  tft.setCursor(10, 25);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println("Jedno-reki bandyta");
  // twórcy
  tft.setCursor(5, 125);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println("Jakub Kula");

  tft.setCursor(5, 135);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println("Gabriel Wyrzychowski");
  tft.setCursor(5, 145);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.println("Polsl AiR gr.6 sem.5");
  delay(1500);

  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  // przywitanie
  tft.setCursor(35, 5);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.println("Witaj");
  tft.setCursor(46, 25);
  tft.println(" w ");
  tft.setCursor(20, 45);
  tft.println("kasynie! ");
  // oznajmienie ile ma początkowej $
  tft.setCursor(5, 140);
  tft.setTextSize(1);
  tft.println("Aktualnie masz: 300$");
  tft.setCursor(18, 150);
  tft.println(" Dobrej zabawy!"); // życzenie dobrej zabawy :) !
  delay(1500);

  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);

  instrukcja();

  display_bid();  // wyświetlenie BID
  display_menu(); // wyświeltnie menu

  figury(-35, 3); // pokazanie figury siódemki na pozycji nr 1
  figury(0, 3);   // pokazanie figury siódemki na pozycji nr 2
  figury(35, 3);  // pokazanie figury siódemki na pozycji nr 3
}
