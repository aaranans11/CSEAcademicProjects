/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the Operational class is to implement the Operational state and define its state specific behaviour.
 */

public class Operational implements State {

    public Operational(Context context) {
        System.out.println("CURRENT STATE: Operational");
        //Transition to vehiclesEnabled state
        context.setState(new vehiclesEnabled(context));
    }

    /**
     * Handles the event that occurs when a pedestrian presses the button and is now waiting at the crossing.
     *
     * @param context the current context.
     */
    @Override
    public void pedestrianWaiting(Context context) {
        //Not needed in this state
    }

    /**
     * Handles the event that occurs when a timeout occurs after killTimer().
     *
     * @param context the current context.
     */
    @Override
    public void timeout(Context context) {
        //Not needed in this state
    }

}
