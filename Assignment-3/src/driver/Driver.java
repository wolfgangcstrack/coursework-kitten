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
	
	/** This method will test out the new Collection implementations
	 * added to this lab:
	 * - ArrayLists of Options
	 * - LinkedHashMaps of Autmobile.OptionSet and BuildAuto.automobiles
	 * 
	public static void testBuildAutoCollectionFunctionality(BuildAuto testBA) {
		
	}*/
	
	/** This method will test out adding new Automobiles to BuildAuto object
	 * by using adapter.CreateAuto interface methods.
	 */
	public static void testCreateAutoInterface(BuildAuto testBA) {
		
	}
	
	/** This method will test out deleting multiple Automobiles in BuildAuto
	 * object by using adapter.DeleteAuto interface methods.
	 */
	public static void testDeleteAutoInterface(BuildAuto testBA) {
		
	}
	
	/** This method will test out updating Automobile options and option
	 * choices in the BuildAuto object.
	 */
	public static void testUpdateAutoInterface(BuildAuto testBA) {
		
	}
}
