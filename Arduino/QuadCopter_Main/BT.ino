

char command;

String string;

void BlueTooth()
{
  
 if(Serial.available() >0)
 {
 char myChar = Serial.read();
if(myChar == '1'){pid_p_gain_roll +=0.02;}
else if(myChar == '4'){pid_p_gain_roll -=0.02;}
else if(myChar == '2'){pid_i_gain_roll +=0.001;}
else if(myChar == '5'){pid_i_gain_roll -=0.001;}
else if(myChar == '3'){pid_d_gain_roll +=0.5;}
else if(myChar == '6'){pid_d_gain_roll -=0.5;}
else if(myChar == '7'){startPower +=50;}
else if(myChar == '8'){startPower -=50;}
else if(myChar == '9'){QuadIsActive = !QuadIsActive; }
//Serial.print("pid_p_gain_roll :");Serial.print(pid_p_gain_roll);Serial.print(" pid_i_gain_roll :");Serial.print(pid_i_gain_roll);Serial.print(" pid_d_gain_roll :");Serial.print(pid_d_gain_roll);Serial.print(" pid_output_pitch :");Serial.println(pid_output_pitch);

//Serial.print("pid_output_roll :");Serial.print(pid_output_roll);Serial.print(" pid_output_pitch :");Serial.print(pid_output_pitch);Serial.print(" pid_output_yaw :");Serial.println(pid_output_yaw);
 }
//
//    if (Serial.available() > 0) 
//    {string = "";}
//    
//    while(Serial.available() > 0)
//    {
//      command = ((byte)Serial.read());
//      
//      if(command == ':')
//      {
//        break;
//      }
//      
//      else
//      {
//        string += command;
//      }
//      
//      delay(1);
//    }
//    
//    if(string == "TO")
//    {
//    }

    
}  

