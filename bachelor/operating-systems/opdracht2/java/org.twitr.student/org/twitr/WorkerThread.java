/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr;

/*
 * This class should not require changes!
 */

public class WorkerThread extends Thread {
	ThreadPool pool;

	public WorkerThread(ThreadPool pool) {
		this.pool = pool;
	}
	
	public void run() {
		while( true ) {		
			pool.waitAndHandleClient();
		}
	}
}