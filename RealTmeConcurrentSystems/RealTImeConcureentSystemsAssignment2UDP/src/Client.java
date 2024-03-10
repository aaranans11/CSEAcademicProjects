/*
SYSC3303B Real-Time Concurrent Systems
Assignment 2 - Introduction to UDP
Aaranan Sathiendran - 101196339
 */

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

/**
 * The Client class implements the client part of the 3 part UDP communication system.  It creates a DatagramSocket to send
 * Either a read or write request containing a filename converted from a string to bytes and a mode.  It then sends the
 * packet to port 23 on the intermediate host, and waits for it to send a packet back and print its contents.
 */
public class Client {
    DatagramPacket sendPacket, receivePacket;
    DatagramSocket sendReceiveSocket;

    public Client() {
        try {
            // Construct a datagram socket and bind it to any available
            // port on the local host machine. This socket will be used to
            // send and receive UDP Datagram packets.
            sendReceiveSocket = new DatagramSocket();
        } catch (SocketException se) {   // Can't create the socket.
            se.printStackTrace();
            System.exit(1);
        }
    }

    /**
     * Sends either a read or write request containing a filename converted from a string to bytes and a mode.  Then sends
     * the packet to port 23 on the intermediate host, and waits for it to send a packet back and print its contents.
     * @param requestTypeBytes a byte array containing whether the request is a read request (0 1) or write request (0 2)
     */
    public void sendToIntermediateHostAndReceive(byte[] requestTypeBytes) {
        // Prepare a DatagramPacket and send it via sendReceiveSocket
        // to port 23 on the intermediate host.
        String strFilename = "test.txt";

        //Convert file name to bytes
        byte[] stringBytes = strFilename.getBytes(StandardCharsets.UTF_8);

        //Create '0' byte to be added between file name and mode as well as at the end of the packet
        byte[] zeroByte = new byte[] { 0x00 };

        String mode = "netascii";
        //Convert mode string to bytes
        byte[] modeBytes = mode.getBytes();

        //Add all components to be sent in the packet to one byte array
        ByteBuffer combinedByteBuffer = ByteBuffer.allocate(requestTypeBytes.length + stringBytes.length + zeroByte.length + modeBytes.length + zeroByte.length);
        combinedByteBuffer.put(requestTypeBytes);
        combinedByteBuffer.put(stringBytes);
        combinedByteBuffer.put(zeroByte);
        combinedByteBuffer.put(modeBytes);
        combinedByteBuffer.put(zeroByte);

        byte [] packetBytes = combinedByteBuffer.array();

        System.out.println("Client: sending a packet containing:\n" + Arrays.toString(packetBytes));

        // Construct a datagram packet that is to be sent to port 23 on the intermediate host.
        try {
            sendPacket = new DatagramPacket(packetBytes, packetBytes.length,
                    InetAddress.getLocalHost(), 23);
        } catch (UnknownHostException e) {
            e.printStackTrace();
            System.exit(1);
        }

        System.out.println("Client: Sending packet:");
        System.out.println("To intermediate host: " + sendPacket.getAddress());
        System.out.println("Destination host port: " + sendPacket.getPort());
        int len = sendPacket.getLength();
        System.out.println("Length: " + len);
        System.out.print("Containing string: ");
        System.out.println(new String(sendPacket.getData(),0,len));
        System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(packetBytes, 0, len)));

        // Send the datagram packet to the server via the send/receive socket.

        try {
            sendReceiveSocket.send(sendPacket);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        System.out.println("Client: Packet sent.\n");

        // For the sake of the assignment requirements, implement a condition where the client will terminate when an invalid
        // request is sent (otherwise it will just hang because per the assignment requirements, the server will throw an
        //Exception and quit when an invalid request is received)
        if (!(Arrays.equals(requestTypeBytes, new byte[]{0, 1}) || Arrays.equals(requestTypeBytes, new byte[]{0, 2}))) {
            System.out.println("Invalid request sent; client will now terminate as the host and server will never send a packet back");
            sendReceiveSocket.close();
            System.exit(1);
        }

        // Construct a DatagramPacket for receiving packets up
        // to 100 bytes long (the length of the byte array).

        byte[] recieveData = new byte[100];
        receivePacket = new DatagramPacket(recieveData, recieveData.length);

        try {
            // Block until a datagram is received via sendReceiveSocket.
            sendReceiveSocket.receive(receivePacket);
        } catch(IOException e) {
            e.printStackTrace();
            System.exit(1);
        }

        // Process the received datagram.
        System.out.println("Client: Packet received:");
        System.out.println("From host: " + receivePacket.getAddress());
        System.out.println("Host port: " + receivePacket.getPort());
        len = receivePacket.getLength();
        System.out.println("Length: " + len);
        System.out.print("Containing string: ");

        // Form a String from the byte array.
        String received = new String(recieveData,0,len);
        System.out.println(received);
        System.out.println("Containing bytes: " + Arrays.toString(Arrays.copyOfRange(recieveData, 0, len)));
        // We're finished, so close the socket.
        sendReceiveSocket.close();
    }

    public static void main(String[] args)
    {
        // First 2 bytes (0 1) for a read request
        byte[] readByte = new byte[] { 0, 1 };
        // First 2 bytes (0 2) for a write request
        byte[] writeByte = new byte[] { 0, 2 };

        //Alternate between sending a read and write request 10 times (5 requests each)
        for(int i = 0; i < 10; i++) {
            Client c = new Client();
            if ((i % 2 == 0)) {
                c.sendToIntermediateHostAndReceive(readByte);
            } else {
                c.sendToIntermediateHostAndReceive(writeByte);
            }
        }
        //Send one invalid request
        Client c = new Client();
        c.sendToIntermediateHostAndReceive(new byte[] {1, 1});
    }

}


