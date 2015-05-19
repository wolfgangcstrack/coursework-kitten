/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the synchronized EditOptions class.
 */
package scale;

import adapter.ProxyAutomobile;

public class EditOptions extends ProxyAutomobile implements Runnable, ScaleThread {
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
	
	public synchronized boolean editOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			) {
		
	}
	
	public synchronized boolean editOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		
	}
}
