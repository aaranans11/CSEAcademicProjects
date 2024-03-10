/*
SYSC3303B Real-Time Concurrent Systems
Assignment 2 - Introduction to UDP
Aaranan Sathiendran - 101196339
 */

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.Arrays;

/**
 * The IntermediateHost class implements the intermediate host part of the 3 part UDP communication system.  It creates a DatagramSocket to send
 * on port 23 to receive a packet from the client, waits to receive a packet from the client, and prints its contents.  It then creates a new
 * packet to send exactly what it received from the client to the server via another DatagramSocket on port 69, and waits to receive
 * a packet back from the server. Once it does, it creates another packet containing what it received from the server and sends it back to the
 * client.
 */
public class IntermediateHost {
    DatagramPacket receiveClientPacket, sendServerPacket, receiveServerPacket, sendClientPacket;
    DatagramSocket clientSendReceiveSocket, serverSendReceiveSocket;

    public IntermediateHost() {
        try {
            // Construct a datagram socket and bind it to port 23
            // on the local host machine. This socket will be used to
            // send and receive UDP Datagram packets from the client.
            clientSendReceiveSocket = new DatagramSocket(23);

            // Construct a datagram socket and bind it to any available
            // port on the local host machine. This socket will be used to
            // send and receive UDP Datagram packets from the server.
            serverSendReceiveSocket = new DatagramSocket();

        } catch (SocketException se) {
            se.printStackTrace();
            System.exit(1);
        }
    }

    /**
     * Waits to receive a packet from the client, and prints its contents.  Then creates a new packet to send exactly what it received from the client
     * to the server via another DatagramSocket on port 69, and waits to receive a packet back from the server. Once it does, it creates another packet
     * containing what it received from the server and sends it back to the client.
     */
    public void receiveAndSendToServerAndClient() {
            // Construct a DatagramPacket for receiving packets up
            // to 100 bytes long (the length of the byte array) from the client.

            byte[] clientBytes = new byte[100];
            receiveClientPacket = new DatagramPacket(clientBytes, clientBytes.length);
            System.out.println("Intermediate host: Waiting for Packet from client.\n");

            // Block until a datagram packet is received from clientSendReceiveSocket.
            try {
                System.out.println("Waiting..."); // so we know we're waiting
                clientSendReceiveSocket.receive(receiveClientPacket);
            } catch (IOException e) {
                System.out.print("IO Exception: likely:");
                System.out.println("Client Receive Socket Timed Out.\n" + e);
                e.printStackTrace();
                System.exit(1);
            }

            // Process the received datagram.
            System.out.println("Intermediate Host: Packet received:");
            System.out.println("From client: " + receiveClientPacket.getAddress());
            System.out.println("CLient port: " + receiveClientPacket.getPort());
            int clientLen = receiveClientPacket.getLength();
            System.out.println("Length: " + clientLen);
            System.out.print("Containing String: " );

            // Form a String from the byte array.
            System.out.println(new String(clientBytes,0, clientLen));
            System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(clientBytes, 0, clientLen)));

            // Slow things down (wait 1 second)
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e ) {
                e.printStackTrace();
                System.exit(1);
            }

            // Create a new datagram packet containing the string received from the client.

            sendServerPacket = new DatagramPacket(clientBytes, receiveClientPacket.getLength(),
                    receiveClientPacket.getAddress(), 69);

            System.out.println("Intermediate Host: Sending packet to server:");
            System.out.println("To host: " + sendServerPacket.getAddress());
            System.out.println("Destination host port: " + sendServerPacket.getPort());
            clientLen = sendServerPacket.getLength();
            System.out.println("Length: " + clientLen);
            System.out.print("Containing string: ");
            System.out.println(new String(sendServerPacket.getData(),0, clientLen));
            System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(clientBytes, 0, clientLen)));


            // Send the datagram packet to server socket via the serverSendReceiveSocket.
            try {
                serverSendReceiveSocket.send(sendServerPacket);
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

            System.out.println("Intermediate host: packet sent to server");

            // Wait for response from server
            byte[] serverBytes = new byte[100];
            receiveServerPacket = new DatagramPacket(serverBytes, serverBytes.length);
            System.out.println("Intermediate host: Waiting for Packet from server.\n");

            // Block until a datagram packet is received from the serverSendReceiveSocket.
            try {
                System.out.println("Waiting..."); // so we know we're waiting
                serverSendReceiveSocket.receive(receiveServerPacket);
            } catch (IOException e) {
                System.out.print("IO Exception: likely:");
                System.out.println("Receive Socket Timed Out.\n" + e);
                e.printStackTrace();
                System.exit(1);
            }

            // Process the received datagram.
            System.out.println("Intermediate host: Packet received:");
            System.out.println("From server: " + receiveServerPacket.getAddress());
            System.out.println("Server port: " + receiveServerPacket.getPort());
            int serverLen = receiveServerPacket.getLength();
            System.out.println("Length: " + serverLen);
            System.out.print("Containing string: " );

            // Form a String from the byte array.
            System.out.println(new String(serverBytes,0,serverLen));
            System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(serverBytes, 0, serverLen)));


            // Slow things down (wait 1 second)
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e ) {
                e.printStackTrace();
                System.exit(1);
            }

            // Create a new datagram packet containing the string received from the server.

            sendClientPacket = new DatagramPacket(serverBytes, receiveServerPacket.getLength(),
                    receiveServerPacket.getAddress(), receiveClientPacket.getPort());

            System.out.println("Intermediate host: Sending packet to server:");
            System.out.println("To client: " + sendClientPacket.getAddress());
            System.out.println("Destination host port: " + receiveClientPacket.getPort());
            serverLen = sendClientPacket.getLength();
            System.out.println("Length: " + serverLen);
            System.out.print("Containing string: ");
            System.out.println(new String(sendClientPacket.getData(),0,serverLen));
            System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(serverBytes, 0, serverLen)));

            // Send the datagram packet to the client via the clientSendReceiveSocket.
            try {
                clientSendReceiveSocket.send(sendClientPacket);
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(1);
            }

            System.out.println("Intermediate host: packet sent");
            // We're finished, so close the sockets.
            clientSendReceiveSocket.close();
            serverSendReceiveSocket.close();
        }

    public static void main( String[] args ) {
        while (true) {
            IntermediateHost intermediateHost = new IntermediateHost();
            intermediateHost.receiveAndSendToServerAndClient();
        }
    }
}
