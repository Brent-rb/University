/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr.data;
import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;

import org.twitr.Indexer;

public class DataStore {
	//We use ConcurrentHashMaps so they are thread safe.
	//In the case that this would be considered cheating
	//I'd use synchronized whenever I would add or remove something from these variables as you can see in Indexer Implementatie 2
	private ConcurrentHashMap<String, User> users = new ConcurrentHashMap<String, User>();
	private ConcurrentHashMap<String, Keyword> keywords = new ConcurrentHashMap<String, Keyword>();
	
	
	private Indexer indexer = null;
	
	public void setIndexer(Indexer indexer) {
		this.indexer = indexer;
	}
	
	public User getUser(String username) {
		return users.get(username);
	}
	
	public User getOrInsertUser(String name) {
		User user = users.get(name);
		if( user == null ) {		
			user = new User(name);
			users.put(name, user);
		}

		return user;
	}
	
	public Keyword getOrInsertKeyword(String name) {
		Keyword keyword = keywords.get(name);
		if( keyword == null ) {		
			keyword = new Keyword(name);
			keywords.put(name, keyword);
		}

		return keyword;
	}
	
	public Keyword getKeyword(String keyword) {
		return keywords.get(keyword);
	}

	public void add(User user) {
		users.put(user.getUserName(), user);
	}
	
	public void addMessage(User user, String message) {
		Message msg = new Message(user, message);
		user.addMessage(msg);
		
		if( indexer != null )
			indexer.process(msg);		
	}
}