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
//
//    ALLIGNMENT Method: 1 Star Alignment - The method I have implemented is part of Mr. Ralph Pass alignment procedure described on http://rppass.com/
//                       Mr. Pass helped rDUINOScope by providing the calculations needed to implement the method. http://rppass.com/align.pdf - the actual PDF
//
//                       Iterative Alignment - The method is based on article from "New" Hamilton Astronomy.com website: http://astro.hcadvantage.com
//                       Actual PDF document: http://astro.hcadvantage.com/ASTRO_ARTICLES/Polar_Alignment_Part_II.pdf
//
// This is the Nextion Enhanced 5" Version that has been coded and modified from the original code by Khairey Nouhe khaireynouhe@gmail.com,
// upon the agreement of the original coder (Dessislav Gouzgounov) as a contribution to the rDUNOScope support group.

#include "DHT.h"
#include <TinyGPS++.h>
#include <Time.h>
#include <SD.h>
#include <DueTimer.h> // interruptions library
#include <DS3231.h>
#include <math.h>
#include <TimeLib.h>
#include "defines.h"
#include <Nextion.h>  // Include the nextion library (the official one) https://github.com/itead/ITEADLIB_Arduino_Nextion
// Make sure you edit the NexConfig.h file on the library folder to set the correct serial port for the display.
// By default it's set to Serial1.

const String FirmwareDate = "10/4/2020";
const String FirmwareNumber = "v2.3.1 Boiana-EQ-Nextion-Solar&AutoGuiding";
const String FirmwareName = "rDUINOScope Boiana-EQ V2.3.1";
const String FirmwareTime = "12:00:00";
const String HardwareVersion = "Fayrouz&Nextion V.1.0";

// Default values to load when CANCEL button is hit on the GPS screen (Change by your Home Location!)
float OBSERVATION_LONGITUDE = 24.7136;  // (24.7136* - Riyadh, Saudi Arabia)
float OBSERVATION_LATTITUDE = 46.6753; // (46.6753* - Riyadh, Saudi Arabia)
float OBSERVATION_ALTITUDE = 612.00;  // Riyadh, Saudi Arabia
int TIME_ZONE = 3;                   // Riyadh, Saudi Arabia
// .............................................................

#define serial_debug       // comment out to deactivate the serial debug mode

#define use_battery_level  // comment out to deactivate the battery level option

// HERE GOES THE Mount, Gears and Drive information.
// ... used to calculate the HourAngle to microSteps ratio
// UPDATE THIS PART according to your SET-UP Using the companion Excel sheet.
// ---------------------------------------------
// NB: RA and DEC uses the same gear ratio (144 tooth in my case)!
//----------------------------------------------
#ifdef serial_debug
int WORM = 144;
#else
int WORM = 144;
#endif
int REDUCTOR = 4;      // 1:4 gear reduction
int DRIVE_STP = 200;   // Stepper drive have 200 steps per revolution
int MICROSteps = 16;   // I'll use 1/16 microsteps mode to drive sidereal - also determines the LOWEST speed.

// below variables are used to calculate the paramters where the drive works. Find them out using the Excel sheet.
#define ARCSEC_F_ROTAT 1296000   // ArcSeconds in a Full earth rotation;
#define SIDEREAL_DAY 86164.0905   // Sidereal day in seconds
float ArcSECstep;
int MicroSteps_360;
int RA_90;  // How much in microSteps the RA motor have to turn in order to make 6h = 90 degrees;
int DEC_90;   // How mich in microSteps the DEC motor have to turn in order to make 6h = 90 degrees;
int HA_H_CONST;
int HA_M_CONST;
int DEC_D_CONST;
int DEC_M_CONST;
int MIN_TO_MERIDIAN_FLIP = 2;   // This constant tells the system when to do the Meridian Flip. "= 2" means 2 minutes before 24:00h (e.g. 23:58h)
int MIN_SOUND_BEFORE_FLIP = 3;   // This constant tells the system to start Sound before it makes Meridian Flip
float mer_flp;                   // The calculateLST_HA() function depending on this timer will convert the HA and DEC to the propper ones to do the flip.
boolean MERIDIAN_FLIP_DO = false;
int Tracking_type = 1;  // 1: Sidereal, 2: Solar, 0: Lunar;
int Clock_Sidereal;  // Variable for the Interruptions.Interruption is initialized depending on the DATA above -in miliseconds
int Clock_Solar;  // Variable for the Interruptions. Interruption is initialized depending on the DATA above -in miliseconds
int Clock_Lunar;  // Variable for the Interruptions. Interruption is initialized depending on the DATA above -in miliseconds

/////////////////// Module Pins Setup /////////////////////////////////

int sd_cs = 21;  // Khairey changed it from 4 to 41
#define DHTPIN 43   // khairey changed it from  3  to   43
#define DHTTYPE DHT22

DS3231 rtc(A4, A5);           // (SDA-A4, SCL-A5) from the RTC board
DHT dht(DHTPIN, DHTTYPE);
TinyGPSPlus gps;             // (Rx-16, Tx-17)

#define DAY_NIGHT_PIN A6 // NIGHT MODE ANALOG pin 

//Joystick Pins//
int yPin = A0;
int xPin = A1;
int Joy_SW = A9;
int x_cal, y_cal = 0;

int FAN1 = A2;
int FAN2 = A3;

int speakerOut = DAC1;
int BAT_PIN = A7;             //Analog channel A7 as used to measure BAT_PIN voltage

////////////////////////// Steppers Setup //////////////////////////////////
int RA_EN = 47;
int RA_STP = 4;
int RA_DIR = 5;
int RA_MODE0 = 11; // PD7
int RA_MODE1 = 12; // PD8
int RA_MODE2 = 13; // PB27

int DEC_EN = 49;
int DEC_STP = 6;
int DEC_DIR = 7;
int DEC_MODE0 = 10; // PC29
int DEC_MODE1 = 9; // PC21
int DEC_MODE2 = 8; // PC22

////////////////////////// Focus Motor Setup //////////////////////////////////
int Focus_EN = 51;
int focus_step_pin = 29;
int focus_dir_pin = 27;
int encoderCLK = 22;
int encoderDT = 35;
const int encoderSW = 33;  // Reading Push Button switch on the Rotary Encoder
int Focus_Motor_position = 50; // The initial position of focus motor
int encoderCLKLast = LOW;
int encoderState = LOW;
int Focus_StepsToTake = 50;    // Controls the resolution of the Focus Stepper

////////////////////////Auto Guiding Setup ////////////////////////////////////
int RA_PlusPin = 24;
int RA_MinusPin = 26;
int DEC_PlusPin = 28;
int DEC_MinusPin = 30;
int Guiding_Sense = 32;
bool IS_CONNECTED = false;
boolean IS_PulseGuiding = false;
#define LEVEL_HIGH      (30)
#define LEVEL_LOW       (0)
#define CH0_OFFSET  (46 - LEVEL_HIGH/2)
#define CH1_OFFSET  (CH0_OFFSET + 62 * 1)
#define CH2_OFFSET  (CH0_OFFSET + 62 * 2)
#define CH3_OFFSET  (CH0_OFFSET + 62 * 3)
static uint8_t ch0_data = LEVEL_LOW;
static uint8_t ch1_data = LEVEL_LOW;
static uint8_t ch2_data = LEVEL_LOW;
static uint8_t ch3_data = LEVEL_LOW;
////////////////////////////////////////////////////////////////////////////////////

// Other Variables:
String Messier_Array[112];
String Treasure_Array[130];
String custom_Array[100];
String ObservedObjects[50];
String Iter_Stars[50];
int int_star_count = 0;       // Counter for how many stars are loaded into Iter_Stars[] array.... to be used with Pages, so that it does not show more pages than needed
int Observed_Obj_Count = 0;
int ALLIGN_STEP = 0;  // Using this variable to count the allignment steps - 1: Synchronize, 2: Allign and Center, 3:....
int ALLIGN_TYPE = 0;  // Variable to store the alignment type (0-Skip Alignment, 1-1 Star alignment, 2-2 Star alignment
float delta_a_RA = 0;
float delta_a_DEC = 0;
int Iterative_Star_Index = 0;
String Prev_Obj_Start;
int lastScreenUpdateTimer;
unsigned long Slew_timer, Slew_RA_timer = 0;
int OBJECT_Index;
String OBJECT_NAME;
String OBJECT_DESCR;
String OBJECT_DETAILS;
String BT_COMMAND_STR;
String START_TIME;
int STP_FWD = LOW;
int STP_BACK = HIGH;
float OBJECT_RA_H;
float OBJECT_RA_M;
float OBJECT_DEC_D;
float OBJECT_DEC_M;
float OBJECT_MAG;
float curr_RA_H, curr_RA_M, curr_RA_S, curr_DEC_D, curr_DEC_M, curr_DEC_S;    // Global variables to store Mount's current RA and DEC.
char curr_RA_lz[9], curr_DEC_lz[10], curr_HA_lz[9];                                                // Global variable to store current RA and DEC with Leading Zeroes and sign (RA: 00:00:00; DEC: +/-00*00:00)
int SELECTED_STAR = 0;
double DELTA_RA_ADJUST = 1; // cos RA
double DELTA_DEC_ADJUST = 1; // cos DEC
int GPS_iterrations = 0;
double LST, HAHour, HAMin, ALT, AZ;
double JD;
String BTs;
int last_button, MESS_PAGER, TREAS_PAGER, STARS_PAGER, CUSTOM_PAGER;
boolean IS_STEPPERS_ON = true;
boolean IS_FOCUS_ON = true;
boolean IS_OBJ_VISIBLE = false;
boolean IS_IN_OPERATION = false;  // This variable becomes True when Main screen appears
boolean IS_TRACKING = false;
boolean IS_NIGHTMODE;
boolean IS_OBJ_FOUND = true;
boolean IS_OBJECT_RA_FOUND = true;
boolean IS_OBJECT_DEC_FOUND = true;
boolean IS_MERIDIAN_PASSED = false;
boolean IS_POSIBLE_MERIDIAN_FLIP = true;
boolean IS_MERIDIAN_FLIP_AUTOMATIC = true;
boolean IS_BT_MODE_ON = false;
boolean IS_MANUAL_MOVE = false;
boolean IS_FAN1_ON = true;
boolean IS_FAN2_ON = true;
boolean IS_CUSTOM_MAP_SELECTED = false;
boolean IS_SOUND_ON = true;
int TFT_Brightness = 255;
String TFT_Time = "AL-ON";
int TFTBright = DAC0;
int TFT_timeout;
int MAIN_SCREEN_MENU = 0;
int CURRENT_SCREEN = 0;
int LOAD_SELECTOR;   // selector to show which LOADING mechanism is used: 1 - Messier, 2 - File, 3 - NGCs
boolean TRACKING_MOON;
boolean sun_confirm = false;
String Fan1_State = "ON";
String Fan2_State = "ON";
String Sound_State = "ON";
String Stepper_State = "ON";
String Focus_Motor_State = "ON";
String Mer_Flip_State = "Auto";
String Tracking_Mode = "Celest";
int RA_microSteps, DEC_microSteps, rev_RA_microSteps, rev_DEC_microSteps;              // Current position of the motors in MicroSteps! - when movement occures, values are changed accordingly (manual, tracking or slew to);
int RA_mode_steps, DEC_mode_steps;
int SLEW_RA_microsteps, SLEW_DEC_microsteps;    // Where the mottors needs to go in order to point to the object
int RA_finish_last = 0;
int map_r = 0;    // Used to determine the StarMap Row ... image name (1-1.bmp; 1-2.bmp ....)
int map_c = 0;    // Ued to determine the StarMap Column .... image name
String old_t, old_d;
String Start_date;
int update_time, Tupdate_time;
unsigned long UPD_T, UPD_coord, DELAY_Slew, UPD_LST;
int RA_move_ending;
int w_DateTime[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // array to store date - as updated from updater screen - Wishing_Date
int dateEntryPos = 0;
int Summer_Time = 0;
int xPosition = 0;  // Joystick
int yPosition = 0;  // Joystick
float _temp, _Stemp;
float _humid, _Shumid;
int16_t texts, Button_State_ON, Button_State_OFF, Button_Title, l_text, d_text, btn_l_border, btn_d_border, btn_l_text, btn_d_text, btn_l_selection, title_bg, title_texts, messie_btn, file_btn, ngc_btn, MsgBox_bg, MsgBox_t; // defines string constants for the clor - Depending on the DAY/NIGHT modes
File StarMaps;                    // bmp files

// Some variables used for Alignment procedure:
double Star_1_HA = 0;
double Star_1_DEC = 0;
double Star_2_HA = 0;
double Star_2_DEC = 0;
double err_RA = 0;
double err_DEC = 0;
double Eerr_RA = 0;
double Eerr_DEC = 0;
double err_ALT = 0;
double err_AZ = 0;
double det = 0;

/////////////////////////////// Nextion TFT Setup /////////////////////////////////////////////
/* ***** Types of objects:
   NexButton - Button
   NexDSButton - Dual-state Button
   NexHotspot - Hotspot, that is like an invisible button
   NexCheckbox - Checkbox
   NexRadio - "Radio" checkbox, that it's exactly like the checkbox but with a rounded shape
   NexSlider - Slider
   NexGauge - Gauge
   NexProgressBar - Progress Bar
   NexText - Text box
   NexScrolltext - Scroll text box
   NexNumber - Number box
   NexVariable - Variable inside the nextion display
   NexPage - Page touch event
   NexGpio - To use the Expansion Board add-on for Enhanced Nextion displays
   NexRtc - To use the real time clock for Enhanced Nextion displays
 * *****
*/

// Declare objects that we are going to read from the display. This includes buttons, sliders, text boxes, etc:
// Format: <type of object> <object name> = <type of object>(<page id>, <object id>, "<object name>");

// Declare pages:
NexPage Boot = NexPage(0, 0, "Boot");  // Page added as a touch event
NexPage GPS = NexPage(1, 0, "GPS");  // Page added as a touch event
NexPage Time_page = NexPage(2, 0, "Time_page");  // Page added as a touch event
NexPage Alignment = NexPage(3, 0, "Alignment");  // Page added as a touch event
NexPage Sync = NexPage(4, 0, "Sync");  // Page added as a touch event
NexPage Manual_Align = NexPage(5, 0, "Manual_Align");  // Page added as a touch event
NexPage Main = NexPage(6, 0, "Main");  // Page added as a touch event
NexPage Menu = NexPage(7, 0, "Menu");  // Page added as a touch event
NexPage Load = NexPage(8, 0, "Load");  // Page added as a touch event
NexPage Options = NexPage(9, 0, "Options");  // Page added as a touch event
NexPage Coordinates = NexPage(10, 0, "Coordinates");  // Page added as a touch event
NexPage Stat = NexPage(11, 0, "Stat");  // Page added as a touch event
NexPage Autoguiding = NexPage(12, 0, "Autoguiding");  // Page added as a touch event
NexPage AstroTools = NexPage(13, 0, "AstroTools");  // Page added as a touch event
NexPage KeyPad = NexPage(14, 0, "Keypad");  // Page added as a touch event
NexPage Info = NexPage(15, 0, "Info");  // Page added as a touch event
NexPage conf_Sun_track = NexPage(16, 0, "conf_Sun_track");  // Page added as a touch event

// Declare Objects per page

// Boot Page Components
NexText ver_data = NexText(0, 29, "ver_data");
NexText T_initialize = NexText(0, 7, "T_initialize");
NexText DHT_initialize = NexText(0, 8, "DHT_initialize");
NexText RTC_initialize = NexText(0, 9, "RTC_initialize");
NexText SD_initialize = NexText(0, 10, "SD_initialize");
NexText Mes_initialize = NexText(0, 13, "Mes_initialize");
NexText tre_initialize = NexText(0, 14, "tre_initialize");
NexText cus_CSV_load = NexText(0, 15, "cus_CSV_load");
NexText cus_opt_load = NexText(0, 33, "cus_opt_load");
NexText BL_initialize = NexText(0, 11, "BL_initialize");
NexText GPS_initialize = NexText(0, 12, "GPS_initialize");
NexText Joy_cal = NexText(0, 16, "Joy_cal");
NexText Joy_warn = NexText(0, 17, "Joy_warn");
NexText Joy_cal_3 = NexText(0, 27, "Joy_cal_3");
NexText Joy_cal_2 = NexText(0, 31, "Joy_cal_2");
NexText Joy_cal_1 = NexText(0, 32, "Joy_cal_1");
NexText Touch_OK = NexText(0, 18, "Touch_OK");
NexText DHT_OK = NexText(0, 19, "DHT_OK");
NexText RTC_OK = NexText(0, 20, "RTC_OK");
NexText SD_OK = NexText(0, 21, "SD_OK");
NexText Messier_OK = NexText(0, 24, "Messier_OK");
NexText Treasures_OK = NexText(0, 25, "Treasures_OK");
NexText CSV_OK = NexText(0, 26, "CSV_OK");
NexText Blue_OK = NexText(0, 22, "Blue_OK");
NexText GPS_OK = NexText(0, 23, "GPS_OK");
NexText Joy_cal_Done = NexText(0, 28, "Joy_cal_Done");
NexText cus_opt_OK = NexText(0, 34, "cus_opt_OK");

// GPS Page Components
NexCheckbox day_night = NexCheckbox(1, 8, "day_night");  // Button added
NexVariable night1 = NexVariable(1, 35, "night1");  // Variable added so we can read it
NexText LAT_val = NexText(1, 10, "LAT_val");
NexText LON_val = NexText(1, 11, "LON_val");
NexText ALT_val = NexText(1, 12, "ALT_val");
NexText SAT_val = NexText(1, 13, "SAT_val");
NexText GMT_val = NexText(1, 14, "GMT_val");
NexText coord_ass_text = NexText(1, 7, "coord_ass_text");
NexButton skip = NexButton(1, 1, "skip");

// Time Page Components
NexButton save_button = NexButton(2, 23, "save_button");
NexNumber hour_set = NexNumber(2, 1, "hour_set");
NexNumber minute_set = NexNumber(2, 2, "minute_set");
NexNumber second_set = NexNumber(2, 3, "second_set");
NexNumber day_set = NexNumber(2, 4, "day_set");
NexNumber month_set = NexNumber(2, 5, "month_set");
NexNumber year_set = NexNumber(2, 6, "year_set");
NexDSButton btdst = NexDSButton(2, 28, "btdst");


// Autoguiding Page Components
NexButton Guiding_back = NexButton(12, 2, "Guiding_back");
NexText Guiding_HA = NexText(12, 11, "Guiding_HA");
NexText Guiding_RA = NexText(12, 12, "Guiding_RA");
NexText Guiding_DEC = NexText(12, 13, "Guiding_DEC");
NexWaveform Guiding_Graph = NexWaveform(12, 4, "Guiding_Graph");
NexGauge RA_Gauge = NexGauge(12, 5, "RA_Gauge");
NexGauge DEC_Gauge = NexGauge(12, 6, "DEC_Gauge");
NexGauge FOC_Gauge = NexGauge(12, 7, "FOC_Gauge");
NexTimer RA_tim1 = NexTimer(12, 14, "RA_tim1");
NexTimer RA_tim2 = NexTimer(12, 15, "RA_tim2");
NexTimer DEC_tim1 = NexTimer(12, 16, "DEC_tim1");
NexTimer DEC_tim2 = NexTimer(12, 17, "DEC_tim2");
NexText Guide_message = NexText(12, 22, "Guide_message");

// Confirm Sun Tracking Page Components
NexButton sun_track_yes = NexButton(16, 5, "sun_track_yes");
NexButton sun_track_no = NexButton(16, 6, "sun_track_no");

// Alignment Page Components
NexButton align1Star = NexButton(3, 1, "align1Star");
NexButton iterativeAlign = NexButton(3, 2, "iterativeAlign");
NexButton skip_align = NexButton(3, 3, "skip_align");

//  Manual Align Page Objects
NexText Del_Ra_val = NexText(5, 5, "Del_Ra_val");
NexText Del_Dec_val = NexText(5, 6, "Del_Dec_val");
NexText Selected_obj = NexText(5, 8, "Selected_obj");
NexButton sync_align = NexButton(5, 2, "sync_align");
NexButton repeat_align = NexButton(5, 1, "repeat_align");
NexText MA_instruction = NexText(5, 9, "MA_instruction");

// Sync Page Components
NexButton sync_next = NexButton(4, 29, "sync_next");
NexButton sync_prev = NexButton(4, 28, "sync_prev");
NexButton sync_done = NexButton(4, 1, "sync_done");
NexVariable sync_page = NexVariable(4, 31, "sync_page"); // Stores Align Page Number
NexVariable alignT = NexVariable(4, 30, "alignT"); // Stores Align Type Value 1Star Alignment Type  or Iterative Alignment Type
NexText sync_obj_1 = NexText (4, 2, "sync_obj_1");
NexText sync_obj_2 = NexText (4, 3, "sync_obj_2");
NexText sync_obj_3 = NexText (4, 4, "sync_obj_3");
NexText sync_obj_4 = NexText (4, 5, "sync_obj_4");
NexText sync_obj_5 = NexText (4, 6, "sync_obj_5");
NexText sync_obj_6 = NexText (4, 7, "sync_obj_6");
NexText sync_obj_7 = NexText (4, 8, "sync_obj_7");
NexText sync_obj_8 = NexText (4, 9, "sync_obj_8");
NexText sync_obj_9 = NexText (4, 10, "sync_obj_9");
NexText sync_obj_10 = NexText (4, 11, "sync_obj_10");
NexText sync_obj_11 = NexText (4, 12, "sync_obj_11");
NexText sync_obj_12 = NexText (4, 13, "sync_obj_12");
NexText sync_obj_13 = NexText (4, 14, "sync_obj_13");
NexText sync_obj_14 = NexText (4, 15, "sync_obj_14");
NexText sync_obj_15 = NexText (4, 16, "sync_obj_15");
NexText sync_obj_16 = NexText (4, 17, "sync_obj_16");
NexText sync_obj_17 = NexText (4, 18, "sync_obj_17");
NexText sync_obj_18 = NexText (4, 19, "sync_obj_18");
NexText sync_obj_19 = NexText (4, 20, "sync_obj_19");
NexText sync_obj_20 = NexText (4, 21, "sync_obj_20");
NexText sync_obj_21 = NexText (4, 22, "sync_obj_21");
NexText sync_obj_22 = NexText (4, 23, "sync_obj_22");
NexText sync_obj_23 = NexText (4, 24, "sync_obj_23");
NexText sync_obj_24 = NexText (4, 25, "sync_obj_24");
NexText Sync_message = NexText (4, 32, "Sync_message");
int sync_object = 0;

// Main Page Text and Number Fields
NexNumber main_temp = NexNumber(6, 42, "main_temp");
NexNumber main_humidity = NexNumber(6, 44, "main_humidity");
NexText main_obj_name = NexText(6, 37, "main_obj_name");
NexText main_obj_info = NexText(6, 39, "main_obj_info");
NexText obj_full_name = NexText(6, 62, "obj_full_name");
NexText main_RA = NexText(6, 58, "main_RA");
NexNumber main_LST1 = NexNumber(6, 46, "main_LST1");
NexNumber main_LST2 = NexNumber(6, 47, "main_LST2");
NexText main_LAT = NexText(6, 49, "main_LAT");
NexText main_LONG = NexText(6, 50, "main_LONG");
NexText main_ALT = NexText(6, 51, "main_ALT");
NexTimer tm1 = NexTimer(6, 33, "tm1");
NexTimer tm2 = NexTimer(6, 38, "tm2");
NexTimer tm3 = NexTimer(6, 64, "tm3");
NexText  t0 = NexText(6, 65, "t0");
NexPicture main_obj_image = NexPicture(6, 36, "main_obj_image");
NexText Main_message = NexText (6, 66, "Main_message");
NexProgressBar battery_power = NexProgressBar (6, 67, "battery_power");
NexText  batt_percent = NexText(6, 68, "batt_percent");
NexVariable va_batt = NexVariable(6, 73, "va_batt");
NexProgressBar focus_bar = NexProgressBar (6, 74, "focus_bar");
NexNumber focus_val = NexNumber(6, 76, "focus_val");

//  Main Page Touch Objects
NexButton main_Load = NexButton(6, 41, "main_Load");
NexButton main_home = NexButton(6, 35, "main_home");
NexButton main_track = NexButton(6, 31, "main_track");
NexButton main_BT = NexButton(6, 32, "main_BT");
NexButton main_menu = NexButton(6, 6, "main_menu");

//  Menu Page Objects
NexButton men_Options = NexButton(7, 2, "men_Options");
NexButton men_Load = NexButton(7, 3, "men_Load");
NexButton men_Coord = NexButton(7, 4, "men_Coord");
NexButton men_Log = NexButton(7, 5, "men_Log");
NexButton men_guiding = NexButton(7, 7, "men_guiding");
NexButton men_back = NexButton(7, 1, "men_back");

//  Options Page Objects
NexButton opt_save = NexButton(9, 5, "opt_save");
NexButton optClock_align = NexButton(9, 19, "optClock_align");
NexDSButton opt_steppers = NexDSButton(9, 14, "opt_steppers");
NexDSButton opt_sound = NexDSButton(9, 16, "opt_sound");
NexDSButton opt_fan1 = NexDSButton(9, 15, "opt_fan1");
NexDSButton opt_fan2 = NexDSButton(9, 17, "opt_fan2");
NexDSButton opt_F_motor = NexDSButton(9, 18, "opt_F_motor");
NexDSButton opt_mer_auto = NexDSButton(9, 33, "opt_mer_auto");
NexDSButton opt_mer_off = NexDSButton(9, 34, "opt_mer_off");
NexDSButton opt_celestial = NexDSButton(9, 20, "opt_celestial");
NexDSButton opt_solar = NexDSButton(9, 22, "opt_solar");
NexDSButton opt_lunar = NexDSButton(9, 21, "opt_lunar");

//  Load Page Objects
NexDSButton load_messier = NexDSButton(8, 4, "load_messier");
NexDSButton load_treasures = NexDSButton(8, 5, "load_treasures");
NexDSButton load_solar_sys = NexDSButton(8, 6, "load_solar_sys");
NexDSButton load_cust_csv = NexDSButton(8, 7, "load_cust_csv");
NexButton load_back = NexButton(8, 3, "load_back");
NexButton load_next = NexButton(8, 2, "load_next");
NexButton load_prev = NexButton(8, 1, "load_prev");
NexVariable Load_button = NexVariable(8, 48, "Load_button");
NexButton load_obj_1 = NexButton(8, 8, "load_obj_1");
NexButton load_obj_2 = NexButton(8, 9, "load_obj_2");
NexButton load_obj_3 = NexButton(8, 10, "load_obj_3");
NexButton load_obj_4 = NexButton(8, 11, "load_obj_4");
NexButton load_obj_5 = NexButton(8, 12, "load_obj_5");
NexButton load_obj_6 = NexButton(8, 13, "load_obj_6");
NexButton load_obj_7 = NexButton(8, 14, "load_obj_7");
NexButton load_obj_8 = NexButton(8, 15, "load_obj_8");
NexButton load_obj_9 = NexButton(8, 16, "load_obj_9");
NexButton load_obj_10 = NexButton(8, 17, "load_obj_10");
NexButton load_obj_11 = NexButton(8, 18, "load_obj_11");
NexButton load_obj_12 = NexButton(8, 19, "load_obj_12");
NexButton load_obj_13 = NexButton(8, 20, "load_obj_13");
NexButton load_obj_14 = NexButton(8, 21, "load_obj_14");
NexButton load_obj_15 = NexButton(8, 22, "load_obj_15");
NexButton load_obj_16 = NexButton(8, 23, "load_obj_16");
NexButton load_obj_17 = NexButton(8, 24, "load_obj_17");
NexButton load_obj_18 = NexButton(8, 25, "load_obj_18");
NexButton load_obj_19 = NexButton(8, 26, "load_obj_19");
NexButton load_obj_20 = NexButton(8, 27, "load_obj_20");
NexButton load_obj_21 = NexButton(8, 28, "load_obj_21");
NexButton load_obj_22 = NexButton(8, 29, "load_obj_22");
NexButton load_obj_23 = NexButton(8, 30, "load_obj_23");
NexButton load_obj_24 = NexButton(8, 31, "load_obj_24");
NexButton load_obj_25 = NexButton(8, 32, "load_obj_25");
NexButton load_obj_26 = NexButton(8, 33, "load_obj_26");
NexButton load_obj_27 = NexButton(8, 34, "load_obj_27");
NexButton load_obj_28 = NexButton(8, 35, "load_obj_28");
NexButton load_obj_29 = NexButton(8, 36, "load_obj_29");
NexButton load_obj_30 = NexButton(8, 37, "load_obj_30");
NexButton load_obj_31 = NexButton(8, 38, "load_obj_31");
NexButton load_obj_32 = NexButton(8, 39, "load_obj_32");
NexButton load_obj_33 = NexButton(8, 40, "load_obj_33");
NexButton load_obj_34 = NexButton(8, 41, "load_obj_34");
NexButton load_obj_35 = NexButton(8, 42, "load_obj_35");
NexText Load_message = NexText (8, 45, "Load_message");
int selected_object;
bool is_btn_pressed = false;

//  Coordinates Page Objects
NexText coord_HA = NexText(10, 3, "coord_HA");
NexText coord_RA = NexText(10, 4, "coord_RA");
NexText coord_DEC = NexText(10, 5, "coord_DEC");
NexButton coord_back = NexButton(10, 1, "coord_back");

//  info page objects
NexText info_hw_ver = NexText(15, 2, "info_hw_ver");
NexText info_fw_date = NexText(15, 4, "info_fw_date");
NexText info_fw_ver = NexText(15, 3, "info_fw_ver");

//  Stat page objects
NexText stat_date = NexText(11, 29, "stat_date");
NexText stat_st_time = NexText(11, 30, "stat_st_time");
NexText stat_rep_time = NexText(11, 31, "stat_rep_time");
NexText stat_LAT = NexText(11, 6, "stat_LAT");
NexText stat_LONG = NexText(11, 7, "stat_LONG");
NexText stat_ALT = NexText(11, 8, "stat_ALT");
NexText stat_obs_per = NexText(11, 4, "stat_obs_per");
NexText stat_obs_start = NexText(11, 5, "stat_obs_start");
NexText stat_temp = NexText(11, 32, "stat_temp");
NexText stat_humidity = NexText(11, 33, "stat_humidity");
NexNumber stat_obj_count = NexNumber(11, 9, "stat_obj_count");
NexButton stat_back = NexButton(11, 1, "stat_back");

/////////////////////// Touch Items per page/////////////////////////////////
// Declare touch event objects to the touch event list:
// You just need to add the names of the objects that send a touch event.
// Format: &<object name>,

NexTouch *nex_listen_list[] =
{
  // GPS Page Touch Objects
  &coord_ass_text,
  &skip,

  // Time Page Components
  &save_button,
  &btdst,

  // STAT Page Components
  &stat_back,

  // Coordinates Page Components
  &coord_back,

  // Autoguiding Page Components
  &Guiding_back,

  // Confirm Sun Tracking Page Components
  &sun_track_yes,
  &sun_track_no,

  // Align Page Components
  &align1Star,
  &iterativeAlign,
  &skip_align,

  // Manual Align Page Components
  &sync_align,
  &repeat_align,

  // Sync Page Components
  &sync_next,
  &sync_prev,
  &sync_done,
  &sync_obj_1,
  &sync_obj_2,
  &sync_obj_3,
  &sync_obj_4,
  &sync_obj_5,
  &sync_obj_6,
  &sync_obj_7,
  &sync_obj_8,
  &sync_obj_9,
  &sync_obj_10,
  &sync_obj_11,
  &sync_obj_12,
  &sync_obj_13,
  &sync_obj_14,
  &sync_obj_15,
  &sync_obj_16,
  &sync_obj_17,
  &sync_obj_18,
  &sync_obj_19,
  &sync_obj_20,
  &sync_obj_21,
  &sync_obj_22,
  &sync_obj_23,
  &sync_obj_24,

  // Main Page Touch Objects
  &main_Load, // Home Button added as a touch button
  &main_home,
  &main_track,
  &main_BT,
  &main_menu,

  // Options Page Objects
  &opt_save,
  &opt_steppers,
  &opt_sound,
  &opt_fan1,
  &opt_fan2,
  &opt_F_motor,
  &opt_mer_auto,
  &opt_mer_off,
  &opt_celestial,
  &opt_solar,
  &opt_lunar,
  &optClock_align,

  // Load Page Touch Objects
  &load_messier,
  &load_treasures,
  &load_solar_sys,
  &load_cust_csv,
  &load_back,
  &load_next,
  &load_prev,
  &load_obj_1,
  &load_obj_2,
  &load_obj_3,
  &load_obj_4,
  &load_obj_5,
  &load_obj_6,
  &load_obj_7,
  &load_obj_8,
  &load_obj_9,
  &load_obj_10,
  &load_obj_11,
  &load_obj_12,
  &load_obj_13,
  &load_obj_14,
  &load_obj_15,
  &load_obj_16,
  &load_obj_17,
  &load_obj_18,
  &load_obj_19,
  &load_obj_20,
  &load_obj_21,
  &load_obj_22,
  &load_obj_23,
  &load_obj_24,
  &load_obj_25,
  &load_obj_26,
  &load_obj_27,
  &load_obj_28,
  &load_obj_29,
  &load_obj_30,
  &load_obj_31,
  &load_obj_32,
  &load_obj_33,
  &load_obj_34,
  &load_obj_35,

  // Menu Page Objects
  &men_Options,
  &men_Load,
  &men_Coord,
  &men_Log,
  &men_guiding,
  &men_back,
  NULL  // String terminated
};  // End of touch event list

//-------------End of Nextion Setup ---------------------------------//


void setup(void) {
#ifdef serial_debug
  Serial.begin(57600);
  while (!Serial) {}
#endif

  //----------------------------- Nextion Setup -------------------------------------//

  Serial1.begin(115200);  // Start serial comunication With Nextion at baud=115200
  nex_attach_pages();
  ///////////////////////////// End Of Nextion Setup //////////////

  Serial2.begin(9600);  // Initialize GPS communication on PINs: 17 (RX) and 16 (TX)
  Serial3.begin(9600); // Bluetooth communication on PINs:  15 (RX) and 14 (TX) // 9600 with HC05  19200 With ESP32 WIFI/BT Bridge
  pinMode(speakerOut, OUTPUT);

  // below variables are used to calculate the paramters where the drive works
  int ww = WORM * REDUCTOR;
  int www = DRIVE_STP * MICROSteps;

  MicroSteps_360 = ww * www;
  RA_90 = MicroSteps_360 / 4;  // How much in microSteps the RA motor have to turn in order to make 6h = 90 degrees;
  DEC_90 = RA_90;   // How mich in microSteps the DEC motor have to turn in order to make 6h = 90 degrees;
  HA_H_CONST = MicroSteps_360 / 360;
  DEC_D_CONST = HA_H_CONST;

  Clock_Sidereal = 1000000 / (MicroSteps_360 / SIDEREAL_DAY); // This way I make the interruption occuer 2wice faster than needed - REASON: allow max time for Pin-UP, Pin-DOWN action
  Clock_Solar = 1000000 / (MicroSteps_360 / (SIDEREAL_DAY - 235.9095));
  Clock_Lunar = 1000000 / (MicroSteps_360 / (SIDEREAL_DAY - 2089.2292));

#ifdef serial_debug
  Serial.print("Clock_Sidereal = ");
  Serial.println(Clock_Sidereal, 6);
#endif

  rtc.begin();
  dht.begin();

  // DRB8825 - drive mode pins (determine Steppping Modes 1/8, 1/16 and etc.
  pinMode(RA_EN, OUTPUT);
  digitalWrite(RA_EN, HIGH);// Turn Off RA Motor at startup
  pinMode(RA_STP, OUTPUT); // RA Step
  pinMode(RA_DIR, OUTPUT); // RA Dir
  pinMode(RA_MODE0, OUTPUT);
  pinMode(RA_MODE1, OUTPUT);
  pinMode(RA_MODE2, OUTPUT);

  pinMode(DEC_EN, OUTPUT);
  digitalWrite(DEC_EN, HIGH);// Turn Off DEC Motor at startup
  pinMode(DEC_STP, OUTPUT); // DEC Step
  pinMode(DEC_DIR, OUTPUT); // DEC Dir
  pinMode(DEC_MODE0, OUTPUT);
  pinMode(DEC_MODE1, OUTPUT);
  pinMode(DEC_MODE2, OUTPUT);

  //digitalWrite(RA_DIR,HIGH); // Set Dir high
  //digitalWrite(RA_STP,LOW);
  //digitalWrite(DEC_DIR,HIGH); // Set Dir high
  //digitalWrite(DEC_STP,LOW);

  // Joystick
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  // Device 1 & 2 command Pins
  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);

  /////////////// Auto Guiding Pins Setup //////////////////
  pinMode (RA_PlusPin, INPUT);
  pinMode (RA_MinusPin, INPUT);
  pinMode (DEC_PlusPin, INPUT);
  pinMode (DEC_MinusPin, INPUT);
  pinMode (Guiding_Sense, INPUT);
  ///////////////// Focus Motor Setup ///////////////////////
  pinMode (encoderCLK, INPUT);
  pinMode (encoderDT, INPUT);
  pinMode(encoderSW, INPUT);
  pinMode(Focus_EN, OUTPUT);
  digitalWrite(Focus_EN, HIGH); // Turn Off Focus Motor at startup
  pinMode(focus_dir_pin, OUTPUT);
  pinMode(focus_step_pin, OUTPUT);
  digitalWrite(encoderSW, HIGH); // Pull-Up resistor for switch

  // Set RA and DEC microstep position
  RA_microSteps = RA_90; //  --> point to North Sudereal Pole = -180 deg (-12h)
  DEC_microSteps = 0; //  --> Point to North Sudereal Pole = 90 deg

  Timer3.attachInterrupt(Sidereal_rate);
  //  Timer3.start(Clock_Sidereal); // executes the code every 62.329 ms.

  ///////////////////////////////////////////// Day/Night Mode Setup ////////////////////////////////////
  if (analogRead(DAY_NIGHT_PIN) < 800)
  {
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
    // Nextion Day mode
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

  //////////////////////////////////////////// System Boot-up //////////////////////////////////////

  // Draw initial screen - INITIALIZE
  // The below part cannot be removed form the code
  // You can add messages, but not remove!
  Boot.show();                // Nextion Show Page Boot
  delay(1000);// Wait Until Nextion Initializes after power-on

  Serial1.print("ver_data.txt=");
  Serial1.print("\"");
  Serial1.print(FirmwareNumber);
  Serial1.print("\"");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  // see if the card is present and can be initialized:
  char in_char;
  String items = "";
  int j = 0;
  int k = 0;
  MESS_PAGER = 0;
  TREAS_PAGER = 0;
  STARS_PAGER = 0;
  CUSTOM_PAGER = 0;

  volatile bool check = true;
  T_initialize.setText("-> Initializing TouchScreen..."); // Nextion
  Touch_OK.setText("OK");

  DHT_initialize.setText("-> Initializing DHT Sensor...."); // Nextion

  if (isnan(dht.readTemperature()) || isnan(dht.readHumidity()))
  {
    DHT_OK.Set_font_color_pco(63488); // Change Font Color To RED
    DHT_OK.setText("Fail");
  }
  else
  {
    DHT_OK.setText("OK");  // Nextion
  }

  RTC_initialize.setText("-> Initializing RTC...........");// Nextion
  int prev_mil = millis();
  if (isnan(rtc.getTemp()))
  {
    RTC_OK.Set_font_color_pco(63488); // Change Font Color To RED
    RTC_OK.setText("Fail"); // Nextion
    check = false;
  }
  else
  {
    RTC_OK.setText("OK"); // Nextion
  }
  SD_initialize.setText("-> Initializing SD Card.......");  // Nextion

  for (int i = 0; i < 10 && !SD.begin(sd_cs); i++)
  {
    if (i == 9)
    {
      SD_OK.Set_font_color_pco(63488); // Change Font Color To RED
      SD_OK.setText("Fail"); // Nextion
      check = false;
    }
    delay(50);
  }
  //Debug or card initialized:
  SD_OK.setText("OK"); // Nextion
  //loadOptions_SD();
  //delay(100);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("messier.csv");

  // if the file is available, write to it:
  if (dataFile)
  {
    Mes_initialize.setText("-> Loading Messier Catalog...."); // Nextion
    delay(100);
    while (dataFile.available())
    {
      in_char = dataFile.read();
      items += in_char;
      k = k + 1;
      if (in_char == '\n') {
        Messier_Array[j] = items;
        j = j + 1;
        //          Serial.print(items);
        items = "";
      }
    }
    Messier_OK.setText("OK");  // Nextion
    delay(100);
  }
  else
  {
    Messier_OK.Set_font_color_pco(63488); // Change Font Color To RED
    Messier_OK.setText("Fail");  // Nextion
  }

  dataFile.close();
  items = "";
  j = 0;
  k = 0;
  dataFile = SD.open("treasure.csv");


  // if the file is available, write to it:
  if (dataFile)
  {
    tre_initialize.setText("-> Loading Treasures Catalog.."); // Nextion
    delay(100);
    while (dataFile.available()) {
      in_char = dataFile.read();
      items += in_char;
      k = k + 1;
      if (in_char == '\n') {
        Treasure_Array[j] = items;
        j = j + 1;
        //          Serial.print(items);
        items = "";
      }
    }
    Treasures_OK.setText("OK");  // Nextion
    delay(100);
  }
  else
  {
    Treasures_OK.Set_font_color_pco(63488); // Change Font Color To RED
    Treasures_OK.setText("Fail");  // Nextion
  }
  dataFile.close();
  last_button = 0;
  LOAD_SELECTOR = 0;
  /////////////////////////////////////////////////////////////////////

  items = "";
  j = 0;
  k = 0;
  dataFile = SD.open("custom.csv");
  // if the file is available, write to it:
  if (dataFile)
  {
    cus_CSV_load.setText("-> loading custom.CSV........."); // Nextion
    delay(100);
    while (dataFile.available())
    {
      in_char = dataFile.read();
      items += in_char;
      k = k + 1;
      if (in_char == '\n')
      {
        custom_Array[j] = items;
        j = j + 1;
        //          Serial.print(items);
        items = "";
      }
    }
    CSV_OK.setText("OK"); // Nextion
    delay(100);
  }
  else
  {
    CSV_OK.Set_font_color_pco(63488); // Change Font Color To RED
    CSV_OK.setText("Fail"); // Nextion
    //check = false;
  }
  dataFile.close();
  last_button = 0;
  LOAD_SELECTOR = 0;

  ////////////////////////////////////////////////////////////////
  cus_opt_load.setText("-> Loading Custom Options.....");
  if (SD.exists("options.txt"))
  {
    loadOptions_SD();
    cus_opt_OK.setText("OK"); // Nextion
  }
  else
  {
    cus_opt_OK.Set_font_color_pco(63488); // Change Font Color To RED
    cus_opt_OK.setText("Fail"); // Nextion
  }
  BL_initialize.setText("-> Initializing Bluetooth....."); // Nextion
  delay(300);
  Blue_OK.setText("OK"); // Nextion
  delay(100);
  GPS_initialize.setText("-> Initializing GPS..........."); // Nextion
  delay(300);
  GPS_OK.setText("OK"); // Nextion

#ifndef serial_debug
  if (check == false)  while (1); //don't do anything more
#endif

  Joy_cal.setText("-> Calibrating Joystick.......");
  calibrateJoypad(&x_cal, &y_cal);

  // Draw Supporters Logos

  // EMPIRIAL MARCH - if sounds everything was initialized well   :)
  if (IS_SOUND_ON)
  {
    SoundOn(note_f, 48);
    delay(100);
    SoundOn(note_f, 48);
    delay(100);
    SoundOn(note_f, 48);
    delay(100);
    SoundOn(note_cb, 32);
    delay(140);
    SoundOn(note_gb, 8);
    delay(50);
    SoundOn(note_f, 48);
    delay(100);
    SoundOn(note_cb, 32);
    delay(140);
    SoundOn(note_gb, 8);
    delay(50);
    SoundOn(note_f, 48);
  }
  delay(500);
  CURRENT_SCREEN = 0;
  drawGPSScreen();

  UPD_T = millis();
  UPD_LST = millis();
  DELAY_Slew = millis();
  RA_move_ending = 0;
  considerTempUpdates();

  // Turn Telescope Steppers ON at Startup by default to enable ALignment and Manual motor control
  digitalWrite(RA_EN, LOW);
  digitalWrite(DEC_EN, LOW);
  Stepper_State = "ON";
  IS_STEPPERS_ON = true;
  opt_steppers.setValue(1);
  Serial1.print("wepo 1,10");  // Change Steppers Button to ON in Options Screen and status bar.
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
  // Turn Off focus motor at startup to consume power.
  digitalWrite(Focus_EN, HIGH);
  Focus_Motor_State = "OFF";
  IS_FOCUS_ON = false;
  opt_F_motor.setValue(0);
  Serial1.print("wepo 0,130");  // Change Focus Motor Button to OFF in Options screen and status bar.
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
}


void loop(void) {

  // AutoGuiding control .... if Any!

  if (CURRENT_SCREEN == 11 && digitalRead (Guiding_Sense) == HIGH)
  {
    if (IS_CONNECTED == false)
    {
      OnScreenMsg(8);
      drawAutoGuidingScreen();
      IS_CONNECTED = true;
    }
    IS_TRACKING = false;
    IS_PulseGuiding = true;
    considerPulseGuiding();
  }
  else if (CURRENT_SCREEN == 4 && digitalRead (Guiding_Sense) == HIGH)
  {

    if (IS_CONNECTED == true)
    {
      Main_message.setText(" Connected     to        PHD2");
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
      Serial1.print("vis Main_message,0");
      Serial1.write(0xff);
      Serial1.write(0xff);
      Serial1.write(0xff);
      IS_CONNECTED = false;
    }
    drawAutoGuidingScreen();
    IS_TRACKING = false;
    IS_PulseGuiding = true;
    considerPulseGuiding();
  } else if (CURRENT_SCREEN == 11 && digitalRead (Guiding_Sense) == LOW && IS_CONNECTED == true && IS_PulseGuiding == true )
  {
    OnScreenMsg(9);
    drawAutoGuidingScreen();
    IS_PulseGuiding = false;
    IS_CONNECTED = false;
  }

  // Focus Motor Control .... if Any!
  if (IS_FOCUS_ON == true)
  {
    consider_focus_control();
  }

  /////////////// Nextion Loop //////////////////////
  nexLoop(nex_listen_list);  // Check for any touch event
  //////////////////// End of Nextion Loop /////////////////////////

  // This is done in order to prevent multiple calculations of LST_HA per second (especially while SlewTo) and only
  // do it once the DEC SlewTo slows down, but before stopping OR once every 10 seconds (in order to do the Meridian Flip)
  if (RA_move_ending == 1) {
    calculateLST_HA();
  }

  if ((IS_MERIDIAN_FLIP_AUTOMATIC) && ((UPD_LST + 10000) <= millis()) && (IS_OBJ_FOUND == true)) {
    calculateLST_HA();
    UPD_LST = millis();
  }

  // Adding this delay to SLOW DOWN the Arduino so that the motors can catch up!
  // The delay is only needed when in full speed.... otherways the CalculateLST_HA() takes over and
  // slows down the arduino enough. CalculateLST_HA() when slewing only fires when the motors slows down
  // after they are very close to the Object Position.
  if ((DELAY_Slew + 1 <= millis()) && (IS_OBJ_FOUND == false)) {

    // If you wonder how I get to this delay - 800 uS
    // When I optimised the code for speed, the main delay was coming from calculateLST_HA() which back then was calculated on every Loop();
    // Once I optimized it to only calculate when the SlewTo stops (to fine tune after DEC stops) it turned out that
    // the code is too fast and the motors only "screemed" but not rotating - due to the low voltage/current.
    // This variable depends on How You Limit the Current to your motors and the Voltage you use!
    // I use 12V and 1.6A (70% in full step = 1.10A) to drive my NEMA 17 SY42STH47-1684B Motors.
    // Please note that Potentiometer does not really give consistent results for current on every restart (it drifted between 1.12A - 0.9A).

    // HINT: you can try to play with the Current/Voltage that powers the motors to get faster speeds.
    if (IS_STEPPERS_ON) {
      cosiderSlewTo();
    } else {
      IS_OBJECT_RA_FOUND = true;
      IS_OBJECT_DEC_FOUND = true;
      IS_OBJ_FOUND = true;
      RA_move_ending = 0;
    }
    DELAY_Slew = millis();
    // delayMicroseconds(800);
  }

  // The below part of the code makes sure that the system does NOT process any other inputs while SlweingTo!
  // Since both motors need every STEP to come from Arduino board, it needs it's entire power to run the motors in fastest possible way
  // The fastes possible from this board in the current state of the software is approx 3 turns/sec (600 steps/sec)
  // IS_OBJ_FOUND == true --> Means that SLEW command have completed
  //
  if (IS_OBJ_FOUND == true)
  {
    // BLUETOOTH Considerations ? ... if any
    if ((IS_BT_MODE_ON == true) && (Serial3.available() > 0) && (IS_MANUAL_MOVE == false))
    {
      BT_COMMAND_STR = Serial3.readStringUntil('#'); // For Bluetooth Module Communication
      //BT_COMMAND_STR = Serial3.readString();        // If You'll use ESP32 WIFI/BT as a Communication bridge. WIFI & BT work, But I found it slower than HC05!
#ifdef serial_debug
      Serial.println(BT_COMMAND_STR);
#endif
      considerBTCommands();
    }

    // JOYSTICK Movements ? ... if any
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);

    if ((xPosition < x_cal - 100) || (xPosition > x_cal + 100) || (yPosition < y_cal - 100) || (yPosition > x_cal + 100))
    {
#ifdef serial_debug
      Serial.print("xPin = ");
      Serial.println(xPosition);
      Serial.print("yPin = ");
      Serial.println(yPosition);
#endif
      IS_MANUAL_MOVE = true;
      if (IS_STEPPERS_ON)
      {
        consider_Manual_Move(xPosition, yPosition);
      }
    }
    else
    {
      IS_MANUAL_MOVE = false;
    }


    // TOUCH SCREEN Inputs ? ... if any
    considerTouchInput();

    // OTHER UPDATES ?  ... if any
    // Happens every 2 seconds
    if (((millis() - UPD_T) > 2000) && (IS_MANUAL_MOVE == false))
    {
      calculateLST_HA();  // Make sure it Updates the LST! used on Main Screen and When Calculating current Coords.
      considerTimeUpdates();
      considerDayNightMode();
      considerTempUpdates();

      // I need to make sure the Drives are not moved to track the stars,
      // if Object is below horizon ALT < 0 - Stop tracking.
      if ((ALT <= 0) && (IS_TRACKING == true) && (IS_IN_OPERATION == true))
      {
        IS_TRACKING = false;
        Timer3.stop();
        tm1.disable(); // Nextion Tracking Animation Stop
        drawMainScreen();
      }
      UPD_T = millis();
    }
  }
}
