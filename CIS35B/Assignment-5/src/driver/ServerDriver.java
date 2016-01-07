/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the server driver class for testing this lab.
 */
package driver;

import server.*;

public class ServerDriver {
	public static void main(String[] args) {
		AutoServerSocket autoServer = new AutoServerSocket();
		
		autoServer.startServer();
	}
}
