// Register the event callback functions of each touch event:
// You need to register press events and release events seperatly.
// Format for press events: <object name>.attachPush(<object name>PushCallback);
void nex_attach_pages() {

  // GPS Page Touch Buttons
  coord_ass_text.attachPush(coord_ass_textPushCallback);
  skip.attachPush(skipPushCallback);

  // Time Page Touch Buttons
  save_button.attachPush(save_buttonPushCallback);
  btdst.attachPush(btdstPushCallback);

  day_up.attachPush(day_upPushCallback);
  day_down.attachPush(day_downPushCallback);
  month_up.attachPush(month_upPushCallback);
  month_down.attachPush(month_downPushCallback);
  year_up.attachPush(year_upPushCallback);
  year_down.attachPush(year_downPushCallback);
  hour_up.attachPush(hour_upPushCallback);
  hour_down.attachPush(hour_downPushCallback);
  minute_up.attachPush(minute_upPushCallback);
  minute_down.attachPush(minute_downPushCallback);
  second_up.attachPush(second_upPushCallback);
  second_down.attachPush(second_downPushCallback);

  // Confirm Sun Tracking Page Touch Buttons
  sun_track_yes.attachPush(sun_track_yesPushCallback);
  sun_track_no.attachPush(sun_track_noPushCallback);

  // Page STAT Touch Buttons
  stat_back.attachPush(stat_backPushCallback);

  // Page Coordinates Touch Buttons
  coord_back.attachPush(coord_backPushCallback);

  // Page AutoGuiding Touch Buttons
  Guiding_back.attachPush(Guiding_backPushCallback);

  // Aling Page Touch Buttons
  align1Star.attachPush(align1StarPushCallback);
  iterativeAlign.attachPush(iterativeAlignPushCallback);
  skip_align.attachPush(skip_alignPushCallback);

  //Manual Align Page Touch Buttons
  sync_align.attachPush(sync_alignPushCallback);
  repeat_align.attachPush(repeat_alignPushCallback);

  //Sync Page Touch Buttons
  sync_next.attachPush(sync_nextPushCallback);
  sync_prev.attachPush(sync_prevPushCallback);
  sync_done.attachPush(sync_donePushCallback);
  sync_obj_1.attachPush(sync_obj_1PushCallback);
  sync_obj_2.attachPush(sync_obj_2PushCallback);
  sync_obj_3.attachPush(sync_obj_3PushCallback);
  sync_obj_4.attachPush(sync_obj_4PushCallback);
  sync_obj_5.attachPush(sync_obj_5PushCallback);
  sync_obj_6.attachPush(sync_obj_6PushCallback);
  sync_obj_7.attachPush(sync_obj_7PushCallback);
  sync_obj_8.attachPush(sync_obj_8PushCallback);
  sync_obj_9.attachPush(sync_obj_9PushCallback);
  sync_obj_10.attachPush(sync_obj_10PushCallback);
  sync_obj_11.attachPush(sync_obj_11PushCallback);
  sync_obj_12.attachPush(sync_obj_12PushCallback);
  sync_obj_13.attachPush(sync_obj_13PushCallback);
  sync_obj_14.attachPush(sync_obj_14PushCallback);
  sync_obj_15.attachPush(sync_obj_15PushCallback);
  sync_obj_16.attachPush(sync_obj_16PushCallback);
  sync_obj_17.attachPush(sync_obj_17PushCallback);
  sync_obj_18.attachPush(sync_obj_18PushCallback);
  sync_obj_19.attachPush(sync_obj_19PushCallback);
  sync_obj_20.attachPush(sync_obj_20PushCallback);
  sync_obj_21.attachPush(sync_obj_21PushCallback);
  sync_obj_22.attachPush(sync_obj_22PushCallback);
  sync_obj_23.attachPush(sync_obj_23PushCallback);
  sync_obj_24.attachPush(sync_obj_24PushCallback);

  // Main Page Touch Buttons
  main_Load.attachPush(main_LoadPushCallback);
  main_home.attachPush(main_homePushCallback);
  main_track.attachPush(main_trackPushCallback);
  main_BT.attachPush(main_BTPushCallback);
  main_menu.attachPush(main_menuPushCallback);

  // Menu Page Touch Buttons
  men_Options.attachPush(men_OptionsPushCallback);
  men_Load.attachPush(men_LoadPushCallback);
  men_Coord.attachPush(men_CoordPushCallback);
  men_Log.attachPush(men_LogPushCallback);
  men_guiding.attachPush(men_guidingPushCallback);
  men_back.attachPush(men_backPushCallback);

  // Options Page Touch Buttons
  opt_save.attachPush(opt_savePushCallback);
  opt_steppers.attachPush(opt_steppersPushCallback);
  opt_sound.attachPush(opt_soundPushCallback);
  opt_fan1.attachPush(opt_fan1PushCallback);
  opt_fan2.attachPush(opt_fan2PushCallback);
  opt_F_motor.attachPush(opt_F_motorPushCallback);
  opt_mer_auto.attachPush(opt_mer_autoPushCallback);
  opt_mer_off.attachPush(opt_mer_offPushCallback);
  opt_celestial.attachPush(opt_celestialPushCallback);
  opt_solar.attachPush(opt_solarPushCallback);
  opt_lunar.attachPush(opt_lunarPushCallback);
  optClock_align.attachPush(optClock_alignPushCallback);

  // Load Page Touch Buttons
  load_messier.attachPush(load_messierPushCallback);
  load_treasures.attachPush(load_treasuresPushCallback);
  load_solar_sys.attachPush(load_solar_sysPushCallback);
  load_cust_csv.attachPush(load_cust_csvPushCallback);
  load_back.attachPush(load_backPushCallback);
  load_next.attachPush(load_nextPushCallback);
  load_prev.attachPush(load_prevPushCallback);
  load_obj_1.attachPush(load_obj_1PushCallback);
  load_obj_2.attachPush(load_obj_2PushCallback);
  load_obj_3.attachPush(load_obj_3PushCallback);
  load_obj_4.attachPush(load_obj_4PushCallback);
  load_obj_5.attachPush(load_obj_5PushCallback);
  load_obj_6.attachPush(load_obj_6PushCallback);
  load_obj_7.attachPush(load_obj_7PushCallback);
  load_obj_8.attachPush(load_obj_8PushCallback);
  load_obj_9.attachPush(load_obj_9PushCallback);
  load_obj_10.attachPush(load_obj_10PushCallback);
  load_obj_11.attachPush(load_obj_11PushCallback);
  load_obj_12.attachPush(load_obj_12PushCallback);
  load_obj_13.attachPush(load_obj_13PushCallback);
  load_obj_14.attachPush(load_obj_14PushCallback);
  load_obj_15.attachPush(load_obj_15PushCallback);
  load_obj_16.attachPush(load_obj_16PushCallback);
  load_obj_17.attachPush(load_obj_17PushCallback);
  load_obj_18.attachPush(load_obj_18PushCallback);
  load_obj_19.attachPush(load_obj_19PushCallback);
  load_obj_20.attachPush(load_obj_20PushCallback);
  load_obj_21.attachPush(load_obj_21PushCallback);
  load_obj_22.attachPush(load_obj_22PushCallback);
  load_obj_23.attachPush(load_obj_23PushCallback);
  load_obj_24.attachPush(load_obj_24PushCallback);
  load_obj_25.attachPush(load_obj_25PushCallback);
  load_obj_26.attachPush(load_obj_26PushCallback);
  load_obj_27.attachPush(load_obj_27PushCallback);
  load_obj_28.attachPush(load_obj_28PushCallback);
  load_obj_29.attachPush(load_obj_29PushCallback);
  load_obj_30.attachPush(load_obj_30PushCallback);
  load_obj_31.attachPush(load_obj_31PushCallback);
  load_obj_32.attachPush(load_obj_32PushCallback);
  load_obj_33.attachPush(load_obj_33PushCallback);
  load_obj_34.attachPush(load_obj_34PushCallback);
  load_obj_35.attachPush(load_obj_35PushCallback);

  // Page Menu Touch Buttons
  men_Options.attachPush(men_OptionsPushCallback);
  men_Load.attachPush(men_LoadPushCallback);
  men_Coord.attachPush(men_CoordPushCallback);
  men_Log.attachPush(men_LogPushCallback);
  men_guiding.attachPush(men_guidingPushCallback);
  men_back.attachPush(men_backPushCallback);

  // End of registering the event callback functions
}

//////////////////////////////////////////////////// Touch events ///////////////////////////////////////////////////////////////////


////////////////////////////GPS Page touch events////////////////////////////////////

void skipPushCallback(void *ptr)  // If SKIP button touched
{
  if (CURRENT_SCREEN == 0)
  {
    if (IS_SOUND_ON) {
      SoundOn(800, 8);
    }
    // Set the earth rotation direction depending on the Hemisphere...
    // HIGH and LOW are substituted
    if (OBSERVATION_LATTITUDE > 0) {
      STP_FWD = LOW;
      STP_BACK = HIGH;
    } else {
      STP_FWD = HIGH;
      STP_BACK = LOW;
    }
    CURRENT_SCREEN = 1;
    drawClockScreen();
  }
}

void coord_ass_textPushCallback(void *ptr)  // If Assigned Coordinates text touched
{
  if (CURRENT_SCREEN == 0)
  {
    if (IS_SOUND_ON) {
      SoundOn(800, 8);
    }
    // Set the earth rotation direction depending on the Hemisphere...
    // HIGH and LOW are substituted
    if (OBSERVATION_LATTITUDE > 0) {
      STP_FWD = LOW;
      STP_BACK = HIGH;
    } else {
      STP_FWD = HIGH;
      STP_BACK = LOW;
    }
    CURRENT_SCREEN = 1;
    drawClockScreen();
  }
}

////////////////////////////Time Page touch events////////////////////////////////////
void btdstPushCallback(void *ptr) // If Sound ON/OFF Button Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }
  uint32_t dual_state;
  btdst.getValue(&dual_state);
  if (dual_state)
  {
    Summer_Time = 1;
  } else {
    Summer_Time = 0;
  }
}

void day_upPushCallback(void *ptr)  // If BTN day_up Touched
{
  IS_Time_Changed = true;
}
void day_downPushCallback(void *ptr)  // If BTN day_down Touched
{
  IS_Time_Changed = true;
}
void month_upPushCallback(void *ptr)  // If BTN month_up Touched
{
  IS_Time_Changed = true;
}
void month_downPushCallback(void *ptr)  // If BTN month_down Touched
{
  IS_Time_Changed = true;
}
void year_upPushCallback(void *ptr)  // If BTN year_up Touched
{
  IS_Time_Changed = true;
}
void year_downPushCallback(void *ptr)  // If BTN year_down Touched
{
  IS_Time_Changed = true;
}
void hour_upPushCallback(void *ptr)  // If BTN hour_up Touched
{
  IS_Time_Changed = true;
}
void hour_downPushCallback(void *ptr)  // If BTN hour_down Touched
{
  IS_Time_Changed = true;
}
void minute_upPushCallback(void *ptr)  // If BTN minute_up Touched
{
  IS_Time_Changed = true;
}
void minute_downPushCallback(void *ptr)  // If BTN minute_down Touched
{
  IS_Time_Changed = true;
}
void second_upPushCallback(void *ptr)  // If BTN second_up Touched
{
  IS_Time_Changed = true;
}
void second_downPushCallback(void *ptr)  // If BTN second_down Touched
{
  IS_Time_Changed = true;
}

void save_buttonPushCallback(void *ptr)  // If BTN Save Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_Time_Changed == true)
  {
    // Do the magic as the date and time has been updated... Update the RTC accordingly
    uint32_t hh = 0 ;
    hour_set.getValue(&hh);
    uint32_t mm = 0;
    minute_set.getValue(&mm);
    uint32_t dd = 0;
    day_set.getValue(&dd);
    uint32_t mo = 0;
    month_set.getValue(&mo);
    uint32_t yy = 0;
    year_set.getValue(&yy);

    rtc.setTime(hh, mm, 00);
    rtc.setDate(dd, mo, yy);
  }
  int ora, date_delay = 0; //, month_delay = 0, year_delay = 0;
  int time_delay = TIME_ZONE;
  time_delay += Summer_Time;

  String Date_q = String(rtc.getDateStr());
  String Time_q = String(rtc.getTimeStr());
  int D = Date_q.substring(0, 2).toInt();
  int M = Date_q.substring(3, 5).toInt();
  int Y = Date_q.substring(6).toInt();
  int H = Time_q.substring(0, 2).toInt();
  int MN = Time_q.substring(3, 5).toInt();
  int S = Time_q.substring(6).toInt();
  //update the value of the variable ora
  //ora = hh - time_delay;
  ora = H - time_delay;
  //to update the real time
  if (ora < 0) // In all these calculations neither month nor year is passed, it must be corrected (although it may work)
  {
    ora += 24;
    date_delay = -1;
    /*if (dd + date_delay < 1)
      {
      dd = (mo==2 || mo==4 || mo==6 || mo==8 || mo==9 || mo==11 || mo==1? 31: (mo!=3? 30: (yy%4==0 and yy%100!=0 or yy%400==0? 29: 28)));
      date_delay = 0;
      month_delay = -1;
      if (mo + month_delay < 1)
      {
        mo = 12;
        month_delay = 0;
        year_delay = -1;
      }
      }*/
  }
  // convert to epoch
  //setTime(ora, mm, 00, dd + date_delay, mo + month_delay, yy + year_delay); // <-- too mantain sync with UTC
  //setTime(ora, mm, 00, dd + date_delay, mo, yy); // <-- too mantain sync with UTC
  setTime(ora, MN, S, D + date_delay, M, Y); // <-- too mantain sync with UTC

  Start_date = String(rtc.getDateStr()).substring(0, 2) + " " + rtc.getMonthStr(FORMAT_SHORT) + " " + String(rtc.getDateStr()).substring(6);
  old_d = rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/');
  START_TIME = rtc.getTimeStr(FORMAT_SHORT);
  _Stemp = dht.readTemperature();;
  _Shumid = dht.readHumidity();

  drawSelectAlignment();
}

////////////////////////////Main Page touch events////////////////////////////////////

void main_LoadPushCallback(void *ptr)  // If LOAD button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (CURRENT_SCREEN == 4) {
    if (IS_BT_MODE_ON == false) {  // If LOAD Button Touched

      if (IS_STEPPERS_ON == true) {
        CURRENT_SCREEN = 6;
        is_btn_pressed = false;
        drawLoadScreen();

      } else if (IS_STEPPERS_ON == false) {
        is_btn_pressed = false;
        OnScreenMsg(5);
        CURRENT_SCREEN = 7;
        drawOptionsScreen();
      }
    }
  }
}

void main_homePushCallback(void *ptr)  // If Home button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_BT_MODE_ON == false && IS_STEPPERS_ON == true) {  // If Home Button Touched

    IS_TRACKING = false;
    Timer3.stop();
    tm1.disable(); // Nextion Tracking Animation Stop
    tm3.disable();// Nextion Object is Invisible Animation Stop
    OnScreenMsg(6);
    OBJECT_NAME = "CP";
    OBJECT_DESCR = "Celestial pole";
    OBJECT_RA_H = 12;
    OBJECT_RA_M = 0;
    OBJECT_DEC_D = 90;
    OBJECT_DEC_M = 0;
    IS_OBJ_FOUND = false;
    IS_OBJECT_RA_FOUND = false;
    IS_OBJECT_DEC_FOUND = false;
    Slew_timer = millis();
    Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
    Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
    Tracking_Mode = "Celest";
    OBJECT_DETAILS = "The north and south celestial poles are the two imaginary points in the sky where the Earth's axis of rotation, intersects the celestial sphere";
  }

  if (IS_BT_MODE_ON == false && IS_STEPPERS_ON == false) {  // If HOME Button Touched
    IS_TRACKING = false;
    Timer3.stop();
    tm1.disable(); // Nextion Tracking Animation Stop
    OnScreenMsg(5);
    drawOptionsScreen();
  }
}

void main_trackPushCallback(void *ptr)  // If TRACK button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_STEPPERS_ON == true) {
    if (IS_TRACKING == false) {
      IS_TRACKING = true;
      tm1.enable();                // Nextion Tracking Animation Start

      setmStepsMode("R", MICROSteps);
      if (Tracking_type == 1) { // 1: Sidereal, 2: Solar, 0: Lunar;
        Timer3.start(Clock_Sidereal);
      } else if (Tracking_type == 2) {
        Timer3.start(Clock_Solar);
      } else if (Tracking_type == 0) {
        Timer3.start(Clock_Lunar);
      }
    } else {
      IS_TRACKING = false;
      OnScreenMsg(2);
      setmStepsMode("R", 1);
      Timer3.stop();
      tm1.disable();                // Nextion Tracking Animation Stop
    }
  }
  else if (IS_STEPPERS_ON == false) {
    OnScreenMsg(5);
    CURRENT_SCREEN = 7;
    drawOptionsScreen();
  }
}

void main_BTPushCallback(void *ptr)  // If Bluetooth button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_STEPPERS_ON == true)
  {
    if (IS_BT_MODE_ON == true)
    {
      IS_BT_MODE_ON = false;
      tm2.disable();   // Nextion Bluetooth Animation Stop
    } else {
      IS_BT_MODE_ON = true;
      tm2.enable();   // Nextion Bluetooth Animation Start
      // Initialize Bluetooth communication on PINs: 15 (RX) and 14 (TX)
    }
  }
  else if (IS_STEPPERS_ON == false) {
    OnScreenMsg(5);
    CURRENT_SCREEN = 7;
    drawOptionsScreen();
  }
}

void main_menuPushCallback(void *ptr)  // If Menu button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_BT_MODE_ON == false) {
    Menu.show();
  }
}

//////////////////////////// Menu Page touch events////////////////////////////////////
void men_OptionsPushCallback(void *ptr)  // If BTN Options Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }
  drawOptionsScreen();
}

void men_LoadPushCallback(void *ptr) // If BTN Load Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (CURRENT_SCREEN == 4) {
    if (IS_BT_MODE_ON == false) {  // If LOAD Button Touched

      if (IS_STEPPERS_ON == true) {
        is_btn_pressed = false;
        CURRENT_SCREEN = 6;
        drawLoadScreen();

      } else if (IS_STEPPERS_ON == false) {
        is_btn_pressed = false;
        OnScreenMsg(5);
        CURRENT_SCREEN = 7;
        drawOptionsScreen();
      }
    }
  }
}

void men_CoordPushCallback(void *ptr) // If BTN Coordinates Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_BT_MODE_ON == false) {  // If COORD Button Touched
    if ((IS_TRACKING == true) && (IS_SOUND_ON)) {
      SoundOn(note_C, 32);
    }
    CURRENT_SCREEN = 5;
    drawCoordinatesScreen();
  }
}

void men_LogPushCallback(void *ptr) // If BTN LOG Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_BT_MODE_ON == false) {
    CURRENT_SCREEN = 10;
    drawSTATScreen();
  }
}

void men_guidingPushCallback(void *ptr) // If BTN Maps Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (IS_BT_MODE_ON == false) {   // If AutoGuiding Button Touched
    CURRENT_SCREEN = 11;
    drawAutoGuidingScreen();
  }
}

void men_backPushCallback(void *ptr) // If BTN Back Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  CURRENT_SCREEN = 4;
  drawMainScreen();
}

//////////////////////////// LOG Page touch events ////////////////////////////////////
void stat_backPushCallback(void *ptr) // If Button Back Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  CURRENT_SCREEN = 4;
  Menu.show();
}
//////////////////////////// Coordinates Page touch events ////////////////////////////////////
void coord_backPushCallback(void *ptr) // If Button Back Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  CURRENT_SCREEN = 4;
  Menu.show();
}

//////////////////////////// AutoGuiding Page touch events ////////////////////////////////////
void  Guiding_backPushCallback(void *ptr) // If Button Back Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  IS_CONNECTED = true;
  IS_PulseGuiding = false;
  CURRENT_SCREEN = 4;
  Menu.show();
}

//////////////////////////// Load Page touch events////////////////////////////////////
void load_messierPushCallback(void *ptr) // If BTN Messier Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  // BTN Messier Touched
  LOAD_SELECTOR = 1; // We're in Messier Catalog
  MESS_PAGER = 0; // We're in page 1
  is_btn_pressed = false;
  //drawLoadObjects();
  Serial.println("Load Selector= ");
  Serial.print(LOAD_SELECTOR);
  Serial.println("Mess Pager = ");
  Serial.print(MESS_PAGER);
}

void load_treasuresPushCallback(void *ptr) // If BTN Treasures Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  // BTN Treasures Touched
  LOAD_SELECTOR = 2;
  TREAS_PAGER = 0; // We're in page 1
  is_btn_pressed = false;
  //drawLoadObjects();
  Serial.println("Load Selector= ");
  Serial.print(LOAD_SELECTOR);
  Serial.println("Treas Pager = ");
  Serial.print(TREAS_PAGER);
}
void load_solar_sysPushCallback(void *ptr) // If BTN Solar Sys Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  // BTN Solar System Touched
  LOAD_SELECTOR = 3;
  is_btn_pressed = false;
  //drawLoadObjects();
}
void load_cust_csvPushCallback(void *ptr) // If BTN CUST CSV Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  // BTN custom.csv touched
  LOAD_SELECTOR = 4;
  is_btn_pressed = false;
  //drawLoadObjects();
}

void load_backPushCallback(void *ptr) // If BTN Back Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  is_btn_pressed = false;
  drawMainScreen();
}

void load_nextPushCallback(void *ptr) // If BTN Next Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (LOAD_SELECTOR == 1)
  {
    MESS_PAGER += 1;
    if (MESS_PAGER <= 3)
    {
      //drawLoadObjects();
    }
    else
    {
      MESS_PAGER = 3;
    }
    Serial.println("Load Selector= ");
    Serial.print(LOAD_SELECTOR);
    Serial.println("MESS_PAGER = ");
    Serial.print(MESS_PAGER);
  }
  else if (LOAD_SELECTOR == 2)
  {
    TREAS_PAGER += 1;
    if (TREAS_PAGER <= 3)
    {
      //drawLoadObjects();
    }
    else
    {
      TREAS_PAGER = 3;
    }
  }
  Serial.println("Load Selector= ");
  Serial.print(LOAD_SELECTOR);
  Serial.println("TREAS_PAGER = ");
  Serial.print(TREAS_PAGER);

}

void load_prevPushCallback(void *ptr) // If BTN Prev Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (LOAD_SELECTOR == 1)
  {
    MESS_PAGER -= 1;
    if (MESS_PAGER >= 0)
    {
      //drawLoadObjects();
    }
    else
    {
      MESS_PAGER = 0;
    }
  }
  else if (LOAD_SELECTOR == 2)
  {
    TREAS_PAGER -= 1;
    if (TREAS_PAGER >= 0)
    {
      //drawLoadObjects();
    }
    else
    {
      TREAS_PAGER = 0;
    }
  }
}

//////////////////////////////////////// Load Object Fields Touch Events //////////////////////////////////////
void load_obj_1PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 1;
}

void load_obj_2PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 2;
}

void load_obj_3PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 3;
}

void load_obj_4PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 4;
}

void load_obj_5PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 5;
}

void load_obj_6PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 6;
}

void load_obj_7PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 7;
}

void load_obj_8PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 8;
}

void load_obj_9PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 9;
}

void load_obj_10PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 10;
}

void load_obj_11PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 11;
}

void load_obj_12PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 12;
}

void load_obj_13PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 13;
}

void load_obj_14PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 14;
}

void load_obj_15PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 15;
}

void load_obj_16PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 16;
}

void load_obj_17PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 17;
}

void load_obj_18PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 18;
}

void load_obj_19PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 19;
}

void load_obj_20PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 20;
}

void load_obj_21PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 21;
}

void load_obj_22PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 22;
}

void load_obj_23PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 23;
}

void load_obj_24PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 24;
}

void load_obj_25PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 25;
}

void load_obj_26PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 26;
}

void load_obj_27PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 27;
}

void load_obj_28PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 28;
}

void load_obj_29PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 29;
}

void load_obj_30PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 30;
}

void load_obj_31PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 31;
}

void load_obj_32PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 32;
}

void load_obj_33PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 33;
}

void load_obj_34PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 34;
}

void load_obj_35PushCallback(void *ptr)
{
  is_btn_pressed = true;
  selected_object = 35;
}

///////////////////////////////////////////// Confirm Sun Tracking Buttons Touch Events ////////////////////////////////

void sun_track_yesPushCallback(void *ptr) // If BTN YES Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (CURRENT_SCREEN == 15)
  {
    planet_pos(0);
    sun_confirm = true;

    if (sun_confirm || selected_object != 0)
    {
      calculateLST_HA();
      if (ALT > 0)
      {
        OnScreenMsg(1);
        if (IS_SOUND_ON)
        {
          SoundOn(note_C, 32);
          delay(200);
          SoundOn(note_C, 32);
          delay(200);
          SoundOn(note_C, 32);
          delay(1000);
        }
        // Stop Interrupt procedure for tracking.
        Timer3.stop(); //
        IS_TRACKING = false;
        IS_OBJ_FOUND = false;
        IS_OBJECT_RA_FOUND = false;
        IS_OBJECT_DEC_FOUND = false;
        Tracking_type = 2; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
        Tracking_Mode = "Solar";
        updateTrackingMode_opt();
        opt_celestial.setValue(0);
        opt_solar.setValue(1);
        opt_lunar.setValue(0);
        Serial1.print("wepo 0,80");  // Change Celestial Button to OFF in Options Screen
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.print("wepo 0,90");  // Change Lunar Button to ON in Options Screen
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.print("wepo 1,100");  // Change Solar Button to OFF in Options Screen
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Slew_timer = millis();
        Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
      }
      UpdateObservedObjects();
      sun_confirm = false;
      drawMainScreen();
    }
  }
}
void sun_track_noPushCallback(void *ptr) // If BTN NO Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (CURRENT_SCREEN == 15)
  {
    is_btn_pressed = false;
    sun_confirm = false;
    CURRENT_SCREEN = 6;
    drawLoadScreen();
  }
}


//////////////////////////// Options Page touch events ////////////////////////////////////

void opt_savePushCallback(void *ptr) // If Button Save Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  storeOptions_SD();
  CURRENT_SCREEN = 4;
  Menu.show();
}

void opt_steppersPushCallback(void *ptr) // If Button Steppers ON/OFF Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  uint32_t dual_state;
  /* Get the state value of dual state button component . */
  opt_steppers.getValue(&dual_state);
  if (dual_state)
  {
    // ON Stepper Motors
    IS_STEPPERS_ON = true;
    digitalWrite(RA_EN, LOW);
    digitalWrite(DEC_EN, LOW);
    Stepper_State = "ON";
    updateStepper_opt();
  }
  else
  {
    // OFF Stepper Motors
    IS_STEPPERS_ON = false;
    digitalWrite(RA_EN, HIGH);
    digitalWrite(DEC_EN, HIGH);
    Stepper_State = "OFF";
    updateStepper_opt();
  }
}

void opt_soundPushCallback(void *ptr) // If Sound ON/OFF Button Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  uint32_t dual_state;
  opt_sound.getValue(&dual_state);
  if (dual_state)
  {
    // ON Sound
    IS_SOUND_ON = true;
    Sound_State = "ON";
    updateSound_opt();
  }
  else
  {
    // OFF Sound
    IS_SOUND_ON = false;
    Sound_State = "OFF";
    updateSound_opt();
  }
}

void opt_fan1PushCallback(void *ptr) // If Button FAN1 ON/OFF Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  uint32_t dual_state;
  opt_fan1.getValue(&dual_state);
  if (dual_state)
  {
    // FAN1 ON
    Fan1_State = "ON";
    IS_FAN1_ON = true;
    digitalWrite(FAN1, HIGH);
  }
  else
  {
    // FAN1 OFF
    Fan1_State = "OFF";
    IS_FAN1_ON = false;
    digitalWrite(FAN1, LOW);
  }
}

void opt_fan2PushCallback(void *ptr) // If Button FAN2 ON/OFF Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  uint32_t dual_state;
  opt_fan2.getValue(&dual_state);
  if (dual_state)
  {
    // FAN1 ON
    Fan2_State = "ON";
    IS_FAN2_ON = true;
    digitalWrite(FAN2, HIGH);
  }
  else
  {
    // FAN1 OFF
    Fan2_State = "OFF";
    IS_FAN2_ON = false;
    digitalWrite(FAN2, LOW);
  }
}

void opt_F_motorPushCallback(void *ptr) // If Button Heater ON/OFF Touched >> Not used For Now
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  uint32_t dual_state;
  opt_F_motor.getValue(&dual_state);
  if (dual_state)
  {
    // Focus Motor ON
    IS_FOCUS_ON = true;
    Focus_Motor_State = "ON";
    digitalWrite(Focus_EN, LOW);
  }
  else
  {
    // Focus Motor OFF
    IS_FOCUS_ON = false;
    Focus_Motor_State = "OFF";
    digitalWrite(Focus_EN, HIGH);
  }
}

void opt_mer_autoPushCallback(void *ptr) // If Button Meridian flip Auto Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  IS_MERIDIAN_FLIP_AUTOMATIC = true;
  Mer_Flip_State = "AUTO";
  updateMeridianFlip_opt();
}

void opt_mer_offPushCallback(void *ptr) // If Button Meridian flip OFF Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  IS_MERIDIAN_FLIP_AUTOMATIC = false;
  Mer_Flip_State = "OFF";
  updateMeridianFlip_opt();
}

void opt_celestialPushCallback(void *ptr) // If Button Celestial Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  Tracking_type = 1;
  Tracking_Mode = "Celest";
  updateTrackingMode_opt();
}

void opt_solarPushCallback(void *ptr)  // If Button Solar Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  Tracking_type = 2;
  Tracking_Mode = "Solar";
  updateTrackingMode_opt();
}

void opt_lunarPushCallback(void *ptr) // If Button Lunar Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  Tracking_type = 0;
  Tracking_Mode = "Lunar";
  updateTrackingMode_opt();
}

void optClock_alignPushCallback(void *ptr) // If Button GPS Clock Align Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  storeOptions_SD();
  CURRENT_SCREEN = 0;
  drawGPSScreen();
}

//////////////////////////// Choose Alignment Type Page touch events////////////////////////////////////

void align1StarPushCallback(void *ptr)  // If 1Star Alignment button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  ALLIGN_TYPE = 1;
  is_btn_pressed = false;
  drawAlignObjects_ali();
}

void iterativeAlignPushCallback(void *ptr)  // If Iterative Alignment button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  ALLIGN_TYPE = 3;
  is_btn_pressed = false;
  // I'll take some time to Initialize the Sub ARRAY with suitable stars (only for Northern Hemi)
  int cc = 0;
  for (int t = 0; t < 203; t++)
  {
    int i1 = Stars[t].indexOf(';');
    int i2 = Stars[t].indexOf(';', i1 + 1);
    int i3 = Stars[t].indexOf(';', i2 + 1);
    OBJECT_NAME = Stars[t].substring(i1 + 1, i2) + " from " + Stars[t].substring(0, i1);
    String OBJ_RA = Stars[t].substring(i2 + 1, i3);
    OBJECT_RA_H = OBJ_RA.substring(0, OBJ_RA.indexOf('h')).toFloat();
    OBJECT_RA_M = OBJ_RA.substring(OBJ_RA.indexOf('h') + 1, OBJ_RA.length() - 1).toFloat();
    float ts_RA = OBJECT_RA_H + OBJECT_RA_M / 100;
    String OBJ_DEC = Stars[t].substring(i3, Stars[t].length());
    String sign = OBJ_DEC.substring(0, 1);
    OBJECT_DEC_D = OBJ_DEC.substring(1, OBJ_DEC.indexOf('°')).toFloat();
    if (sign == "-")
    {
      OBJECT_DEC_D *= (-1);
    }
    OBJECT_DEC_M = 0;
    if (ts_RA > 5.3 && ts_RA < 23.3)
    {
      calculateLST_HA();
      if (AZ > 90 && AZ < 270 && ALT > 20)
      {
        Iter_Stars[cc] = Stars[t];
        cc += 1;
        if (cc > 49)
        {
          break;
        }
      }
    }
    int_star_count = floor(cc / 15) + 1;
  }
  delay(500);
  drawAlignObjects_ali();
}

void skip_alignPushCallback(void *ptr)  // If SKIP button touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  IS_IN_OPERATION = true;
  drawMainScreen();

  int do_kolko = 0;
  if (ALLIGN_TYPE == 3) {
    do_kolko = int_star_count;
  } else {
    do_kolko = 24;
  }
}

//////////////////////////// Manual Align Page touch events////////////////////////////////////

void sync_alignPushCallback(void *ptr)  // If Sync button touched
{
  // BTN "Align/Sync!" pressed
  // Here we need to know which Star is this - 1st, 2nd, 3rd... etc ?
  // In order to use Ralph Pass alignment procedure described on http://rppass.com/
  // http://rppass.com/align.pdf - the actual PDF

  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (ALLIGN_STEP == 1) // If in 1Star Alignment Method Step1
  {
    if (ALLIGN_TYPE == 1) // If in 1Star Alignment Method
    {
      Serial.println("Sync Button Pressed");
      Serial.println("Allign Type=");
      Serial.print (ALLIGN_TYPE);
      Serial.println("Allign Step=");
      Serial.print(ALLIGN_STEP);
      is_btn_pressed = false;
      IS_TRACKING = false;
      IS_IN_OPERATION = true;
      drawMainScreen();
    }
    else if (ALLIGN_TYPE == 3) // If in Iterative Alignment Method and in Step1       // Edit this part
    {
      Serial.println("Sync Button Pressed");
      Serial.println("Allign Type=");
      Serial.print (ALLIGN_TYPE);
      Serial.println("Allign Step=");
      Serial.print(ALLIGN_STEP);
      // Select Polaris and SlewTo...
      IS_TRACKING = false; // Select Polaris and SlewTo...
      //
      //
      // NOW I have to SYNC on that STAR!
      // Assign Values calculated for
      // SLEW_RA_microsteps and SLEW_DEC_microsteps
      //
      selectOBJECT_M(192, 2); // Polaris in on Index 192 in the Stars Array
      calculateLST_HA();
      OnScreenMsg(1);
      if (IS_SOUND_ON)
      {
        SoundOn(note_C, 32);
        delay(200);
        SoundOn(note_C, 32);
        delay(200);
        SoundOn(note_C, 32);
        delay(200);
      }
      // Stop Interrupt procedure for tracking.
      Timer3.stop();
      tm1.disable(); // Nextion Tracking Animation Stop
      IS_TRACKING = false;
      IS_OBJ_FOUND = false;
      IS_OBJECT_RA_FOUND = false;
      IS_OBJECT_DEC_FOUND = false;
      Slew_timer = millis();
      Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
      //drawConstelationScreen(0);
      ALLIGN_STEP = 2;
    }
  }
  else if (ALLIGN_STEP == 2)
  {
    if (ALLIGN_TYPE == 3) // If in Iterative Alignment Method  Step 2
    {
      Serial.println("Sync Button Pressed");
      Serial.println("Allign Type=");
      Serial.print (ALLIGN_TYPE);
      Serial.println("Allign Step=");
      Serial.print(ALLIGN_STEP);
      // Select First Star Again and SlewTo...
      is_btn_pressed = false;
      IS_TRACKING = false;
      selectOBJECT_M(Iterative_Star_Index, 3); // Load First Star from the Stars Array
      calculateLST_HA();
      OnScreenMsg(1);
      if (IS_SOUND_ON)
      {
        SoundOn(note_C, 32);
        delay(200);
        SoundOn(note_C, 32);
        delay(200);
        SoundOn(note_C, 32);
        delay(200);
      }
      // Stop Interrupt procedure for tracking.
      Timer3.stop();
      tm1.disable(); // Nextion Tracking Animation Stop
      IS_TRACKING = false;
      IS_OBJ_FOUND = false;
      IS_OBJECT_RA_FOUND = false;
      IS_OBJECT_DEC_FOUND = false;
      Slew_timer = millis();
      Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
      //drawConstelationScreen(0);
      ALLIGN_STEP = 1;
    }
  }
}

void repeat_alignPushCallback(void *ptr)  // If BTN Repeat/ EXIT is touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  if (ALLIGN_TYPE == 3) // If Button <Repeat / EXIT is Pressed in Iterative Alignment Method
  {
    // delta_a_RA = 0;
    // delta_a_DEC = 0;
    STARS_PAGER = 0;
    is_btn_pressed = false;
    IS_TRACKING = false;
    IS_IN_OPERATION = true;
    drawMainScreen();
  }
  else
  {
    ALLIGN_STEP -= 1; // If Button <REPEAT / Exit is Pressed in 1Star Alignment Method
    is_btn_pressed = false;
    drawAlignObjects_ali();
  }
}

////////////////////////////Sync Page touch events////////////////////////////////////

void  sync_donePushCallback(void *ptr) // If Button done Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  is_btn_pressed = false;
  IS_IN_OPERATION = true;
  drawMainScreen();
}

void sync_nextPushCallback(void *ptr) // If Button Next Touched
{
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  is_btn_pressed = false;
  int do_kolko = 0;
  if (ALLIGN_TYPE == 3)
  {
    do_kolko = int_star_count;
    if (STARS_PAGER <= do_kolko - 3) {
      STARS_PAGER += 1;
      drawAlignObjects_ali();
      Serial.println("int_star_count = ");
      Serial.println(int_star_count);
    }
  } else if (ALLIGN_TYPE == 1)
  {
    do_kolko = 9; // 9 Pages of Stars
    STARS_PAGER += 1;
    if ( STARS_PAGER >= 9)
    {
      STARS_PAGER = 9;
    }
  }
  Serial.println("Stars Pager = ");
  Serial.println(STARS_PAGER);
}

void  sync_prevPushCallback(void *ptr) // If Button Prev touched
{
  // BTN <prev pressed
  if (IS_SOUND_ON) {
    SoundOn(800, 8);
  }

  is_btn_pressed = false;
  int do_kolko = 0;
  if (ALLIGN_TYPE == 3)
  {
    do_kolko = int_star_count;
    STARS_PAGER -= 1;
    if (STARS_PAGER >= 0) {
      drawAlignObjects_ali();
    } else {
      STARS_PAGER = 0;
    }
  } else if (ALLIGN_TYPE == 1)
  {
    do_kolko = 9; // 9 Pages of Stars
    STARS_PAGER -= 1;
    if (STARS_PAGER <= 0)
    {
      STARS_PAGER = 0;
    }
  }
  Serial.println("Stars Pager = ");
  Serial.println(STARS_PAGER);
}

//////////////////////////////////////////// Sync Text Boxes Touch Events
void sync_obj_1PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 1;
}

void sync_obj_2PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 2;
}

void sync_obj_3PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 3;
}

void sync_obj_4PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 4;
}

void sync_obj_5PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 5;
}

void sync_obj_6PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 6;
}

void sync_obj_7PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 7;
}

void sync_obj_8PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 8;
}

void sync_obj_9PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 9;
}

void sync_obj_10PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 10;
}

void sync_obj_11PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 11;
}

void sync_obj_12PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 12;
}
void sync_obj_13PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 13;
}

void sync_obj_14PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 14;
}

void sync_obj_15PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 15;
}

void sync_obj_16PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 16;
}

void sync_obj_17PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 17;
}

void sync_obj_18PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 18;
}

void sync_obj_19PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 19;
}

void sync_obj_20PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 20;
}

void sync_obj_21PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 21;
}

void sync_obj_22PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 22;
}

void sync_obj_23PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 23;
}

void sync_obj_24PushCallback(void *ptr)
{
  is_btn_pressed = true;
  sync_object = 24;
}
