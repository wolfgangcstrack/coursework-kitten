/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the driver class for testing this lab.
 */
package driver;

import java.util.Scanner;

import util.*;

class Driver {
	private static Scanner input = new Scanner(System.in);
	
	public static void main(String[] args) throws AutoException {
		String propertiesFileName = "FordZTW.properties";
		AutoIO aio = new AutoIO();
		
		try {
			model.Automobile testAuto = aio.buildAutoObject(propertiesFileName, true);
			System.out.println(testAuto.toString());
		} catch (StringIndexOutOfBoundsException ioobe) {
			ioobe.printStackTrace();
		}
		
		input.close();
	}
}
