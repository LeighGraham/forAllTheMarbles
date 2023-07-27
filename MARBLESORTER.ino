#include <Servo.h>

Servo hopperServo;
Servo collectionServo;

int outPin = 7;
int S0 = 3;
int S1 = 4;
int S2 = 5;
int S3 = 6;

bool once = true;

void setup() {

hopperServo.attach(12);
collectionServo.attach(13);

pinMode(S0,OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2,OUTPUT);
pinMode(S3,OUTPUT);
pinMode(outPin,INPUT);

digitalWrite(S0,HIGH);
digitalWrite(S1, HIGH);

Serial.begin(9600);

Serial.println("Color Reader");

}

void loop()
{

if (once)
{
hopperServo.write(0);
delay(4000);
hopperServo.write(180);
once = false;
}

long red=readRed();
long green=readGreen();
long blue = readBlue();

if ((red<green)&&(red<blue)&&(green>40)) //red
{
collectionServo.write(180);
Serial.println("RED");
delay(3000);
hopperServo.write(0);
once = true;
}
if((red = green) && (green < 40 ) && (blue > 29) && (green > blue)) //blue
{
collectionServo.write(0);
Serial.println("GREEN");
delay(3000);
hopperServo.write(0);
once = true;
}
if ((red = green) && (blue < red) && (blue < 29)) //green
{
collectionServo.write(45);
Serial.println("BLUE");
delay(3000);
hopperServo.write(0);
once = true;
}

}
long readRed()
{
return (readColor(LOW,LOW));
}
long readGreen()
{
return(readColor(HIGH,HIGH));
}
long readBlue() 
{
return(readColor(LOW,HIGH));
}
long readColor(int bit0, int bit1)
{
digitalWrite(S2, bit0);
digitalWrite(S3, bit1);

long start = millis();
for (int i = 0; i <1000; i++)
{
pulseIn(outPin,HIGH);
}
return (millis()-start);
}
