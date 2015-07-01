/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the ScaleThread interface.
 */
package scale;

public interface ScaleThread extends Runnable {
	public boolean editOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			);
	public boolean editOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			);
}
