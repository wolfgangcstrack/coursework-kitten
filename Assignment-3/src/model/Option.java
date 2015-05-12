/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This file includes the class Option, which is used
 * by the OptionSet and Automobile classes.
 */
package model;

class Option implements java.io.Serializable {
	// serialVersionUID generated with serialver
	// private static final long serialVersionUID = 2716888257427982132L;
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
