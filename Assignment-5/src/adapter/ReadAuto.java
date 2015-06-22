/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the ReadAuto interface.
 */
package adapter;

public interface ReadAuto {
	public String readAuto(String autoMake, String autoModel);
	public String readAllAuto();
	
	public void printAuto(String autoMake, String autoModel);
	public void printAllAuto();
}
