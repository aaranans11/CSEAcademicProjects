/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the pedestriansEnabled class is to implement the pedestriansEnabled state and define its state specific behaviour.
 */

public class pedestriansEnabled implements State {

    public pedestriansEnabled(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: pedestriansEnabled");
        //Entry condition for pedestriansEnabled state
        System.out.println("Entry/Updating traffic signal to 'RED'");
        //Update traffic light to red
        context.signalVehicles(Context.TrafficLightColours.RED);
        //Exit condition for pedestriansEnabled state
        context.setState(new pedestriansWalk(context));
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
