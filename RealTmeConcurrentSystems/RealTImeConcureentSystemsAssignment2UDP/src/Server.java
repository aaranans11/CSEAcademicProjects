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
 * The Server class implements the server part of the 3 part UDP communication system.  It creates a DatagramSocket on port 69
 * to receive a packet from the intermediate host, waits to receive a packet from the host, and verifies that the format of the packet
 * received is valid.  If the format is valid, it prints the contents of the packet, creates a new DatagramSocket to send a
 * packet back to the intermediate host, and sends a new packet containing the information it just received back to the host.
 */
public class Server {
    DatagramPacket receivePacket, sendPacket;
    DatagramSocket receiveSocket, sendSocket;

    public Server() {
        try {
            // Construct a datagram socket and bind it to port 69
            // on the local host machine. This socket will be used to
            // receive UDP Datagram packets.
            receiveSocket = new DatagramSocket(69);

            // Construct a datagram socket and bind it to any available
            // port on the local host machine. This socket will be used to
            // send UDP Datagram packets.
            sendSocket = new DatagramSocket();
        } catch (SocketException se) {
            se.printStackTrace();
            System.exit(1);
        }
    }

    /**
     * waits to receive a packet from the host, and verifies that the format of the packet received is valid.  If the format is valid,
     * it prints the contents of the packet, creates a new DatagramSocket to send a packet back to the intermediate host, and sends a
     * new packet containing the information it just received back to the host.
     * @throws Exception
     */
    public void receiveAndSendToHost() throws Exception {
        byte[] hostBytes = new byte[100];
        receivePacket = new DatagramPacket(hostBytes, hostBytes.length);
        System.out.println("Server: Waiting for Packet.\n");

        // Block until a datagram packet is received from receiveSocket.
        try {
            System.out.println("Waiting..."); // so we know we're waiting
            receiveSocket.receive(receivePacket);
        } catch (IOException e) {
            System.out.print("IO Exception: likely:");
            System.out.println("Receive Socket Timed Out.\n" + e);
            e.printStackTrace();
            System.exit(1);
        }

        byte[] requestTypeBytes = Arrays.copyOfRange(hostBytes, 0, 2);

        //Verify that first 2 bytes are either 0 1 or 0 2
        if (requestTypeBytes[0] == 0 && (requestTypeBytes[1] == 1 || requestTypeBytes[1] == 2)) {
            System.out.println("Received packet's first 2 bytes contain valid bytes for a read or write request");
        } else {
            throw new Exception ("Error: Received packet's first 2 bytes do not contain the proper bytes for a valid read or write request");
        }

        //Verify that bytes after request type contain some text followed by a 0
        int firstZeroIndex = -1;
        for(int i = 2; i < hostBytes.length; i++) {
            if (hostBytes[i] == 0) {
                firstZeroIndex = i;
                break;
            }
        }

        if (firstZeroIndex != -1) {
            System.out.println("Bytes after request type contain some text followed by a 0");
        } else {
            throw new Exception("Error: Bytes after request type do not contain some text followed by a 0");
        }

        //Verify that bytes after first 0 contain some text followed by a 0
        int secondZeroIndex = -1;
        for(int i = firstZeroIndex + 1; i < hostBytes.length; i++) {
            if (hostBytes[i] == 0) {
                secondZeroIndex = i;
                break;
            }
        }

        if (secondZeroIndex != -1) {
            System.out.println("Bytes after first 0 type contain some text followed by another 0");
        } else {
            throw new Exception("Error: Bytes after first 0 do not contain some text followed by a 0");
        }

        //Verify that there is no other data after the second 0
        for (int i = secondZeroIndex + 1; i < hostBytes.length; i++) {
            if (hostBytes[i] != 0) {
                throw new Exception("Error: Data exists after second 0");
            }
        }
        System.out.println("No data exists after second 0");

        System.out.println("Server: Packet received:");
        System.out.println("From intermediate host: " + receivePacket.getAddress());
        System.out.println("Intermediate host port: " + receivePacket.getPort());
        int len = receivePacket.getLength();
        System.out.println("Length: " + len);
        System.out.print("Containing String: " );

        // Form a String from the byte array.
        System.out.println(new String(hostBytes,0,len));
        System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(hostBytes, 0, len)));

        // Slow things down (wait 1 second)
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e ) {
            e.printStackTrace();
            System.exit(1);
        }

        // Create a new datagram packet containing the bytes for responding to a valid read or write request.

        byte[] responseBytes = (requestTypeBytes[1] == 1) ? new byte [] { 0, 3, 0, 1 } : new byte [] { 0, 4, 0, 0 };

        sendPacket = new DatagramPacket(responseBytes, responseBytes.length,
                receivePacket.getAddress(), receivePacket.getPort());

        System.out.println("Server: Sending packet:");
        System.out.println("To intermediate host: " + sendPacket.getAddress());
        System.out.println("Destination host port: " + sendPacket.getPort());
        len = sendPacket.getLength();
        System.out.println("Length: " + len);
        System.out.print("Containing string: ");
        System.out.println(new String(sendPacket.getData(),0,len));
        System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(responseBytes, 0, len)));

        // Send the datagram packet to the client via the send socket.
        try {
            sendSocket.send(sendPacket);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        System.out.println("Server: packet sent");
        // We're finished, so close the sockets.
        sendSocket.close();
        receiveSocket.close();
    }

    public static void main(String[] args) throws Exception {
        while (true) {
            Server s = new Server();
            s.receiveAndSendToHost();
        }
    }

}
