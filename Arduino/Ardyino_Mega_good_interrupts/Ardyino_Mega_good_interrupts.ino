/*
 * Connections:
 * A0 (PF0) -> PCINT0 (PB0 / 53)
 * A1 (PF1) -> PCINT1 (PB1 / 52)
 * A2 (PF2) -> PCINT2 (PB2 / 51)
 * A3 (PF3) -> PCINT3 (PB3 / 50)
 * A4 (PF4) -> PCINT6 (PB6 / 12)
 * A5 (PF5) -> PCINT7 (PB7 / 13)
 */

 
//Declaring Variables
volatile byte last_channel_1, last_channel_2, last_channel_3, last_channel_4, last_channel_5, last_channel_6;
volatile int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4, receiver_input_channel_5, receiver_input_channel_6;
volatile unsigned long timer_1, timer_2, timer_3, timer_4, timer_5, timer_6;


void setup() {
  
  Serial.begin(9600);

  //channel 1 -> pin 53
  //channel 2 -> pin 52
  //channel 3 -> pin 51
  //channel 4 -> pin 50
  //channel 5 -> pin 12
  //channel 6 -> pin 13
  
  
  // Make PF0-5 outputs:
  DDRF   = _BV(PF0) | _BV(PF1) | _BV(PF2) | _BV(PF3) | _BV(PF4) | _BV(PF5);

  PCICR  = _BV(PCIE0);
  PCMSK0 = _BV(PCINT0) | _BV(PCINT1) | _BV(PCINT2) | _BV(PCINT3) | _BV(PCINT6) | _BV(PCINT7);

}

void loop() {

  delay(250);
  print_signals();
}




//This routine is called every time input 8, 9, 10 or 11 changed state
ISR(PCINT0_vect){
  //Channel 1=========================================
  if(last_channel_1 == 0 && PINB & B00000001 ){         //Input 8 changed from 0 to 1
    last_channel_1 = 1;                                 //Remember current input state
    timer_1 = micros();                                 //Set timer_1 to micros()
  }
  else if(last_channel_1 == 1 && !(PINB & B00000001)){  //Input 8 changed from 1 to 0
    last_channel_1 = 0;                                 //Remember current input state
    receiver_input_channel_1 = micros() - timer_1;      //Channel 1 is micros() - timer_1
  }
  //Channel 2=========================================
  if(last_channel_2 == 0 && PINB & B00000010 ){         //Input 9 changed from 0 to 1
    last_channel_2 = 1;                                 //Remember current input state
    timer_2 = micros();                                 //Set timer_2 to micros()
  }
  else if(last_channel_2 == 1 && !(PINB & B00000010)){  //Input 9 changed from 1 to 0
    last_channel_2 = 0;                                 //Remember current input state
    receiver_input_channel_2 = micros() - timer_2;      //Channel 2 is micros() - timer_2
  }
  //Channel 3=========================================
  if(last_channel_3 == 0 && PINB & B00000100 ){         //Input 10 changed from 0 to 1
    last_channel_3 = 1;                                 //Remember current input state
    timer_3 = micros();                                 //Set timer_3 to micros()
  }
  else if(last_channel_3 == 1 && !(PINB & B00000100)){  //Input 10 changed from 1 to 0
    last_channel_3 = 0;                                 //Remember current input state
    receiver_input_channel_3 = micros() - timer_3;      //Channel 3 is micros() - timer_3
  }
  //Channel 4=========================================
  if(last_channel_4 == 0 && PINB & B00001000 ){         //Input 11 changed from 0 to 1
    last_channel_4 = 1;                                 //Remember current input state
    timer_4 = micros();                                 //Set timer_4 to micros()
  }
  else if(last_channel_4 == 1 && !(PINB & B00001000)){  //Input 11 changed from 1 to 0
    last_channel_4 = 0;                                 //Remember current input state
    receiver_input_channel_4 = micros() - timer_4;      //Channel 4 is micros() - timer_4
  }

   //Channel 5=========================================
  if(last_channel_5 == 0 && PINB & B01000000 ){         //Input 12 changed from 0 to 1
    last_channel_5 = 1;                                 //Remember current input state
    timer_5 = micros();                                 //Set timer_5 to micros()
  }
  else if(last_channel_5 == 1 && !(PINB & B01000000)){  //Input 12 changed from 1 to 0
    last_channel_5 = 0;                                 //Remember current input state
    receiver_input_channel_5 = micros() - timer_5;      //Channel 5 is micros() - timer_5
  }

     //Channel 6=========================================
  if(last_channel_6 == 0 && PINB & B10000000 ){         //Input 13 changed from 0 to 1
    last_channel_6 = 1;                                 //Remember current input state
    timer_6 = micros();                                 //Set timer_6 to micros()
  }
  else if(last_channel_6 == 1 && !(PINB & B10000000)){  //Input 13 changed from 1 to 0
    last_channel_6 = 0;                                 //Remember current input state
    receiver_input_channel_6 = micros() - timer_6;      //Channel 6 is micros() - timer_6
  }
}

//Subroutine for displaying the receiver signals
void print_signals(){
  Serial.print("Roll:");
  if(receiver_input_channel_1 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_1 - 1520 > 0)Serial.print(">>>");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_1);
  
  Serial.print("  Nick:");
  if(receiver_input_channel_2 - 1480 < 0)Serial.print("^^^");
  else if(receiver_input_channel_2 - 1520 > 0)Serial.print("vvv");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_2);
  
  Serial.print("  Gas:");
  if(receiver_input_channel_3 - 1480 < 0)Serial.print("vvv");
  else if(receiver_input_channel_3 - 1520 > 0)Serial.print("^^^");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_3);
  
  Serial.print("  Yaw:");
  if(receiver_input_channel_4 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_4 - 1520 > 0)Serial.print(">>>");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_4);

    Serial.print("  Channel 5:");
  if(receiver_input_channel_5 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_5 - 1520 > 0)Serial.print(">>>");
  else Serial.print("-+-");
  Serial.print(receiver_input_channel_5);

     Serial.print("  Channel 6:");
  if(receiver_input_channel_6 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_6 - 1520 > 0)Serial.print(">>>");
  else Serial.print("-+-");
  Serial.println(receiver_input_channel_6);
}

