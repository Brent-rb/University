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

public class User {
	private String name;
	//Multiple EventHandlers can add messages to the same user, so we need to make it thread-safe.
	//For exlpenation look at Keyword.java, it's exactly the same.
	private LinkedList<Message> messages = new LinkedList<Message>();
	
	public User(String name) {
		this.name = name;
	}
	
	public String getUserName() {
		return name;
	}
	
	public void addMessage(Message msg) {
		synchronized(messages) {
			messages.add(msg);
		}
	}

	public LinkedList<Message> getMessages() {
		LinkedList<Message> clone;
		
		synchronized(messages) {
			clone = new LinkedList<Message>(messages);
		}
		
		return clone;
	}
	
	public String toString() {
		return "user " + name;
	}
	
	public int count() {
		return messages.size();
	}
	
	public void printMessages(PrintWriter out) {
		List<Message> messages = getMessages();
		
		for(Message msg : messages) {
			out.println( msg );
		}		
	}
}