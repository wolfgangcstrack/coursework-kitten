/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the driver class for testing this lab.
 */
package driver;

import java.util.Scanner;

import adapter.BuildAuto;
import util.*;

class Driver {
	private static Scanner input = new Scanner(System.in);
	
	public static void main(String[] args) throws AutoException {
		BuildAuto testBA = new BuildAuto();
		
		testCreateAutoInterface(testBA);
		testDeleteAutoInterface(testBA);
		testUpdateAutoInterface(testBA);
		
		input.close();
	}
	
	/** This method will test out adding new Automobiles to BuildAuto object
	 * by using adapter.CreateAuto interface methods.
	 */
	public static void testCreateAutoInterface(BuildAuto testBA) {
		System.out.println("Now testing new CreateAuto interface and BuildAuto's LinkedHashMap of Automobiles:\n");
		
		String filename1 = "FordZTW_updated.txt";
		String filename2 = "UglyCar.txt";
		
		boolean successfulRun = false;
		while (!successfulRun) {
			try {
				testBA.buildAuto(filename1);
				testBA.buildAuto(filename2);
				successfulRun = true;
			} catch (AutoException ae) {
				System.out.println(ae.toString()); // will print filename with error
				System.out.println("Fix file and then press enter to continue...");
				input.nextLine(); // user must press enter to continue program
			}
		}
		
		System.out.println("Successfully added the two automobiles:\n");
		testBA.printAuto("Ford Focus Wagon ZTW");
		testBA.printAuto("No-Name-Make Ugly Bus 6000");
		
		System.out.println("\n");
	}
	
	/** This method will test out deleting multiple Automobiles in BuildAuto
	 * object by using adapter.DeleteAuto interface methods.
	 */
	public static void testDeleteAutoInterface(BuildAuto testBA) {
		System.out.println("Now testing DeleteAuto interface to delete automobiles from BuildAuto object.\n");
		
		System.out.println("Deletion of automobile from BuildAuto " + 
		(testBA.deleteAuto("No-Name-Make", "Ugly Bus 6000") ? "successful" : "failed"));
		
		System.out.println("\n");
	}
	
	/** This method will test out updating Automobile options and option
	 * choices in the BuildAuto object.
	 */
	public static void testUpdateAutoInterface(BuildAuto testBA) {
		System.out.println("Now testing UpdateAuto interface to update Option choice in an automobile.");
		
		if (testBA.updateOptionChoice("Ford", "Focus Wagon ZTW", "Color", "French Blue Clearcoat Metallic")) {
			System.out.println("Option Choice of Color updated:");
			testBA.printAuto("Ford Focus Wagon ZTW");
		} else {
			System.out.println("Option choice update unsuccessful");
		}
		
		System.out.println("\n");
	}
}
