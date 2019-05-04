#ifndef FEEDSERVO_H
#define FEEDSERVO_H

#include "Servo.h"

class FeedServo : public Servo
{
  public:
#define dcMin 2.9
#define dcMax 91.7
#define s_stop 94

    FeedServo(byte, byte);
    FeedServo(double*, double*, double*, byte, byte);
    double read_pos();
    void Compute();
    void write_pos(int);
    void init();

  private:

    double last_pos;             //   To detect mouvements in edge cases (350° to 10°)
    int runs;                    //   To calculate absolute position      -> 350° to 370°

    double* myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double* myOutput;             //   This creates a hard link between the variables and the
    double* mySetpoint;           //   PID, freeing the user from having to constantly tell us
    //   what these values are.  with pointers we'll just know.

    byte port;                    //   Control port of the servo
    byte feedback_port;           //   Port to get position feedback from the servo (yellow wire)
};
#endif //FEEDSERVO_H