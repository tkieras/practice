package com.tkieras.review;

import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.*;

public class ExecutorExample {

    public static void test(int producerThreadCount, int consumerThreadCount) {
        ExecutorService producers = Executors.newFixedThreadPool(producerThreadCount);

        ExecutorService consumers = Executors.newFixedThreadPool(consumerThreadCount);
        NumberMaker maker = new NumberMaker();
        Busywork work = new Busywork();

        for (int i = 0; i < producerThreadCount; i++) {
            
            producers.submit(new Runnable() {
                @Override public void run() {
                    int bigNumber = maker.make();
                    System.out.printf("\t%s: %d\n", Thread.currentThread().toString(), bigNumber);
                    consumers.submit(new Runnable() {
                        @Override public void run() {
                            
                            int bigPrime = work.largestPrime(bigNumber);
                            System.out.printf("%s: %d -> %d\n", Thread.currentThread().toString(), bigNumber, bigPrime);
                        }
                    });
                    producers.submit(this);
                    try {
                        Thread.sleep(10L);
                    } catch (InterruptedException ioe) {
                        producers.shutdownNow();
                        consumers.shutdownNow();
                    }
                }
            });
        }


        while(!consumers.isTerminated()) {
            try {
                Thread.sleep(100L);
            } catch (InterruptedException ioe) {
                consumers.shutdownNow();
            }
        }
    }
}