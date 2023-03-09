#include <Servo.h>
#include <rotary.h>
#include <RotaryEncoder.h>

Servo myservo;
Rotary r = Rotary(A1, A0, A2);
#define outputA A0
#define outputB A1
int counter = 0; 
int aState;
int aLastState;  
#define PIN_IN1 A1
#define PIN_IN2 A0
const int buzzer = A5;
int16_t last, value=0;
int aproapen = 0;
int catel=0,lastcatel=0;  //0 inchis 1 deschis
static int digits[] = {5,4,3,2};
int num1=0,num2=0,num3=0,num0=0;
static int clk = 10;
static int latch = 9;
static int data = 8;
int digitselect = 0;
int n = 0;
int passcode=0;
int safecodeparola=1000;

bool seinchide = 0;
bool sedeschide = 0;
int timpsunet = 0;

int fanta = 0;
int chiarfanta = 0;

int redledPin = 17;
int greenledPin = 18;

int lastred = 0;
int lastgreen = 0;
int lastbuttonpasscode = 0;
int lastbuttoncancel = 0;

int tongresit = 1000;
int toncorect = 2000;
static int tonreset = 500;

int david = 1;
int georgel = 0;

//6,7,12,13
int greenbuttonPin=6;
int redbuttonPin=7;
int buttonpasscodePin=12;
int buttoncancelPin=13;

void digit(int d, int n)
{  

    for (int i = 0; i<4; i++) digitalWrite(digits[i],LOW);
    digitalWrite(latch, LOW);
    shiftOut(data, clk, MSBFIRST, n);
    digitalWrite(latch,HIGH);
    digitalWrite(digits[d],HIGH);
    delay(1.5);

}

void locked()
{
  myservo.write(90);
}
void unlocked()
{
  myservo.write(180);
}

void setup() 
{
  Serial.begin(9600);
  myservo.attach(11);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(redledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  digitalWrite(redledPin,HIGH);
  digitalWrite(greenledPin, LOW);

  pinMode(greenbuttonPin, INPUT_PULLUP);
  pinMode(redbuttonPin, INPUT_PULLUP);
  pinMode(buttonpasscodePin, INPUT_PULLUP);
  pinMode(buttoncancelPin, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  pinMode (outputA,INPUT_PULLUP);
  pinMode (outputB,INPUT_PULLUP);
  aLastState = digitalRead(outputA);   
}

void loop() 
{
     aState = digitalRead(outputA);
     if (aState != aLastState)
     {     
       if (digitalRead(outputB) != aState) 
       { 
         fanta ++;
       } 
       else 
       {
         fanta --;
       }
       Serial.print("Position: ");
       Serial.println(aproapen);
     } 

   aLastState = aState; 
    aproapen += fanta - chiarfanta;
    chiarfanta = fanta;
    n = aproapen/4;
    if(aproapen>=40)
    {
      n=0;
      aproapen=0;
    }
    if(aproapen<=-2)
    {
      n=9;aproapen=38;
    }



  if(digitalRead(redbuttonPin) == LOW && lastred == 1)
  {
    if(david == 1)
    {
    locked();
    digitalWrite(greenledPin, LOW);
    digitalWrite(redledPin, HIGH);
    sedeschide = 0;
    seinchide = 1;
    timpsunet = 0;
    num0 = 0;
    num1 = 0;
    num2 = 0;
    num3 = 0;
    n=0;
    aproapen = 0;
    Serial.println("rosu");
    if(catel == 1)
    {
      tone(buzzer, tonreset);
      sedeschide = 1;
      seinchide = 0;
      timpsunet = 0;
    }
    catel = 0;
    }
    else
    {
      num0 = 0;
      num1 = 0;
      num2 = 0;
      num3 = 0;
      n=0;
      aproapen = 0;
    }
    digitselect = 0;
  }
  lastred = digitalRead(redbuttonPin);

  if(digitalRead(greenbuttonPin) == LOW && lastgreen == 1)
  {
    if(safecodeparola == passcode)
    {
      catel = 1;
    }
    if((safecodeparola == passcode) && (catel != lastcatel))
    {
      unlocked();
      digitalWrite(greenledPin, HIGH);
      digitalWrite(redledPin, LOW);
      catel = 1;
      tone(buzzer, toncorect);
      sedeschide = 1;
      seinchide = 0;
      timpsunet = 0;
      Serial.println("deblocat,corect");
    }
    else if(( safecodeparola != passcode )&&(catel == 0))
    {
      catel = 0;
      tone(buzzer, tongresit);
      sedeschide = 0;
      seinchide = 1;
      timpsunet = 0;
      Serial.println("gresit");
    }
    Serial.println("verde");
    if(david == 0)
    {
      safecodeparola = georgel;
      Serial.println(safecodeparola);
    }
    david = 1;
    switch(digitselect)
      {
        case 0:
        {
          n = num0;
          aproapen = n*4;
          break;
        }
        case 1:
        {
          n = num1;
          aproapen = n*4;
          break;
        }
        case 2:
        {
          n = num2;
          aproapen = n*4;
          break;
        }
        case 3:
        {
          n = num3;
          aproapen = n*4;
          break;
        }
      }

  }
  lastgreen = digitalRead(greenbuttonPin);


  if(digitalRead(buttonpasscodePin) == LOW && lastbuttonpasscode == 1)
  {
    if(catel == 1)
    {
      digitselect = 0;
      david = 0;
      num0 = safecodeparola/1000;
      num1 = safecodeparola/100%10;
      num2 = safecodeparola/10%10;
      num3 = safecodeparola%10;
      switch(digitselect)
      {
        case 0:
        {
          n = num0;
          aproapen = n*4;
          break;
        }
        case 1:
        {
          n = num1;
          aproapen = n*4;
          break;
        }
        case 2:
        {
          n = num2;
          aproapen = n*4;
          break;
        }
        case 3:
        {
          n = num3;
          aproapen = n*4;
          break;
        }
      }
    }
    Serial.println("passcode");
  }
  lastbuttonpasscode = digitalRead(buttonpasscodePin);


  if(digitalRead(buttoncancelPin) == LOW && lastbuttoncancel == 1)
  {
    num0 = 0;
    num1 = 0;
    num2 = 0;
    num3 = 0;
    n=0;
    aproapen = 0;
    if(catel == 1)
    {
      num0 = safecodeparola/1000;
      num1 = safecodeparola/100%10;
      num2 = safecodeparola/10%10;
      num3 = safecodeparola%10;
      switch(digitselect)
      {
        case 0:
        {
          n = num0;
          aproapen = n*4;
          break;
        }
        case 1:
        {
          n = num1;
          aproapen = n*4;
          break;
        }
        case 2:
        {
        
          n = num2;
          aproapen = n*4;
          break;
        }
        case 3:
        {
          n = num3;
          aproapen = n*4;
          break;
        }
      }
    }
    Serial.println("cancel");
    david = 1;
  }
  lastbuttoncancel = digitalRead(buttoncancelPin);



    if (r.buttonPressedReleased(200)) 
    {
      Serial.print("Button Pressed");
      if(digitselect<3)
        {
          digitselect++;
        }
      else digitselect = 0;
      Serial.println(digitselect);

      switch(digitselect)
      {
        case 0:
        {
          num3 = n;
          break;
        }
        case 1:
        {
          num0 = n;
          break;
        }
        case 2:
        {
          num1 = n;
          break;
        }
        case 3:
        {
          num2 = n;
          break;
        }

      }
      n=0;
      value=0;
      aproapen=0;

    }
    switch(digitselect)
    {
      case 0:
      {
        digit(0,n);
        digit(1,num1);
        digit(2,num2);
        digit(3,num3);
        num0=n;
        break;
      }
      case 1:
      {
        digit(0,num0);
        digit(1,n);
        digit(2,num2);
        digit(3,num3);
        num1=n;
        break;
      }
      case 2:
      {
        digit(0,num0);
        digit(1,num1);
        digit(2,n);
        digit(3,num3);
        num2=n;
        break;
      }
      case 3:
      {
        digit(0,num0);
        digit(1,num1);
        digit(2,num2);
        digit(3,n);
        num3=n;
        break;
      }
    }

    if(david == 1)
    {
    passcode=num0*1000+num1*100+num2*10+num3;
    }
    else
    {
      georgel=num0*1000+num1*100+num2*10+num3;
    }

    lastcatel = catel;


    if(sedeschide + seinchide != 0)
    {
      timpsunet++;
      if(timpsunet >50)
      {
        timpsunet = 0;
        sedeschide = 0;
        seinchide = 0;
        noTone(buzzer); 
      }
  
    }
    else
    {
      timpsunet = 0;
      sedeschide = 0;
      seinchide = 0;
      noTone(buzzer); 
    }

}