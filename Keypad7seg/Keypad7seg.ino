/*  A -- 6
    B -- 7
    C -- 8
    D -- 9
    E -- 10
    F -- 11
    G -- 12 */
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

char keys[ROWS][COLS] = { // Define the Keymap
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { A0, A1, A2, A3 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.

byte colPins[COLS] = { 2,3,4,5}; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// Create the Keypad

 


void setup()
{
  

   for(int i= 6;i<=12;i++)
   {
    pinMode(i,OUTPUT);
   }
   
  
  Serial.begin(9600);
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '1':
        digitalWrite(10,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(12,LOW);
        digitalWrite(9,LOW);
        digitalWrite(11,LOW);
        digitalWrite(8,HIGH);
        
        break;
      
      case '2':
        digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(8,LOW);
        
        Serial.println("2");
        break;
      case '3':
        digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(8,HIGH);
        Serial.println("3");
        break;
      case '4':
        digitalWrite(7,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(12,HIGH);
        digitalWrite(9,LOW);
        digitalWrite(11,HIGH);
        digitalWrite(10,LOW);
        digitalWrite(8,HIGH);
        Serial.println("4");
        break;
      case '5':
        digitalWrite(7,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(10,LOW);
        digitalWrite(8,HIGH);
        Serial.println("5");
        break;
      case '6':
        digitalWrite(7,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(8,HIGH);
        Serial.println("6");
        break;
    }
  }
}
