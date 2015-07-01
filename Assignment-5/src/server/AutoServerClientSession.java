/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoServerClientSession class.
 */
package server;

import java.io.*;
import java.net.*;
import java.util.*;

import model.Automobile;
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
		
		sendOutput(new String("Greetings from AutoServer 0.1!"));
		
		while (sessionOn) {
			try {
				input = ois.readObject();
				
				handleInput(input); // can turn session off
			} catch (ClassNotFoundException | IOException e) {
				sessionOn = false;
			} catch (Exception e) {
				sessionOn = false;
			}
		}
	}
	
	public void handleInput(Object input) {
		if (input instanceof String) {
			handleQuery((String) input);
		} else if (input instanceof Automobile) {
			handleAuto((Automobile) input);
		} else if (input instanceof Properties) {
			handleProperties((Properties) input);
		} else {
			System.out.println("Object from client: " + input);
			sendOutput("Invalid query");
		}
	}

	private void handleQuery(String query) {
		if (query.equals("exit")) {
			sessionOn = false;
			sendOutput("Bye");
			return;
		}
		
		AutoClientQueryHandler queryHandler = new AutoClientQueryHandler();
		String serverResponse = queryHandler.handleQuery(query);
		sendOutput(serverResponse);
	}

	private void handleAuto(Automobile input) {
		AutoServer autoBuilder = new BuildCarModelOptions();
		
		if (autoBuilder.addAuto(input)) {
			sendOutput("Successfully added automobile to server");
		} else {
			sendOutput("Unsuccessfully added automobile to server");
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
