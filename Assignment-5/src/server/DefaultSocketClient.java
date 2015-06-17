/*
 * CIS 35B
 * Modified by: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the DefaultSocketClient class.
 */
package server;

import java.net.*;
import java.io.*;

public class DefaultSocketClient extends Thread implements SocketClientInterface {
	private ObjectInputStream ois;
	private ObjectOutputStream oos;
	private Socket soc;
	
	DefaultSocketClient(Socket s) {
		soc = s;
	}
	
	public void run() {
		if (openConnection()) {
			handleSession();
			closeSession();
		}
	}
	
	public boolean openConnection() {
		try {
			ois = new ObjectInputStream(soc.getInputStream());
			oos = new ObjectOutputStream(soc.getOutputStream());
		} catch (Exception e) {
			return false;
		}
		
		return true;
	}
	
	public void handleSession() {
		Object input;
		
		try {
			while ((input = ois.readObject()) != null) {
				handleInput(input);
			}
		} catch (Exception e) {}
	}
	
	public void sendOutput(Object output) {
		try {
			oos.writeObject(output);
		} catch (IOException ioe) {}
	}
	
	public void handleInput(Object input) {
		System.out.println(input);
	}
	
	public void closeSession() {
		try {
			ois.close();
			oos.close();
			soc.close();
		} catch (IOException ioe) {}
	}
}
