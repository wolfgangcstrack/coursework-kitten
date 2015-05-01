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
	public void updateOptionPrice(
			String modelName,
			String optionName,
			String option,
			float newPrice
		);
}
