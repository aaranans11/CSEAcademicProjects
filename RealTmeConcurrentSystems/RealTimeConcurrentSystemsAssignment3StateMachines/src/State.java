/**
SYSC3303 Assignment 3
Aaranan Sathiendran 101196339

The purpose of the state interface is to provide each state with a base interface that other states within the machine
can then implement to define state-specific behaviour for each state.
 */

public interface State {

    /**
     * Handles the event that occurs when a pedestrian presses the button and is now waiting at the crossing.
     * @param context the current context.
     */
    public void pedestrianWaiting(Context context);

    /**
     * Handles the event that occurs when a timeout occurs after killTimer().
     * @param context the current context.
     */
    public void timeout(Context context);
}
