#include <Arduino.h>


byte last_channel_1, last_channel_2, last_channel_3, last_channel_4, last_channel_5, last_channel_6;
int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4, receiver_input_channel_5, receiver_input_channel_6;
unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_timer, esc_loop_timer;
unsigned long timer_1, timer_2, timer_3, timer_4, timer_5, timer_6, current_time;

void receiverSetup() {

  Serial.println("InitializeReciver");


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

  Serial.println("end InitializeReciver");
}

void printValues() {
  Serial.print(receiver_input_channel_1);
  Serial.print(", ");
  Serial.print(receiver_input_channel_2);
  Serial.print(", ");
  Serial.print(receiver_input_channel_3);
  Serial.print(", ");
  Serial.print(receiver_input_channel_4);
  Serial.print(", ");
  Serial.print(receiver_input_channel_5);
  Serial.print(", ");
  Serial.println(receiver_input_channel_6);
}

//This routine is called every time input 53,52,51,50,12,13 changed state
ISR(PCINT0_vect){

  current_time = micros();

  //Channel 1=========================================
  if(PINB & B00000001){
    if(last_channel_1 == 0){
      last_channel_1 = 1;
      timer_1 = current_time;
    }
  }
  else if(last_channel_1 == 1){
    last_channel_1 = 0;
    receiver_input_channel_1 = current_time - timer_1;
  }


  //Channel 2=========================================
  if(PINB & B00000010){
    if(last_channel_2 == 0){
      last_channel_2 = 1;
      timer_2 = current_time;
    }
  }
  else if(last_channel_2 == 1){
    last_channel_2 = 0;
    receiver_input_channel_2 = current_time - timer_2;
  }


  //Channel 3=========================================
  if(PINB & B00000100){
    if(last_channel_3 == 0){
      last_channel_3 = 1;
      timer_3 = current_time;
    }
  }
  else if(last_channel_3 == 1){
    last_channel_3 = 0;
    receiver_input_channel_3 = current_time - timer_3;
  }


  //Channel 4=========================================
  if(PINB & B00001000){
    if(last_channel_4 == 0){
      last_channel_4 = 1;
      timer_4 = current_time;
    }
  }
  else if(last_channel_4 == 1){
    last_channel_4 = 0;
    receiver_input_channel_4 = current_time - timer_4;
  }


   //Channel 5=========================================
   if(PINB & B01000000){
    if(last_channel_5 == 0){
      last_channel_5 = 1;
      timer_5 = current_time;
    }
   }
  else if(last_channel_5 == 1){
    last_channel_5 = 0;
    receiver_input_channel_5 = current_time - timer_5;
  }

     //Channel 6=========================================
   if(PINB & B10000000){
    if(last_channel_6 == 0){
      last_channel_6 = 1;
      timer_6 = current_time;
    }
  }
  else if(last_channel_6 == 1){
    last_channel_6 = 0;
    receiver_input_channel_6 = current_time - timer_6;
  }
}
