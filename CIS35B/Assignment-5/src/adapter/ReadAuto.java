/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the ReadAuto interface.
 */
package adapter;

public interface ReadAuto {
	public String getListOfAutos();
	
	public String readAuto(String autoMake, String autoModel);
	public String readAllAuto();
	
	public boolean containsOptionSet(
			String autoMake,
			String autoModel,
			String optionSetName);
	public boolean containsOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName);
	
	public void printAuto(String autoMake, String autoModel);
	public void printAllAuto();
}
