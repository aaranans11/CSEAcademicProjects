import java.util.*;

/**
 * Table is the class that represents an object similar to a shared buffer where chefs and agents
 * can put and take ingredients.  The table class has an int TABLE_SIZE to specify the number of
 * ingredients that should be on a table.  It also has an ArrayList potentialIngredients to represent
 * a list of all the ingredients that the agent can randomly select and put on the table.  It also has
 * a separate ArrayList tableIngredients to represent the ingredients that are currently on the table.
 * It also has an Integer numSandwichesCreated that tracks the number of sandwiches that have been created.
 *
 * The table has a method getNumSandwichesCreated(), which returns the number of sandwiches created.  It also
 * has a method addIngredientsToTable(), which shuffles the ArrayList of potential ingredients, randomly selects
 * 2 and puts them on the table, notifying all the chefs so that they can take them and make a sandwich.  It also
 * has a method makeSandwich(), which takes the ingredients on the table and makes a sandwich, signaling the agent
 * on completion.
 */
public class Table {

    /**
     * Specifies the number of ingredients that should be on the table.
     */
    private static final int TABLE_SIZE = 2;
    /**
     * Represents a list of all the ingredients that the agent can randomly select and put on the table.
     */
    private static final ArrayList<String> potentialIngredients = new ArrayList<>(Arrays.asList("bread", "peanut butter", "jam"));
    /**
     * Represents the ingredients that are currently on the table.
     */
    private ArrayList<String> tableIngredients = new ArrayList<>();
    /**
     * Tracks the number of sandwiches that have been created.
     */
    private Integer numSandwichesCreated = 0;

    /**
     * Returns the number of sandwiches that have been created.
     * @return numSandwichesCreated the number of sandwiches that have been created
     */
    public Integer getNumSandwichesCreated() {
        return numSandwichesCreated;
    }

    /**
     * Shuffles the ArrayList of potential ingredients, randomly selects 2 and puts them on the table,
     * notifying all the chefs so that they can take them and make a sandwich.
     */
    public synchronized void addIngredientsToTable() {
        //Continue to wait while there are already 2 ingredients on the table until a chef takes them
        while(tableIngredients.size() == TABLE_SIZE) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        //TEST
//        System.out.println("Current list of potential ingredients: \n" + potentialIngredients);
        //Shuffle the ArrayList of potentialIngredients to randomize the ingredients to be put on the table
        Collections.shuffle(potentialIngredients);
        //TEST
//        System.out.println("Shuffled list of potential ingredients: \n" + potentialIngredients);
        //Select the first 2 ingredients from potentialIngredients and put them on the table
        tableIngredients.add(potentialIngredients.get(0));
        tableIngredients.add(potentialIngredients.get(1));

        //TEST
        System.out.println("Current list of ingredients on table: \n" + tableIngredients);
        //Notify all the chef threads that they can now take ingredients from the table
        notifyAll();
    }

    /**
     * Takes the ingredients on the table and makes a sandwich, signaling the agent on completion.
     * @param chefIngredient the missing ingredient the chef is waiting to add to complete a sandwich
     */
    public synchronized void makeSandwich(String chefIngredient) {
        /*
         * Continue to wait while the table is empty or the table already contains the ingredient the chef is responsible for
         * (if the chef's ingredient is already on the table, then it is impossible for the combination of ingredients on the
         * table to be the right combination the chef needs to complete a sandwich)
         */
        while(tableIngredients.isEmpty() | tableIngredients.contains(chefIngredient)) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
            /* If 20 sandwiches have already been made, then stop waiting for more ingredients to be added to the table
             * /stop making more sandwiches and return
             */
            if (getNumSandwichesCreated() == 20) {
                return;
            }
        }

        //TEST
        System.out.println("Ingredient " + chefIngredient + " added to make a sandwich");
        //Clear the ingredients on the table to represent the fact that the chef took the ingredients to make a sandwich
        tableIngredients.clear();
        //Increment the number of sandwiches that have been created to ensure the program stops when 20 have been made
        numSandwichesCreated++;
        //TEST
        System.out.println("Number of sandwiches created: " + numSandwichesCreated);
        System.out.println("New list of ingredients on table: \n" + tableIngredients);
        //Notify all other threads that they can now put/take ingredients from the table
        notifyAll();

    }
}

