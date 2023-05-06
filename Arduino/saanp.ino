#include <math.h>
#define pi 22/7
#define servo_numbers 8
double deg2rad = 22.000/(180.000*7.000);
int t = 0;  
#include <Servo.h>
Servo servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8,  servo9, servo10, servo11, servo12,  servo13, servo14, servo15; // create servo object to control a servo


double wave_position(double t, double x)
{
  double f = 1;
  double theta_Max = 10;
  double y = theta_Max*sin(deg2rad*(x-t)*f)*sqrt(x);
  return y;
}

double circle_y_value(double a,double b,double r,double x_value,double t)//:  #a-> x_curr, b-> y_curr
{
  double y_value;
  double wave_pos = wave_position(t,x_value);
  //Serial.println(a);
  //Serial.print(", ");
  //Serial.println(a);
  if (wave_pos>b)
  {
    y_value = sqrt(sq(r)-(sq(a-x_value))) + b;
  }
  else if (wave_pos<b)
  {
    y_value = -sqrt(sq(r)-(sq(a-x_value))) + b;
  }
  else if (wave_pos==b)
  {
    if (wave_pos>=0)
    {
      y_value = sqrt(sq(r)-(sq(a-x_value))) + b;
    }
    else
    {
      y_value = -sqrt(sq(r)-(sq(a-x_value))) + b;
    }
  }
  return y_value;
} 

double intersection_x_value(double x,double t,double l)
{
  double i;
  //Serial.println(x);
  double flag = 0;
  for (i=x+l-1; i>=x; i=i-1)
  {
    double wave1 = wave_position(t,i);
    double wave2 = wave_position(t,i+1);
    double circle1 = circle_y_value(x,wave_position(t,x),l,i,t);
    double circle2 = circle_y_value(x,wave_position(t,x),l,i+1,t);
      
    double d1 = wave1 - circle1;
    double d2 = wave2 - circle2;
    //Serial.println(x);
    //Serial.print(", ");
    //Serial.println(x,6);
    if (d1==0 || d2==0 || (d1*d2<0 && (d1<0 || d2<0)))
    {
      //Serial.println("***");
      flag = i;
      break;
    }
  }
  return flag;
}

double angle_lines(double m1,double m2)
{
  double servo_angle = atan((m1-m2)/(1+(m1*m2)));
  return servo_angle;
}

double angle(double x1,double x2,double x3,double y1,double y2,double y3)
{
  double m1 = (y1-y2)/(x1-x2);
  double m2 = (y2-y3)/(x2-x3);
  double servo_angle = angle_lines(m1,m2);
  return servo_angle;
}


void setup() {
// put your setup code here, to run once:
    
  servo1.attach(2);   // attaches the servo on respective pins to the servo object
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
//  servo8.attach(9);
//  servo9.attach(10);
//  servo10.attach(11);
//  servo11.attach(12);
//  servo12.attach(13);
//  servo13.attach(44);
//  servo14.attach(45);
//  servo15.attach(46);
  

  Serial.begin(115200);
  t = 0;
  
}

void loop() {
  unsigned long start = millis();
  int angles[servo_numbers];
  
  // put your main code here, to run repeatedly:
  double x_data[servo_numbers+1];
  double y_data[servo_numbers+1];
  double x_value = 1;
  for(int i = 0; i<servo_numbers+1; i++)
  {
    x_data[i] = x_value;
    y_data[i] = wave_position(t,x_value);
    //Serial.println(t);
    x_value = intersection_x_value(x_value,t,60);    
    //Serial.println(x_value);
  }

                 
  /*for(int i=0;i<servo_numbers+1;i++)
  {
    Serial.print(x_data[i]);
    Serial.print(", ");
    Serial.print(y_data[i]);
  }*/
  Serial.println();
  angles[0] = (angle_lines(0,y_data[1]/x_data[1])*180*7/22)+90;
  for(int i = 1;i<servo_numbers;i++)
  {
    angles[i] = (angle(x_data[i-1],x_data[i],x_data[i+1],y_data[i-1],y_data[i],y_data[i+1])*180*7/22)+90;
  }

  
  for(int i=0;i<servo_numbers;i++)
  {
    Serial.print(angles[i]);
    Serial.print(", ");
  }
  Serial.print("||| ");
  Serial.print(t);

  
  unsigned long ends = millis();
  Serial.print(", ");
  Serial.println(ends-start);
  t = t+1;

   int input1=angles[0];  
   int input2=angles[1];       
   int input3=angles[2];  
   int input4=angles[3];  
   int input5=angles[4];  
   int input6=angles[5];  
   int input7=angles[6];   
   
  servo1.write(input1);      // tell servo to go to position in variable 'angles'
  servo2.write(input2);
  servo3.write(input3);
  servo4.write(input4);
  servo5.write(input5);
  servo6.write(input6);
  servo7.write(input7);
  //delay(1000);
}
