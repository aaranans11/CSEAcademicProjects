/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the pedestriansWalk class is to implement the pedestriansWalk state and define its state specific behaviour.
 */

public class pedestriansWalk implements State {

    public pedestriansWalk(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: pedestriansWalk");
        //Entry condition for pedestriansWalk state
        System.out.println("Entry/Setting timer to 15 seconds'");
        context.setTimer(15000);
        //Update pedestrian light to 'WALK'
        context.signalPedestrians(Context.PedestrianSignals.WALK);
        //Exit condition for pedestriansWalk state
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
        //Transition to the pedestriansFlash state
        context.setState(new pedestriansFlash(context));
    }
}
