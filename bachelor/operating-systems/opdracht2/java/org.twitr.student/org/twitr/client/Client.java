/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr.client;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/*
 * The client connects to the server with multiple threads
 * and sends messages read from a specified file.
 * 
 * This class does not require changes!
 */

public class Client extends Thread {
	Socket socket;
	static final int defaultPort = 1234;
	MessageList list;

	public Client(String host, MessageList list) throws IOException {
		this.socket = new Socket(host, defaultPort);
		this.list = list;
	}

	public void run() {
		try {
			BufferedReader in = new BufferedReader(
					new InputStreamReader(socket.getInputStream()));			
			PrintWriter out = new PrintWriter(
					socket.getOutputStream(), true /* autoFlush */);
			
			String msg;
			while( (msg = list.getMessage()) != null ) {
				System.out.println( "Msg, " + msg );
				out.println(msg);

				String resp = in.readLine();
				int count = Integer.parseInt( resp.split(" ")[0] );
				System.out.println( "Response, " + resp );
				for(int i = 0; i < count; ++i) {
					System.out.println( in.readLine() );
				}

				try {
					Thread.sleep( (int)(Math.random() * 1000) );
				} catch (InterruptedException ie) {
				}				
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String args[]) throws Exception {
		if( args.length < 3 ) {
			System.err.println("Usage: client <num threads> <filename> <server>");
			System.exit(1);
		}

		try {
			int numThreads = Integer.parseInt(args[0]);
			File file = new File(args[1]);
			if(!file.exists())
				file.createNewFile();
			MessageList list = new MessageList(file);
			
			Client clients[] = new Client[numThreads];
			for(int i = 0; i < numThreads; ++i) {
				clients[i] = new Client(args[2], list);
				clients[i].start();
			}
			
			for(int i = 0; i < numThreads; ++i) {
				clients[i].join();
			}
		} catch( IOException ie ) {
			ie.printStackTrace();			
		}
		
		System.out.println("Client end");
	}
}