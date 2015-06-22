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
	BufferedReader in;
	PrintWriter out;
	ObjectOutputStream fileSender;
	
	public AutoClient() throws IOException {
		clientSocket = new Socket(InetAddress.getLocalHost(), 4444);
		out = new PrintWriter(clientSocket.getOutputStream(), true);
		in = new BufferedReader(new InputStreamReader(System.in));
		fileSender = new ObjectOutputStream(clientSocket.getOutputStream());
	}
	
	public void selectServiceOperation() throws IOException {		
		String choice = "";
		
		while (!choice.equals("0")) {
			printMenu();
			
			choice = in.readLine();
			
			switch (choice) {
			case "0": continue; // exit while loop
			case "1": performOperation(1); break;
			case "2": performOperation(2); break;
			default: System.out.println("Invalid operation choice.\n");
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
			String filename = in.readLine();
			
			CarModelOptionsIO cmoIO = new CarModelOptionsIO();
			
			fileSender.writeObject(cmoIO.readData(filename, optionChoice));
			
			System.out.println("The file " + filename + " sent!");
		} catch (FileNotFoundException fnfe) {
			System.out.println(fnfe.toString());
		} catch (IOException ioe) {
			System.out.println(ioe.toString());
		}
	}
}
