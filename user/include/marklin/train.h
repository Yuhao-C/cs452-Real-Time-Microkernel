#ifndef USER_MARKLIN_TRAIN_H_
#define USER_MARKLIN_TRAIN_H_

#include "track_data.h"

namespace marklin {

class Train {
 public:
  int id;
  int velocity[3];
  int stopDist[3];

  enum SpeedLevel { SevenDec, TenInc, FourteenInc, Zero };
  enum Direction { Forward = 30000, Backward = 150000 };

  SpeedLevel speedLevel;
  Direction direction;

  int reverseTid;
  bool isReversing;

  track_node* nextSensor;  // predicted next sensor
  int nextSensorTick;      // predicted time of arrival at next sensor
  int nextSensorDist;      // distance to predicted next sensor
  track_node* lastSensor;  // actual last triggered sensor
  int lastSensorTick;      // actual trigger time of last sensor

  Train(int id, int* velocity, int* stopDist);
  void setSpeedLevel(SpeedLevel speedLevel);
  int getVelocity() const;
  int getStopDist() const;
  SpeedLevel getSpeedLevel() const;
  int getSpeedLevelInt() const;
  void reverseDirection();

  static SpeedLevel getSpeedLevel(int speed);
};
}  // namespace marklin

#endif  // USER_MARKLIN_TRAIN_H_