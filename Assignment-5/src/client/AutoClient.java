/*
 * CIS 35B
 * Modified by: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the CreateClient class.
 */
package client;

import java.net.*;
import java.io.*;

public class AutoClient {
	private Socket clientSocket;
	// leaving DefaultClientSocket out from here because
	// its functionality doesn't seem to fit as a helper
	// for the client
	ObjectInputStream clientIn;
	ObjectOutputStream clientOut;
	
	BufferedReader stdIn;
	
	public AutoClient() throws IOException {
		clientSocket = new Socket(InetAddress.getLocalHost(), 4444);
		clientIn = new ObjectInputStream(clientSocket.getInputStream());
		clientOut = new ObjectOutputStream(clientSocket.getOutputStream());
		
		stdIn = new BufferedReader(new InputStreamReader(System.in));
	}
	
	public void selectServiceOperation() {		
		String choice = "";
		
		while (!choice.equals("0")) {
			try {
				printMenu();
				
				choice = stdIn.readLine();
				
				switch (choice) {
				case "0": clientOut.writeObject("exit"); break;
				case "1": performOperation(1); break;
				case "2": performOperation(2); break;
				default: System.out.println("Invalid operation choice.\n");
				}
			} catch (IOException ioe) {
				System.out.println(ioe.toString());
			}
		}
	}
	
	private void printMenu() {
		System.out.println("Select a service operation below by entering the number of your choice:\n");
		
		System.out.println("1\tSend automobile to server by default-format file");
		System.out.println("2\tSend automobile to server by Properties file");
		System.out.println("0\tQuit\n");
	}
	
	private void performOperation(int optionChoice) {
		System.out.print("Enter name of file to send: ");
		
		try {
			String filename = stdIn.readLine();
			
			CarModelOptionsIO cmoIO = new CarModelOptionsIO();
			
			clientOut.writeObject(cmoIO.readData(filename, optionChoice));
			
			System.out.println("The file " + filename + " sent!");
		} catch (FileNotFoundException fnfe) {
			System.out.println(fnfe.toString());
		} catch (IOException ioe) {
			System.out.println(ioe.toString());
		}
	}
}
