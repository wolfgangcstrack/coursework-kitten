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
	
	public AutoServerSocket(int port) {
		try {
			serverSocket = new ServerSocket(port);
		} catch (IOException ioe) {
			System.err.println("Could not listen on port: " + port);
			System.exit(1);
		}
	}
	
	public void startServer() {
		while (true) {
			DefaultSocketClient clientSocket;
			
			try (Socket soc = serverSocket.accept()) {
				clientSocket = new DefaultSocketClient(soc);
				clientSocket.start();
			} catch (IOException ioe) {
				System.err.println("Accept failed.");
			}
		}
	}
}
