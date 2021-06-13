void considerTouchInput()
{
  int object_selected = 0;
  if (CURRENT_SCREEN == 6)
  {
    if (LOAD_SELECTOR == 1)
    {
      if (MESS_PAGER == 0 )
      {
        object_selected = selected_object;
      }
      else if (MESS_PAGER == 1)
      {
        object_selected = selected_object + 35;
      } else if (MESS_PAGER == 2 )
      {
        object_selected = selected_object + 70;
      } else if (MESS_PAGER == 3)
      {
        object_selected = selected_object + 105;
      }
    } else if (LOAD_SELECTOR == 2)
    {
      if (TREAS_PAGER == 0 )
      {
        object_selected = selected_object;
      }
      else if (TREAS_PAGER == 1)
      {
        object_selected = selected_object + 35;
      } else if (TREAS_PAGER == 2 )
      {
        object_selected = selected_object + 70;
      } else if (TREAS_PAGER == 3)
      {
        object_selected = selected_object + 105;
      }
    } else if (LOAD_SELECTOR == 3)
    {
      object_selected = selected_object;
    } else if (LOAD_SELECTOR == 4)
    {
      object_selected = selected_object;
    }
    //////////////////////////////////////////////////// In Messier Catalog ////////////////////////////////////////////////
    if (LOAD_SELECTOR == 1 && is_btn_pressed == true) // If we're in Messier Catalog and a button is pressed
    {
      if (IS_SOUND_ON) {
        SoundOn(800, 8);
      }
      if (object_selected > 0) {

        object_selected = object_selected - 1;
        //Serial.println("Selected Object= ");
        //Serial.println(selected_object);
        selectOBJECT_M(object_selected, 0);
        calculateLST_HA();
        if (ALT > 0) {
          OnScreenMsg(1);
          if (IS_SOUND_ON) {
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
          Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
          Tracking_Mode = "Celest";
          updateTrackingMode_opt();
          opt_celestial.setValue(1);
          opt_solar.setValue(0);
          opt_lunar.setValue(0);
          Serial1.print("wepo 1,80");  // Change Celestial Button to ON in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,90");  // Change Solar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Slew_timer = millis();
          Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
        }
        UpdateObservedObjects();
        MESS_PAGER == 0;
        sun_confirm = false;
        drawMainScreen();
      }
    }

    ///////////////////////////////////////////////// In Treasures Catalog /////////////////////////////////////
    else if (LOAD_SELECTOR == 2 && is_btn_pressed == true) // If we're in Treasures Catalog and a button is pressed
    {
      if (IS_SOUND_ON) {
        SoundOn(800, 8);
      }

      if (object_selected > 0) {
        object_selected = object_selected - 1;
        selectOBJECT_M(object_selected, 1);
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
          Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
          Tracking_Mode = "Celest";
          updateTrackingMode_opt();
          opt_celestial.setValue(1);
          opt_solar.setValue(0);
          opt_lunar.setValue(0);
          Serial1.print("wepo 1,80");  // Change Celestial Button to ON in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,90");  // Change Solar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Slew_timer = millis();
          Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
        }
        UpdateObservedObjects();
        TREAS_PAGER == 0;
        sun_confirm = false;
        drawMainScreen();
      }
    }
    /////////////////////////////////////////////// In Solar System Catalog /////////////////////////////////////////////

    else if (LOAD_SELECTOR == 3 && is_btn_pressed == true) // If we're in Solar System Catalog and a button is pressed
    {
      if (IS_SOUND_ON) {
        SoundOn(800, 8);
      }

      calculateLST_HA();
      if (object_selected > 0) {
        object_selected = object_selected - 1;

        if (object_selected == 3) // If I Chose Earth
        {
          OnScreenMsg(7);
          delay(2000);
          drawMainScreen();
        }
        else if (object_selected <= 10)
        {
          if (object_selected == 0) // If I chose the Sun
          {
            CURRENT_SCREEN = 15;
            conf_Sun_track.show();
          } else {
            planet_pos(object_selected); // If I Chose Another Planet
          }

          if (sun_confirm || object_selected != 0)
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
              tm1.disable();// Nextion Tracking Animation Stop
              IS_TRACKING = false;
              IS_OBJ_FOUND = false;
              IS_OBJECT_RA_FOUND = false;
              IS_OBJECT_DEC_FOUND = false;
              switch (object_selected)
              {
                case 0:
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
                  Serial1.print("wepo 1,90");  // Change Solar Button to ON in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  break;
                case 10:
                  Tracking_type = 0; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
                  Tracking_Mode = "Lunar";
                  updateTrackingMode_opt();
                  opt_celestial.setValue(0);
                  opt_solar.setValue(0);
                  opt_lunar.setValue(1);
                  Serial1.print("wepo 0,80");  // Change Celestial Button to OFF in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.print("wepo 0,90");  // Change Solar Button to ON in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.print("wepo 1,100");  // Change Lunar Button to OFF in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  break;
                default:
                  Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
                  Tracking_Mode = "Celest";
                  updateTrackingMode_opt();
                  opt_celestial.setValue(1);
                  opt_solar.setValue(0);
                  opt_lunar.setValue(0);
                  Serial1.print("wepo 1,80");  // Change Celestial Button to OFF in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.print("wepo 0,90");  // Change Solar Button to ON in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  Serial1.write(0xff);
                  break;
              }
              Slew_timer = millis();
              Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
            }
            UpdateObservedObjects();
            sun_confirm = false;
            drawMainScreen();
          }
        }
      }
    }

    ////////////////////////////////////////////////// In Custom CSV Catalog ///////////////////////////////////////
    else if (LOAD_SELECTOR == 4 && is_btn_pressed == true) // If we're in Custom CSV Catalog and a button is pressed
    {
      if (IS_SOUND_ON) {
        SoundOn(800, 8);
      }

      if (object_selected > 0) {
        object_selected = object_selected - 1;
        selectOBJECT_M(object_selected, 4);
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
          Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
          Tracking_Mode = "Celest";
          updateTrackingMode_opt();
          opt_celestial.setValue(1);
          opt_solar.setValue(0);
          opt_lunar.setValue(0);
          Serial1.print("wepo 1,80");  // Change Celestial Button to ON in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,90");  // Change Solar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Slew_timer = millis();
          Slew_timer = millis();
          Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
        }
        UpdateObservedObjects();
        sun_confirm = false;
        drawMainScreen();
      }
    }
  }////////////////////////////////////////////////////////// Start of Star Sync Screen Touch Events ///////////////////////////////////////////////////////////////////////////////////

  else if (CURRENT_SCREEN == 12) // captures touches on drawStarSyncScreen()
  {
    int selected_object = 0;
    if (STARS_PAGER == 0)
    {
      selected_object = sync_object;
    } else if (STARS_PAGER == 1)
    {
      selected_object = sync_object + 24;
    } else if (STARS_PAGER == 2)
    {
      selected_object = sync_object + 48;
    } else if (STARS_PAGER == 3)
    {
      selected_object = sync_object + 72;
    } else if (STARS_PAGER == 4)
    {
      selected_object = sync_object + 96;
    } else if (STARS_PAGER == 5)
    {
      selected_object = sync_object + 120;
    } else if (STARS_PAGER == 6)
    {
      selected_object = sync_object + 144;
    } else if (STARS_PAGER == 7)
    {
      selected_object = sync_object + 168;
    } else if (STARS_PAGER == 8)
    {
      selected_object = sync_object + 192;
    }


    if (ALLIGN_TYPE < 3 && is_btn_pressed == true)// found button pressed.... now I need to get his ID and link to the ARRAY;
    {
      if (IS_SOUND_ON) {
        SoundOn(800, 8);
      }

      selected_object = selected_object - 1;
      if (Stars[selected_object] != "")
      {
        selectOBJECT_M(selected_object, 2);
        calculateLST_HA();
        if (ALT < 0)
        {
          OnScreenMsg(3); // Error Not Visible!
          if (IS_SOUND_ON)
          {
            SoundOn(note_C, 96);
            delay(2000);
          }
          //drawAlignObjects_ali(); // Nextion goes Back to first Page, If removed, no buttons work   // Still Hangs Here
          CURRENT_SCREEN = 12;
          STARS_PAGER = STARS_PAGER;
          ALLIGN_TYPE = 0;
          is_btn_pressed = false;
        }
        else
        {
          OnScreenMsg(1); // Moving Step Back Please !
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
          Timer3.stop(); //
          IS_TRACKING = false;
          IS_OBJ_FOUND = false;
          IS_OBJECT_RA_FOUND = false;
          IS_OBJECT_DEC_FOUND = false;
          Slew_timer = millis();
          Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
          Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
          Tracking_Mode = "Celest";
          updateTrackingMode_opt();
          opt_celestial.setValue(1);
          opt_solar.setValue(0);
          opt_lunar.setValue(0);
          Serial1.print("wepo 1,80");  // Change Celestial Button to ON in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,90");  // Change Solar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Slew_timer = millis();
          STARS_PAGER == 0;
          SELECTED_STAR = selected_object;
          ALLIGN_STEP += 1;
          //drawConstelationScreen(zz);
        }
      }
    }
    ////////////////////////////////////// Constelation Screen Touch Events//////////////////////////////////////////////
    else
    {
      // I'm in STARS selector and need to check which Star object is pressed

      if (is_btn_pressed == true)
      {
        if (IS_SOUND_ON) {
          SoundOn(800, 8);
        }

        // found button pressed.... now I need to get his ID and link to the ARRAY;
        selected_object = selected_object - 1;
        if (Iter_Stars[selected_object] != "")
        {
          // selectOBJECT_M(zz,3);
          Iterative_Star_Index = selected_object;

          // replaced the above with the below row...
          // to make sure each press selects the same star (inital or on Step 2)
          // change made after Test on 17th March.
          selectOBJECT_M(Iterative_Star_Index, 3);
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
          Timer3.stop(); //
          IS_TRACKING = false;
          IS_OBJ_FOUND = false;
          IS_OBJECT_RA_FOUND = false;
          IS_OBJECT_DEC_FOUND = false;
          Slew_timer = millis();
          Slew_RA_timer = Slew_timer + 20000;   // Give 20 sec. advance to the DEC. We will revise later.
          Tracking_type = 1; // Change the tracking type Automatically. 1: Sidereal, 2: Solar, 0: Lunar;
          Tracking_Mode = "Celest";
          updateTrackingMode_opt();
          opt_celestial.setValue(1);
          opt_solar.setValue(0);
          opt_lunar.setValue(0);
          Serial1.print("wepo 1,80");  // Change Celestial Button to ON in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,90");  // Change Solar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.print("wepo 0,100");  // Change Lunar Button to OFF in Options Screen
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);
          STARS_PAGER == 0;
          SELECTED_STAR = selected_object;
          ALLIGN_STEP += 1;
          // drawConstelationScreen(zz);

        }
      }
    }
  }
}
