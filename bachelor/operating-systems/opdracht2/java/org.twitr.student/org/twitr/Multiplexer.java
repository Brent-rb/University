/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr;
import java.io.IOException;
import java.io.InputStream;
import java.net.*;
import java.util.*;

/*
 * The purpose of a Multiplexer is to handle a herd of Sockets
 * which will have data coming to them from lots of clients.
 *  
 * The 'demux' method finds a client that has something to say
 * and returns its socket after removing it from the queue. 
 * Remember to reinsert it afterwards!
 * 
 * This class does not require changes!
 */

public class Multiplexer {
	// How long we sleep between checking sockets for data
	static final int sleepLength = 50;

	protected Vector<Socket> sockets = new Vector<Socket>();

	// Handle a socket
	public void addSocket(Socket socket) {
		synchronized (sockets) {
			sockets.add(socket);
		}
	}

	// Get a socket that has data available
	public Socket demux() {
		while( true ) {
			synchronized (sockets) {
				// Scan sockets
				for(Iterator<Socket> i = sockets.iterator(); i.hasNext();) {
					Socket socket = i.next();
					try {
						// Check for new data
						InputStream in = socket.getInputStream();
						int bytesReady = in.available();

						// If there is data
						if (bytesReady > 0) {
							i.remove();
							return socket;
						}
					} catch( IOException ie ) {
						// Remove offending socket
						i.remove();
					}
				}
			}

			// Sleep before polling again
			try {
				Thread.sleep( sleepLength );
			} catch( InterruptedException ie ) {}
	    }
	}
}