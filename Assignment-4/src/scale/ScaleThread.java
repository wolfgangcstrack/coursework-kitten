/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the ScaleThread interface.
 */
package scale;

public interface ScaleThread {
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
}
