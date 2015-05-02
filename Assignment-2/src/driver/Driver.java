/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the driver class for testing this lab.
 */
package driver;

import util.*;

class Driver {
	public static void main(String[] args) throws AutoException {
		String filetoread = "FordZTW.txt";
		String serFile = "fordztw.ser";
		
		// Build Automotive Object from the file <filetoread>
		util.AutoIO autoIO = new util.AutoIO();
		model.Automobile FordZTW = autoIO.buildAutoObject(filetoread);
		
		// Print before serialization
		System.out.println("Before Serialization:");
		System.out.println(FordZTW.toString());
		System.out.println();
		
		// Serialize
		autoIO.serializeAutoObject(serFile, FordZTW);
		// Deserialize
		model.Automobile newFordZTW = autoIO.deserializeAutoObject(serFile);
		
		// Print after deserialization
		System.out.println("After Deserialization:");
		System.out.println(newFordZTW.toString());
	}
}
