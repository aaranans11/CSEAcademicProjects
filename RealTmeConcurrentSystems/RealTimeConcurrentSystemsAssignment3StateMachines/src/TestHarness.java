/**
 SYSC3303 Assignment 3
 Aaranan Sathiendran 101196339

 The purpose of the TestHarness class is to invoke the state machine by sending events while the machine is in various
 states.
 */

public class TestHarness {

    public static void main(String[] args) throws InterruptedException {
        Context context = new Context();

        //Simulate pressing pedestrian button when state machine is in vehiclesGreen state
        Thread.sleep(5000);
        System.out.println("Invoking pedestrianWaiting() during vehiclesGreenInt state");
        context.pedestrianWaiting();

        //Simulate pressing pedestrian button when state machine is in vehiclesGreenInt state
        Thread.sleep(44000);
        System.out.println("Invoking pedestrianWaiting() during vehiclesGreenInt state");
        context.pedestrianWaiting();

        //Simulate pressing pedestrian button when state machine is in pedestriansWalk state
        Thread.sleep(5000);
        System.out.println("Invoking pedestrianWaiting() during pedestriansWalk state");
        context.pedestrianWaiting();

        //Simulate pressing pedestrian button when state machine is in pedestriansFlash state
        Thread.sleep(15000);
        System.out.println("Invoking pedestrianWaiting() during pedestriansFlash state");
        context.pedestrianWaiting();

    }
}
