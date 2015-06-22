/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoSocketClient class.
 */
package server;

import java.io.*;
import java.net.*;
import java.util.*;

import util.AutoException;

public class AutoServerClientSession extends DefaultSocketClient {
	boolean sessionOn;
	
	public AutoServerClientSession(Socket s) {
		super(s);
		sessionOn = false;
	}
	
	public void handleSession() {
		sessionOn = true;
		
		Object input;
		
		while (sessionOn) {
			try {
				input = ois.readObject();
				
				handleInput(input); // can turn session off
			} catch (ClassNotFoundException | IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void handleInput(Object input) {
		if (input instanceof String) {
			handleQuery((String) input);
		} else if (input instanceof FileReader) {
			handleFileReader((FileReader) input);
		} else if (input instanceof Properties) {
			handleProperties((Properties) input);
		}
	}

	private void handleQuery(String query) {
		if (query.equals("exit")) {
			sessionOn = false;
			sendOutput("Bye");
		} else {
			System.out.println("Bad query from client: " + query);
			sendOutput("Invalid query");
		}
	}

	private void handleFileReader(FileReader input) {
		AutoServer autoBuilder = new BuildCarModelOptions();
		
		try {
			autoBuilder.addAuto(autoBuilder.createAuto(input));
			sendOutput("Succesfully added automobile to server from default-formatted file");
		} catch (AutoException ae) {
			System.out.println("Error while handling file reader");
			System.out.println(ae.toString());
			sendOutput("Could not add automobile from default-formatted file");
		}
	}
	
	private void handleProperties(Properties input) {
		AutoServer autoBuilder = new BuildCarModelOptions();
		
		try {
			autoBuilder.addAuto(autoBuilder.createAuto(input));
			sendOutput("Successfully added automobile to server from properties file");
		} catch (AutoException ae) {
			System.out.println("Error while handling properties file");
			System.out.println(ae.toString());
			sendOutput("Could not add automobile from properties file");
		}
	}
}
