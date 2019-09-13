/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr;

import java.io.*;
import java.net.*;

import org.twitr.data.*;

/*
 * Server framework for our multiplexers. This class does the work of
 * listening on a socket, handing connections over to a multiplexer.
 *
 * This class does not require changes!
 */

public class Server {
	static final int defaultPort = 1234;
	static final int poolSize = 4;

	// The Multiplexer we use for all our reading from Clients
	private Multiplexer mux;

	// Wait for connections with this
	protected ServerSocket ss;

	// Start a background thread here
	public Server(int port, Multiplexer mux) throws Exception {
		this.mux = mux;
		ss = new ServerSocket(port);
	}

	public void close() throws IOException {
		ss.close();
		ss = null;
	}

	// Listen for new connections; when they come in, hand them over to Multiplexer
	public void listen() {
		System.out.println("Listening....");
		try {
			while (true) {
				// Get a connection
				Socket socket = ss.accept();
				System.out.println("Connection from " + socket);

				// Hand it over
				mux.addSocket(socket);
			}
			// Deal with socket problems
		} catch (IOException ioe) {
			System.err.println("Exception in listening on " + ss + ": " + ioe);
		} finally {
			try {
				close();
			} catch (IOException ioe) {
				System.err.println("Can't close " + ss + ": "
						+ ioe.getMessage());
			}
		}
	}


	// Usage: java Server <portnum>
	public static void main(String args[]) throws Exception {
		DataStore datastore = new DataStore();
		Indexer indexer = new Indexer(datastore);
		datastore.setIndexer(indexer);

		Multiplexer mux = new Multiplexer();
		EventHandler eh = new EventHandler(datastore);
		ThreadPool pool = new ThreadPool(mux, eh);
		pool.spawn(poolSize);
		StringBuilder string = new StringBuilder();
		string.append(true);
		

		// Start server and get it listening for new connections
		int port = defaultPort;
		if( args.length > 2 )
			port = Integer.parseInt(args[1]);
		Server server = new Server(port, mux);
		server.listen();
	}
}
