package com.tkieras.review;


import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

import java.lang.Thread.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;


public class LockConditionExample {

    public static void test(int producerThreadCount, int consumerThreadCount) {
        Thread[] producers = new Thread[producerThreadCount];
        Thread[] consumers = new Thread[consumerThreadCount];

        LockConditionExample queue = new LockConditionExample(100);

        for(int i = 0; i < producerThreadCount; i++) {
            producers[i] = new Thread(new Runnable() {
                @Override public void run() {
                    NumberMaker maker = new NumberMaker();

                    while(!Thread.currentThread().isInterrupted()) {

                        int bigNumber = maker.make();
                        System.out.printf("\t%s: %d\n", Thread.currentThread().toString(), bigNumber);     
                        queue.add(bigNumber);
                    
                    }
                }
            });
        }

        Busywork work = new Busywork();
       
        for (int i = 0; i < consumerThreadCount; i++) {
            consumers[i] = new Thread(new Runnable() {
                @Override public void run() {
                    
                    while(!Thread.currentThread().isInterrupted()){
                        
                        int bigNumber = queue.remove();   
                        int bigPrime = work.largestPrime(bigNumber);
                        System.out.printf("%s: %d -> %d\n", Thread.currentThread().toString(), bigNumber, bigPrime);
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
        }

    }
    private final int[] array;
    private final Lock monitor;
    private final Condition emptyCondition;
    private final Condition fullCondition;
    private int index;

    public LockConditionExample(int size) {
        this.array = new int[size];
        this.monitor = new ReentrantLock();
        this.emptyCondition = monitor.newCondition();
        this.fullCondition = monitor.newCondition();
        index = 0;
    }

    public int add(int toAdd){
        monitor.lock();
        try {
            while(index == array.length - 1) {
                fullCondition.await();
            }
            array[index++] = toAdd;
            emptyCondition.signalAll();
        } catch (InterruptedException ioe) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(ioe);
        } finally {
            monitor.unlock();
        }
        return toAdd;
    }

    public int remove() {
        monitor.lock();
        try {
            while (index <= 0) {
                emptyCondition.await();
            }
            int removed = array[--index];
            array[index] = -1;
            fullCondition.signalAll();
            return removed;
        } catch (InterruptedException ioe) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(ioe);
        } finally {
            monitor.unlock();
        }
    }
}