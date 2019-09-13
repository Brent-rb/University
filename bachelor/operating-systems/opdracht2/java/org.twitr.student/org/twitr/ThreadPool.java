/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */

package org.twitr;
import java.io.IOException;
import java.net.Socket;

/*
 * The ThreadPool should work like taxis at an airport: a number of taxis wait
 * for clients to arrive. A client always takes the first taxi (the �leader�), 
 * and this taxi will �handle� the client. Next, another taxi becomes the new 
 * leader, and will handle the next client. This system allows for quick and 
 * efficient processing of clients.
 */

public class ThreadPool {
	private Multiplexer mux;
	private EventHandler handler;

	public ThreadPool(Multiplexer mux, EventHandler handler) {
		this.mux = mux;
		this.handler = handler;
	}
	
	/*
	 * Threads call 'waitAndHandleClient' to wait for and demultiplex incoming events
	 */
	public void waitAndHandleClient() {
	    /* .... */
		System.out.println(Thread.currentThread() + " is new leader");
		/* .... */
		Socket socket = mux.demux(); // Wait for a client to act
		/* .... */
		try {
			System.out.println(Thread.currentThread() + " is handling " + socket);
			if( handler.handle(socket) )  // Process one request from client
				mux.addSocket(socket);  // Reinsert client into multiplexer if still active
		} catch( IOException ie ) {
			System.err.print(ie);
		}
		/* .... */
	}

	public void spawn(int size) {
		for(int i = 0; i < size; ++i)
			new WorkerThread(this).start();
	}
}