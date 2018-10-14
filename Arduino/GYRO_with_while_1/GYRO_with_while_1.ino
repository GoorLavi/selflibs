const int xPin = 0;
const int yPin = 1;

#define motor1 3  
#define motor4 5
#define motor3 6
#define motor2 10

double x;
double y;


int minVal = 130;
int maxVal = 190;

void setup() {
 Serial.begin(9600); 
 
pinMode ( motor1 , OUTPUT );
pinMode ( motor2 , OUTPUT );
pinMode ( motor3 , OUTPUT );
pinMode ( motor4 , OUTPUT );


analogWrite(motor1,230);
analogWrite(motor2,230);
analogWrite(motor3,230);
analogWrite(motor4,230);

}

void loop() {
   int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);

 //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
   
   //Output the caculations
   x = xAng;
   y = yAng;
   
   

 //הגדרת משתנה מהירות לכל מנוע 
 int m1speed =  analogRead (motor1);
 int m2speed =  analogRead (motor2);
 int m3speed =  analogRead (motor3);
 int m4speed =  analogRead (motor4);
  
  while (  530 < xAng < 490 || 530 < yAng < 490)
  {
  
  
  //אם זווית X קטנה מ 490 תתייצב
  if ( xAng < 490) {
 analogWrite  (motor1,m1speed++);
analogWrite  (motor3,m3speed++);
  }
  

  else if ( xAng > 530) {
 analogWrite  (motor2,m2speed++);
analogWrite  (motor4,m4speed++);
  }

 

 else if ( yAng < 490) {
 analogWrite  (motor1,m1speed++);
analogWrite  (motor2,m2speed++);

  }
  


  else if ( yAng > 530) {
 analogWrite  (motor3,m3speed++);
analogWrite  (motor4,m4speed++);
  }
  }

analogWrite  ( m1speed,230);
analogWrite  ( m2speed,230);
analogWrite  ( m3speed,230);
analogWrite  ( m4speed,230);


}
