
#define btnUp              3
#define btnRight           2
#define btnQuit            7

byte dino[8] =
{
 B00010,
 B00111,
 B00111,
 B00110,
 B00111,
 B10110,
 B11110,
 B01010
};
byte dino1[8] =
{
 B00010,
 B00111,
 B00111,
 B00110,
 B00111,
 B10110,
 B11110,
 B01000
};

byte dino2[8] =
{
 B00010,
 B00111,
 B00111,
 B00110,
 B00111,
 B10110,
 B11110,
 B00010
};
byte dinosit[8] =
{
 B00000,
 B00000,
 B00010,
 B00111,
 B00111,
 B10110,
 B11110,
 B01010
};
byte dinosit1[8] =
{
 B00000,
 B00000,
 B00010,
 B00111,
 B00111,
 B10110,
 B11110,
 B01000
};
byte dinosit2[8] =
{
 B00000,
 B00000,
 B00010,
 B00111,
 B00111,
 B10110,
 B11110,
 B00010
};
byte obs1[8] =
{
 B00000,
 B00000,
 B10000,
 B11101,
 B11010,
 B01010,
 B01110,
 B01100
};

byte obs2[8] =
{
 B00100,
 B00100,
 B01110,
 B11111,
 B11111,
 B01110,
 B00100,
 B00100
};

byte obs3[8] =
{
 B11111,
 B01110,
 B00100,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};

byte obs4[8] =
{
 B00100,
 B10101,
 B10101,
 B11111,
 B10101,
 B10101,
 B11111,
 B00100
};
byte freep[8] =
{
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};

int mat[2][24] = {
  {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
  {7,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
  };

int dinoAnim[] = {1,0,2,3};

void dinorun_setup() {

  pinMode(btnUp         , INPUT_PULLUP);
  pinMode(btnRight    , INPUT_PULLUP);
  pinMode(btnQuit    , INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("DinoRun");
  delay(2000);
  
  lcd.createChar(0, dino1);
  lcd.createChar(1, dino2);
  lcd.createChar(2, dinosit1);
  lcd.createChar(3, dinosit2);
  lcd.createChar(4, obs1);
  lcd.createChar(5, obs3);
  lcd.createChar(6, obs4);
  lcd.createChar(7, freep);

  gameover();

}

int b1 = 0;
int b2 = 0;
int walk = 0;
int fps = 0;
int maxhigh = 600;
long jumpstarted = 0;
int isJumping = 1;
int pausebetween = 1;
bool gamestarted = false;
int highscore = 0;
int dino_score = 0;

void redraw(){ 
  for(int j = 15; j >= 0; j--){
    for(int i = 0; i < 2; i++){
      lcd.setCursor(j,i);
      lcd.write(mat[i][j]);
    }
  }
  if(!gamestarted){
    String s = "Score: "+String(dino_score);
    String hs = "HighS: "+String(highscore);
    lcd.setCursor(3,0);
    lcd.print(s);
    lcd.setCursor(3,1);
    lcd.print(hs);
  }
}

void cleanmat(){
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 16; j++){
      mat[i][j] = 7;
    }
  }
}

void gameover(){
  cleanmat();
  gamestarted = false;
  pausebetween = 1;
  delay(1000);
  redraw();
}
int dinorun_loop(bool is_running) {
  while (is_running == true){
    if((getKey() == btnUp) && !b1)jumpstarted = millis();
    
    
    b1 = (getKey() == btnUp);
    b2 = (getKey() == btnRight);
    
    if(!gamestarted){
      if(b2 || b1){
        gamestarted = true;
        dino_score = 0;
      }
    }
    if(gamestarted){
      if(fps%3==0)walk+=1;
      walk%=2;
      if(fps%4==0){
        pausebetween -= 1;
        for(int i = 0; i<2;i++){
          for(int j = 0; j<23; j++){
            mat[i][j] = mat[i][j+1];
          }
        }
        mat[0][23] = 7;
        mat[1][23] = 7;
      }
    
      if(!pausebetween)generate_obstacles();
      
      isJumping = !((millis()-jumpstarted<maxhigh) && b1);

      if(!isJumping && mat[0][1]==6){
        gameover();
        is_running = false;
      }
      if(!isJumping && !b2 && mat[0][1]==5){
        gameover();
        is_running = false;
      }
      if(isJumping && mat[1][1]==4){
        gameover();
        is_running = false;
      }
      if(isJumping && mat[1][1]==5 && !b2){
        gameover();
        is_running = false;
      }
      if(!b1) dino_score+=1;
      if(dino_score>highscore)highscore=dino_score; 
      fps+=1;
    }
    if(gamestarted){
      redraw();
      lcd.setCursor(1,isJumping);
      lcd.write(dinoAnim[b2*2+(walk)]);
      
      delay(20);
    }
  }
  return 0;
}

void generate_obstacles(){
  int obscount = random(1,1);
  int types[3][2] = {{7,4},{6,5},{6,7}} ;
  int type = random(0,3);
  for(int i = 0; i< obscount; i++){
    mat[0][16+i] = types[type][0];
    mat[1][16+i] = types[type][1];
  }
  int spacecount = random(2,5);
  pausebetween = obscount + spacecount;
}