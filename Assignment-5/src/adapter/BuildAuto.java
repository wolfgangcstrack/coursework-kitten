/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the BuildAuto class.
 */
package adapter;

import server.AutoServer;

public class BuildAuto extends ProxyAutomobile
implements CreateAuto, ReadAuto, UpdateAuto, DeleteAuto,
		FixAuto, AutoServer {
	// magic
}
