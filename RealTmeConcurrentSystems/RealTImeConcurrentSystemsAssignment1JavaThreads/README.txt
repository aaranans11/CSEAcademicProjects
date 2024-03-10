Real-Time Concurrent Systems
Assignment 1 - Java Threads

This assignment implements a solution for the Sandwich Making Chefs Problem by implementing a monitor that synchronizes the agent and chefs.  The solution follows a pattern similar to a traditional producer/consumer problem where the Table object acts as a shared buffer, the Agent acts as the producer by putting ingredients onto the table, and the Chefs act as consumers by taking ingredients from the table.

FILE BREAKDOWN:
Within the src folder, there are 4 Java files:
- Agent.java: contains the Agent class and all its attributes and methods
- Chef.java: contains the Chef class and all its attributes and methods
- Table.java: contains the Table class and all its attributes and methods
- Main.java: contains the source code needed to create the 3 chef threads and 1 agent thread, and start them to complete the execution of the program

HOW TO RUN THE PROGRAM:
To run the program within IntelliJ, run Main.java (CTRL + R or click the 'Run Main' button within IntelliJ).  Once the program starts running, the terminal output will show when the agent is adding ingredients, what ingredients are being added/what is currently on the table, and which chef is taking the ingredients from the table to make a sandwich.  The output will repeat until 20 sandwiches have been made, at which point the chef and agent threads will terminate.