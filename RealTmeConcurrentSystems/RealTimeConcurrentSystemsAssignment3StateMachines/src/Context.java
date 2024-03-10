/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the context class is to act as an interface with the outside world and maintain a pointer to the
 current state of the state machine.
 */

public class Context implements Runnable {

     /**
      * Pointer to the current state of the state machine.
      */
    private State currentState;

    /**
     * boolean flag for keeping track of whether a pedestrian is currently waiting
     */
    public boolean isPedestrianWaiting;

    /**
     * Thread for executing Context
     */
    public Thread thread;

    /**
     * enum for defining the different possible signals the pedestrian light will display
     */
    public static enum PedestrianSignals {
        DONT_WALK,
        WALK,
        BLANK
    }

    /**
     * Current pedestrian signal being displayed
     */
    private PedestrianSignals pedestrianSignal;

    /**
     * enum for defining the different possible vehicle traffic light colours
     */
    public static enum TrafficLightColours {
        GREEN,
        YELLOW,
        RED
    }

    /**
     * Current traffic light colour being displayed
     */
    private TrafficLightColours trafficLightColour;

    /**
     * Constructor for a new Context object
     */
    public Context() {
        this.thread = new Thread(this);
        thread.start();
    }

    @Override
    public void run() {
        setState(new Operational(this));
    }

    /**
     * Returns the current state.
     * @return the current state
     */
    public State getState() {
        return currentState;
    }

    /**
     * Sets the current state to the new specified state.
     * @param state the new state to set the current state to.
     */
    public void setState(State state) {
        currentState = state;
    }

    /**
     * Handles the event that occurs when a pedestrian presses the button and is now waiting at the crossing.
     */
    public void pedestrianWaiting() {
        currentState.pedestrianWaiting(this);
    }

    /**
     * Handles the event that occurs when a timeout occurs after killTimer().
     */
    public void timeout() {
        currentState.timeout(this);
    }

    /**
     * Returns context's boolean flag indicating if a pedestrian is waiting
     * @return isPedestrianWaiting the boolean flag indicating if a pedestrian is waiting
     */
    public boolean isPedestrianWaiting(){
        return isPedestrianWaiting;
    }

    /**
     * Updates context's boolean flag indicating if a pedestrian is waiting
     * @param pedestriansWaiting true if pedestrian is waiting, false otherwise
     */
    public void setPedestriansWaiting(boolean pedestriansWaiting) {
        isPedestrianWaiting = pedestriansWaiting;
    }

    /**
     * Update the pedestrian light with the provided pedestrian signal.
     *
     * @param signal the PedestrianSignal to update the pedestrian light to.
     */
    public void signalPedestrians(PedestrianSignals signal) {
        pedestrianSignal = signal;
        System.out.println("Pedestrian signal set to " + pedestrianSignal.toString());
    }

    /**
     * Update the traffic light with the provided traffic light colour.
     *
     * @param colour the colour to update the traffic light to.
     */
    public void signalVehicles(TrafficLightColours colour) {
        trafficLightColour = colour;
        System.out.println("Traffic signal set to " + trafficLightColour.toString());
    }

    /**
     * Set the timer for the specified amount of time
     */
    public void setTimer(int time) {
        System.out.printf("Setting timer to %d seconds\n", time / 1000);
        try {
            Thread.sleep(time);
        } catch (InterruptedException e) {
            e.printStackTrace();
            System.err.println("Sleep operation was interrupted while transitioning from " + currentState.getClass().toString());
        }
    }

    /**
     * Kill the timer to indicate that the timeout action needs to be dispatched.
     */
    public void killTimer() {
        System.out.println("killTimer() invoked");
        timeout();
    }
}