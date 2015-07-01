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

import adapter.BuildAuto;

public class AutoServerSocket {
	protected static BuildAuto autoServer;
	private ServerSocket serverSocket;
	
	public AutoServerSocket(/*int port*/) {
		int port = 4444;
		try {
			serverSocket = new ServerSocket(port);
		} catch (IOException ioe) {
			System.err.println("Could not listen on port: " + port);
			System.exit(1);
		}
	}
	
	public void startServer() {
		System.out.println("Started server\n");
		while (true) {
			AutoServerClientSession ascs;
			System.out.println("Waiting for client socket to connect...");
			try {
				Socket soc = serverSocket.accept();
				System.out.println("Client connected, starting session\n");
				ascs = new AutoServerClientSession(soc);
				ascs.start();
			} catch (IOException ioe) {
				System.err.println("Accept client connection failed.");
			}
		}
	}
}
