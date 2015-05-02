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
		String filetoread = "FordZTW.txt";
		
		// Demonstrate BuildAuto and all API's from this lab
		System.out.println("Demonstrating BuildAuto class and API's");
		BuildAuto bAuto = new BuildAuto();
		
		// create and print the Automobile using the CreateAuto API
		bAuto.buildAuto(filetoread);
		bAuto.printAuto(""); // empty string for model name for now
		System.out.println();
		
		// update the Automobile's options with the UpdateAuto API
		bAuto.updateOptionSetName("", "Color", "Paint Job");
		bAuto.updateOptionName("", "Transmission", "Manual", "Stick Shift");
		bAuto.updateOptionPrice("", "Brakes/Traction Control", "ABS", 777);
		
		// demonstrate the FixAuto API by catching AutoException
		demonstrateFixAutoAPI(filetoread, bAuto);
		bAuto.printAuto("");
	}
	
	private static void demonstrateFixAutoAPI(String filetoread, BuildAuto bAuto) {
		boolean successfulBuild = false;
		filetoread = "/dev/null/black-hole.FAKE"; // will make bAuto throw an exception
		
		while (!successfulBuild) {
			try {
				System.out.println("Reading from file " + filetoread);
				bAuto.buildAuto(filetoread);
				successfulBuild = true;
			} catch (AutoException aE) {
				successfulBuild = false;
				System.out.println(aE.toString());
				
				System.out.print("\nBuild Automobile manually? (Y/N): ");
				char choice = input.nextLine().toUpperCase().charAt(0);
				System.out.println();
				
				if (choice == 'Y') {
					try {
						bAuto.manualBuild(input);
						successfulBuild = true;
					} catch (Exception e) {
						System.out.println(e.toString());
						continue;
					}
				} else {
					System.out.print("Enter new filename to read from: ");
					filetoread = input.nextLine();
				}
			}
		}
	}
}
