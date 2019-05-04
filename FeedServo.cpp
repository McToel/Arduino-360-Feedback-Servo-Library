#include "Arduino.h"
#include "FeedServo.h"

FeedServo::FeedServo(byte Port, byte Feedback_Port)
{
  port = Port;
  feedback_port = Feedback_Port;

  last_pos = 180;
  runs = 0;
}

void FeedServo::init()
{
  attach(port);
  pinMode(feedback_port, INPUT);
}

double FeedServo::read_pos()
{
  long tHigh, tLow, tCycle;
  while (true) //From Parallax spec sheet
  {
    tHigh = pulseIn(feedback_port, HIGH);
    tLow = pulseIn(feedback_port, LOW);
    tCycle = tHigh + tLow;
    if ( tCycle > 1000 && tCycle < 1200)
      break; //valid tCycle;
  }
  double dc = (100.00 * (double)tHigh) / (double)tCycle; //From Parallax spec sheet, you are trying to determine the percentage of the HIGH in the pulse

  double angle = ((dc - dcMin) * 360.00) / (dcMax - dcMin + 1.00);
  angle = (angle < 0) ? 0 : angle;
  angle = (angle > 359) ? 359 : angle;
  runs += (last_pos > angle + 180);
  runs -= (last_pos < angle - 180);
  last_pos = angle;
  angle += 360 * runs;
  return angle;
}

void FeedServo::Compute()
{
  double error;
  error = mySetpoint - myInput;
  error = min(30, error);
  error = max(-30, error);
  myOutput = -(error * Kp);
}

void FeedServo::write_pos(int pos)
{
  mySetpoint = pos;
  myInput = read_pos();
  double last_pos = 0;
  do
  {
    Compute();
    write(myOutput + s_stop);
    //delay(1);
    last_pos = myInput;
    myInput = read_pos();
  } while (last_pos != myInput || myInput > mySetpoint + 4 || myInput < mySetpoint - 4);
  for (int i = 0; i < 200; i++)
  {
    myInput = read_pos();
    Compute();
    write(myOutput + s_stop);
  }
  write(s_stop);
}

void FeedServo::write_p_error(int pos)
{
  mySetpoint = pos;
  myInput = read_pos();
  Compute();
  write(myOutput + s_stop);
}
