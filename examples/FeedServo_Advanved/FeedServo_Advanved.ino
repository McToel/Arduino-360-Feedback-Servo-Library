#include "FeedServo.h"

#define servo_port 7
#define servo_feedback_port 6

#define poti_port A0

//Create FeedServo Object
FeedServo FS(servo_port, servo_feedback_port);

void setup()
{
  FS.init();
}

double Position;

void loop()
{
  //Set the servo to the value of the poti
  Position = map(analogRead(poti_port), 0, 1023, 0, 359);

  //You can also do more than one rotation:
  //Position = map(analogRead(poti_port), 0, 1023, 0, 719);
  
  FS.write_p_error(Position);

}
