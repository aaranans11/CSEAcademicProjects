/**
 * Main is the class for creating and starting the execution of the 3 chef threads and the agent thread.
 */
public class Main {

    /**
     * Creates and starts the execution of the 3 chef threads and the agent thread
     */
    public static void main(String[] args) {
        Thread agent, breadChef, peanutButterChef, jamChef;
        //Create new Table object to act as shared buffer to be shared between chefs and agent
        Table table = new Table();

        //Create agent thread and 3 chef threads, 1 for each ingredient
        agent = new Thread(new Agent(table), "Agent");
        breadChef = new Thread(new Chef("bread", table), "Bread chef");
        peanutButterChef = new Thread(new Chef("peanut butter", table), "Peanut butter chef");
        jamChef = new Thread(new Chef("jam", table), "Jam chef");

        //Start threads
        agent.start();
        breadChef.start();
        peanutButterChef.start();
        jamChef.start();
    }
}