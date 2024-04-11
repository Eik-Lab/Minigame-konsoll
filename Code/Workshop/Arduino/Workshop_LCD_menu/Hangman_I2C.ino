  #define btnSelect          7
  #define btnLeft            5
  #define btnRight           2

void(* resetFunc) (void) = 0;             //declare reset function @ address 0

String guessWord = String(10);

  char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int currentIndex = 0;
  const char* words[] = {"atmosphere", "verbatim", "postscript", "deadline", "censorship", "shorthand", "monkey", "dickhead", "dilemma", "interface"};
  char guessLetter;
  char guessLast;
  char guessed[25];
  char* secretWord;
  int guessedCount = 1;
  int wordSize;
  int gotOne = 0;
  int alreadyGuessed = 0;
  int showAsterisk = 0;
  int hangman = 0;
  int totalRight = 0;

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

void hangman_setup() {

  currentIndex = 0;
  guessedCount = 1;
  gotOne = 0;
  alreadyGuessed = 0;
  showAsterisk = 0;
  hangman = 0;
  totalRight = 0;

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("HANGMANDUINO");
  delay(2000);

  // pick a random word using analog 5 for random data
  randomSeed(analogRead(0));
  newWord();

  //draw the board
  draw_board();
}

void newWord() {
  //pick a random word from the list
  int pick = random(10); // Adjusted for the size of the words array
  const char* pickWord = words[pick];
  guessWord = pickWord;
  wordSize = guessWord.length();
}

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

void hangman_loop() {

  int key = getKey();
  switch (key) {
    case btnLeft:                       // If the Left button is pressed
      currentIndex--;                   // Decrease the current index
      if (currentIndex < 0)             // If the current index is less than 0
        currentIndex = sizeof(alphabet) / sizeof(alphabet[0]) - 1; // Set it to the last index
      break;                       // Debounce delay

    case btnRight:                      // If the right button is pressed
      currentIndex++;                   // Increase the current index
      if (currentIndex >= sizeof(alphabet) / sizeof(alphabet[0])) // If the current index exceeds the array size
        currentIndex = 0;               // Set it to the first index
      break;                       // Debounce delay
  }

  guessLetter = alphabet[currentIndex];

  // if letter is different from last, print to lcd
  // this prevents from printing the same char over and over
  if (guessLetter != guessLast) {
    guessLast = guessLetter;
    showAsterisk = 0;

    // cycle through all guessed letters and determine whether to show * or the letter
    for (int x = 0; x < guessedCount; x++) {
      if (guessLetter == guessed[x]) {
        showAsterisk = 1;
      }
    }

    // print letters to the left of selected letter
    lcd.setCursor(3, 0);
    for (int x = 5; x >= 1 ; x--) {
      if (currentIndex - x >= 0) {
        lcd.print(alphabet[currentIndex - x]);
      }
      else {
        lcd.print(" ");
      }
    }

    // print left arrow
    lcd.write(4);

    // print the letter
    if (showAsterisk == 0) {
      lcd.setCursor(9, 0);
      lcd.print(guessLetter);
      alreadyGuessed = 0;
    }
    // print a *
    else {
      lcd.setCursor(9, 0);
      lcd.print("*");
      alreadyGuessed = 1;
    }

    // print right arrow
    lcd.write(5);

    // print letters to the right of selected letter
    lcd.setCursor(11, 0);
    for (int x = 1; x <= 5 ; x++) {
      if (currentIndex + x <= 25) {
        lcd.print(alphabet[currentIndex + x]);
      }
      else {
        lcd.print(" ");
      }
    }
  }

  //Selection of letter

  if (getKey() == btnSelect) {
    gotOne = 0;
    if (alreadyGuessed == 0) {
      alreadyGuessed = 1;
      lcd.setCursor(9, 0);
      lcd.print("*");
      char buf[wordSize+1];
      guessWord.toCharArray(buf,wordSize+1);
      for (int i = 0; i < wordSize; i++) {
        if (buf[i] == guessLetter) {
          lcd.setCursor(i + 3, 1);
          lcd.print(guessLetter);
          gotOne = 1;
          totalRight = totalRight + 1;
        }
      }

      // add letter to guessed letter array
      guessed[guessedCount] = guessLetter;
      guessedCount++;

      // none of the letters match, draw the next body part on the hangman
      if (gotOne == 0) {
        hangman++;
        draw_hangman(hangman);
      }

      //all letters have been guessed...WIN!
      if (totalRight == wordSize) {
        gameOver(1);
      }
    }
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

void gameOver(int whatToDo) {
  // decide whether win, lose or restart game
  switch (whatToDo) {
    case 0:  // GAME OVER
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("GAME");
      lcd.setCursor(6, 1);
      lcd.print("OVER");
      break;
    case 1:  // WINNER
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("HANGMAN");
      lcd.setCursor(4, 1);
      lcd.print("MASTER!");
      break;
  }
  delay(2000);
  LCDML.FUNC_goBackToMenu(1);     // Go back to game menu
}
