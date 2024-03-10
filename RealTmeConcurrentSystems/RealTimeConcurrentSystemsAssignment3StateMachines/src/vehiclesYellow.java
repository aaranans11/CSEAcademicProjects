/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the vehiclesYellow class is to implement the vehiclesYellow state and define its state specific behaviour.
 */
public class vehiclesYellow implements State {

    public vehiclesYellow(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: vehiclesYellow");
        //Entry condition for vehiclesYellow state
        System.out.println("Entry/Setting timer to 3 seconds");
        context.setTimer(3000);
        //Update traffic light to yellow
        context.signalVehicles(Context.TrafficLightColours.YELLOW);
        //Exit condition for vehiclesYellow state
        System.out.println("Exit/invoking killTimer()");
        context.killTimer();
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
        //Reset pedestrianWaiting flag since pedestrian will now get their turn to cross upon transition to pedestriansEnabled
        context.setPedestriansWaiting(false);
        context.setState(new pedestriansEnabled(context));
    }
}
