/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This class represents the Model/Automotive class.
 */
package model;

import java.util.Iterator;
import java.util.LinkedHashMap;

public class Automobile implements java.io.Serializable {
	// serialVersionUID generated with serialver
	// private static final long serialVersionUID = 6569130310546375757L;
	private String name;
	private String make;
	private String model;
	private double baseprice;
	private LinkedHashMap<String, OptionSet> optionSets;
	
	// constructors ------------------------------------------------------
	public Automobile() { this("", "", "", 0, 0);  }
	public Automobile(String name) { this(name, "", "", 0, 0); }
	public Automobile(String name, String make) { this(name, make, "", 0, 0); }
	public Automobile(String name, String make, String model) { this(name, make, model, 0, 0); }
	public Automobile(String name, String make, String model, double baseprice) {
		this(name, make, model, baseprice, 0);
	}
	
	public Automobile(String name, String make, String model, double baseprice, int optionSetsSize) {
		this.name = name;
		this.make = make;
		this.model = model;
		this.baseprice = baseprice;
		optionSets = new LinkedHashMap<String, OptionSet>(optionSetsSize);
	}
	
	// getters -----------------------------------------------------------
	public String getName() { return name; }
	public String getMake() { return make; }
	public String getModel() { return model; }
	public double getBasePrice() { return baseprice; }
	public LinkedHashMap<String, OptionSet> getOptionSets() { return optionSets; }
	
	// ----- get OptionSet.choice's values
	public String getOptionChoice(String optionSetName) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the name of its choice, else null
		return (opset != null ? opset.getOptionChoice().getName() : null);
	}
	
	public float getOptionChoicePrice(String optionSetName) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the price of its choice, else 0
		return (opset != null ? opset.getOptionChoice().getPrice() : 0);
	}
	
	// ----- get individual Options' values (in context of OptionSet)
	public String getOptionName(String optionSetName, int optionIndex) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the name of the choice, else null
		return (opset != null ? opset.getOption(optionIndex).getName() : null);
	}
	
	public float getOptionPrice(String optionSetName, int optionIndex) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the price of the choice, else 0
		return (opset != null ? opset.getOption(optionIndex).getPrice() : 0);
	}
	
	public double getTotalPrice() {
		double total = baseprice;
		
		Iterator<OptionSet> a = optionSets.values().iterator();
		while (a.hasNext()) {
			total += a.next().getOptionChoice().getPrice();
		}
		
		return total;
	}

	// setters -----------------------------------------------------------
	public void setName(String name) { this.name = name; }
	public void setMake(String make) { this.make = make; }
	public void setModel(String model) { this.model = model; }
	public void setBasePrice(double baseprice) { this.baseprice = baseprice; }
	
	// ----- set the choice for an OptionSet
	public void setOptionChoice(String optionSetName, String optionName) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionChoice(optionName);
		}
	}

	// ----- set individual OptionSets' values
	public void setOptionSetName(String optionSetName, String newName) {
		optionSets.get(optionSetName).setName(newName);
	}

	// ----- set individual Options and their values (in context of OptionSet)
	public void setOptionName(String optionSetName, int optionIndex, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionName(optionIndex, newName);
		}
	}
	
	public void setOptionName(String optionSetName, String optionName, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionName(optionName, newName);
		}
	}
	
	public void setOptionPrice(String optionSetName, int optionIndex, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionPrice(optionIndex, newPrice);
		}
	}
	
	public void setOptionPrice(String optionSetName, String optionName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionPrice(optionName, newPrice);
		}
	}
	
	public void setOption(String optionSetName, int optionIndex, String newName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOption(optionIndex, newName, newPrice);
		}
	}
	
	public void setOption(String optionSetName, String optionName, String newName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOption(optionName, newName, newPrice);
		}
	}
	
	// contains methods ------------------------------------------------------	
	public boolean containsOptionSet(String optionSetName) {
		return optionSets.containsKey(optionSetName);
	}
	
	public boolean containsOption(String optionSetName, String optionName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.containsOption(optionName);
		}
		
		return false;
	}
	
	// update methods (like set, but returns boolean) --------------------
	// ----- update an OptionSetChoice
	public boolean updateOptionChoice(String optionSetName, String optionName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			opset.setOptionChoice(optionName);
			return true;
		}
		
		return false;
	}

	// ----- update individual OptionSets and their values
	public boolean updateOptionSetName(String optionSetName, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			opset.setName(newName);
			return true;
		}
		
		return false;
	}

	// ----- update individual Options and their values (in context of OptionSet)
	public boolean updateOptionName(String optionSetName, String optionName, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.updateOptionName(optionName, newName);
		}
		
		return false;
	}
	
	public boolean updateOptionPrice(String optionSetName, String optionName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.updateOptionPrice(optionName, newPrice);
		}
		
		return false;
	}
	
	public boolean updateOption(String optionSetName, String optionName, String newName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.updateOption(optionName, newName, newPrice);
		}
		
		return false;
	}
	
	/*
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
	
	public boolean addOption(String opsName, String newOpName, float newOpPrice) {
		return addOption(findOptionSet(opsName), newOpName, newOpPrice);
	}
	
	public boolean addOption(int opsIndex, String opName, float opPrice) {
		if (opsIndex < 0 || opsIndex >= opsets.length)
			return false; // opsIndex out of range, Option not added
		
		return opsets[opsIndex].addOption(opName, opPrice);
	}
	*/
	/*
	// delete (OptionSet/Option from this) methods -----------------------
	public boolean deleteOptionSet(String opsName) {
		return deleteOptionSet(findOptionSet(opsName));
	}
	
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
	
	public boolean deleteOption(String opsName, int opIndex) {
		return deleteOption(findOptionSet(opsName), opIndex);
	}
	
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
	*/
	/*
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
	*/
}
