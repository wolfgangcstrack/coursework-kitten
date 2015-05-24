/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This class represents the Model/Automotive class.
 */
package model;

import java.util.Iterator;
import java.util.LinkedHashMap;

public class Automobile implements java.io.Serializable {
	// serialVersionUID generated with serialver
	private static final long serialVersionUID = 1537933008010191291L;
	private String make;
	private String model;
	private double baseprice;
	private LinkedHashMap<String, OptionSet> optionSets;
	
	// constructors ------------------------------------------------------
	public Automobile() { this("", "", 0, 0);  }
	public Automobile(String make) { this(make, "", 0, 0); }
	public Automobile(String make, String model) { this(make, model, 0, 0); }
	public Automobile(String make, String model, double baseprice) {
		this(make, model, baseprice, 0);
	}
	public Automobile(String make, String model, double baseprice, int optionSetsSize) {
		this.make = make;
		this.model = model;
		this.baseprice = baseprice;
		optionSets = new LinkedHashMap<String, OptionSet>(optionSetsSize);
	}
	
	// getters -----------------------------------------------------------
	public synchronized String getMake() { return make; }
	public synchronized String getModel() { return model; }
	public synchronized double getBasePrice() { return baseprice; }
	public synchronized LinkedHashMap<String, OptionSet> getOptionSets() { return optionSets; }
	
	// ----- get OptionSet.choice's values
	public synchronized String getOptionChoice(String optionSetName) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the name of its choice, else null
		return (opset != null ? opset.getOptionChoice().getName() : null);
	}
	
	public synchronized float getOptionChoicePrice(String optionSetName) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the price of its choice, else 0
		return (opset != null ? opset.getOptionChoice().getPrice() : 0);
	}
	
	// ----- get individual Options' values (in context of OptionSet)
	public synchronized String getOptionName(String optionSetName, int optionIndex) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the name of the choice, else null
		return (opset != null ? opset.getOption(optionIndex).getName() : null);
	}
	
	public synchronized float getOptionPrice(String optionSetName, int optionIndex) {
		OptionSet opset = optionSets.get(optionSetName);
		// if optionSetName is valid, return the price of the choice, else 0
		return (opset != null ? opset.getOption(optionIndex).getPrice() : 0);
	}
	
	public synchronized double getTotalPrice() {
		double total = baseprice;
		
		Iterator<OptionSet> a = optionSets.values().iterator();
		while (a.hasNext()) {
			total += a.next().getOptionChoice().getPrice();
		}
		
		return total;
	}

	// setters -----------------------------------------------------------
	public synchronized void setMake(String make) { this.make = make; }
	public synchronized void setModel(String model) { this.model = model; }
	public synchronized void setBasePrice(double baseprice) { this.baseprice = baseprice; }
	
	// ----- set the choice for an OptionSet
	public synchronized void setOptionChoice(String optionSetName, String optionName) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionChoice(optionName);
		}
	}

	// ----- set individual OptionSets' values
	public synchronized void setOptionSetName(String optionSetName, String newName) {
		optionSets.get(optionSetName).setName(newName);
	}

	// ----- set individual Options and their values (in context of OptionSet)
	public synchronized void setOptionName(String optionSetName, int optionIndex, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionName(optionIndex, newName);
		}
	}
	
	public synchronized void setOptionName(String optionSetName, String optionName, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionName(optionName, newName);
		}
	}
	
	public synchronized void setOptionPrice(String optionSetName, int optionIndex, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionPrice(optionIndex, newPrice);
		}
	}
	
	public synchronized void setOptionPrice(String optionSetName, String optionName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOptionPrice(optionName, newPrice);
		}
	}
	
	public synchronized void setOption(String optionSetName, int optionIndex, String newName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOption(optionIndex, newName, newPrice);
		}
	}
	
	public synchronized void setOption(String optionSetName, String optionName, String newName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		if (opset != null) {
			opset.setOption(optionName, newName, newPrice);
		}
	}
	
	// contains methods ------------------------------------------------------	
	public synchronized boolean containsOptionSet(String optionSetName) {
		return optionSets.containsKey(optionSetName);
	}
	
	public synchronized boolean containsOption(String optionSetName, String optionName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.containsOption(optionName);
		}
		
		return false;
	}
	
	// update methods (like set, but returns boolean) --------------------
	// ----- update an OptionSetChoice
	public synchronized boolean updateOptionChoice(String optionSetName, String optionName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			opset.setOptionChoice(optionName);
			return true;
		}
		
		return false;
	}

	// ----- update individual OptionSets and their values
	public synchronized boolean updateOptionSetName(String optionSetName, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			opset.setName(newName);
			return true;
		}
		
		return false;
	}

	// ----- update individual Options and their values (in context of OptionSet)
	public synchronized boolean updateOptionName(String optionSetName, String optionName, String newName) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.updateOptionName(optionName, newName);
		}
		
		return false;
	}
	
	public synchronized boolean updateOptionPrice(String optionSetName, String optionName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.updateOptionPrice(optionName, newPrice);
		}
		
		return false;
	}
	
	public synchronized boolean updateOption(String optionSetName, String optionName, String newName, float newPrice) {
		OptionSet opset = optionSets.get(optionSetName);
		
		if (opset != null) {
			return opset.updateOption(optionName, newName, newPrice);
		}
		
		return false;
	}
	
	// add (OptionSet/Option) methods ------------------------------------
	public synchronized boolean addOptionSet(String opsName) { return addOptionSet(opsName, 0); }
	
	public synchronized boolean addOptionSet(String opsName, int opsSize) {
		if (opsSize < 0) {
			return false;
		}
		
		if (optionSets.containsKey(opsName)) {
			return false;
		}
		
		optionSets.put(opsName, new OptionSet(opsName, opsSize));
		return true;
	}
	
	public synchronized boolean addOption(String opsName, String newOpName, float newOpPrice) {
		OptionSet opset = optionSets.get(opsName);
		
		if (opset != null) {
			if (!opset.containsOption(newOpName)) {
				opset.addOption(newOpName, newOpPrice);
				return true;
			}
		}
		
		return false;
	}
	
	// delete (OptionSet/Option) methods ---------------------------------
	public synchronized boolean deleteOptionSet(String opsName) {
		// if remove was successful, return true, else return false
		return (optionSets.remove(opsName) != null ? true : false);
	}
	
	public synchronized boolean deleteOption(String opsName, String opName) {
		OptionSet opset = optionSets.get(opsName);
		
		if (opset != null) {
			return opset.deleteOption(opName);
		}
		
		return false;
	}
	
	// toString() --------------------------------------------------------
	public synchronized String toString() {
		StringBuilder sb = new StringBuilder(make).append(" ").append(model);
		// keep decimal precision at two for price
		java.text.DecimalFormat two = new java.text.DecimalFormat("$0.00");
		String newline = "\n", tab = "\t";
		sb.append(newline)
		.append("Base Price: ").append(two.format(baseprice)).append(newline)
		.append("Options:").append(newline);
		
		for (String key : optionSets.keySet()) {
			sb.append(tab).append(optionSets.get(key).toString()).append(newline);
		}
		
		return sb.toString();
	}
}
