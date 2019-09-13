/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */

package org.twitr.data;

import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Keyword {
	private String name;
	//Unfortunatly there is no ConcurrentList implementation here
	//Different threads can add a message to the same keyword so we need to make this threadsafe
	private LinkedList<Message> messages = new LinkedList<Message>();
	
	public Keyword(String name) {
		this.name = name;
	}
	
	public String getName() {
		//Name only changes in constructor no need to worry about dirty reads
		return name;
	}
	
	public void addMessage(Message msg) {
		synchronized(messages) {
			messages.add(msg);
		}
	}
	
	public LinkedList<Message> getMessages() {
		//We return a copy because if we do not we can't guarantee messages will be used in a thread safe way.
		//We could skip this and return messages and count on the fact that the user that calls getMessages() keeps it thread-safe
		LinkedList<Message> copy = null;
		synchronized(messages) {
			copy = new LinkedList<Message>(messages);
		}
		
		return copy;
	}
	
	public int count() {
		int size;
		//Lock to prevent dirty reads
		synchronized(messages) {
			size = messages.size();
		}
		
		return size;
	}	
	
	public void printMessages(PrintWriter out) {
		//getMessages is thread safe so we don't need to worry about this
		List<Message> messages = getMessages();
		for(Message msg : messages) {
			out.println( msg );
		}		
	}	
}