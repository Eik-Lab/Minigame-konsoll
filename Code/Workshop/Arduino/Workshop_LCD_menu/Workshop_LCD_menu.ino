
//Workshop_LCD_menu.ino

// *********************************************************************
// includes
// *********************************************************************
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib2.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _LCDML_DISP_cols  16
  #define _LCDML_DISP_rows  2

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol

  // LCD object
  LiquidCrystal_I2C lcd(0x27,_LCDML_DISP_cols,_LCDML_DISP_rows);

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************
    #define SPEED_PAC 150
    #define SPEED_FANT 2000
    #define MAXX 15
    #define MAXY 1

    bool is_running;

    byte points[MAXX + 1][MAXY + 1];

// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)

     
  LCDML_add         (0  , LCDML_0         , 1  , "Games"            , NULL);                    
  LCDML_add         (1  , LCDML_0_1       , 1  , "Hangman"          , NULL);                    
  LCDML_add         (2  , LCDML_0_1_1     , 1  , "Run"              , mFunc_run_hangman);                    
  LCDML_add         (3  , LCDML_0_1_1     , 2  , "Back"             , mFunc_back);              
  LCDML_add         (4  , LCDML_0_1       , 2  , "Pac-Man"          , NULL);             
  LCDML_add         (5  , LCDML_0_1_2     , 1  , "Run"              , mFunc_run_pacman);           
  LCDML_add         (6  , LCDML_0_1_2     , 2  , "Back"             , mFunc_back);   
  LCDML_add         (7  , LCDML_0_1       , 3  , "DinoRun"          , NULL);
  LCDML_add         (8  , LCDML_0_1_3     , 1  , "Run"              , mFunc_run_dinorun);                    
  LCDML_add         (9  , LCDML_0_1_3     , 2  , "Back"             , mFunc_back);   
  LCDML_add         (10 , LCDML_0_1       , 4  , "Tetris"           , mFunc_goToRootMenu);
  LCDML_add         (11 , LCDML_0_1_4     , 1  , "Settings"         , NULL);                    
  LCDML_add         (12 , LCDML_0_1_4     , 2  , "Back"             , mFunc_back);  
  LCDML_add         (13 , LCDML_0_1       , 5  , "Back"             , mFunc_back);
  LCDML_add         (14 , LCDML_0         , 2  , "Filler 1"         , mFunc_information);       
  LCDML_add         (15 , LCDML_0         , 3  , "Filler 2"         , mFunc_timer_info);               
  LCDML_add         (16 , LCDML_0         , 4  , "Screensaver"      , mFunc_screensaver);       
  // ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    16

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // LCD Begin
    lcd.init();
    lcd.backlight();
    //lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  // some display types needs here the initialization

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
    //LCDML.SCREEN_disable();

  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();
  }