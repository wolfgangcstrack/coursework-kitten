/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoServerSocket class.
 */
package server;

import java.net.*;
import java.io.*;

public class AutoServerSocket {
	private ServerSocket serverSocket;
	Socket clientSocket;
	
	private ObjectInputStream ois;
	private ObjectOutputStream oos;
	
	public AutoServerSocket() {
		try {
			serverSocket = new ServerSocket(4444);
		} catch (IOException ioe) {
			System.err.println("Could not listen on port: 4444.");
			System.exit(1);
		}
	}
	
	public void startServer() throws IOException {
		try {
			clientSocket = serverSocket.accept();
		} catch (IOException ioe) {
			System.err.println("Accept failed.");
			System.exit(1);
		}
		
		PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
		BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		String inputLine, outputLine;
	}
}
