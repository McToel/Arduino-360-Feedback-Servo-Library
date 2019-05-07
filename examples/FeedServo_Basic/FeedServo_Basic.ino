#include "FeedServo.h"

#define servo_port 7
#define servo_feedback_port 6

//Create FeedServo Object
FeedServo FS(servo_port, servo_feedback_port);

void setup()
{
  Serial.begin(9600);
  FS.init();
}

double Position;

void loop()
{
  //Set the servo to 270°, like you could do with the standard servo library
  FS.write_pos(270);
  delay(100);

  //Read the position of the servo
  Position = FS.read_pos();
  Serial.println(Position);
}
