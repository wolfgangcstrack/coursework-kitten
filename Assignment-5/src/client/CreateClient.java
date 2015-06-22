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

import server.DefaultSocketClient;

public class CreateClient {
	private Socket clientSocket;
	private DefaultSocketClient dsc;
	
	PrintWriter out;
	BufferedReader in;
	
	public CreateClient() throws IOException {
		clientSocket = new Socket(InetAddress.getLocalHost(), 4444);
		dsc = new DefaultSocketClient(clientSocket);
		out = new PrintWriter(clientSocket.getOutputStream(), true);
		in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
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
			default: out.println("Invalid operation choice.\n");
			}
		}
	}
	
	private void printMenu() {
		out.println("Select a service operation below by entering the number of your choice:\n");
		
		out.println("1\tSend automobile to server by default-format file");
		out.println("2\tSend automobile to server by Properties file");
		out.println("0\tQuit\n");
	}
	
	private void performOperation(int optionChoice) {
		out.print("Enter name of file to send: ");
		
		switch (optionChoice) {
		case 1:
			out.print("Enter name of file: ");
		}
	}
}
