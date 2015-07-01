/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the driver class for testing this lab.
 */
package driver;

import java.util.Scanner;

import adapter.BuildAuto;
import util.*;
import scale.*;

class Driver {
	private static Scanner input = new Scanner(System.in);
	
	public static void main(String[] args) throws AutoException {
		String filename1 = "FordZTW_updated.txt";
		String filename2 = "UglyCar.txt";
		
		BuildAuto testBA = new BuildAuto();
		
		testBA.buildAuto(filename1);
		testBA.buildAuto(filename2);
		
		testScaleThreadInterface(testBA);
		
		input.close();
	}
	
	public static void testScaleThreadInterface(BuildAuto testBA) {
		// These Strings will be the arguments passed to EditOptions constructor
		int editOptionName = 0;
		String autoMake = "Ford", autoModel = "Focus Wagon ZTW",
				optionSetName = "Transmission", optionName = "Manual",
				newOptionName1 = "Stick-shift",
				newOptionName2 = "Stick";
		
		// declare runnable EditOptions objects
		ScaleThread sc1 = new EditOptions(editOptionName,
				autoMake, autoModel,
				optionSetName, optionName,
				newOptionName1);
		ScaleThread sc2 = new EditOptions(editOptionName,
				autoMake, autoModel,
				optionSetName, optionName,
				newOptionName2);
		
		Thread t1 = new Thread(sc1);
		Thread t2 = new Thread(sc2);
		
		try {
			// will print debug statements from EditOptions method call
			t1.start();
			t2.start();
			/* Only one of the two threads will succeed in changing option "Manual"
			 * (whichever thread runs first) because the thread that runs second will
			 * try to change "Manual" after it has already been changed by the thread
			 * that runs first
			 */
			
			// wait until threads terminate to continue
			while (Thread.activeCount() > 1) {
				Thread.sleep(1000);
			}
		} catch (InterruptedException ie) {
			System.out.println(ie);
		}
		
		testBA.printAuto(autoMake, autoModel);
	}
}
