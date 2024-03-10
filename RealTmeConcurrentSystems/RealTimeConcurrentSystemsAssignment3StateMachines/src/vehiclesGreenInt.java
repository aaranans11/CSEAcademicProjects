/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the vehiclesGreen class is to implement the vehiclesGreen state and define its state specific behaviour.
 */

public class vehiclesGreenInt implements State {

    public vehiclesGreenInt(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: vehiclesGreenInt");
        //Continue to wait in this state until a pedestrian is waiting
        while (!context.isPedestrianWaiting()) {
            try{
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
                System.err.println("Sleep operation was interrupted while waiting for a pedestrian");
            }
        }
        //Transition to vehiclesYellow state now that loop has been exited due to pedestrian waiting
        context.setState(new vehiclesYellow(context));
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
        //Not needed in this state
    }
}
