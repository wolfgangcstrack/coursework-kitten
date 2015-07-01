/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the CreateAuto interface.
 */
package adapter;

import util.AutoException;

public interface CreateAuto {
	public void buildAuto(String filename) throws AutoException;
	public void printAuto(String modelName);
}
