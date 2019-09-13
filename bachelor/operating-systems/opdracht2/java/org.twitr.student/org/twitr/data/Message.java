/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr.data;

public class Message {
	private User owner;
	private String text;
	
	//All variables get changed in the constructor, so we don't need to worry about dirty reads.
	public Message(User user, String text) {
		this.owner = user;
		this.text = text;
	}

	public User getOwner() {
		return owner;
	}
	
	public String getText() {
		return text;
	}

	public String toString() {
		return owner + " said " + text;
	}
}