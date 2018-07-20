
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#define POT_PIN_TIME A0 // Input from TIME pot
#define POT_PIN_BEATSPERMINUTE A1 // Input from BEATSPERMINUTE pot

Adafruit_7segment displayTime = Adafruit_7segment();// Add time display
Adafruit_7segment displayBeatsPerMinute = Adafruit_7segment(); // Add BeatsPerMinute display
int buttonStartStop = 2; //Set pin 2 for Start/Stop button
int buttonAdultChild = 4; //Set pin 4 for Adult/Child button
int ledStartStop = 8; // Set pin 8 for Start/Stop button LED
int ledAdultChild = 12; //Set pin 12 for Adult/Child button LEDs

void setup() {

  pinMode(buttonStartStop,INPUT_PULLUP); //button is active low
  pinMode(buttonAdultChild,INPUT_PULLUP); //button is in Child mode when pressed (low); Adult mode when released (high).
  pinMode(ledStartStop,OUTPUT);
  pinMode(ledAdultChild,OUTPUT);
  
  Serial.begin(9600);
  displayTime.begin(0x70);
  displayBeatsPerMinute.begin(0x71);
}

void loop() {

  for (int x=0; x < 2; x++) {  //Loop to test button LEDs.  Turn them on and off sequentially.
      digitalWrite(ledStartStop, HIGH);
      Serial.println ("Start/Stop LED on");
      delay (200);
    
      digitalWrite(ledStartStop, LOW);
      Serial.println ("Start/Stop LED off");  
      Serial.println (); 
      delay (200); 
      
      digitalWrite(ledAdultChild, HIGH);
      Serial.println ("Adult/Child LED on"); 
      delay (200);
    
      digitalWrite(ledAdultChild, LOW);
      Serial.println ("Adult/Child LED off") ;
      Serial.println ();
      delay (200); 
  }
  
  delay (1000); //Hold after completion of for loop


    //Test the green Start/Stop button
   int buttonStartStopVal = 0;
   Serial.println ("Push the green Start/Stop button now") ;
   
   for (int x=0; x < 100; x++) { 
     	buttonStartStopVal = digitalRead(buttonStartStop);
  		buttonStartStopVal = !buttonStartStopVal; //Invert button state to make turn LED on when button is depressed

  		digitalWrite(ledStartStop, buttonStartStopVal); 
  		Serial.print ("Start/Stop button value is: ");
  		Serial.println (buttonStartStopVal);

	  }
	
	  buttonStartStopVal=0; //Turn off ledStartStop
  	digitalWrite(ledStartStop, buttonStartStopVal);
  	Serial.println (buttonStartStopVal);
	  delay (1000);

    //Test the yellow Adult/Child button 
	  int buttonAdultChildVal = 0; 
    Serial.println ("Repeatedly press the yellow Adult/Child button now") ;
	  for (int x=0; x < 100; x++) { 
  	
	  	buttonAdultChildVal = digitalRead(buttonAdultChild);
	  	buttonAdultChildVal = !buttonAdultChildVal; //Invert button state to make turn LED on when button is depressed
  	
	  	digitalWrite(ledAdultChild, buttonAdultChildVal);
	  	Serial.print ("Adult/Child button value is: ");
	  	Serial.println (buttonAdultChildVal);

    }
  
	  buttonAdultChildVal=0;
  	digitalWrite(ledAdultChild, buttonAdultChildVal);
  	Serial.println (buttonAdultChildVal); //Turn off ledAdultChild
	  delay (1000);

    //Check time pot and display.  Print to serial and time display
   Serial.println ("Rotate the Time pot now") ;
   for (int x=0; x < 100; x++) { 
	  	int timePotValue = analogRead(POT_PIN_TIME);
	  	Serial.print("Time pot value is: ");
	  	Serial.print(timePotValue);
	  	Serial.println(); 
	  	displayTime.print(timePotValue);
	  	displayTime.writeDisplay();
	  	delay(100);
   }
   delay(1000);

  //Check beatsPerMinute pot and display.  Print to serial and time display.
   Serial.println ("Slide the Beats Per Minute pot now") ;
   for (int x=0; x < 100; x++) { 

	  	int beatsPerMinutePotValue = analogRead(POT_PIN_BEATSPERMINUTE);
	  	Serial.print("Beats Per Minute pot value is: ");
	  	Serial.print(beatsPerMinutePotValue);
	  	Serial.println(); 
	  	displayBeatsPerMinute.print(beatsPerMinutePotValue);
	  	displayBeatsPerMinute.writeDisplay();
  	
	  	delay(100);
	}
	delay(10000);
}
