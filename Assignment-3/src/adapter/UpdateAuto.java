/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the UpdateAuto interface.
 */
package adapter;

public interface UpdateAuto {
	public void updateOptionSetName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newName
			);
	public void updateOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			);
	public void updateOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			);
	public void updateOptionChoice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName
			);
}
