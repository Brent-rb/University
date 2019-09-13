/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr;

import java.util.StringTokenizer;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.twitr.data.DataStore;
import org.twitr.data.Keyword;
import org.twitr.data.Message;

/*
 * The Indexer searches all incoming messages for keywords '#name'.
 * The (keyword,message) pairs are then added to the datastore.
 */

public class Indexer extends Thread {
	private DataStore datastore;
	private Pattern p = Pattern.compile("#([a-zA-Z0-9]+)");
	private ConcurrentLinkedQueue<Message> $messageList;
	
	public Indexer(DataStore datastore) {
		this.datastore = datastore;
		$messageList = new ConcurrentLinkedQueue<>();
		this.start();
	}
	
	
	//Implementatie 1
	public void process(Message msg) {
		//$messageList is a ConcurrentLinkedQueue which has thread-safe methods.
		$messageList.add(msg);
	}
	
	//Implemantatie 1
	public void run() {
		while( true ) {
			Message msg;
			//If the list is not empty, remove a message from the list.
			if(!$messageList.isEmpty()) {
				//See process Implementatie 1
				msg = $messageList.remove();
				parseMessage(msg);
			}
		}
	}
	
	
	/*
	//Implementatie 2
	public void process(Message msg) {
		//Lock our message list
		synchronized($messageList) {
			//update it
			$messageList.add(msg);
		}
	}
	
	//Implementatie 2
	public void run() {
		Message msg;
		
		while(true) {
			//We set it to null to test later (so we lock the list for as little time as possible)
			msg = null;
			
			//lock the list
			synchronized($messageList) {
				//if its not empty remove a message and store it
				if(!$messageList.isEmpty()) {
					msg = $messageList.remove();
				}
			}
			
			//Check if we actually removed a message
			if(msg != null)
				//If so, parse
				parseMessage(msg);
			//Else we sleep
			else {
				try {
					//Sleep for a short time so we dont block process
					Thread.sleep(5);
				} catch(InterruptedException ie) {
					
				}
			}
		}
	}
	*/
	
	
	private void parseMessage(Message msg) {
		// Find occurrences of #keyword
		StringTokenizer st = new StringTokenizer( msg.getText() );
	     while( st.hasMoreTokens() ) {
	    	 Matcher m = p.matcher( st.nextToken() );
	    	 if( m.matches() ) {
				System.out.println( "keyword found: " + m.group(1) );
				Keyword keyword = datastore.getOrInsertKeyword( m.group(1) );
				keyword.addMessage(msg);
			}
		}
	    
	    // Simulate complicated process
		try {
			Thread.sleep(1000);
		} catch (InterruptedException ie) {
		}	     
	}
}
