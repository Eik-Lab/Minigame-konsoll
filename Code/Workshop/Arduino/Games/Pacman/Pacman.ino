#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define VITESSE_PAC 150
#define VITESSE_FANT 2000
#define MAXX 15
#define MAXY 1

#define btnRight     2
#define btnUp        3
#define btnDown      4
#define btnLeft      5
#define btnSelect    6
#define btnNone      7

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pacman sprite
byte pacman[8] = {
  B00000,
  B00000,
  B01110,
  B11011,
  B11100,
  B01110,
  B00000,
  B00000
};

// fantom sprite
byte fantome[8] = {
  B00000,
  B00000,
  B01110,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000
};

// Coin sprite
byte point[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B01110,
  B00000,
  B00000,
  B00000
};

// Tableau des points à manger
byte points[MAXX + 1][MAXY + 1];

int xpac = 2; // Position de pacman en X (colone)
int ypac = 1; //position de pacman en y (ligne)
int xfant = 15; // Position du fantome en X (colone)
int yfant = 0; // Position du fantome en Y (ligne)
byte light = true; //Eclairage
long keystruck = 0; //dernier appui sur un bouton
long poursuite = 0; //dernier movement du fantome
byte partieEnCours = true; // pour eviter de boucler sur la fin
byte vide = false; // pour tester si tout est manger

byte level = 0; // niveau
int score = 0; // niveau

void setup() {

  // Initialize buttons as inputs
  pinMode(btnRight, INPUT_PULLUP);
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnSelect, INPUT_PULLUP);

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, pacman);
  lcd.createChar(1, fantome);
  lcd.createChar(2, point);
  lcd.setCursor(0, 0);
  lcd.print("Pacman!");
  delay(5000); // Splash screen
  initLevel(); // initialisation du tableau
}

void loop() {
  // Check button input every 200ms
  if (millis() - keystruck > VITESSE_PAC) {
    int joy = getKey();
    switch (joy) {
      case btnNone:
        break;
      case btnLeft:
        move(-1, 0);
        break;
      case btnRight:
        move(1, 0);
        break;
      case btnUp:
        move(0, -1);
        break;
      case btnDown:
        move(0, 1);
        break;
    }
    keystruck = millis();
  }

  // Move the ghost periodically
  if (millis() - poursuite > VITESSE_FANT / (level + 1) + 10) {
    pursue();
    poursuite = millis();
  }

  // Check for collision with ghost
  if ((xpac == xfant) && (ypac == yfant) && (partieEnCours)) {
    lost();
  }
}

void move(int x, int y) {
  int oldx = xpac;
  int oldy = ypac;
  if (((xpac + x) >= 0) && ((xpac + x) <= MAXX)) xpac = xpac + x;
  if (((ypac + y) >= 0) && ((ypac + y) <= MAXY)) ypac = ypac + y;
  lcd.setCursor(xpac, ypac);
  lcd.write(byte(0));
  lcd.setCursor(oldx, oldy);
  if ((xpac != oldx) || (ypac != oldy)) lcd.print(" ");
  if (points[xpac][ypac]) {
    points[xpac][ypac] = false;
    score++;
  }
  vide = true;
  for (int i = 0; i <= MAXX; i = i + 1)
    for (int j = 0; j <= MAXY; j = j + 1)
      if (points[i][j])  vide = false;
  if ((vide) && (partieEnCours)) won();
}

void lost() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("***Game Over****");
  lcd.setCursor(3, 1);
  lcd.print("***");
  lcd.print(score);
  lcd.print("***");
  delay(2000);
}

void won() {
  level++;
  lcd.setCursor(0, 0);
  lcd.print("*** Next level ***");
  lcd.setCursor(0, 1);
  lcd.print("*** ");
  lcd.print(level, DEC);
  lcd.print(" ***");
  delay(2000);
  initLevel();
}

void pursue() {
  int oldx = xfant;
  int oldy = yfant;
  if (yfant < ypac) yfant = yfant + 1;
  else if (yfant > ypac) yfant = yfant - 1;
  else if (xfant < xpac) xfant = xfant + 1;
  else if (xfant > xpac) xfant = xfant - 1;
  lcd.setCursor(xfant, yfant);
  lcd.write(1);
  lcd.setCursor(oldx, oldy);
  if ((oldx != xfant) || (oldy != yfant)) {
    if (points[oldx][oldy]) lcd.write(2);
    else lcd.print(" ");
  }
}

void initLevel() {
  for (int i = 0; i <= MAXX; i = i + 1)
    for (int j = 0; j <= MAXY; j = j + 1) {
      points[i][j] = true;
      lcd.setCursor(i - 1, j - 1);
      lcd.write(2);
    }
  lcd.setCursor(xpac, ypac);
  lcd.write(byte(0));
  lcd.setCursor(xfant, yfant);
  lcd.write(1);
  poursuite = millis();
  vide = false;
}

int getKey() {
  if (digitalRead(btnRight) == LOW) return btnRight;
  if (digitalRead(btnUp) == LOW) return btnUp;
  if (digitalRead(btnDown) == LOW) return btnDown;
  if (digitalRead(btnLeft) == LOW) return btnLeft;
  if (digitalRead(btnSelect) == LOW) return btnSelect;
}
