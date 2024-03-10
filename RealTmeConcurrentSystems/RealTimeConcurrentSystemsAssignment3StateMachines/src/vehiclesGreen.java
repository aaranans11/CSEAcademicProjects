/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the vehiclesGreen class is to implement the vehiclesGreen state and define its state specific behaviour.
 */

public class vehiclesGreen implements State {

    public vehiclesGreen(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: vehiclesGreen");
        //Entry condition for vehiclesGreen state
        System.out.println("Entry/Setting timer to 10 seconds");
        context.setTimer(10000);
        //Update traffic light to green
        context.signalVehicles(Context.TrafficLightColours.GREEN);
        //Exit condition for vehiclesGreen state
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
        //Update pedestrianWaiting flag in context to reflect that a pedestrian is now waiting
        context.setPedestriansWaiting(true);
    }

    /**
     * Handles the event that occurs when a timeout occurs after killTimer().
     *
     * @param context the current context.
     */
    @Override
    public void timeout(Context context) {
        System.out.println("TIMEOUT");
        //If a pedestrian is waiting, transition to vehiclesYellow state, otherwise transition to vehiclesGreenInt
        if (context.isPedestrianWaiting()) {
            System.out.println("[isPedestrianWaiting] -> transitioning to vehiclesYellow");
            context.setState(new vehiclesYellow(context));
        } else {
            System.out.println("[else] -> transitioning to vehiclesGreenInt");
            context.setState(new vehiclesGreenInt(context));
        }
    }
}
