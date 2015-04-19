/*
 * CIS 35B - Assignment 1
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This class represents the Model/Automotive class.
 */
package Model;

public class Automotive {
	private String name;
	private double baseprice;
	private OptionSet opsets[];
	
	
	// constructors ------------------------------------------------------
	public Automotive() { this("", 0, 0); }
	public Automotive(String name) { this(name, 0, 0); }
	public Automotive(String name, double baseprice) { this(name, baseprice, 0); }
	public Automotive(String name, int optionSetSize)
		{ this(name, 0, (optionSetSize >= 0 ? optionSetSize : 0)); }
	public Automotive(String name, double baseprice, int optionSetSize) {
		this.name = name;
		this.baseprice = baseprice;
		opsets = new OptionSet[(optionSetSize >= 0 ? optionSetSize : 0)];
	}
	
	
	// getters -----------------------------------------------------------
	public String getName() { return name; }
	public double getBasePrice() { return baseprice; }
	
	// ----- get this.opsets or a subset of this.opsets
	public OptionSet[] getOptionSets() { return opsets; }
	public OptionSet[] getOptionSets(int length) { return getOptionSets(0, length); }
	public OptionSet[] getOptionSets(int start, int length) {
		if (start < 0 || start > opsets.length || length < 0 || length > opsets.length-1)
			return null; // if start or length are invalid
		OptionSet result[] = new OptionSet[length];
		System.arraycopy(opsets, start, result, 0, length);
		return result;
	}
	
	// ----- get individual OptionSets and their values
	public OptionSet getOptionSet(int index) {
		if (index < 0 || index >= opsets.length)
			return null;
		return opsets[index];
	}
	
	public String getOptionSet_Name(int index) {
		if (index < 0 || index >= opsets.length)
			return null;
		return opsets[index].getName();
	}
	
	// ----- get individual Options and their values (in context of OptionSet)
	public String getOptionName(int opsIndex, int opIndex) {
		if (opsIndex < 0 || opsIndex >= opsets.length ||
				opIndex < 0 || opIndex >= opsets[opsIndex].getOptions().length)
			return null;
		return opsets[opsIndex].getOptions()[opsIndex].getName();
	}
	
	public String getOptionName(String opsName, int opIndex) 
		{ return getOptionName(findOptionSet(opsName), opIndex); }
	
	public float getOptionPrice(int opsIndex, int opIndex) {
		if (opsIndex < 0 || opsIndex >= opsets.length ||
				opIndex < 0 || opIndex >= opsets[opsIndex].getOptions().length)
			return Float.NaN;
		return opsets[opsIndex].getOptions()[opsIndex].getPrice();
	}
	
	public float getOptionPrice(String opsName, int opIndex)
		{ return getOptionPrice(findOptionSet(opsName), opIndex); }
	
	
	// setters -----------------------------------------------------------
	public void setName(String name) { this.name = name; }
	public void setBasePrice(double baseprice) { this.baseprice = baseprice; }
	public void setOptionSets(OptionSet newOpSets[]) { opsets = newOpSets; }
	// ----- set individual OptionSets and their values
	public void setOptionSet(int index, OptionSet newOps) { opsets[index] = newOps; }
	public void setOptionSet_Name(int index, String name) { opsets[index].setName(name); }
	// ----- set individual Options and their values (in context of OptionSet)
	public void setOptionName(int opsIndex, int opIndex, String opName)
		{ opsets[opsIndex].setOptionName(opIndex, opName); }
	public void setOptionPrice(int opsIndex, int opIndex, float opPrice)
		{ opsets[opsIndex].setOptionPrice(opIndex, opPrice); }
	public void setOption(int opsIndex, int opIndex, String opName, float opPrice)
		{ opsets[opsIndex].setOption(opIndex, opName, opPrice); }
	
	
	// find methods ------------------------------------------------------
	public int findOptionSet(String name) {
		for (int i = 0; i < opsets.length; i++) {
			if (opsets[i].getName().equals(name))
				return i;
		}
		return -1;
	}
	
	public int findOption(String opsName, String opName)
		{ return findOption(findOptionSet(opsName), opName); }
	public int findOption(int opsIndex, String name) {
		if (opsIndex < 0 || opsIndex >= opsets.length)
			return -1;
		
		for (int i = 0; i < opsets[opsIndex].getOptions().length; i++) {
			if (opsets[opsIndex].getOptions()[i].equals(name))
				return i;
		}
		return -1;
	}
	
	
	// update (find and set) methods -------------------------------------
	// ----- update individual OptionSets and their values
	public boolean updateOptionSet(String opsName, OptionSet ops) {
		int opsIndex = findOptionSet(opsName);
		if (opsIndex == -1)
			return false;
		
		opsets[opsIndex] = ops;
		return true;
	}
	public boolean updateOptionSet_Name(String opsName, String newOpsName) {
		int opsIndex = findOptionSet(opsName);
		if (opsIndex == -1)
			return false;
		
		opsets[opsIndex].setName(name);
		return true;
	}
	
	// ----- update individual Options and their values (in context of OptionSet)
	public boolean updateOptionName(String opsName, int opIndex, String opName)
		{ return updateOptionName(findOptionSet(opsName), opIndex, opName); }
	public boolean updateOptionName(String opsName, String opName, String newOpName) {
		int opsIndex = findOptionSet(opsName);
		return updateOptionName(opsIndex, findOption(opsIndex, opName), newOpName);
	}
	public boolean updateOptionName(int opsIndex, int opIndex, String opName) {
		if (opsIndex < 0 || opsIndex >= opsets.length ||
				opIndex < 0 || opIndex >= opsets[opsIndex].getOptions().length)
			return false;
		
		opsets[opsIndex].setOptionName(opIndex, opName);
		return true;
	}
	
	public boolean updateOptionPrice(String opsName, int opIndex, float opPrice)
		{ return updateOptionPrice(findOptionSet(opsName), opIndex, opPrice); }
	public boolean updateOptionPrice(String opsName, String opName, float opPrice) {
		int opsIndex = findOptionSet(opsName);
		return updateOptionPrice(opsIndex, findOption(opsIndex, opName), opPrice);
	}
	public boolean updateOptionPrice(int opsIndex, int opIndex, float opPrice) {
		if (opsIndex < 0 || opsIndex >= opsets.length ||
				opIndex < 0 || opIndex >= opsets[opsIndex].getOptions().length)
			return false;
		
		opsets[opsIndex].setOptionPrice(opIndex, opPrice);
		return true;
	}
	
	public boolean updateOption(String opsName, int opIndex, String opName, float opPrice)
	{ return updateOption(findOptionSet(opsName), opIndex, opName, opPrice); }
	public boolean updateOption(String opsName, String opName, String newOpName, float newOpPrice) {
		int opsIndex = findOptionSet(opsName);
		return updateOption(opsIndex, findOption(opsIndex, opName), newOpName, newOpPrice);
	}
	public boolean updateOption(int opsIndex, int opIndex, String newOpName, float newOpPrice) {
		if (opsIndex < 0 || opsIndex >= opsets.length ||
				opIndex < 0 || opIndex >= opsets[opsIndex].getOptions().length)
			return false;
		
		opsets[opsIndex].setOption(opIndex, newOpName, newOpPrice);
		return true;
	}
	
	
	// add (OptionSet/Option to this) methods ----------------------------
	public boolean addOptionSet(String opsName) { return addOptionSet(opsName, 0); }
	public boolean addOptionSet(String opsName, int opsSize) {
		if (opsSize < 0)
			return false;
		
		OptionSet newOpsets[] = new OptionSet[opsets.length+1];
		// here's one good reason why this class probably
		// should have used an ArrayList instead
		for (int i = 0; i < opsets.length; i++)
			newOpsets[i] = opsets[i]; // copy this.opsets to newOpsets
		newOpsets[opsets.length] = new OptionSet(opsName, opsSize); // add new OptionSet
		
		opsets = newOpsets; // assign the new array to this.opsets
		return true; // successfully added new OptionSet
	}
	
	public boolean addOption(String opsName, String newOpName, float newOpPrice)
		{ return addOption(findOptionSet(opsName), newOpName, newOpPrice); }
	public boolean addOption(int opsIndex, String opName, float opPrice) {
		if (opsIndex < 0 || opsIndex >= opsets.length)
			return false; // opsIndex out of range, Option not added
		
		return opsets[opsIndex].addOption(opName, opPrice);
	}
	
	
	// delete (OptionSet/Option from this) methods -----------------------
	public boolean deleteOptionSet(String opsName) { return deleteOptionSet(findOptionSet(opsName)); }
	public boolean deleteOptionSet(int opsIndex) {
		if (opsIndex < 0 || opsIndex >= opsets.length)
			return false;
		
		// make new array have size = this.opsets.length-1
		OptionSet newOpsets[] = new OptionSet[opsets.length-1];
		// copy all OptionSets besides the one at opsIndex
		for (int i = 0; i < newOpsets.length; i++) {
			if (i < opsIndex)
				newOpsets[i] = opsets[i];
			else if (i > opsIndex)
				newOpsets[i] = opsets[i+1];
		}
		opsets = newOpsets; // assign the new array of OptionSets
		return true;
	}
	
	public boolean deleteOption(String opsName, int opIndex)
		{ return deleteOption(findOptionSet(opsName), opIndex); }
	public boolean deleteOption(String opsName, String opName) {
		int opsIndex = findOptionSet(opsName);
		return deleteOption(opsIndex, findOption(opsIndex, opName));
	}
	public boolean deleteOption(int opsIndex, int opIndex) {
		if (opsIndex < 0 || opsIndex >= opsets.length ||
				opIndex < 0 || opIndex >= opsets[opsIndex].getOptions().length)
			return false;
		
		return opsets[opsIndex].deleteOption(opIndex);
	}
	
	
	// toString() --------------------------------------------------------
	public String toString() {
		StringBuilder sb = new StringBuilder(name);
		// keep decimal precision at two for price
		java.text.DecimalFormat two = new java.text.DecimalFormat("$0.00");
		String newline = "\n", tab = "\t";
		sb.append(newline)
		.append("Base Price: ").append(two.format(baseprice)).append(newline)
		.append("Options:");
		for (int i = 0; i < opsets.length; i++)
			sb.append(newline)
			.append(tab).append(opsets[i].toString());
		
		return sb.toString();
	}
}
