/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the vehiclesEnabled class is to implement the vehiclesEnabled state and define its state specific behaviour.
 */

public class vehiclesEnabled implements State {

    public vehiclesEnabled(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: VehiclesEnabled");
        //Entry condition for vehiclesEnabled state
        System.out.println("Entry/Updating pedestrian signal to 'DONT_WALK'");
        context.signalPedestrians(Context.PedestrianSignals.DONT_WALK);
        //Transition to vehiclesEnabled state
        context.setState(new vehiclesGreen(context));
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
