/*
 * CIS 35B
 * Modified by: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the SocketClientInterface.
 */
package server;

public interface SocketClientInterface {
	boolean openConnection();
	void handleSession();
	void closeSession();
}
