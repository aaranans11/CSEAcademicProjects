SYSC3303B Real-Time Concurrent Systems
Assignment 3 - Introduction to UDP
Aaranan Sathiendran - 101196339

This assignment implements a state machine used to control a Pelican type pedestrian crossing.  The solution follows the state design pattern, meaning there is a Context class which acts as an interface with the outside world, delegating events such as a pedestrian pressing the button requesting to cross to the state machine.  There is a state interface, which acts as a base interface that other concrete states within the state machine can implement to define state-specific behaviour.

FILE BREAKDOWN:
There are 11 files:
- State.java: contains the State interface
- Context.java: contains the interface for interacting with the outside world
- Operational.java: implements the Operational state
- vehiclesEnabled.java: implements the vehiclesEnabled state
- vehiclesGreen.java: implements the vehiclesGreen state
- vehiclesGreenInt.java: implements the vehiclesGreenInt state
- vehiclesYellow.java: implements the vehiclesYellow state
- pedestriansEnabled.java: implements the pedestriansEnabled state
- pedestriansWalk.java: implements the pedestriansWalk state
- pedestriansFlash.java: implements the pedestriansFlash state
- TestHarness.java: tests state machine by sending events while the machine is in various
 states.

DEFECTS:

The first defect in the presented state machine design is that when the pedestrian presses the button while the state machine is in the pedestrianFlashing state. the button press won't be tracked by the machine until it is pressed again while in the vehiclesGreen state.

Another defect could be that when the state machine is in the pedestriansFlash state and doesn't complete counting down, it resets pedestrianFlashCtr to 7 upon re-entering the state, which could result in an infinite loop

Another defect that could be annoying to some pedestrians is that with the current design, the vehicles are guaranteed a green light for at least 10 seconds before the pedestrian can press the button and cross.