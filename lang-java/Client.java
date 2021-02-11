package com.tkieras.socket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

import java.net.Socket;

import java.nio.channels.*;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;


public class Client {
    private static final int NUM_REQUESTS = 5;

    public static final String SERVER_HOST = "localhost";

    public static final int SERVER_PORT = 8080;

    public static void main(String[] args) {
        if (args == null) {
            throw new IllegalArgumentException();
        }

        Client client = new Client(42);
        client.start();
    }

    private final int clientId;
    private final Socket socket;
    private final InputStream in;
    private final OutputStream out;

    public Client(int clientId){
        this.clientId = clientId;
        try{
            socket = new Socket(SERVER_HOST, SERVER_PORT);
            System.out.println("Connected...");
            this.in = socket.getInputStream();
            this.out = socket.getOutputStream();
        } catch (IOException ioe) {
            throw new RuntimeException();
        }

    }

    public void start() {

        String messageBase = "message";

        for (int i=0; i<NUM_REQUESTS; i++) {
            String message = messageBase + " " + i + " from client " + clientId + "\n";
            send(message);
            String received = receive();
            //System.out.printf("Received: %s\n", received);
        }

    }

    private void send(String message) {
        try{
            out.write(message.getBytes("UTF-8"));
            out.flush();
        } catch (IOException ioe) {
            throw new RuntimeException();
        }
    }

    private String receive() {
        //byte[] buffer = new byte[2048];
        ByteBuffer byteBuffer = ByteBuffer.allocate(256);
        byte[] byteArray = new byte[byteBuffer.limit()];

       try{
        in.read(byteArray);

        String string = new String(byteArray).trim();
        System.out.println(string);

            
        return "nothing";

        } catch (IOException ioe) {
           throw new RuntimeException();
        }
    }
    
}