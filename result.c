#include <OneButton.h>
#include<LiquidCrystal.h> // lcd library
#include <EEPROM.h> //EEPROM library
LiquidCrystal lcd(13,12,11,10,9,8); // lcd control and data lines
// button pin definitions
int result=5;
int total=7;
OneButton button1(A0,true);
OneButton button2(6,true);
int a=4;
int b=3;
int c=2;
int unlock=A1; 
int led3=A5;
int led4=A3;
int led5=A4;
int buzzer= A2;
 //temporary variables used in program
int v1;
int v2;
int v3;
int v;
boolean ag = false;
boolean bg = false;
boolean cg = false;
boolean clearg = false;
boolean unlockg = true;
boolean resultg = false;
boolean totalg = false;

void setup()
{
  v1=EEPROM.read(1);// v1 stores the vote count of party A
  v2=EEPROM.read(2); // v2 stores thevote count of party B
  v3=EEPROM.read(3); // v3 stores the vote count of party C
  pinMode(a,INPUT_PULLUP); // declaration of buttons as input
  pinMode(b,INPUT_PULLUP);
  pinMode(c,INPUT_PULLUP);
  pinMode(total,INPUT_PULLUP);
  pinMode(result,INPUT_PULLUP);
  pinMode(unlock,INPUT_PULLUP);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(buzzer,OUTPUT);

  button1.attachClick(singleclick1);   // link the function to be called on a singleclick event.
  button1.attachLongPressStop(longclick1);  // link the function to be called on a longpress event.

  button2.attachClick(singleclick2);
  button2.attachLongPressStop(longclick2);

  Serial.begin(9600);
  
  lcd.begin(16,2);
  lcd.print("Welcome to ");
  lcd.setCursor(0,1);
  lcd.print("Project 'EVM'");
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(5000);
  digitalWrite(led4,HIGH);
  lcd.clear();
  lcd.print("Voting Locked");
  lcd.setCursor(0,1);
  lcd.print("Contact Admin");
  }

void rpt ()
{
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("Voting Locked");
  lcd.setCursor(0,1);
  lcd.print("Contact Admin");
  digitalWrite(led4,HIGH);
  digitalWrite(led5,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(buzzer,LOW);
  
  }

  void lock() {
    ag = false;
    bg = false;
    cg = false;
  }

void loop(){
  button1.tick();        // check the status of the button
  delay(10);           // a short wait between checking the button

  button2.tick();
  delay(10); 
  
  if (ag == true){
  if(digitalRead(a)==LOW) // if party A button is pressed
  {
    v1=v1+1;
    EEPROM.write(1,v1);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("vote received...");
    digitalWrite(buzzer,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led5,LOW);
    delay(1000);
    rpt(); 
    lock();
    unlockg = true;
  }}
  
 if (unlockg == true) {
 if (digitalRead(unlock) == LOW){ // if unlock button is pressed
      lcd.clear();
      lcd.setCursor(0,0);
      digitalWrite(led4,LOW);
      digitalWrite(led5,HIGH);
      lcd.print("Voting Unlocked");
      delay(2500);
      lcd.clear();
      lcd.print("Please Vote");
      ag = true;
      bg = true;
      cg = true;
      }
 }

      if(bg == true){
  if(digitalRead(b)==LOW) // if party B button is pressed
  {
    v2=v2+1;
    EEPROM.write(2,v2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("vote received...");
    digitalWrite(buzzer,HIGH);
    digitalWrite(led5,LOW);
    digitalWrite(led3,HIGH);
    delay(1000);
    rpt();
    lock();
    unlockg = true;
  }}
 
  if(cg == true){
  if(digitalRead(c)==LOW) // if party C button is pressed
  {
    v3=v3+1;
    EEPROM.write(3,v3);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("vote received...");
    digitalWrite(buzzer,HIGH);
    digitalWrite(led5,LOW);
    digitalWrite(led3,HIGH);
    delay(1000);
    rpt();
    lock();
    unlockg = true;
  }}
  if(totalg == false){
  if (digitalRead(total)== LOW){ //if total button is pressed before close button
    v=v1+v2+v3;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Total votes ");
    lcd.setCursor(0,1);
    lcd.print("received: ");
    lcd.print(v);
    Serial.println("Total votes received: ");
    Serial.println(v);
    
    
    
    }}

    
    if (totalg == true) { 
    if (digitalRead(total)== LOW){ //if total button is pressed after close button
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A");
      lcd.setCursor(0,1);
      lcd.print(v1);
      lcd.setCursor(6,0);
      lcd.print("B");
      lcd.setCursor(6,1);
      lcd.print(v2);
      lcd.setCursor(12,0);
      lcd.print("C");
      lcd.setCursor(12,1);
      lcd.print(v3);
      resultg = true;
      Serial.println("Candidate A: ");
      Serial.println(v1);
      Serial.println("Candidate B: ");
      Serial.println(v2);
      Serial.println("Candidate C: ");
      Serial.println(v3);
    }}
     if (resultg == true){  //if result button is pressed after closed button
     if (digitalRead(result) == LOW){
      lcd.clear();
      lcd.print("Total Votes:");
      lcd.print(v);
     if(v1==v2 && v2==v3)
    {
     
      lcd.setCursor(0,1);
      lcd.print("Result Tied");
      Serial.println("Result Tied");
    }
   
    if(v1==v2 && v1>v3)
    {
      
      lcd.setCursor(0,1);
      lcd.print("Tie b/w A and B");
      Serial.println("Tie b/w A and B");
    }
   
    if(v2==v3 && v2>v1)
    {
     
      lcd.setCursor(0,1);
      lcd.print("Tie b/w B and C");
      Serial.println("Tie b/w B and C");
    }
    if(v1==v3 && v1>v2)
    {
      
      lcd.setCursor(0,1);
      lcd.print("Tie b/w A and C");
      Serial.println("Tie b/w A and C");
    }
   
    if(v1>v2)
    {
      if(v1>v3)
      {
        
        lcd.setCursor(0,1);
        lcd.print("Party A wins");
        Serial.println("Party A wins");
        
      }
      else if(v3>v1)
      {
       
        lcd.setCursor(0,1);
        lcd.print("Party C wins");
        Serial.println("Party C wins");
      }
    }
   
    else
    {
      if(v2>v3 && v1!=v2)
      {
        
        lcd.setCursor(0,1);
        lcd.print("Party B wins");
        Serial.println("Party B wins");
        
      }
      else if(v3>v2)
      {
        
        lcd.setCursor(0,1);
        lcd.print("Party C wins");
        Serial.println("Party C wins");
        
      }
       }
       
        }
     }
    
    if(resultg == false){  // when result button is pressed before close button 
      if (digitalRead(result) == LOW){
      lcd.clear();
      lcd.print("Sorry! voting is");
      lcd.setCursor(0,1);
      lcd.print("not closed yet.");
      }
     }
}

void singleclick1(){  // when memory clear button is pressed long
  lcd.clear();
  lcd.print("Long press to");
  lcd.setCursor(0,1);
  lcd.print("clear memory");
}

void longclick1(){          // when memory clear button is pressed long
    for (int i = 0; i < 512; i++)
    {
      EEPROM.write(i, 0);
    }
    v1=0;
    v2=0;
    v3=0;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Memory Cleared");
    Serial.println("Memory Cleared");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press unlock");
    lcd.setCursor(0,1);
    lcd.print("button.");
    lock();
    unlockg = true;
    resultg = false;
    totalg = false;
    digitalWrite(led4,HIGH); 
    digitalWrite(led5,LOW);
  }

  void singleclick2(){ // when close button is pressed once
      lcd.clear();
      lcd.setCursor(0,0);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      lcd.print("Voting Locked");
      lcd.setCursor(0,1);
      lcd.print("Contact Admin");
      lock();
      
  }

  void longclick2(){ // when close button is pressed long
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Voting is Closed.");
      Serial.println("Voting is Closed.");
      lock(); 
      resultg = true;
      unlockg = false;
      totalg = true;
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      }
