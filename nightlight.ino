//config

const int ledR = 9;
const int ledG = 6;
const int ledB = 5;
const int pBtn = 2;
const int ledW = 11;

//#define beepEnable;
//const int  beepPin = 11;


const long interval = 20;           // interval at which to blink (milliseconds)
const int  maxBright = 200;

// variables
int btnState = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned LedMode = 6;

//int ledState = 0; 
//int ledStateR = 0; 
//int ledStateG = 0; 
//int ledStateB = 0; 



int incrR = 1;
int incrG = 1;
int incrB = 1;


// Variables will change:
int lastButtonState = LOW;   // the previous reading from the input pin

int lPowerR = 30;
int lPowerG = 10;
int lPowerB = 50;



// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // put your setup code here, to run once:
pinMode (ledR, OUTPUT);
pinMode (ledG, OUTPUT);
pinMode (ledB, OUTPUT);
pinMode (ledW, OUTPUT);
pinMode (pBtn, INPUT_PULLUP);

ledset (LOW,LOW,LOW,HIGH);

}

void loop() {

  int reading = digitalRead(pBtn);
if (reading == HIGH) { reading = LOW; } else {reading = HIGH;}
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btnState) {
      btnState = reading;

      // only toggle the LED if the new button state is HIGH
      if (btnState == HIGH) {
          // кнопа нажата
        LedMode++;
        
        if (LedMode > 7) {LedMode=0;}
        
                                      #ifdef beepEnable
                                              {tone (beepPin,5000,50);}
                                      #endif
          if (LedMode<7) {
              switch (LedMode) {

                    case 0:  ledset (LOW,LOW,LOW,HIGH);
                      break;
                    case 1:  ledset (HIGH,LOW,LOW,HIGH);
                      break;
                    case 2:  ledset (LOW,HIGH,LOW,HIGH);
                      break;
                    case 3: ledset (LOW,LOW,HIGH,HIGH);
                      break;
                    case 4: ledset (HIGH,HIGH,LOW,HIGH);
                      break;
                    case 5: ledset (HIGH,LOW,HIGH,HIGH);
                      break;
                    case 6: ledset (LOW,HIGH,HIGH,HIGH);
                      break;
                    case 7: crazy();
                      break;                    
                    default:   ledset (LOW,LOW,LOW,LOW);
                      break;
                  }
            
                }
      
      
      
      }
    }
  }

if (LedMode == 7 ) {crazy();}





  
lastButtonState = reading;
}



void ledset (int RedL, int GreenL, int BlueL, int WhiteL)
{
          digitalWrite(ledR, RedL);
          digitalWrite(ledG, GreenL);
          digitalWrite(ledB, BlueL); 
          digitalWrite(ledW, WhiteL);
}

void moreRandom () 
{
  int a = random(1, 2000);
switch (a) {
    case 100:
          incrR=incrR - 2 * incrR;
          break;
    case 1000:
          incrG=incrG - 2 * incrG;
          break;
    case 1800:
          incrB=incrB - 2 * incrB;
          break;
    default:
    break;
}
  
  
}


void crazy()
{
  unsigned long currentMillis = millis();
          analogWrite(ledR, lPowerR);
          analogWrite(ledG, lPowerG);
          analogWrite(ledB, lPowerB);   

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
   lPowerR = lPowerR + incrR;
   if (lPowerR>maxBright or lPowerR<1) {incrR=incrR - 2 * incrR;}
          
 lPowerG = lPowerG + incrG;
   if (lPowerG>maxBright or lPowerG<1) {incrG=incrG - 2 * incrG;}

   lPowerB = lPowerB + incrB;
   if (lPowerB>maxBright or lPowerB<1) {incrB=incrB - 2 * incrB;}
  
 moreRandom();
  
  
  }







}


