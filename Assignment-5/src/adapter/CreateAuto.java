/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the CreateAuto interface.
 */
package adapter;

import util.AutoException;

public interface CreateAuto {
	public void buildAuto(String filename) throws AutoException;
	
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName);
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName,
			float newOptionPrice);
}
