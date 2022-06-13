#ifndef USER_MARKLIN_SERVER_H_
#define USER_MARKLIN_SERVER_H_

#define MARKLIN_SERVER_NAME "MARKLIN_SERVER"

namespace marklin {

#define MRV_CAP 10
#define SENSOR_CAP 80

struct Msg {
  enum class Action {
    Ready = 0,            // data = {}
    SwitchReady,          // data = {}
    Cmd,                  // data = {cmd1[, cmd2]}
    ReverseReady = 0x10,  // data = {0, trainId}
    TrainCmd,             // data = {speed, trainId}
    ReverseCmd,           // data = {0, trainId}
    SwitchCmd = 0x20      // data = {direction, switchId}
  };
  Action action;
  int data[2];
  int len;

  int getTrainId() const;

  static Msg go();
  static Msg stop();
  static Msg tr(char speed, char trainId);
  static Msg sw(char direction, char switchId);
  static Msg rv(char trainId);
  static Msg solenoidOff();
  static Msg querySensors();
};

struct Train {
  int id;
  int speed;
  int reverseTid;
  bool isReversing;

  void setSpeed(int speed);
};

struct MrvNode {
  int bitIdx;
  int time;
};

struct Sensor {
  int mrvIdx;
  int mrvSize;
  char data[SENSOR_CAP];
  char status[SENSOR_CAP];
  MrvNode mostRecentlyVisited[MRV_CAP];
};

void cmdServer();

}  // namespace marklin

#endif  // USER_MARKLIN_SERVER_H_