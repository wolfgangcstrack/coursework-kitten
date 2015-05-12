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
	// private static final long serialVersionUID = 5537926375200316701L;
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
	protected String getName() { return name; }
	
	protected Option[] getOptions() { return ((Option[])options.toArray()); }
	
	protected Option[] getOptions(int length) { return getOptions(0, length); }
	
	protected Option[] getOptions(int start, int length) {
		Option result[] = new Option[length];
		System.arraycopy(options, start, result, 0, length);
		return result;
	}
	
	protected Option getOption(int index) {
		if (index >= 0 && index < options.size())
			return options.get(index);
		return null; // when index is not within range
	}
	
	protected Option getOption(String optionName) {
		for (Option option : options) {
			if (option.getName().equals(optionName))
				return option;
		}
		return null; // Option not found
	}
	
	protected Option getOptionChoice() { return choice; }
	
	// setters -----------------------------------------------------------
	protected void setName(String name) { this.name = name; }
	
	//protected void setOptions(Option options[]) { this.options = options; }
	
	protected void setOptionName(int index, String opName) { options.get(index).setName(opName); }
	
	protected void setOptionName(String opName, String newName) {
		for (Option option : options) {
			if (option.getName().equals(opName)) {
				option.setName(newName);
			}
		}
	}
	
	protected void setOptionPrice(int index, float opPrice) { options.get(index).setPrice(opPrice); }
	
	protected void setOption(int index, String opName, float opPrice) {
		options.set(index, new Option(opName, opPrice));
	}
	
	protected void setOptionChoice(String optionName) {
		for (Option option : options) {
			if (option.getName().equals(optionName))
				choice = option;
		}
	}
	
	protected void setOptionChoice(int optionIndex) {
		if (optionIndex >= 0 && optionIndex <= options.size() - 1)
			choice = options.get(optionIndex);
	}
	
	// add Option methods ------------------------------------------------
	protected boolean addOption(String opName, float opPrice) {
		return options.add(new Option(opName, opPrice));
	}
	
	// delete Option methods ---------------------------------------------
	protected boolean deleteOption(int index) {
		if (index < 0 || index >= options.size())
			return false;
		// else
		options.remove(index);
		return true;
	}
	
	// OptionSet.toString() ----------------------------------------------
	public String toString() {
		StringBuilder sb = new StringBuilder(name);
		String newline = "\n", tab = "\t";
		for (int i = 0; i < options.size(); i++)
			sb.append(newline)
			.append(tab).append(tab).append(options.get(i).toString());
		
		return sb.toString();
	}
}
