/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the client driver class for testing this lab.
 */
package driver;

import java.io.IOException;

import client.*;

public class ClientDriver {
	public static void main(String[] args) {
		AutoClient client = new AutoClient();
		
		try {
			client.startClient();
		} catch (IOException ioe) {
			System.out.println("Client could not connect to server");
			ioe.printStackTrace();
		}
	}
}
