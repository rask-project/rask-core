# Rask Core
This library implements an event loop, which allows the execution of timers on pseudo-threads and resources for signals and slots.

### Classes
***RaskObject*** - contains properties to run the timer, often at intervals or single shot.
Properties / Functions:
  * interval() - Interval time defined
  * setInterval(nsigned long value) - Set timer interval
  * startTimer(unsigned long value) - Start running the timer
  * stopTimer() - Stop running the timer
  * lastRun() - Last timer run
  * setLastRun(unsigned long value) - Set the last run time
  * isSingleShot() - Return whehter the timer is single shot
  * singleShot(unsigned long value) - Set timer as single shot
  * running() - Returns whether the timer is running
  * setRunning(bool value) - Set whether the timer is running
  * removeEventFromLoop() - Removes RaskObject from the event loop

***RaskSignal*** - Signal emission template
Properties / Functions:
  * emit(Args... args) - Signal emission
  * connect(RaskSlot<Args...> *) - Connects the slot to the signal
  * disconnect(RaskSlot<Args...> *) - Disconnect the slot of the signal
  * disconnect() - Disconnect all slots

***RaskSlot*** - Slot / callback to be executed when the signal is emitted
Properties / Functions:
  * setCallback(std::function<void(Args...)>) - Set callback to be executed
  * setSignalParent(RaskSignal<Args...> *) - Sets the parent signal to remove the signal slot when it is deleted
