/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the AddAuto interface.
 */
package adapter;

public interface AddAuto {
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName);
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName);
}
