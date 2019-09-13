/*
	Besturingssystemen: opdracht 2
	Academiejaar 2010-2011

	Naam: Brent Berghmans
	Nr: 1334252
 */


package org.twitr.client;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class MessageList {
	private Queue<String> messages = new LinkedList<String>();
	
	public MessageList(File file) {
		readMessages(file);
	}
	
	private void readMessages(File file) {
		try {
			FileInputStream fis = new FileInputStream(file);
			BufferedReader bis = new BufferedReader(new InputStreamReader(fis) );
			
			String line;
			while( (line = bis.readLine()) != null ) {
				messages.add(line);
			}
		} catch( FileNotFoundException fe ) {
			System.err.println("Unable to read file (" + file + "): " + fe);
		} catch( IOException ie ) {
			System.err.println("IO error while reading file (" + file + "): " + ie);
			ie.printStackTrace();
		}
	}
	
	synchronized public String getMessage() {
		return messages.poll();
	}
}