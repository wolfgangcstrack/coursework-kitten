/*
 * CIS 35B - Assignment 1
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the driver class for testing this lab.
 */
class Driver {
	public static void main(String[] args) {
		String filetoread = "FordZTW.txt";
		String serFile = "fordztw.ser";
		
		// Build Automotive Object from the file <filetoread>
		Util.AutoIO autoIO = new Util.AutoIO();
		Model.Automotive FordZTW = autoIO.buildAutoObject(filetoread);
		
		// Print before serialization
		System.out.println("Before Serialization:");
		System.out.println(FordZTW.toString());
		System.out.println();
		
		// Serialize
		autoIO.serializeAutoObject(serFile, FordZTW);
		// Deserialize
		Model.Automotive newFordZTW = autoIO.deserializeAutoObject(serFile);
		
		// Print after deserialization
		System.out.println("After Deserialization:");
		System.out.println(newFordZTW.toString());
	}
}
