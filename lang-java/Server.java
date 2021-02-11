package com.tkieras.socket;

import java.io.IOException;

import java.nio.channels.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;



public class Server {
    public static final String SERVER_HOST = "localhost";

    public static final int SERVER_PORT = 8080;

    private static final String MESSAGE_BASE = "reply ";

    public static void main(String[] args) {
        if (args == null) {
            throw new IllegalArgumentException();
        }

        Server server = new Server(1);
        server.start();
    }

    private final int serverId;
    public Server(int serverId) {
        this.serverId = serverId;
    }

    public void start() {
        try {
            ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
            serverSocketChannel.socket().bind(new InetSocketAddress(SERVER_HOST, SERVER_PORT));
            System.out.println("Server ready...");

            while(true){
                try(SocketChannel channel = serverSocketChannel.accept()){
                    System.out.println("Accepted a connection!");
                    ByteBuffer buffer = ByteBuffer.allocate(2048);

                    while (channel.read(buffer) > 0) {

                        String received = new String(buffer.array(), StandardCharsets.UTF_8);
                        System.out.printf("Server received: %s\n", received);
                        buffer.clear();

                        String serverResponse = "server responds";
                        byte[] message = serverResponse.getBytes();
                        ByteBuffer outSend = ByteBuffer.wrap(message);

                        channel.write(outSend);
                        buffer.clear();
                    }
                } catch (IOException ioe) {
                    throw new RuntimeException();
                }
    
            }
            

        } catch (IOException ioe) {
            throw new RuntimeException();
        }
        
    }
    
}