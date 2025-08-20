const int trigPin1 = 11; // output pin number (sensor 1)
const int echoPin1 = 10; // input pin number (sensor 1)    
const int trigPin2 = 6;  // output pin number (sensor 2)
const int echoPin2 = 5;  // input pin number (sensor 2)

////////////////////////////////// variables used for distance calculation 
long duration;                               
int senzor1, senzor2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;
////////////////////////////////

void find_distance (void);

// this function returns the value in cm.
// we should not trigger both ultrasonic sensors at the same time. 
// it could cause errors due to interference between both sound waves.
void find_distance (void)                   
{ 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH, 5000); // here, pulseIn will not wait more than 5000us for the ultrasonic wave to return 
                                            // (because of this it won’t measure more than 60cm).
                                            // this helps the project use gesture control within a defined space. 
                                            // it will return zero if the distance is greater than 60cm 
                                            // (useful if we move our hands away from the sensors).
 
  r = 3.4 * duration / 2;                   // calculation to get the measurement in cm using the time returned by pulseIn.     
  senzor1 = r / 100.00;
  /////////////////////////////////////////upper part for the left sensor and lower part for the right sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin2, LOW);

  duration = pulseIn(echoPin2, HIGH, 5000);
  r = 3.4 * duration / 2;     
  senzor2 = r / 100.00;
  delay(100);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT); // initialize the trigger and echo pins of the sensor as input and output:
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  delay (1000);
    
}

void loop()
{
  find_distance(); // this function will store the current distance measured by the ultrasonic sensor 
                   // in the global variables “senzor1” and “senzor2”.
                   // regardless of what happens, the program must continuously call this function 
                   // to get the distance values in real-time.
  
  if(senzor2<=30 && senzor2>=15) // once we place our hand in front of the right sensor between 15 and 30 cm, this condition becomes true.
  { 
    find_distance();             // store the current hand position in variable temp.   
    while(senzor2<=40 || senzor2==0)    // this while loop will run until we remove the hand from the right sensor.
    {
      find_distance();                      // continuously call this function to get live data.
      if(senzor2>20 && senzor2<=35)         // this condition becomes true if we move the hand away from the right sensor 
                                            // (but still in front of it). here "temp + 6" is for calibration.
      {
        Serial.println("scrolldown/volumdown");   // send “down”.
        delay (300);                          
      }
      else if(senzor2<10)           // this condition becomes true if we move the hand closer to the right sensor.
      {
        Serial.println("scrollup/volumup");       // send “up”.
        delay (300);                          
      }
    }    
  }

  // Pause/Play
  if ( (senzor1>25 && senzor2>25) && (senzor1<50 && senzor2<50)) // activates when both sensors are triggered simultaneously.
  {
    Serial.println("Play/Pause");
    delay (500);
  }
   
  // Rewind/Forward
  // Lock Right - Control Mode
  if (senzor1>=10 && senzor1<=20)
  {
    // Hand Hold Time
    find_distance();
    if (senzor1>=10 && senzor1<=20)
    {
      Serial.println("Right Locked");
      while(senzor1<=40)
      {
        find_distance();
        if (senzor1<10 ) // Right hand pushed in
        {
          Serial.println ("Rewind"); 
          delay (300);
        }
        if (senzor1>20) // Right hand pulled out
        {
          Serial.println ("Forward"); 
          delay (300);
        }
      }
    }
  }

}
