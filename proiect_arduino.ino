
const int trigPin1 = 11; // numărul pinului de ieșire  (senzorul 1)
const int echoPin1 = 10; // numărul pinului de intrare  (senzorul 1)    
const int trigPin2 = 6;  // numărul pinului de ieșire (senzorul 2)
const int echoPin2 = 5;  // numărul pinului de intrare (senzorul 2)

////////////////////////////////// variabile folosite pentru capculul distantei 
long duration;                               
int senzor1, senzor2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;
////////////////////////////////

void find_distance (void);

// această funcție returnează valoarea în cm.
// nu ar trebui să declanșăm ambii senzori ultrasonici în același timp. 
//ar putea provoca rezultatul unei erori datorită intrării ambelor unde sonore.
void find_distance (void)                   
{ 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH, 5000);// aici această funcție pulsein nu va aștepta mai mult de 5000u   s pentru ca sunetul ultrasonic să revină. (datorită acestui lucru nu va măsura mai mult de 60cm)
                                           // ajută acest proiect să utilizeze controlul gesturilor în spațiul definit. 
                                           // astfel încât, va reveni la zero dacă distanța e mai mare de 60m. (ajută de obicei dacă ne îndepărtăm mâinile din fața senzorilor).
 
  r = 3.4 * duration / 2;                  // calcul pentru a obține măsurarea în cm folosind timpul returnat de funcția pulsin.     
  senzor1 = r / 100.00;
  /////////////////////////////////////////partea superioară pentru senzorul stâng și partea inferioară pentru senzorul drept
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
  pinMode(trigPin1, OUTPUT); // inițializează pinii de declanșare și ecou ai senzorului ca intrare și ieșire:
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  delay (1000);
    
}

void loop()
{
  find_distance(); // această funcție va stoca distanța curentă măsurată de senzorul cu ultrasunete în variabila globală „distanță1 și distanță2”
                   // indiferent de ce, programul trebuie să numească continuu această funcție „find_distance” pentru a obține valoarea distanței în orice moment.
  
  if(senzor2<=30 && senzor2>=15) // o dată dacă ne-am așezat mâinile în fața senzorului potrivit în intervalul cuprins între 15 și 35cm această condiție devine adevărată.
  { 
    find_distance();             // stocați poziția curentă a mâinii noastre în variabila temp.   
    while(senzor2<=40 || senzor2==0)    // aceast while va rula până când ne scoatem mâna din fața senzorului dreapta.
    {
      find_distance();                      // apelați continuu această funcție pentru a obține datele live.
      if(senzor2>20 && senzor2<=35)                // această condiție devine adevărată dacă ne îndepărtăm mâna de senzorul potrivit (** dar în fața acestuia). aici "temp + 6" este pentru calibrare.
      {
      Serial.println("scrolldown/volumdown");            // trimite „jos”.
      delay (300);                          
      }
      else if(senzor2<10)           // această condiție devine adevărată dacă ne apropiem mâna de senzorul potrivit.
      {
      Serial.println("scrollup/volumup");           // trimite „sus” .
      delay (300);                          
      }
    }    
  }

  //Pause/Play
  if ( (senzor1>25 && senzor2>25) && (senzor1<50 && senzor2<50)) // actioneaza ambii senzori simutan.
  {
    Serial.println("Play/Pause");
    delay (500);
  }
   
  //Rewind/Forward
  //Lock Right - Control Mode
  if (senzor1>=10 && senzor1<=20)
  {
    //Hand Hold Time
    find_distance();
    if (senzor1>=10 && senzor1<=20)
    {
      Serial.println("Right Locked");
      while(senzor1<=40)
      {
        find_distance();
        if (senzor1<10 ) //Right hand pushed in
        {
          Serial.println ("Rewind"); 
          delay (300);
        }
        if (senzor1>20) //Right hand pulled out
        {
          Serial.println ("Forward"); 
          delay (300);
        }
      }
    }
  }

}