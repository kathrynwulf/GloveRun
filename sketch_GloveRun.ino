//Ground digital pins 9, 10, 11, and 12 to press the joystick
//buttons 0, 1, 2, and 3


//Step 1
//Upload the Code
//Step 2
// Go to the control panel- view devices and printers
//Step 3
//Right click on arduino leonardo (only after uploading code)
// Go to game controller settings
//Go to properties

//TaDa! It's buttons 1 through 12
/*
 * Buttons 1, 3, 5, and 7 are dedicated to the fingers (on/off)
 * Buttons 2, 4, 6, and 0 are only triggered when both the buttons are pressed down and the fingers are bent
 * Button 9 is at the top of the breadboard, closest to the input wire, then 12, 11, 12
 * Buttons 9, 10, 11, and 12 are for the buttons on the breadboard ^^sex
 * 12 buttons
 * 
 */

#include <Joystick.h>

Joystick_ Joystick;

boolean minSet = false;

int raw1 = 0;
int raw2 = 0;
int raw3 = 0;
int raw4 = 0;
int voltageIn = 5;

float voltageOut = 0;

float Ref1 = 10000;
float R2 = 0;

float Ref3 = 10000;
float R3 = 0;

float Ref4 = 0;
float R4 = 0;

//float R1_limit_min=0;float R2_limit_min=0;float R3_limit_min=0;float R4_limit_min=0;float R5_limit_min=0;
//float R1_limit_max=0;float R2_limit_max=0;float R3_limit_max=0;float R4_limit_max=0;float R5_limit_min=0;

void setup() {
  Serial.begin(9600);
  //Initialize button pins
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  //Initialize Joystick Library
  Joystick.begin();

}

//Constant that maps the physical pin to the joystick button
const int pinToButtonMap = 9;

//Last state of the button
int lastResistorState[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; //12 buttons

void loop() {
  raw1 = analogRead(A0);
  raw2 = analogRead(A1);
  raw3 = analogRead(A2);
  raw4 = analogRead(A3);

  //Setup Check
  /*
   * if (digitalRead(9) == HIGH && digitalRead(10) == HIGH && digitalRead(11) == HIGH && digitalRead(12) == HIGH)
   * { 
   * Serial.println();
   * 
   * if (!minSet) {
   * Serial.println("Open Hand... Calculating Minimums...");
   *   delay(1000);
   * Serial.println("5");
   *  delay(1000);
   * Serial.println("4");
   *  delay(1000);
   * Serial.println("3");
   *   delay(1000);
   * Serial.println("2");
   *   delay(1000);
   * Serial.println("1");
   *   delay(1000);
   * 
   * if(raw1) //MINS
   * {
   *   buffer = raw1 * voltageIn;
   *   voltageOut = (buffer) / 1024.0;
   *   buffer = (voltageIn / voltageOut) -1;
   *   R1_limit_min = Ref1 * buffer;
   *   }
   *   if(raw2)
   *   {
   *    buffer = raw2 * voltageIn;
   *    voltageOut = (buffer) / 1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R2_limit_min = Ref2 * buffer;
   *    }
   *    if(raw3)
   *    {
   *    buffer = raw3 * voltageIn;
   *    voltageOut = (buffer) / 1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R3_limit_min = Ref3 * buffer;
   *    }
   *    if(raw4)
   *    {
   *    buffer = raw4 * voltageIn;
   *    voltageOut = (buffer) / 1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R4_limit_min = Ref4 * buffer;
   *    }
   *    Serial.println("Minimums Calibrated.");
   *    delay(1000);
   *    
   *    }
   *    
   *    if (minSet) {
   *    Serial.println("Close Hand... Calculating Maximums...");
   *      delay(1000);
   *    Serial.println("5");
   *      delay(1000); 
   *    Serial.println("4");
   *      delay(1000);
   *    Serial.println("3");
   *      delay(1000);
   *    Serial.println("2");
   *      delay(1000);
   *    Serial.println("1");
   *      delay(1000);
   *    
   *    if(raw1) //MAXES
   *    {
   *    buffer = raw1 * voltageIn;
   *    voltageOut = (buffer) / 1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R1_limit_max = Ref1 * buffer;
   *    }
   *    if(raw2)
   *    {
   *    buffer = raw2 * voltageIn;
   *    voltageOut = (buffer) /1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R2_limit_max = Ref2 * buffer;
   *    }
   *    if(raw3)
   *    {
   *    buffer = raw3 * voltageIn;
   *    voltageOut = (buffer) / 1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R3_limit_max = Ref3 * buffer;
   *    }
   *    if(raw4)
   *    {
   *    buffer = raw4 * voltageIn;
   *    voltageOut = (buffer)/1024.0;
   *    buffer = (voltageIn / voltageOut) -1;
   *    R4_limit_max = Ref4 * buffer;
   *    }
   *    
   *    Serial.println("Maximums Calibrated. Returning...");
   *    delay(500);
   *    minSet = false;
   *    }
   *        delay(2000);
   *      Serial.print("R1MxL = "); Serial.print(R1_limit_max); Serial.print(" R1MnL = "); Serial.println(R1_limit_min);
   *      Serial.print("R2MxL = "); Serial.print(R2_limit_max); Serial.print(" R2MnL = "); Serial.println(R2_limit_min);
   *      Serial.print("R3MxL = "); Serial.print(R3_limit_max); Serial.print(" R3MnL = "); Serial.println(R3_limit_min);
   *      Serial.print("R3MxL = "); Serial.print(R3_limit_max); Serial.print(" R3MnL = "); Serial.println(R4_limit_min);
   *      minSet = true;
   *      }
   * 
   */
   //End of Setup

   //Buttons (standalone)
   if(digitalRead(9) !=HIGH) { Joystick.setButton(8, false); } else { Joystick.setButton(8, true); };
   if(digitalRead(10) !=HIGH) { Joystick.setButton(9, false); } else { Joystick.setButton(9, true); };
   if(digitalRead(11) !=HIGH) { Joystick.setButton(10, false); } else { Joystick.setButton(10, true); };
   if(digitalRead(12) != HIGH) { Joystick.setButton(11, false); } else { Joystick.setButton(11, true); };

   if(raw1)
   {
    buffer = raw1 * voltageIn;
    voltageOut = (buffer) / 1024.0;
    buffer = (voltageIn / voltageOut) -1;
    R1 = Ref1 * buffer;
   }
   if(raw2)
   {
    buffer = raw2 * voltageIn;
    voltageOut = (buffer) / 1024.0;
    buffer = (voltageIn / voltageOut) -1;
    R2 = Ref2 * buffer;
   }
   if(raw3)
   {
    buffer = raw3 * voltageIn;
    voltageOut = (buffer) / 1024.0;
    buffer = (voltageIn / voltageOut) -1;
    R3 = Ref3 * buffer;
   }
   if(raw4)
   {
    buffer = raw4 * voltageIn;
    voltageOut = (buffer) / 1024.0;
    buffer = (voltageIn / voltageOut) -1;
    R4 = Ref4 * buffer;
   }

   if(R1 > 95000) {
    if(digitalRead(10) !=HIGH) {
      Joystick.setButton(2, true);
      Joystick.setButton(3, false);
    }
    else
    {
      Joystick.setButton(3, true);
      Joystick.setButton(2, false);
    }
    delay(10);
   } //middle
   else { Joystick.setButton(2, false); Joystick.setButton(3, false); }

   // ON OFF FUNCTIONALITY
   if(R2 > 130000) {
    if(digitalRead(9) !=HIGH) {
      Joystick.setButton(0, true);
      Joystick.setButton(1, false);
    }
    else
    {
      Joystick.setButton(1, true);
      Joystick.setButton(0, false);
    }
    delay(10);
   }
   //index
   else {Joystick.setButton(0, false); Joystick.setButton(1,false);}

   if(R3 > 400000) {
    if(digitalRead(11) != HIGH) {
      Joystick.setButton(4, true);
      Joystick.setButton(5, false);
    }
    else
    {
      Joystick.setButton(5, true);
      Joystick.setButton(4, false);
    }
    delay(10);
   }//ring
   else { Joystick.setbutton(4, false); Joystick.setButton(5, false); }

   if(R4 > 70000) {
    if(digitalRead(12) != HIGH) {
      Joystick.setButton(6, true);
      Joystick.setButton(7, false);
    }
    else
    {
      Joystick.setButton(7, true);
      Joystick.setButton(6, false);
    }
    delay(10)
   }//pinkie
   else {Joystick.setButton(6, false); Joystick.setButton(7, false); }
   /*
    * Read pin values
    * for (int index = 0; index < 8; index++)
    * {
    *   int curentButtonState = digitalRead(index + pinToButtonMap);
    *   if(currentButtonState != lastResistorState[index])
    *   {
    *   Joystick.setButton(index, currentButtonState);
    *   lastResistorState[index] = currentButtonState;
    *   }
    *   }
    */
    //Serial.println(R1); Serial.println(R2); Serial.println(R3); Serial.println(R4); Serial.println("");
    delay(35);
    //delay(1000);
}
