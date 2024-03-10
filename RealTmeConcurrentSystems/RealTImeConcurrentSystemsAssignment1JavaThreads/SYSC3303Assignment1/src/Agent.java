/**
 * Agent is the class for the agent thread.  Each agent has a table object that it shares with the
 * other chefs and the agent to act as a shared buffer for the ingredients.
 *
 * The agent has a method run(), within which it calls addIngredientsToTable() from the table class, which
 * randomly selects 2 potential ingredients and puts them on the table, notifying all the chefs so that
 * they can take them and make a sandwich. The agent will continue putting ingredients on the table 20
 * times to ensure 20 sandwiches are made.
 */
class Agent implements Runnable {
    /**
     * A table object that the chef shares with the other chefs and the agent to act as a shared buffer
     * for the ingredients.
     */
    private Table table;

    /**
     * Creates a new agent object and sets the table object to share with the other chefs and the agent.
     * @param table A table object that the chef shares with the other chefs and the agent to act as a shared buffer for the ingredients.
     */
    public Agent(Table table) {
        this.table = table;
    }

    /**
     * Overrides the thread's run() method to implement the run functionality for the agent.  The
     * function repeatedly calls addIngredientsToTable() from the table class, which randomly selects 2 potential
     * ingredients and puts them on the table, notifying all the chefs so that they can take them and make a
     * sandwich.  The function puts ingredients on the table 20 times.
     */
    public void run() {
        for (int i = 0; i < 20; i++) {
            //TEST
            System.out.println(Thread.currentThread().getName() + " adding ingredients to table");
            //Repeatedly add ingredients to the table
            table.addIngredientsToTable();
            //Sleep statement added for debugging/code tracking purposes
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        System.out.println("Exiting agent thread");
    }
}
