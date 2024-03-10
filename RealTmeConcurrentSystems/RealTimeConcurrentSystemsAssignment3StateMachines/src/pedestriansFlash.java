/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the pedestriansFlash class is to implement the pedestriansFlash state and define its state specific behaviour.
 */

public class pedestriansFlash implements State {

    private int pedestrianFlashCtr;

    public pedestriansFlash(Context context) {
        //Update state pointer in context to reflect new current state
        context.setState(this);
        System.out.println("CURRENT STATE: pedestriansFlash");
        //Entry condition for pedestriansFlash state
        System.out.println("Entry/Setting timer to 1 second");
        context.setTimer(1000);
        //Initialize pedestrianFlashCtr
        pedestrianFlashCtr = 7;
        //Exit condition for pedestriansFlash state
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
        //Decrement pedestrianFlashCtr
        pedestrianFlashCtr -= 1;
        //If countdown has completed, transition back to vehiclesEnabled state
        if (pedestrianFlashCtr == 0) {
            context.setState(new vehiclesEnabled(context));
            //If countdown is still going and count is even, flash the pedestrian light with 'DONT_WALK'
        } else if ((pedestrianFlashCtr & 1) == 0) {
            context.signalPedestrians(Context.PedestrianSignals.DONT_WALK);
            //If countdown is still going and count is odd, flash the pedestrian light with 'BLANK'
        } else {
            context.signalPedestrians(Context.PedestrianSignals.BLANK);
        }
        //Re-enter the pedestriansFlash state since the countdown is not complete
        reEnterPedestriansFlash(context);
    }

    /**
     * Handles when the countdown alerting pedestrians not to cross is not complete and the state machine needs to return
     * to the pedestriansFlash state without resetting the count
     * @param context the current context.
     */
    private void reEnterPedestriansFlash(Context context) {
        System.out.println("CURRENT STATE: pedestriansFlash");
        //Entry condition for pedestriansFlash state
        System.out.println("Entry/Setting timer to 1 second");
        context.setTimer(1000);
        //Exit condition for pedestriansFlash state
        System.out.println("Exit/invoking killTimer()");
        context.killTimer();
    }
}
