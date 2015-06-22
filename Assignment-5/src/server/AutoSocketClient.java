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

public class AutoSocketClient extends DefaultSocketClient {
	boolean sessionOn;
	
	public AutoSocketClient(Socket s) {
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
			handleString((String) input);
		} else if (input instanceof FileReader) {
			handleFileReader((FileReader) input);
		} else if (input instanceof Properties) {
			handleProperties((Properties) input);
		}
	}

	private void handleString(String input) {
		if (input.equals("exit")) {
			sessionOn = false;
		}
	}

	private void handleFileReader(FileReader input) {
		AutoServer autoBuilder = new BuildCarModelOptions();
		
		try {
			autoBuilder.addAuto(autoBuilder.createAuto(input));
		} catch (AutoException ae) {
			System.out.println("Error while handling file reader");
			System.out.println(ae.toString());
		}
	}
	
	private void handleProperties(Properties input) {
		AutoServer autoBuilder = new BuildCarModelOptions();
		
		try {
			autoBuilder.addAuto(autoBuilder.createAuto(input));
		} catch (AutoException ae) {
			System.out.println("Error while handling properties file");
			System.out.println(ae.toString());
		}
	}
}
