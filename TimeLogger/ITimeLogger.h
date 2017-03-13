//
// Created by Alex Paniutin on 6/12/15.
//

#ifndef TIMELOGGER_ITIMELOGGER_H
#define TIMELOGGER_ITIMELOGGER_H

#include <string>

/**
 * This is the interface for TimeLogger that monitors your application performance
 * by logging the timestamp at certain check point.
 * CP will be used to shorten the function name and it stands for CheckPoint
 * Usage:
 *     1. add checkpoints as you need before your main work.
 *        It will define internal storage properly and optimal for the need
 *     2. when run the main work cycles, set the checkpoint time by specifying the ID
 *     3. trigger the end of the cycle. This should dump the current readings and reset all the checkpoints
 */
class ITimeLogger {
 public:
  /**
   * @brief adds a checkpoint to the set. set your own ID and pick up a checkpoint name
   * @param cpID checkpoint ID
   * @param cpName checkpoint name
   * @return true if checkpoint has been added successfully
   */
  virtual bool addCheckPoint(const unsigned int cpID, std::string cpName) = 0;

  /**
   * @brief sets the current time for a checkpoint by its ID
   * @param cpID checkpoint ID
   * @return true if checkpoint was registered successfully
   */
  virtual bool setCPTime(const unsigned int cpID) = 0;
};
#endif //TIMELOGGER_ITIMELOGGER_H
