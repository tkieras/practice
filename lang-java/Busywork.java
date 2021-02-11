package com.tkieras.review;

import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



public class Busywork {
    private final AtomicInteger currentMaximum;
    private boolean[] primes;
    private final int threadCount;
    private final Lock lock;

    public Busywork() {
        this(1);
    }

    public Busywork(int threadCount) {
        this.currentMaximum = new AtomicInteger(0);
        primes = new boolean[currentMaximum.get()+1];
        this.threadCount = threadCount;
        this.lock = new ReentrantLock();     
    }

    public int largestPrime(int max) {

        if (max <= 1) {
            return -1;
        }

        if (max <= currentMaximum.get()) {
            return retrieveLargestPrime(max);
        } else {
            mapPrimes(max);
            
            return retrieveLargestPrime(max);
        }
    }

    private int retrieveLargestPrime(int max) {

        for (int i=max; i >= 0; i--) {
            if (primes[i] == true) {
                return i;
            }
        }
        return -1;    
     
    }

    private void mapPrimes(int max) {
    
        boolean[] localPrime = new boolean[max+1];

        for (int i = 0; i <= max; i++) {
            localPrime[i] = true;
        }

        localPrime[0] = false;
        localPrime[1] = false;

        for (int i = 0; i <= max; i++) {
            if (localPrime[i] == true) {
                int n = i*i;
                while (n <= max && n >= 0)  {
                    localPrime[n] = false;
                    n += i;
                }
            }
        }

        lock.lock();
        currentMaximum.set(max);
        primes = localPrime;
        lock.unlock();

    }
}