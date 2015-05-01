/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the ProxyAutomobile class.
 */
package adapter;

import model.*;

public abstract class ProxyAutomobile {
	private Automobile a1;
	
	// CreateAuto interface methods --------------------------------------
	public void buildAuto(String filename) {
		util.AutoIO autoIO = new util.AutoIO();
		a1 = autoIO.buildAutoObject(filename);
	}
	
	public void printAuto(String modelName) {
		System.out.println(a1.toString());
	}
	
	// UpdateAuto interface methods --------------------------------------
	public void updateOptionSetName(
			String modelName,
			String optionSetName,
			String newName
		) {
		a1.updateOptionSetName(optionSetName, newName);
	}
	
	public void updateOptionName(
			String modelName,
			String optionSetName,
			String optionName,
			String newName
		) {
		a1.updateOptionName(optionSetName, optionName, newName);
	}
	
	public void updateOptionPrice(
			String modelName,
			String optionSetName,
			String optionName,
			float newPrice
		) {
		a1.updateOptionPrice(optionSetName, optionName, newPrice);
	}
}
