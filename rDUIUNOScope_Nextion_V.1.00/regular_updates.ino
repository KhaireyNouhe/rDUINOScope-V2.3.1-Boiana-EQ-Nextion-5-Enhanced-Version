//
//    rDUINOScope - Arduino based telescope control system (GOTO).
//    Copyright (C) 2016 Dessislav Gouzgounov (Desso)
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    PROJECT Website: http://rduinoscope.tk/
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
//  - Measures Temperature and Humidity;
//  - On each TimeInterval (~10 sec.) - Updates screens accordingly (e.g. Time, LST, Temperature, Humidity and etc.)
//

///////////////////////////////////////////////////////////////////// Update Temperature in Main Screen ///////////////////////////////////////////////////////////

void considerTempUpdates() // Temperature && Humidity Updates && battery voltage
{
  if (CURRENT_SCREEN == 4 && (millis() - Tupdate_time) > 30000)
  {
    float tHum = dht.readHumidity();
    float tTemp = dht.readTemperature();
    if (isnan(tHum) || isnan(tTemp))
    {
      return;
    }
    else
    {
      //_temp = tTemp - 2;  // I need to calibrate my sensor... it reads 2 deg. higher temp.
      _temp = tTemp;
      _humid = tHum;
    }

    if (_temp > -75 && _temp < 75 && _humid < 100 && _humid > 0)
    {
      main_temp.setValue (_temp);                         // Nextion
      main_humidity.setValue (_humid);                    // Nextion
    }
    Tupdate_time = millis();

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
  }
}

///////////////////////////////////////////////////////////////////// Update Time in Clock Screen and Main Screen ///////////////////////////////////////////////////////////

void considerTimeUpdates()
{ // UPDATEs time on Screen1 && Screen4 -  Clock Screen and Main Screen
  int changes = 0;
  for (int y = 0; y < 12; y++)
  {
    if (w_DateTime[y] != 0)
    {
      changes = 1;
    }
  }
  int mer_flp_sound = HAHour + ((HAMin + MIN_TO_MERIDIAN_FLIP + MIN_SOUND_BEFORE_FLIP) / 60);
  if ((millis() - update_time) > 10000 && mer_flp_sound >= 24)
  {
    if (IS_SOUND_ON)
    {
      SoundOn(3830, 8);
    }
    ////////////////////////// Nextion Main Screen Time Sync ////////////////////////

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
  }
  ///////////////////////////////////////////////////////////////////// Update Date in Main Screen ///////////////////////////////////////////////////////////

  if (CURRENT_SCREEN == 4 && (millis() - update_time) > 10000)
  {

    if (old_d != rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'))
    {
      ////////////////////////// Nextion Main Screen Date Sync ////////////////////////

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

    }
    ///////////////////////////////////////////////////////////////////// Update Time in Main Screen ///////////////////////////////////////////////////////////

    ////////////////////////// Nextion Main Screen Time Sync ////////////////////////
    // Sync Nextion RTC Hour to Arduino RTC
    String Time_q = String(rtc.getTimeStr());
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

    ///////////////////////////////////////////////////////////////////// Update LST in Main Screen ///////////////////////////////////////////////////////////
    if ((int)LST < 10)
    {
      main_LST1.setValue((int)LST); // Nextion
    }
    else
    {
      main_LST1.setValue((int)LST); // Nextion
    }

    if ((LST - (int)LST) * 60 < 10)
    {
      // Nextion
      int mainLST2_Val = ((LST - (int)LST) * 60);
      main_LST2.setValue (mainLST2_Val);
    }
    else
    {
      // Nextion
      int mainLST2_Val = ((LST - (int)LST) * 60);
      main_LST2.setValue (mainLST2_Val);
    }

    ///////////////////////////////////////////////////////////////////// Update Object Data in Main Screen ///////////////////////////////////////////////////////////

    if ((OBJECT_NAME != "") && (OBJECT_NAME != "CP") && (IS_BT_MODE_ON == false))
    {
      /*
        if (TRACKING_MOON)
        {
        planet_pos(10);
        }
      */
      /////////////////////////////////////////// Nextion //////////////////////
      Serial1.print("main_HA.txt=");
      Serial1.print("\"");
      Serial1.print(HAHour, 0);
      Serial1.print("h");
      Serial1.print(" ");
      Serial1.print(HAMin, 1);
      Serial1.print("m   ");
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);

      ///////////////////////////////////////////////////// Nextion /////////////////////////
      Serial1.print("main_ALT_AZ.txt=");
      Serial1.print("\"");
      Serial1.print(floor(AZ), 0);
      Serial1.print("^ ");
      Serial1.print((AZ - floor(AZ)) * 60, 0);
      Serial1.print("' / ");
      Serial1.print(floor(ALT), 0);
      Serial1.print("^ ");
      Serial1.print((ALT - floor(ALT)) * 60, 0);
      Serial1.print("'   ");
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }

    if ((IS_BT_MODE_ON == true) && (OBJECT_DESCR == "Pushed via BlueTooth")) {

      /////////////////////////////////////// Nextion //////////////////
      Serial1.print("main_HA.txt=");
      Serial1.print("\"");
      Serial1.print(HAHour, 0);
      Serial1.print("h");
      Serial1.print(HAMin, 1);
      Serial1.print("m    | HS:");
      Serial1.println(SLEW_RA_microsteps);
      Serial1.print("               | CS:");
      Serial1.print(RA_microSteps);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }
    update_time = millis();
  }
  ///////////////////////////////////////////////////////////////////// Update HA/RA/DEC in Coordinates Screen ///////////////////////////////////////////////////////////

  else if (CURRENT_SCREEN == 5 && (millis() - update_time) > 2000)
  {
    Current_RA_DEC();
    coord_HA.setText(curr_HA_lz);          // Nextion Coordintes Screen
    coord_RA.setText(curr_RA_lz);           // Nextion Coordintes Screen
    coord_DEC.setText(curr_DEC_lz);          // Nextion Coordintes Screen
    update_time = millis();
  }
  ///////////////////////////////////////////////////////////////////// Update HA/RA/DEC in AutoGuiding Screen ///////////////////////////////////////////////////////////
  /*
    // Wasn't included since the update timer affects the delay time that is responsible for moving the steppers, i.e makes the Autoguiding inaccurate.
    else if (CURRENT_SCREEN == 11 && (millis() - update_time) > 2000)
    {
      Current_RA_DEC();
      Guiding_HA.setText(curr_HA_lz);          // Nextion Coordintes Screen
      Guiding_RA.setText(curr_RA_lz);           // Nextion Coordintes Screen
      Guiding_DEC.setText(curr_DEC_lz);          // Nextion Coordintes Screen
      update_time = millis();
    }
  */
  ///////////////////////////////////////////////////////////////////// Update Time in Time Screen ///////////////////////////////////////////////////////////

  // Takes Place Locally on the Nextion TFT.

  ///////////////////////////////////////////////////////////////////// Update GPS Data in GPS Screen ///////////////////////////////////////////////////////////
  else if (CURRENT_SCREEN == 0 && (millis() - update_time) > 5000)
  {
    /////////////////////////////////////// Nextion //////////
    Serial1.print("LAT_val.txt=");
    Serial1.print("\"");
    Serial1.print(gps.location.lat(), 4);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    /////////////////////////////////////// Nextion //////////
    Serial1.print("LON_val.txt=");
    Serial1.print("\"");
    Serial1.print(gps.location.lng(), 4);
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    /////////////////////////////////////// Nextion //////////
    Serial1.print("SAT_val.txt=");
    Serial1.print("\"");
    Serial1.print(gps.satellites.value());
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    /////////////////////////////////////// Nextion //////////
    Serial1.print("GMT_val.txt=");
    Serial1.print("\"");
    Serial1.print(gps.time.hour());
    Serial1.print(":");
    Serial1.print(gps.time.minute());
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    /////////////////////////////////////// Nextion //////////
    Serial1.print("ALT_val.txt=");
    Serial1.print("\"");
    Serial1.print(gps.altitude.meters());
    Serial1.print("\"");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    if (gps.satellites.value() == 0)
    {
      smartDelay(1000);
    }
    else
    {
      GPS_iterrations += 1;
      smartDelay(1000);
    }

    if ((GPS_iterrations > 2) && (gps.location.lat() != 0))
    {
      OBSERVATION_LONGITUDE = gps.location.lng();
      OBSERVATION_LATTITUDE = gps.location.lat();
      OBSERVATION_ALTITUDE = gps.altitude.meters();
      // Set the earth rotation direction depending on the Hemisphere...
      // HIGH and LOW are substituted
      if (OBSERVATION_LATTITUDE > 0)
      {
        STP_FWD = LOW;
        STP_BACK = HIGH;
      }
      else
      {
        STP_FWD = HIGH;
        STP_BACK = LOW;
      }
      Serial.println(OBSERVATION_LATTITUDE);
      Serial.print("STP_FWD = ");
      Serial.println(STP_FWD);
      Serial.print("STP_BACK = ");
      Serial.println(STP_BACK);
      if (IS_SOUND_ON) {
        SoundOn(note_C, 32);
      }
      CURRENT_SCREEN = 1;
      // Serial2.end();

      int ora, date_delay = 0;
      // int time_delay = round(gps.location.lng() * 4 / 60); //rough calculation of the timezone delay
      int time_delay = TIME_ZONE; // Use the time zone delay   Sujjested By Aitor
      // convert to epoch
      setTime(gps.time.hour(), gps.time.minute(), gps.time.second(), gps.date.day(), gps.date.month(), gps.date.year());
#ifdef serial_debug
      Serial.print("epoch: ");
      Serial.println(now());
#endif

      if (isSummerTime())
      {
        //If in summer time sum 1h and put Summer_Time flag as 1
        time_delay += 1;
        Summer_Time = 1;
      }

      //update the value of the variable Now
      ora = gps.time.hour() + time_delay;

      //to update the real time
      if (ora >= 24)
      {
        ora -= 24;
        date_delay = 1;
      }

      //setTime(Now, gps.time.minute(), gps.time.second(), gps.date.day()+date_delay, gps.date.month(), gps.date.year()); <-- too mantain sync with UTC
      rtc.setDate(gps.date.day() + date_delay, gps.date.month(), gps.date.year());
      rtc.setTime(ora, gps.time.minute(), gps.time.second());
      drawClockScreen();
    }
    update_time = millis();
  }
  ///////////////////////////////////////////////////////////////////// Update Delta RA / Delta DEC in Constelations (Manual Align) Screen //////////////////////////////////////////////

  else if ((CURRENT_SCREEN == 13) && (IS_OBJ_FOUND == true) && ((millis() - update_time) > 2000))
  {
    float HAHh;
    float HAMm;
    float HA_deci;

    if (HAHour >= 12) {
      HAHh = HAHour - 12;
    } else {
      HAHh = HAHour;
    }

    HAMm = HAMin;
    HA_deci = (HAHh + (HAMm / 60)) * 15; // In degrees - decimal

    if (ALLIGN_STEP == 1)
    {

      delta_a_RA = (double(RA_microSteps) - double(HA_deci * HA_H_CONST)) / double(HA_H_CONST);
      delta_a_DEC = (double(DEC_microSteps) - double(SLEW_DEC_microsteps)) / double(DEC_D_CONST);

      Serial1.print("Del_Ra_val.txt=");      // Nextion
      Serial1.print("\"");
      Serial1.print(delta_a_RA * 60, 6);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);

      Serial1.print("Del_Dec_val.txt="); // Nextion
      Serial1.print("\"");
      Serial1.print(delta_a_DEC * 60, 6);
      Serial1.print("\"");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
    }
    update_time = millis();
  }
}
