/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the UpdateAuto interface.
 */
package adapter;

public interface UpdateAuto {
	public boolean updateOptionSetName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newName
			);
	public boolean updateOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			);
	public boolean updateOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			);
	public boolean updateOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName,
			float newPrice);
	public boolean updateOptionChoice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName
			);
}
