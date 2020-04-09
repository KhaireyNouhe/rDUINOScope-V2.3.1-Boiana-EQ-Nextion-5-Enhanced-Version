//
//    rDUINOScope - Arduino based telescope control system (GOTO).
//    Copyright (C) 2016 Dessislav Gouzgounov (Desso)
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    PROJECT Website: http://rduinoscope.byethost24.com
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// ......................................................................
//  This part of the code take care of:
//  - Drawing interface screens;
//  - Day / Night mode set;
//  - Draws symbols on certain screens (e.g. XX/XX/XXXX in day/time screen)
//  - Draws OnScreen Messages
//
//  Screens are separated like:
//    * CURRENT_SCREEN==0  - drawGPSScreen() Where the GPS coordinates are displayed
//    * CURRENT_SCREEN==1  - drawClockScreen() Captures updates on the time and date
//    * CURRENT_SCREEN==2  -                - not used
//    * CURRENT_SCREEN==3  - drawSelectAlignment() Select Alignment method (only have 3 buttons)
//    * CURRENT_SCREEN==4  - drawMainScreen() Captures all clicks on the MAIN Screen of the application
//    * CURRENT_SCREEN==5  - drawCoordinatesScreen() Only have "back" button
//    * CURRENT_SCREEN==6  - drawLoadScreen() Captures input on Load screen (all of them: Messier && Treasurres)
//    * CURRENT_SCREEN==7  - drawOptionsScreen();
//    * CURRENT_SCREEN==8  -                - not used
//    * CURRENT_SCREEN==9  -                - not used
//    * CURRENT_SCREEN==10  - drawSTATScreen()
//    * CURRENT_SCREEN==11  - drawAutoGuidingScreen();
//    * CURRENT_SCREEN==12  - drawStarSyncScreen() - To Select Alignment Star;
//    * CURRENT_SCREEN==13  - drawConstelationScreen(int indx) - to actually align on Star. Called few times per alignment procedure.
//    * CURRENT_SCREEN==14  - drawAutoGuidingScreen();
//    * CURRENT_SCREEN==15  - drawSunConfScreen();
///////////////////////////////////////////////////////////////////// Draw Remove Time in Clock Screen /////////////////////////////////////////////////////////////////////////////

// Takes Place Locally on the Nextion TFT.
///////////////////////////////////////////////////////////////////// Draw GPS Screen /////////////////////////////////////////////////////////////////////////////

void drawGPSScreen()
{
  CURRENT_SCREEN = 0;
  GPS.show(); // Nextion >>> Show GPS Page

  ////////////////////////// Nextion GPS Screen Time Sync ////////////////////////

  String Date_q = String(rtc.getDateStr());
  String Time_q = String(rtc.getTimeStr());
  // Sync Nextion RTC Year to Arduino RTC
  int Y = Date_q.substring(6).toInt();
  Serial1.print("rtc0=");
  Serial1.print(Y);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Month to Arduino RTC
  int M = Date_q.substring(3, 5).toInt();
  Serial1.print("rtc1=");
  Serial1.print(M);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Day to Arduino RTC
  int D = Date_q.substring(0, 2).toInt();
  Serial1.print("rtc2=");
  Serial1.print(D);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Hour to Arduino RTC
  int H = Time_q.substring(0, 2).toInt(); // hours
  Serial1.print("rtc3=");
  Serial1.print(H);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Minute to Arduino RTC
  int MN = Time_q.substring(3, 5).toInt();
  Serial1.print("rtc4=");
  Serial1.print(MN);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Second to Arduino RTC
  int S = Time_q.substring(6).toInt();
  Serial1.print("rtc5=");
  Serial1.print(S);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  // Draw SKIP BTN
  coord_ass_text.setText("Will assign coordinates      for Cairo, Egypt"); // Nextion
}

///////////////////////////////////////////////////////////////////// Draw Clock Screen /////////////////////////////////////////////////////////////////////////////

void drawClockScreen()
{
  CURRENT_SCREEN = 1;
  if (isSummerTime) {
    Summer_Time = 1;
    btdst.setValue (1);
    Serial1.print("wepo 1,30");  // Change page boot To Night Mode
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  } else {
    Summer_Time = 0;
    btdst.setValue (0);
    Serial1.print("wepo 0,30");  // Change page boot To Night Mode
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }

  Time_page.show();
}

///////////////////////////////////////////////////////////////////// Draw Alignment Screen /////////////////////////////////////////////////////////////////////////////

void drawSelectAlignment() {
  CURRENT_SCREEN = 3;
  Alignment.show();
}

///////////////////////////////////////////////////////////////////// Draw Main Screen /////////////////////////////////////////////////////////////////////////////

void drawMainScreen()
{
  CURRENT_SCREEN = 4;
  Main.show(); // Nextion Show Main Screen
  w_DateTime[0] = 0;
  calculateLST_HA();
  update_time = millis();

  ////////////////////////// Nextion Main Screen Time Sync ////////////////////////

  String Time_q = String(rtc.getTimeStr());
  // Sync Nextion RTC Hour to Arduino RTC
  int H = Time_q.substring(0, 2).toInt(); // hours
  Serial1.print("rtc3=");
  Serial1.print(H);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Minute to Arduino RTC
  int MN = Time_q.substring(3, 5).toInt();
  Serial1.print("rtc4=");
  Serial1.print(MN);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Second to Arduino RTC
  int S = Time_q.substring(6).toInt();
  Serial1.print("rtc5=");
  Serial1.print(S);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  if ((int)LST < 10) {
    main_LST1.setValue((int)LST); // Nextion
  } else {
    main_LST1.setValue((int)LST); // Nextion
  }

  if ((LST - (int)LST) * 60 < 10) {
    // Nextion
    int mainLST2_Val = ((LST - (int)LST) * 60);
    main_LST2.setValue (mainLST2_Val);
  } else {
    // Nextion
    int mainLST2_Val = ((LST - (int)LST) * 60);
    main_LST2.setValue (mainLST2_Val);
  }

  main_temp.setValue (_temp);                         // Nextion
  main_humidity.setValue (_humid);                    // Nextion

  /////////////////////////////////// Nextion Main Screen Date Sync /////////////////////
  String Date_q = String(rtc.getDateStr());
  // Sync Nextion RTC Year to Arduino RTC
  int Y = Date_q.substring(6).toInt();
  Serial1.print("rtc0=");
  Serial1.print(Y);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Month to Arduino RTC
  int M = Date_q.substring(3, 5).toInt();
  Serial1.print("rtc1=");
  Serial1.print(M);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Sync Nextion RTC Day to Arduino RTC
  int D = Date_q.substring(0, 2).toInt();
  Serial1.print("rtc2=");
  Serial1.print(D);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  // Nextion
  Serial1.print("main_LAT.txt=");
  Serial1.print("\"");
  Serial1.print(OBSERVATION_LATTITUDE, 4);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("main_LONG.txt=");
  Serial1.print("\"");
  Serial1.print(OBSERVATION_LONGITUDE, 4);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("main_ALT.txt=");
  Serial1.print("\"");
  Serial1.print(OBSERVATION_ALTITUDE, 0);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

#ifdef use_battery_level
  Serial1.print("batt_percent.txt=");// Nextion Battery Voltage Text
  Serial1.print("\"");
  Serial1.print(calculateBatteryLevel());
  Serial1.print(" %");
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  va_batt.setValue(calculateBatteryLevel());  // Nextion Battery Voltage Indicator
  Serial1.print("wepo va_batt.val,380");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  battery_power.setValue(calculateBatteryLevel()); // Nextion Battery Progress bar Indicator
  Serial1.print("ref battery_power");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("vis t3,1");   // Show degrees indicators - - - -
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("vis t4,1");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("vis t6,1");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("vis t7,1");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

#endif

  // Data for the observed object....
  if (OBJECT_NAME != "") {
    // Nextion
    Serial1.print("main_obj_name.txt=");
    Serial1.print("\"");
    Serial1.print(OBJECT_NAME);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    if ((OBJECT_NAME != "CP") && (IS_BT_MODE_ON == false)) {
      // Nextion
      Serial1.print("main_HA.txt=");
      Serial1.print("\"");
      Serial1.print(HAHour, 0);
      Serial1.print("h ");
      Serial1.print(HAMin, 1);
      Serial1.println("m   ");
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }

    if ((OBJECT_NAME != "") && (ALT < 0)) {               // If object is below horizon
      ////////////////////////////////////////// Nextion //////////////////
      Serial1.print("obj_full_name.pco="); // Change Color of Alert Phrase to RED
      Serial1.print(63488);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("main_obj_name.pco="); // Change Color of Object Name to RED
      Serial1.print(63488);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      obj_full_name.setText("OBJECT NOT VISIBLE!"); // Nextion
      tm3.enable(); // Nextion // Object Not Visible Animation
    }
    else
    {
      char obj_name[50];
      String OBJ_NAME = "objects/";
      OBJ_NAME += String(OBJECT_NAME) + ".bmp";
      tm3.disable();// Nextion
#ifdef serial_debug
      Serial.print("file name: ");
      Serial.println(OBJ_NAME);
      Serial.print("SD.open(OBJ_NAME) = ");
      Serial.println(SD.open(OBJ_NAME));
#endif

      /*  // Draw Image of Object           // Nextion Doesn't Support that
                 if (SD.open(OBJ_NAME))
                 {
                   OBJ_NAME.toCharArray(obj_name, 50);
                   bmpDraw(obj_name, 235, 200);
                   //delay(200);
                 }
      */

      if  (OBJECT_NAME == "MERCURY")
      {
        main_obj_image.setPic(55);
      } else if  (OBJECT_NAME == "VENUS")
      {
        main_obj_image.setPic(62);
      } else if  (OBJECT_NAME == "MARS")
      {
        main_obj_image.setPic(32);
      } else if (OBJECT_NAME == "Jupiter")
      {
        main_obj_image.setPic(42);
      } else if  (OBJECT_NAME == "SATURN")
      {
        main_obj_image.setPic(59);
      } else if  (OBJECT_NAME == "URANUS")
      {
        main_obj_image.setPic(61);
      } else if  (OBJECT_NAME == "NEPTUNE")
      {
        main_obj_image.setPic(57);
      } else if  (OBJECT_NAME == "PLUTO")
      {
        main_obj_image.setPic(58);
      } else if  (OBJECT_NAME == "SUN")
      {
        main_obj_image.setPic(60);
      } else if  (OBJECT_NAME == "MOON")
      {
        main_obj_image.setPic(56);
      } else if  (OBJECT_NAME == "BlueTooth")
      {
        main_obj_image.setPic(63);
      } else if  (OBJECT_NAME == "M1")
      {
        main_obj_image.setPic(64);
      } else if  (OBJECT_NAME == "M8")
      {
        main_obj_image.setPic(65);
      }
      else if  (OBJECT_NAME == "M16")
      {
        main_obj_image.setPic(66);
      } else if  (OBJECT_NAME == "M17")
      {
        main_obj_image.setPic(67);
      } else if  (OBJECT_NAME == "M20")
      {
        main_obj_image.setPic(68);
      } else if  (OBJECT_NAME == "M27")
      {
        main_obj_image.setPic(69);
      } else if  (OBJECT_NAME == "M29")
      {
        main_obj_image.setPic(70);
      } else if  (OBJECT_NAME == "M33")
      {
        main_obj_image.setPic(71);
      } else if  (OBJECT_NAME == "M42")
      {
        main_obj_image.setPic(72);
      } else if  (OBJECT_NAME == "M43")
      {
        main_obj_image.setPic(73);
      } else if  (OBJECT_NAME == "M51")
      {
        main_obj_image.setPic(74);
      } else if  (OBJECT_NAME == "M58")
      {
        main_obj_image.setPic(75);
      } else if  (OBJECT_NAME == "M61")
      {
        main_obj_image.setPic(76);
      } else if  (OBJECT_NAME == "M66")
      {
        main_obj_image.setPic(77);
      } else if  (OBJECT_NAME == "M74")
      {
        main_obj_image.setPic(78);
      } else if  (OBJECT_NAME == "M76")
      {
        main_obj_image.setPic(79);
      } else if  (OBJECT_NAME == "M77")
      {
        main_obj_image.setPic(80);
      } else if  (OBJECT_NAME == "M78")
      {
        main_obj_image.setPic(81);
      } else if  (OBJECT_NAME == "M81")
      {
        main_obj_image.setPic(82);
      } else if  (OBJECT_NAME == "M82")
      {
        main_obj_image.setPic(83);
      } else if  (OBJECT_NAME == "M83")
      {
        main_obj_image.setPic(84);
      } else if  (OBJECT_NAME == "M88")
      {
        main_obj_image.setPic(85);
      } else if  (OBJECT_NAME == "M90")
      {
        main_obj_image.setPic(86);
      } else if  (OBJECT_NAME == "M91")
      {
        main_obj_image.setPic(87);
      } else if  (OBJECT_NAME == "M94")
      {
        main_obj_image.setPic(88);
      } else if  (OBJECT_NAME == "M95")
      {
        main_obj_image.setPic(89);
      } else if  (OBJECT_NAME == "M96")
      {
        main_obj_image.setPic(90);
      } else if  (OBJECT_NAME == "M98")
      {
        main_obj_image.setPic(91);
      } else if  (OBJECT_NAME == "M99")
      {
        main_obj_image.setPic(92);
      } else if  (OBJECT_NAME == "M100")
      {
        main_obj_image.setPic(93);
      } else if  (OBJECT_NAME == "M101")
      {
        main_obj_image.setPic(94);
      } else if  (OBJECT_NAME == "M102")
      {
        main_obj_image.setPic(95);
      } else if  (OBJECT_NAME == "M104")
      {
        main_obj_image.setPic(96);
      } else if  (OBJECT_NAME == "M106")
      {
        main_obj_image.setPic(97);
      } else if  (OBJECT_NAME == "M109")
      {
        main_obj_image.setPic(98);
      } else if  (OBJECT_NAME == "CP")
      {
        main_obj_image.setPic(99);
      }
      else
      {
        main_obj_image.setPic(54);
      }

      /****************************************************************Nextion****/
      Serial1.print("main_obj_name.txt=");
      Serial1.print("\"");
      Serial1.print(OBJECT_NAME);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);

      /*****************************************************************************/
      Serial1.print("main_obj_info.txt=");
      Serial1.print("\"");
      Serial1.print(OBJECT_DETAILS);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);

      /*****************************************************************************/
      Serial1.print("obj_full_name.txt=");
      Serial1.print("\"");
      Serial1.print(OBJECT_DESCR);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }

    /*****************************************************************************/
    Serial1.print("main_obj_info.txt=");
    Serial1.print("\"");
    Serial1.print(OBJECT_DETAILS);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    /***************************************************Nextion Main RA / HA / DEC *****************************/

    Serial1.print("main_RA.txt=");
    Serial1.print("\"");
    Serial1.print(OBJECT_RA_H, 0);
    Serial1.print("h ");
    Serial1.print(OBJECT_RA_M, 2);
    Serial1.println("'   ");
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    Serial1.print("main_DEC.txt=");
    Serial1.print("\"");
    Serial1.print(OBJECT_DEC_D, 0);
    Serial1.print("  ");
    Serial1.print(abs(OBJECT_DEC_M), 2);
    Serial1.println("'    ");
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    // Show t0 that shows ˚ symbol
    Serial1.print("vis t0,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    /********************************************************************************/

    // End data for the observed object...

    if (IS_TRACKING == true) {
      tm1.enable();// Nextion Tracking Animation Start
    } else {
      tm1.disable(); // Nextion Tracking Animation Stop
    }

    if (IS_BT_MODE_ON == true) {
      tm2.enable();// Nextion Bluetooth Icon Animation Start
    } else {
      tm2.disable(); // Nextion Bluetooth Icon Animation Stop
    }

  } else {
    obj_full_name.setText("No object is selected!"); // Nextion
    main_obj_info.setText("Use LOAD Button below to select an  object from the Catalog.");// Nextion
  }
}

///////////////////////////////////////////////////////////////////// Draw Coordinates Screen /////////////////////////////////////////////////////////////////////////////

void drawCoordinatesScreen() {
  CURRENT_SCREEN = 5;
  Coordinates.show();  // Nextion Coordinates Page
}

///////////////////////////////////////////////////////////////////// Draw Load Screen /////////////////////////////////////////////////////////////////////////////

void drawLoadScreen() {
  CURRENT_SCREEN = 6;
  Load.show();     // Show Page Load on Nextion
  //drawLoadObjects();
}

///////////////////////////////////////////////////////////////////// Draw Options Screen /////////////////////////////////////////////////////////////////////////////

void drawOptionsScreen()
{
  CURRENT_SCREEN = 7;
  Options.show();     // Nextion Show Page Options
  // Update Options...
  updateTrackingMode_opt();
  updateMeridianFlip_opt();
  updateSound_opt();
  updateStepper_opt();
}

///////////////////////////////////////////////////////////////////// Draw OnScreen Messages /////////////////////////////////////////////////////////////////////////////

void OnScreenMsg(int Msg) {

  if (Msg == 1) {  //   "  MOVING..  Step Back,  Please !"
    if (CURRENT_SCREEN == 6) // If we're in Load Screen.
    {
      Load_message.setText("  MOVING.. Step Back ,  Please !");
      Serial1.print("vis Load_message,1");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    } else if (CURRENT_SCREEN == 12) // If we're in StarSyncScreen.
    {
      Sync_message.setText("  MOVING.. Step Back ,  Please !");
      Serial1.print("vis Sync_message,1");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }
  } else if (Msg == 2) { // " Warning !  Tracking  was Turned    OFF !"
    Main_message.setText(" Warning !  Tracking  was Turned    OFF !");
    Serial1.print("vis Main_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    drawMainScreen();

  } else if (Msg == 3) { // "  Error !  Object  Not  Visible!"
    Sync_message.setText("  Error !  Object  Not  Visible!");
    Serial1.print("vis Sync_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    delay(1000);
    Serial1.print("vis Sync_message,0");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  } else if (Msg == 4) { // Pick Again "ALT=" + String(ALT, 0); "RA= " + String(OBJECT_RA_H, 0);
    // "Pick Again!ALT:       RA:"

  } else if (Msg == 5) { // "  Error !  Please Turn Steppers      ON!"
    Main_message.setText("  Error !  Please Turn Steppers      ON!");
    Serial1.print("vis Main_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    if (IS_SOUND_ON) {
      SoundOn(note_C, 32);
      delay(200);
      SoundOn(note_C, 32);
      delay(200);
      SoundOn(note_C, 32);
      delay(1000);
    }

  } else if (Msg == 6) { // "Backing Up! Step Back   Please!"
    Main_message.setText("Backing Up! Step Back   Please!");
    Serial1.print("vis Main_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (Msg == 7) { // " Just Look   Around    Yourself!"
    Load_message.setText(" Just Look   Around    Yourself!");
    Serial1.print("vis Load_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (Msg == 8) {
    Guide_message.setText(" Connected     to        PHD2");
    Serial1.print("vis Guide_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    if (IS_SOUND_ON) {
      SoundOn(note_C, 32);
      delay(200);
      SoundOn(note_C, 32);
      delay(200);
      SoundOn(note_C, 32);
      delay(1000);
    }
    Serial1.print("vis Guide_message,0");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

  } else if (Msg == 9) {
    Guide_message.setFont(6);
    Guide_message.setText(">Disconnected    from         PHD2");
    Serial1.print("vis Guide_message,1");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    if (IS_SOUND_ON) {
      SoundOn(note_C, 32);
      delay(200);
      SoundOn(note_C, 32);
      delay(200);
      SoundOn(note_C, 32);
      delay(1000);
    }
    Serial1.print("vis Guide_message,0");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
}

///////////////////////////////////////////////////////////////////// Consider Day/Night Mode /////////////////////////////////////////////////////////////////////////////

void considerDayNightMode() {
  boolean prev_night_mode = IS_NIGHTMODE;
  if (analogRead(DAY_NIGHT_PIN) < 800) {
    IS_NIGHTMODE = true;
  } else {
    IS_NIGHTMODE = false;
  }
  // Now make sure it works for all screen - redraws them when mode switched
  if (prev_night_mode != IS_NIGHTMODE) {
    if (IS_NIGHTMODE == true) {
      IS_NIGHTMODE = true;
      // Nextion Night mode
      Serial1.print("wepo 1,140");  // Change page boot To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,150"); // Change page GPS To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,160");  // Change page Time_Set To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,170");  // Change page Alignment To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,180");  // Change page Sync To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,190");  // Change page Manual_Align To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,200");  // Change page Main To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,210");  // Change page Menu To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,220");  // Change page Load To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,230");  // Change page Options To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,240");  // Change page Coordinates To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,250");  // Change page Stat To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 1,255");  // Change page Autoguiding To Night Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    } else {
      IS_NIGHTMODE = false;
      // Nextion Day Mode
      Serial1.print("wepo 0,140");  // Change page boot To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,150"); // Change page GPS To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,160");  // Change page Time_Set To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,170");  // Change page Alignment To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,180");  // Change page Sync To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,190");  // Change page Manual_Align To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,200");  // Change page Main To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,210");  // Change page Menu To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,220");  // Change page Load To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,230");  // Change page Options To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,240");  // Change page Coordinates To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,250");  // Change page Stat To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.print("wepo 0,255");  // Change page Autoguiding To day Mode
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }
    if (CURRENT_SCREEN == 0) {
      drawGPSScreen();
    } else if (CURRENT_SCREEN == 1) {
      drawClockScreen();
    } else if (CURRENT_SCREEN == 3) {
      drawSelectAlignment();
    } else if (CURRENT_SCREEN == 4) {
      drawMainScreen();
    } else if (CURRENT_SCREEN == 5) {
      drawCoordinatesScreen();
    } else if (CURRENT_SCREEN == 6) {
      drawLoadScreen();
    } else if (CURRENT_SCREEN == 7) {
      drawOptionsScreen();
    } else if (CURRENT_SCREEN == 10) {
      drawSTATScreen();
    } else if (CURRENT_SCREEN == 12) {
      drawAlignObjects_ali();
    } else if (CURRENT_SCREEN == 13) {
      drawConstelationScreen(0);
    } else if (CURRENT_SCREEN == 11) {
      drawAutoGuidingScreen();
    }
  }
}

///////////////////////////////////////////////////////////////////// Draw Main Screen Menu /////////////////////////////////////////////////////////////////////////////
// Takes place locally on Nextion!

///////////////////////////////////////////////////////////////////// Draw Update date/time in Time Screen ////////////////////////////////////////////////////////////////////////
// Takes place locally on Nextion!

///////////////////////////////////////////////////////////////////// Draw AutoGuiding Screen /////////////////////////////////////////////////////////////////////////////
void drawAutoGuidingScreen() {
  CURRENT_SCREEN = 11;
  Autoguiding.show();
}
///////////////////////////////////////////////////////////////////// Draw Status bar on Main Page /////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////// Update tracking mode on Options Screen ////////////////////////////////////////////////////////////////////
void updateTrackingMode_opt()
{

}
///////////////////////////////////////////////////////////////////// Update Screen Time-out buttons in Options Screen /////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////// Update Meridian Flip buttons in Options Screen //////////////////////////////////////////////////////////////
void updateMeridianFlip_opt()
{

}
///////////////////////////////////////////////////////////////////// Update Sound buttons in Options Screen //////////////////////////////////////////////////////////////
void updateSound_opt()
{

}
///////////////////////////////////////////////////////////////////// Update Steppers buttons in Options Screen //////////////////////////////////////////////////////////////
void updateStepper_opt()
{

}
///////////////////////////////////////////////////////////////////// Update Triangle Brightness in Options Screen //////////////////////////////////////////////////////////////
// Runs Locally on Nextion

///////////////////////////////////////////////////////////////////// Confirm Sun Tracking in Suntrack confirm Screen ///////////////////////////////////////////////////////////
// Runs Locally on Nextion

///////////////////////////////////////////////////////////////////// Calibrate Touch Screen ///////////////////////////////////////////////////////////
// Runs Locally on Nextion

///////////////////////////////////////////////////////////////////// Draw Load Objects in Load Screen //////////////////////////////////////////////////////////////
void drawLoadObjects()
{
  ///////     Messier Screen /////////////
  if (LOAD_SELECTOR == 1)
  {
    // I'll draw 20 objects per page, thus "(pager*20)" will give me the start of the [index_]
    int kk = MESS_PAGER * 20;
    //tft.fillRect(10,160, 310, 250, ILI9488_BLACK);

    for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        String M_NAME = Messier_Array[kk].substring(0, Messier_Array[kk].indexOf(';'));
        if (M_NAME == "")
        {
          //tft.fillRect(((j * 75) + 12), ((i * 50) + 160), 71, 45, BLACK);
        }
        else
        {
          //DrawButton(((j * 75) + 12), ((i * 50) + 160), 71, 45, M_NAME, messie_btn, 0, btn_l_text, 2);
          // 75 box width ,12start from left , 50 box hight , 110 start from up
          kk += 1;
        }
      }
    }
  }
  ///////     Treasures Screen /////////////
  else if (LOAD_SELECTOR == 2)
  {
    //tft.setTextSize(1);
    int ll = TREAS_PAGER * 20;
    //tft.fillRect(10,160, 310, 250, ILI9488_BLACK);

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 4; j++) {
        String M_NAME = Treasure_Array[ll].substring(0, Treasure_Array[ll].indexOf(';'));
        if (M_NAME == "")
        {
          //tft.fillRect(((j * 75) + 12), ((i * 50) + 160), 71, 45, BLACK);
        }
        else
        {
          //DrawButton(((j * 75) + 12), ((i * 50) + 160), 71, 45, M_NAME, messie_btn, 0, btn_l_text, 1);
          ll += 1;
        }
      }
    }
  }
  else if (LOAD_SELECTOR == 3)  // solar system planets
  {
    //tft.setTextSize(1);
    int ll = 0;

    for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (ll >= 11)
        {
          //tft.fillRect(((j * 75) + 12), ((i * 50) + 160), 71, 45, BLACK);
        }
        else
        {
          String M_NAME = ss_planet_names[ll];
          //DrawButton(((j * 75) + 12), ((i * 50) + 160), 71, 45, M_NAME, messie_btn, 0, btn_l_text, 1);
        }
        ll += 1;
      }
    }
  }
  else if (LOAD_SELECTOR == 4) // custom.csv
  {
    //tft.setTextSize(1);
    int ll = CUSTOM_PAGER * 20;
    //tft.fillRect(10,160, 310, 250, ILI9488_BLACK);

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 4; j++) {
        String M_NAME = custom_Array[ll].substring(0, custom_Array[ll].indexOf(';'));
        if (M_NAME == "")
        {
          //tft.fillRect(((j * 75) + 12), ((i * 50) + 160), 71, 45, BLACK);
        }
        else
        {
          //DrawButton(((j * 75) + 12), ((i * 50) + 160), 71, 45, M_NAME, messie_btn, 0, btn_l_text, 1);
          ll += 1;
        }
      }
    }
  }
}


///////////////////////////////////////////////////////////////////// Draw STAT Screen /////////////////////////////////////////////////////////////////////////////

void drawSTATScreen() {

  CURRENT_SCREEN = 10;
  Stat.show();

  Serial1.print("stat_date.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(Start_date);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_st_time.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(START_TIME);
  Serial1.print(" H");
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_rep_time.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(String(rtc.getTimeStr()).substring(0, 5));
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_LAT.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(OBSERVATION_LATTITUDE, 4);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_LONG.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(OBSERVATION_LONGITUDE, 4);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_ALT.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(OBSERVATION_ALTITUDE, 0);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  double st;
  int st_h;
  int st_m;
  st = (String(rtc.getTimeStr()).substring(0, 2).toInt() * 60) + String(rtc.getTimeStr()).substring(3, 5).toInt();
  st -= (START_TIME.substring(0, 2).toInt() * 60) + START_TIME.substring(3, 5).toInt();
  if (st < 0) {
    st += 1440;
  }
  st_h = int(st / 60);
  st_m = ((st / 60) - st_h) * 60;

  Serial1.print("stat_obs_per.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(st_h);
  Serial1.print(" H");
  Serial1.print("  ");
  Serial1.print(st_m);
  Serial1.print(" M");
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_obs_start.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(START_TIME);
  Serial1.print("H");
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_temp.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(_Stemp, 0);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("stat_humidity.txt="); // Nextion
  Serial1.print("\"");
  Serial1.print(_Shumid, 0);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  stat_obj_count.setValue(Observed_Obj_Count);// Print the number of observed objects on Nextion.
  ////////////////////////////////////////Record Observed Objects/////////////

  for (int i = 0; i < Observed_Obj_Count; i++) {
    int i1 = ObservedObjects[i].indexOf(';');
    int i2 = ObservedObjects[i].indexOf(';', i1 + 1);
    int i3 = ObservedObjects[i].indexOf(';', i2 + 1);
    int i4 = ObservedObjects[i].indexOf(';', i3 + 1);
    int i5 = ObservedObjects[i].indexOf(';', i4 + 1);
    int i6 = ObservedObjects[i].indexOf(';', i5 + 1);
    int i7 = ObservedObjects[i].indexOf(';', i6 + 1);
    int i8 = ObservedObjects[i].indexOf('\n');
    int tt;
    String ha_;
    String degs_;
    if (i == (Observed_Obj_Count - 1)) {
      tt = (((String(rtc.getTimeStr()).substring(0, 2).toInt()) * 60)  + (String(rtc.getTimeStr()).substring(3, 5).toInt())) - ((ObservedObjects[i].substring(i2 + 1, i2 + 3).toInt() * 60) + ObservedObjects[i].substring(i2 + 4, i3).toInt());
      if (tt < 0) {
        tt += 1440;
      }
    } else {
      tt = ObservedObjects[i].substring(i7 + 1, ObservedObjects[i].length()).toInt();
    }

    degs_ = ObservedObjects[i].substring(i6 + 1, i7);
    ha_ = ObservedObjects[i].substring(i5 + 1, i6);
    String Composed = ObservedObjects[i].substring(0, i1) + " @ " + ObservedObjects[i].substring(i2 + 1, i3) + " for " + String(tt) + " min | Alt: " + degs_ + " deg " + " | HA:" + ha_ + " .";
    //Composed += "above horizon, with HA:" +ha_+ " .";
    Serial.print(Composed);

    Serial1.print("stat_obj_");
    Serial1.print(i + 1);
    Serial1.print(".txt=");
    Serial1.print("\"");
    Serial1.print(Composed);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
}

///////////////////////////////////////////////////////////////////// Draw Star Sync Screen /////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////// Draw Align Objects in Align Screen //////////////////////////////////////////////////////////////
void drawAlignObjects_ali()
{
  CURRENT_SCREEN = 12;
  Sync.show();    // >>> Nextion Show Page Sync

  if (ALLIGN_TYPE == 3)         // If I'm in the Iterative Alignment Page
  {
    if (STARS_PAGER == 0)
    {
      int kk = STARS_PAGER * 24;
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
          int i1 = Iter_Stars[kk].indexOf(';');
          int i2 = Iter_Stars[kk].indexOf(';', i1 + 1);
          String S_NAME = Iter_Stars[kk].substring(i1 + 1, i2);
          String C_NAME = Iter_Stars[kk].substring(0, i1);
          if (S_NAME == "") {
            break;
          }
          int l = (S_NAME.length() / 2) * 6;
          Serial.println(S_NAME);
          Serial.println(C_NAME);

          Serial1.print("sync_obj_");
          Serial1.print(kk + 1);
          Serial1.print(".txt=");
          Serial1.print("\"");
          Serial1.print(S_NAME);
          Serial1.print("     ");
          Serial1.print(C_NAME);
          Serial1.print("\"");
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          kk += 1;
        }
      }
    } else if (STARS_PAGER == 1)
    {
      int kk = STARS_PAGER * 24;
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
          int i1 = Iter_Stars[kk].indexOf(';');
          int i2 = Iter_Stars[kk].indexOf(';', i1 + 1);
          String S_NAME = Iter_Stars[kk].substring(i1 + 1, i2);
          String C_NAME = Iter_Stars[kk].substring(0, i1);
          if (S_NAME == "") {
            break;
          }
          int l = (S_NAME.length() / 2) * 6;
          Serial.println(S_NAME);
          Serial.println(C_NAME);

          Serial1.print("sync_obj_");
          Serial1.print((kk + 1) - 24);
          Serial1.print(".txt=");
          Serial1.print("\"");
          Serial1.print(S_NAME);
          Serial1.print("     ");
          Serial1.print(C_NAME);
          Serial1.print("\"");
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          kk += 1;

        }
      }
    }
  }
}
///////////////////////////////////////////////////////////////////// Draw Constelations Screen /////////////////////////////////////////////////////////////////////////////

void drawConstelationScreen(int indx)                              // Manual Alignment in Nextion
{
  CURRENT_SCREEN = 13;
  Manual_Align.show();// Nextion show Page Manual Align Page

  if (ALLIGN_TYPE != 3)
  {
    repeat_align.setText("<Repeat");
  }
  else
  {
    repeat_align.setText("<Exit");
  }
  if (ALLIGN_STEP == 1)
  {
    sync_align.setText("SYNC !");
    MA_instruction.setText("Use manual motor movement  to center the star!        Once centered, hit 'SYNC!' button.");
    Serial1.print("Selected_obj.txt=");
    Serial1.print("\"");
    Serial1.print(OBJECT_NAME);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (ALLIGN_STEP == 2)
  {
    if (ALLIGN_TYPE == 3)
    {

      sync_align.setText("NEXT>");
      MA_instruction.setText("Use Alt/Az (physical) knobson your mount to center on Polaris! Once centered,hit 'ALIGN' button.            NB! Only correct halfway tocenter!"); // Don't Change the spaces!
      Serial1.print("Selected_obj.txt=");
      Serial1.print("\"");
      Serial1.print(OBJECT_NAME);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }
    else
    {
      sync_align.setText("CENTER");
      MA_instruction.setText("Use manual motor movement  to center the star!        Once centered, hit 'SYNC!' button."); // Don't Change the spaces!
    }
  }
}
