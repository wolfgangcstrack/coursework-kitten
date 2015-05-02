/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the FixAuto interface.
 */
package adapter;

import java.util.Scanner;

// Essentially, these methods handle "fixing" AutoExceptions
public interface FixAuto {
	/* This method is called in the event that 
	 * the user wants to build the Automobile
	 * manually instead of fixing the input file.
	 * In essence, this is the "fix" method.
	 */
	public void manualBuild(Scanner input) throws util.AutoException;
}
