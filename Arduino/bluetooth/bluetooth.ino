


char command;

String string;

void setup()
{
//Serial.begin(9600); //pc
Serial.begin(9600); //BT
}
void loop()
{
 
    if (Serial.available() > 0) 
    {string = "";}
    
    while(Serial.available() > 0)
    {
      command = ((byte)Serial.read());
      
      if(command == ':')
      {
        break;
      }
      
      else
      {
        string += command;
      }
      
      delay(1);

      
    }


    Serial.println(string);
}  //end program

