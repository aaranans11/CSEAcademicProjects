SYSC3303B Real-Time Concurrent Systems
Assignment 2 - Introduction to UDP
Aaranan Sathiendran - 101196339

This assignment implements a basic three part system consising of a client, an intermediate host, and a server.  The solution uses UDP and Java's DatagramPacket and DatagramSocket classes to send read or write requests tofrom the client to the intermediate host, which sends them onto the server.  The server then validates the request and sends a packet indicating a successful request back to the intermediate host, which sends it back to the client.

FILE BREAKDOWN:
There are 3 Java files:
- Client.java: contains the Client class and all its attributes and methods
- IntermediateHost.java: contains the IntermediateHost class and all its attributes and methods
- Server.java: contains the Server class and all its attributes and methods

HOW TO RUN THE PROGRAM:
To run the program within IntelliJ, first run the main() function of Server.java, then run the main() function of IntermediateHost.java, and lastly run the main() function of Client.Java.  The client will send 5 read requests, 5 write requests, and 1 invalid request to the intermediate host.  Note that the Server will terminate when it receives the 11th invalid request as per the assigment requirements, and as such logic has been added to the client to terminate when it sends an invalid request since it will hang waiting for a reply from the intermediate host.