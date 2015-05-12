/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This file includes the class OptionSet, which
 * is used by the Model class.
 */
package model;

import java.util.ArrayList;

class OptionSet implements java.io.Serializable {
	// serialVersionUID generated with serialver
	private static final long serialVersionUID = 5537926375200316701L;
	private String name;
	private ArrayList<Option> options;
	private Option choice;
	
	// constructors ------------------------------------------------------
	protected OptionSet() { this("", 0); }
	
	protected OptionSet(String name) { this(name, 0); }
	
	protected OptionSet(String name, int size) {
		this.name = name;
		options = new ArrayList<Option>(size);
		for (int i = 0; i < options.size(); i++) {
			options.set(i, new Option());
		}
	}
	
	// getters -----------------------------------------------------------
	/*
	protected String getName() { return name; }
	
	protected Option[] getOptions() { return options; }
	
	protected Option[] getOptions(int length) { return getOptions(0, length); }
	
	protected Option[] getOptions(int start, int length) {
		Option result[] = new Option[length];
		System.arraycopy(options, start, result, 0, length);
		return result;
	}
	
	protected Option getOption(int index) {
		if (index >= 0 && index < options.length)
			return options[index];
		return null; // when index is not within range
	}
	*/
	// setters -----------------------------------------------------------
	/*
	protected void setName(String name) { this.name = name; }
	
	protected void setOptions(Option options[]) { this.options = options; }
	
	protected void setOptionName(int index, String opName) { options[index].setName(opName); }
	
	protected void setOptionPrice(int index, float opPrice) { options[index].setPrice(opPrice); }
	
	protected void setOption(int index, String opName, float opPrice) {
		options[index] = new Option(opName, opPrice);
	}
	*/
	// add Option methods ------------------------------------------------
	/*
	protected boolean addOption(String opName, float opPrice) {
		// function does not return false (no parameter checking) for now
		
		Option newoptions[] = new Option[options.length+1];
		// copy old options to the new array
		for (int i = 0; i < options.length; i++)
			newoptions[i] = options[i];
		// add the new Option
		newoptions[options.length] = new Option(opName, opPrice);
		
		options = newoptions; // copy the new array to this.options
		return true;
	}
	
	// delete functions -------------------------
	protected boolean deleteOption(int index) {
		if (index < 0 || index >= options.length)
			return false;
		
		Option temp[] = new Option[options.length-1];
		for (int i = 0; i < temp.length; i++) {
			if (i < index)
				temp[i] = options[i];
			else if (i > index)
				temp[i] = options[i+1];
		}
		return true;
	}
	
	// OptionSet.toString() ----------------------------------------------
	public String toString() {
		StringBuilder sb = new StringBuilder(name);
		String newline = "\n", tab = "\t";
		for (int i = 0; i < options.length; i ++)
			sb.append(newline)
			.append(tab).append(tab).append(options[i].toString());
		
		return sb.toString();
	}
	*/
}
