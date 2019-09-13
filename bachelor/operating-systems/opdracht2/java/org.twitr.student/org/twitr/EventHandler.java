/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import org.twitr.data.*;

/*
 * The EventHandler reads events from clients and acts on them.
 * 
 * This class should not require changes!
 */

public class EventHandler {
	private DataStore datastore;

	public EventHandler(DataStore datastore) {
		this.datastore = datastore;
	}
	
	public boolean handle(Socket socket) throws IOException {
		BufferedReader in = new BufferedReader(
				new InputStreamReader(socket.getInputStream()));
		PrintWriter out = new PrintWriter(
				socket.getOutputStream(), true /* autoFlush */);
		
		String line = in.readLine();
		if( line == null )
			return false;

		line = line.trim();
		String command[] = line.split(" ", 3);
		System.out.println(socket + " said '" + line + "'");

		if( command[0].equals("say") ) {
			System.out.println("say, " +command[1] + " " + command[2]);
			User user = datastore.getOrInsertUser(command[1]);
			datastore.addMessage(user, command[2]);
			out.println( "0 " + user );
		} else if( command[0].equals("ask") ) {
			User user = datastore.getUser( command[1] );
			System.out.println("ask, " + command[1]);

			if( user != null ) {
				out.println( user.count() + " ask " );
				user.printMessages(out);
			} else {
				out.println("0 user " +command[1] + " does not exist");
			}
		} else if( command[0].equals("key") ) {
			System.out.println("key, " +command[1]);
			Keyword keyword = datastore.getKeyword( command[1] );
			if( keyword != null ) {
				out.println( keyword.count() + " key" );
				keyword.printMessages(out);		
			} else {
				out.println("0 keyword " +command[1] + " not found");
			}
		}
		
		try {
			Thread.sleep(1000);
		} catch (InterruptedException ie) {
		}
		
		return true;
	}
}