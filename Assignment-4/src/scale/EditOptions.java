/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the synchronized EditOptions class.
 */
package scale;

import adapter.ProxyAutomobile;

public class EditOptions extends ProxyAutomobile implements ScaleThread {
	// ScaleThread extends the Runnable interface
	
	private int operation;
	private String[] args;
	
	public EditOptions(int op, String ... args) {
		if (args.length != 5) {
			throw new IllegalArgumentException();
		}
		
		operation = op;
		this.args = args;
	}
	
	public void run() {
		switch(operation) {
		case 0: editOptionName(args[0], args[1], args[2], args[3], args[4]); break;
		case 1: editOptionPrice(args[0], args[1], args[2], args[3], Float.parseFloat(args[4])); break;
		}
	}
	
	public boolean editOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			) {
		// The locked object is the automobile in the LinkedHashMap with
		// String key "autoMake autoModel"
		synchronized (getAutoWithKey(autoMake, autoModel)) {
			/* This if statement is only here for printing debug statements in driver.Driver.
			 * Otherwise, this statement should normally just return the result of updateOptionName()
			 * without printing debug statements.
			 * See editOptionPrice() below for example format
			 */
			if (updateOptionName(autoMake, autoModel, optionSetName, optionName, newName)) {
				System.out.println("Change of option " + optionName + " to " + newName + " successful");
				return true;
			} else {
				System.out.println("Change of option " + optionName + " to " + newName + " unsuccessful");
				return false;
			}
		}
	}
	
	public boolean editOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		synchronized (getAutoWithKey(autoMake, autoModel)) {
			return updateOptionPrice(autoMake, autoModel, optionSetName, optionName, newPrice);
		}
	}
}
