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
			String modelName,
			String optionSetName,
			String newName
			);
	public void updateOptionName(
			String modelName,
			String optionSetName,
			String optionName,
			String newName
			);
	public void updateOptionPrice(
			String modelName,
			String optionSetName,
			String optionName,
			float newPrice
			);
}
