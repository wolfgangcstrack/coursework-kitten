/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This file includes the class OptionSet, which
 * is used by the Model class, and the protected
 * class Option, which is used by OptionSet.
 */
package model;

class OptionSet implements java.io.Serializable {
	// serialVersionUID generated with serialver
	private static final long serialVersionUID = 5537926375200316701L;
	private String name;
	private Option options[]; // defined at end of class
	
	// constructors ------------------------------------------------------
	protected OptionSet() { this("", 0); }
	
	protected OptionSet(String name) { this(name, 0); }
	
	protected OptionSet(String name, int size) {
		this.name = name;
		options = new Option[size];
		for (int i = 0; i < options.length; i++)
			options[i] = new Option();
	}
	
	// getters -----------------------------------------------------------
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
	
	// setters -----------------------------------------------------------
	protected void setName(String name) { this.name = name; }
	
	protected void setOptions(Option options[]) { this.options = options; }
	
	protected void setOptionName(int index, String opName) { options[index].setName(opName); }
	
	protected void setOptionPrice(int index, float opPrice) { options[index].setPrice(opPrice); }
	
	protected void setOption(int index, String opName, float opPrice) {
		options[index] = new Option(opName, opPrice);
	}
	
	// add Option methods ------------------------------------------------
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
	
	// Option class definition -------------------------------------------
	class Option implements java.io.Serializable {
		// serialVersionUID generated with serialver
		private static final long serialVersionUID = 2716888257427982132L;
		private String name;
		private float price;
		
		// constructors -------------------------
		protected Option() { this("", 0); }
		
		protected Option(String name) { this(name, 0); }
		
		protected Option(float price) { this("", price); }
		
		protected Option(String name, float price) {
			this.name = name;
			this.price = price;
		}
		
		// getters ------------------------------
		protected String getName() { return this.name; }
		
		protected float getPrice() { return this.price; }
		
		// setters ------------------------------
		protected void setName(String name) { this.name = name; }
		
		protected void setPrice(float price) { this.price = price; }
		
		// Option.toString() --------------------
		public String toString() {
			// keep decimal precision at two for price
			java.text.DecimalFormat two = new java.text.DecimalFormat("$0.00");
			return (new StringBuilder(name).append(": ").append(two.format(price))).toString();
		}
	}
}
