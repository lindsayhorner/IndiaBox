// India Box Sketch 1.0
// By Lindsay Horner 2013
// Uses the 'Cemetary Howler' Project's loop
// Uses Bill Porters MP3 Shield library http://www.billporter.info/2012/01/28/sparkfun-mp3-shield-arduino-library/

// libraries

    #include <SPI.h>
    #include <SdFat.h>
    #include <SdFatUtil.h> 
    #include <SFEMP3Shield.h>
    SFEMP3Shield MP3player;

  
// these are constants  
    int butPin = 5;                   // Button pin
    unsigned long playTime = 20000;   // Length of the tracks (20000=20 seconds)
    unsigned long pauseTime = 50;     // how long the pause will be after the track ends (10000=10 seconds)
    int readingInterval = 10;         // how often to look for button press
 
   
// variables 
    int rantrack = 0;                    // random number for track
    unsigned long currentMillis = 0;     // time variable to track running time: current time
    unsigned long startingMillis = 0;    // time variable to track running time: starting time
    byte result;                         // variable for mp3 player shield, can be used to debug
        
// set it up   
   void setup() { 
    pinMode(butPin, INPUT);
    digitalWrite(butPin, LOW);

  //give the sensor some time to calibrate
     pinMode(butPin, INPUT);                        // button becomes an input
      digitalWrite(butPin, LOW);                    // activate internal pull-up resistor
      result = MP3player.begin();                   // start mp3 player shield
      MP3player.SetVolume(30, 30);                  // set volume of the mp3 player ( 0 = loudest )
    }
    
// loop 
    void loop(){ 
      if (digitalRead(butPin)== HIGH) {               // if button press...
          randomSeed(millis());                       // more random seed for the random funct 
          rantrack = random(8);                       // random track number
          result = MP3player.playTrack(rantrack);     // play track                          
          playtime();                                 // call playtime function        
         MP3player.stopTrack();                       // stop track   
          delay(pauseTime);                           // wait...   
    }
      
      delay(readingInterval);                         
   }  

// figure out playtime
  void playtime() {
       startingMillis = millis();                                 // set both time counter
       currentMillis = millis();
      while ( currentMillis - startingMillis < playTime ) {      // while track plays, runs until playTime is reached
          currentMillis = millis();                               // set to actual time
          delay(40);                                              
       }      
   }
