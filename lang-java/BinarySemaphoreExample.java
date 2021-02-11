package com.tkieras.review;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.Semaphore;
import java.lang.Thread.*;
import java.util.Queue;
import java.util.LinkedList;

public class BinarySemaphoreExample {

    public static void test(int producerThreadCount, int consumerThreadCount) {
        Thread[] producers = new Thread[producerThreadCount];
        Thread[] consumers = new Thread[consumerThreadCount];

        Queue<Integer> queue = new LinkedList<Integer>();
        Semaphore semaphore = new Semaphore(1, true);

        for(int i = 0; i < producerThreadCount; i++) {
            producers[i] = new Thread(new Runnable() {
                @Override public void run() {
                    NumberMaker maker = new NumberMaker();
                    boolean insertSucceeded = false;
                    int bigNumber = maker.make();

                    while(!Thread.currentThread().isInterrupted()) {
                        if (insertSucceeded){
                            bigNumber = maker.make();
                        }
                        System.out.printf("\t%s: %d\n", Thread.currentThread().toString(), bigNumber);
                        try {
                            semaphore.acquire();
                            insertSucceeded = queue.offer(bigNumber);
                        } catch (InterruptedException ioe) {
                            return;
                        } finally {
                            semaphore.release();
                        }
                    }
                }
            });
        }

        Busywork work = new Busywork();
        for (int i = 0; i < consumerThreadCount; i++) {
            consumers[i] = new Thread(new Runnable() {
                @Override public void run() {
                    
                    while(!Thread.currentThread().isInterrupted()){
                        try{
                            semaphore.acquire();
                            Integer bigNumber;
                            try {
                                bigNumber = queue.poll();
                            } finally {
                                semaphore.release();
                            }
                            if (bigNumber != null) {
                                int bigPrime = work.largestPrime(bigNumber);
                                System.out.printf("%s: %d -> %d\n", Thread.currentThread().toString(), bigNumber, bigPrime);
                            }
                            
                        } catch (InterruptedException ioe) {
                            return;
                        }
                    }
                }
            });
        }

        for (Thread thread : producers) {
            if (thread != null) {
                thread.start();
            }
        }
        for (Thread thread: consumers) {
            if (thread != null) {
                thread.start();
            }
        }

        try {
            Thread.sleep(100L);
        } catch (InterruptedException ioe) {
            for (Thread thread : producers) {
                if (thread != null) {
                    thread.interrupt();
                }
            }
            for (Thread thread : consumers) {
                if (thread != null) {
                    thread.interrupt();
                }
            }
            throw new RuntimeException(ioe);
        }

    }
}