
//LCDML_control.ino

// *********************************************************************
// ***************   CONTROL OVER DIGITAL PINS   ***********************
// *********************************************************************
// settings
  unsigned long g_LCDML_DISP_press_time = 0;

  #define _LCDML_CONTROL_digital_low_active      0    // 0 = high active (pulldown) button, 1 = low active (pullup)
                                                      // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
  #define _LCDML_CONTROL_digital_enable_quit     1
  #define _LCDML_CONTROL_digital_enable_lr       1

  #define btnSelect          7
  #define btnUp              3
  #define btnDown            4
  #define btnQuit            6
  #define btnLeft            5
  #define btnRight           2
  #define btnNone            12
// *********************************************************************
void lcdml_menu_control(void)
{
  // If something must init, put in in the setup condition
  if(LCDML.BT_setup()) {
    // runs only once
    // init buttons
    pinMode(btnSelect      , INPUT_PULLUP);
    pinMode(btnUp         , INPUT_PULLUP);
    pinMode(btnDown       , INPUT_PULLUP);
    # if(_LCDML_CONTROL_digital_enable_quit == 1)
      pinMode(btnQuit     , INPUT_PULLUP);
    # endif
    # if(_LCDML_CONTROL_digital_enable_lr == 1)
      pinMode(btnLeft     , INPUT_PULLUP);
      pinMode(btnRight    , INPUT_PULLUP);
    # endif
  }

  #if(_LCDML_CONTROL_digital_low_active == 1)
  #  define _LCDML_CONTROL_digital_a !
  #else
  #  define _LCDML_CONTROL_digital_a
  #endif

  uint8_t but_stat = 0x00;

  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(!digitalRead(btnSelect)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(!digitalRead(btnUp)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(!digitalRead(btnDown)));
  #if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(!digitalRead(btnQuit)));
  #endif
  #if(_LCDML_CONTROL_digital_enable_lr == 1)
  bitWrite(but_stat, 4, _LCDML_CONTROL_digital_a(!digitalRead(btnLeft)));
  bitWrite(but_stat, 5, _LCDML_CONTROL_digital_a(!digitalRead(btnRight)));
  #endif

  if (but_stat > 0) {
    if((millis() - g_LCDML_DISP_press_time) >= 300) {
      g_LCDML_DISP_press_time = millis(); // reset press time

      if (bitRead(but_stat, 0)) { LCDML.BT_enter(); }
      if (bitRead(but_stat, 1)) { LCDML.BT_up();    }
      if (bitRead(but_stat, 2)) { LCDML.BT_down();  }
      if (bitRead(but_stat, 3)) { LCDML.BT_quit();  }
      if (bitRead(but_stat, 4)) { LCDML.BT_left();  }
      if (bitRead(but_stat, 5)) { LCDML.BT_right(); }
    }
  }
}

//function to pickup keystrokes

int getKey() {
  int b = digitalRead(btnNone);
  if (b == HIGH) return btnNone;
  delay(8);
  if (digitalRead(btnRight) == LOW) return btnRight;
  if (digitalRead(btnUp) == LOW) return btnUp;
  if (digitalRead(btnDown) == LOW) return btnDown;
  if (digitalRead(btnLeft) == LOW) return btnLeft;
  if (digitalRead(btnSelect) == LOW) return btnSelect;
}
