// *********************************************************************
// includes
// *********************************************************************

//Er noen ting som trenger å inkluderes (#include)

//må definere noen knapper kanskje?

void(* resetFunc) (void) = 0;             //declare reset function @ address 0

// *********************************************************************
// Variabler
// *********************************************************************


char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int currentIndex = 0;   // Initialize the current index to 0

const char* words[] = {"atmosphere", "verbatim", "postscript", "deadline", "censorship", "shorthand", "monkey", "dickhead", "dilemma", "interface"};
char guessLetter;
char lastGuess;
char guessed[25];
char* secretWord;
int guessedCount = 1;
int wordSize;
int gotOne = 0;
int alreadyGuessed = 0;
int showAsterisk = 0;
int hangman = 0;
int totalRight = 0;


//må vell definere LCD skjermen et sted her

String guessWord = String(10);

// *********************************************************************
// grafikk til Hangman(trenger ikke å tenke på det)
// *********************************************************************

// hangman graphic characters
byte topleft[] = { 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 };
byte topright[] = { 0x1C, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte bottomleft[] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x1F, 0x1F };
byte bottomright[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte head[] = { 0x1C, 0x04, 0x04, 0x0E, 0x0E, 0x00, 0x00, 0x00 };
byte topbody[] = { 0x1C, 0x04, 0x04, 0x0E, 0x0E, 0x04, 0x04, 0x04 };
byte bottombody[] = { 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte rightarm[] = { 0x1C, 0x04, 0x04, 0x0E, 0x0E, 0x05, 0x06, 0x04 };
byte leftarm[] = { 0x1C, 0x04, 0x04, 0x0E, 0x0E, 0x15, 0x0E, 0x04 };
byte rightleg[] = { 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00 };
byte leftleg[] = { 0x04, 0x04, 0x0A, 0x0A, 0x11, 0x00, 0x00, 0x00 };
byte leftarrow[] = { 0x10, 0x18, 0x1C, 0x1E, 0x1E, 0x1C, 0x18, 0x10 };
byte rightarrow[] = { 0x01, 0x03, 0x07, 0x0F, 0x0F, 0x07, 0x03, 0x01 };


// *********************************************************************
// Setup: her går all koden som skal kjøre en gang på starten av programmet
// *********************************************************************
void setup() {

  //kanskje sette opp PINMODE for knappene?

  // må vell starte opp lcd skjermen?

  //hvis du vil ha en startskjerm typ noe som sier HANGMAN el. så kan det legges in her



  // pick a random word using analog 5 for random data
  randomSeed(analogRead(0));
  newWord();

  //draw the board
  draw_board();
}


// *********************************************************************
// Loop: Her går all kode som skal skje om igjen, dette er kjernen av programmet
// *********************************************************************
void loop() {

//En måte å bla gjennom alfabetet for å kunne velge bokstaver
//kanskje en if-statement som bestemmer om du trykket deg til høyre eller venstre?

  guessLetter = alphabet[currentIndex];

  // noe for å passe på at det ikke blir valgt samme bokstav om igjen
  if (guessLetter != lastGuess) {


    //kan brukes til å vise bokstaver som har blitt gjettet, evntuelt kan den fjernes
    for (int x = 0; x < guessedCount; x++) {
      //trengs noe mere kode her
    }

  //kan være greit å vise bokstaver forran og etter den du har valgt
  //så blir det litt lettere å navigere for å finne bokstaver
  //husk å bestemme hvor du skal skrive fra lcd.setCursor(x,y)

  // kanskje også greit med noe for å indikere hvilken bokstav som er valgt før den blir bekreftet 

  // lcd.write(4); og lcd.write(5); kan brukes for å skrive grafikken til venstre og høyre pil
  }

  //valg av bokstav

  if (getKey() == btnSelect) {
    //sjekk om bokstaven har blitt gjettet før?

    //hvis bokstaven ikke er gjettet før legg den til i en liste over gjetta bokstaver

    // hvis bokstaven ikke samsvarer med noen bokstaver i ordet 
    if(){
      hangman++;
      draw_hangman(hangman);
    }

    //må lage en kriterie for hvordan spillet slutter
    if () {
      gameOver();
    }
    
  }
}


// *********************************************************************
// Funksjoner
// *********************************************************************

void newWord() {
  //velg et tilfeldig tall
  int pick = random(10); // juster tallet etter antall ord i ordlisten


  //noe code for å bestemme et tilfeldig ord
  //kan være greit å definere størrelsen på ordet også
  //så kan det bli brukt til å understreke og vise lengden på ordet du prøver å finne
  //se nederste delen av funksjonen draw_board() hvor wordSize brukes.
}

void gameOver(int whatToDo) {
  //burde finne ut om spiller har vunnet eller tapt
  //så det kan vises ulike skjermer basert på om de vant eller tapte

  resetFunc();      // reset arduino for et nytt spill
}


// *********************************************************************
// Funksjoner relatert til grafikken
// *********************************************************************

void draw_board() {
  // define the custom characters
  lcd.createChar(0, topleft);
  lcd.createChar(1, topright);
  lcd.createChar(2, bottomleft);
  lcd.createChar(3, bottomright);
  lcd.createChar(4, leftarrow);
  lcd.createChar(5, rightarrow);

  // draw blank hangman table
  lcd.clear();
  lcd.home();
  lcd.write(byte(0));
  lcd.write(1);
  lcd.setCursor(0, 1);
  lcd.write(2);
  lcd.write(3);

  // print underlines
  lcd.setCursor(3, 1);
  for (int x = 0; x < wordSize; x++) {
    lcd.print("_");
  }
}

void draw_hangman(int var) {
  // Draw hangman body parts based on 'var'
  switch (var) {
    case 1:
      lcd.createChar(1, head);           // head
      break;
    case 2:
      lcd.createChar(1, topbody);        // body
      lcd.createChar(3, bottombody);
      break;
    case 3:
      lcd.createChar(1, rightarm);       // right arm
      break;
    case 4:
      lcd.createChar(1, leftarm);        // left arm
      break;
    case 5:
      lcd.createChar(3, rightleg);       // right leg
      break;
    case 6:
      lcd.createChar(3, leftleg);        // left leg
      break;
    case 7:
      gameOver(0);
    default:
      break;
  }
}

// *********************************************************************
// Funksjon for å korte need og gjøre test av knappetrykk kortere
// *********************************************************************
int getKey() {
  if (digitalRead(btnRight) == LOW) return btnRight;
  if (digitalRead(btnLeft) == LOW) return btnLeft;
  if (digitalRead(btnSelect) == LOW) return btnSelect;
}