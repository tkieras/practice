package com.tkieras.review;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.*;

public class ExecutorLambdaExample {

    public static void test(int producerThreadCount, int consumerThreadCount) {
        ExecutorService producers = Executors.newFixedThreadPool(producerThreadCount);

        ExecutorService consumers = Executors.newFixedThreadPool(consumerThreadCount);
        NumberMaker maker = new NumberMaker();

        Runnable producer = () -> {
            int bigNumber = maker.make();
            System.out.printf("\t%s: %d\n", Thread.currentThread().toString(), bigNumber);

            Runnable consumer = () -> {
                Busywork work = new Busywork();
                int bigPrime = work.largestPrime(bigNumber);
                System.out.printf("%s: %d -> %d\n", Thread.currentThread().toString(), bigNumber, bigPrime);
            };

            consumers.submit( consumer );

            try {
                Thread.sleep(10L);
            } catch (InterruptedException ioe) {
                producers.shutdownNow();
                consumers.shutdownNow();
            }
        };

        while(!Thread.currentThread().isInterrupted()) {
            producers.submit( producer );
            try {
                Thread.sleep(10L);
            } catch (InterruptedException ioe) {
                Thread.currentThread().interrupt();
            }
        }

        producers.shutdownNow();
        consumers.shutdownNow();
    
    }
}