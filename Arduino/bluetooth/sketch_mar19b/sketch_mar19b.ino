void setup()
{
Serial.begin(9600); //pc
Serial1.begin(9600); //BT
}

bool first = false;
void loop()
{
 char ser_char;

 // Are Data from PC available?
 //Take them and give them via BT
 if (Serial.available() >0)
    {
     Serial1.write(Serial.read());
    }

 //Are Data at BT available?
 if(Serial1.available() >0)
 {
   while (Serial1.available() >0)
     { 
      ser_char = Serial1.read();
      if(ser_char == 'P')
      Serial.println();
       //write them to PC via USB
       Serial.print(ser_char);
       delay(2);
       
    }
    first = true;
 }
 else if(first)
 {
  first = false;
  Serial.println();
  }
}  

