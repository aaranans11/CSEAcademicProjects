/**
 * Chef is the class for each of the chef threads.  Each chef has an ingredient attribute
 * to represent the ingredient they are responsible for.  Each chef also has a table object
 * that it shares with the other chefs and the agent to act as a shared buffer for the ingredients.
 *
 * Chef has a method run(), within which it calls makeSandwich() from the table class, which takes
 * the ingredients on the table and makes a sandwich, signaling the agent on completion.  The chef
 * thread will continue running/making sandwiches until 20 sandwiches have been made. The ingredient
 * associated with the chef and the table object to share are to be passed down as parameters when
 * creating a new chef thread.
 */
class Chef implements Runnable {

    /**
     * Represents the ingredient the chef is responsible for/has an infinite supply of.
     */
    private final String ingredient;
    /**
     * A table object that the chef shares with the other chefs and the agent to act as a shared buffer
     * for the ingredients.
     */
    private Table table;

    /**
     * Creates a new chef object and sets the ingredient it is responsible for as well as the table object
     * to share with the other chefs and the agent.
     *
     * @param ingredient The ingredient the chef is responsible for/has an infinite supply of.
     * @param table A table object that the chef shares with the other chefs and the agent to act as a shared buffer for the ingredients.
     */
    public Chef(String ingredient, Table table) {
        this.ingredient = ingredient;
        this.table = table;
    }

    /**
     * Overrides the thread's run() method to implement the run functionality for the chef.  The
     * function repeatedly calls makeSandwich() from the table class, which takes the ingredients
     * on the table and makes a sandwich, signaling the agent on completion.  The function runs
     * until 20 sandwiches have been made.
     */
    public void run() {
        while(table.getNumSandwichesCreated() < 20) {
            //Repeatedly call makeSandwich() until 20 sandwiches have been made
            table.makeSandwich(ingredient);
            //Sleep statement added for debugging/code tracking purposes
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        //TEST
        System.out.println("Exiting " + ingredient + " chef thread");
    }
}
