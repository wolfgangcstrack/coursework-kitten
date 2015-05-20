/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the ProxyAutomobile class.
 */
package adapter;

import java.util.Scanner;
import java.util.LinkedHashMap;

import util.*;
import model.*;

public abstract class ProxyAutomobile {
	protected static LinkedHashMap<String, Automobile> automobiles;
	static { // initialize the LinkedHashMap
		automobiles = new LinkedHashMap<String, Automobile>();
	}
	
	// protected helper methods --------------------------------------------
	protected Automobile getAutoWithKey(String autoMake, String autoModel) {
		return automobiles.get(this.getKey(autoMake, autoModel));
	}
	
	protected String getKey(String autoMake, String autoModel) {
		StringBuilder key = new StringBuilder(autoMake);
		key.append(" ").append(autoModel);
		return key.toString();
	}
	
	// CreateAuto interface methods --------------------------------------
	public void buildAuto(String filename) throws AutoException {
		// Construct a new Automobile from filename
		AutoIO autoIO = new AutoIO();
		Automobile newAuto = autoIO.buildAutoObject(filename);
		// Get key for this Automobile, which is "<Make> <Model>"
		String key = getKey(newAuto.getMake(), newAuto.getModel());
		// Insert the key and new Automobile in the static LinkedHashMap
		automobiles.put(key, newAuto);
	}
	
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName) {
		return getAutoWithKey(autoMake, autoModel)
				.addOptionSet(newOptionSetName);
	}
	
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName,
			float newOptionPrice) {
		return getAutoWithKey(autoMake, autoModel)
				.addOption(optionSetName, newOptionName, newOptionPrice);
	}
	
	// ReadAuto interface methods ----------------------------------------
	public synchronized void printAuto(String autoMake, String autoModel) {
		System.out.println(getAutoWithKey(autoMake, autoModel).toString());
	}
	
	public synchronized void printAllAuto() {
		for (String key : automobiles.keySet()) {
			System.out.println(automobiles.get(key));
			System.out.println();
		}
	}
	
	// UpdateAuto interface methods --------------------------------------
	public boolean updateOptionSetName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newName
			) {
		return getAutoWithKey(autoMake, autoModel)
				.updateOptionSetName(optionSetName, newName);
	}
	
	public boolean updateOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			) {
		return getAutoWithKey(autoMake, autoModel)
				.updateOptionName(optionSetName, optionName, newName);
	}
	
	public boolean updateOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		return getAutoWithKey(autoMake, autoModel)
				.updateOptionPrice(optionSetName, optionName, newPrice);
	}
	
	public boolean updateOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName,
			float newPrice) {
		return getAutoWithKey(autoMake, autoModel)
				.updateOption(optionSetName, optionName, newName, newPrice);
	}
	
	public boolean updateOptionChoice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName
			) {
		return getAutoWithKey(autoMake, autoModel)
				.updateOptionChoice(optionSetName, optionName);
	}
	
	// DeleteAuto interface methods --------------------------------------
	public boolean deleteOptionSet(
			String autoMake,
			String autoModel,
			String optionSetName) {
		return getAutoWithKey(autoMake, autoModel)
				.deleteOptionSet(optionSetName);
	}
	
	public boolean deleteOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName) {
		return getAutoWithKey(autoMake, autoModel)
				.deleteOption(optionSetName, optionName);
	}
	
	public boolean deleteAuto(
			String autoMake,
			String autoModel) {
		// if remove is successful, the value returned by remove() won't be null
		// therefore, the function would return true
		// otherwise, if remove() returns null, function returns false
		return (automobiles.remove(getKey(autoMake, autoModel)) != null ? true : false);
	}
	
	// FixAuto interface methods -----------------------------------------
	/* This method is called in the event that 
	 * the user wants to build the Automobile
	 * manually instead of fixing the input file.
	 * In essence, this is the "fix" method.
	 */
	public void manualBuild(Scanner input) throws AutoException {
		String makeHolder;
		String modelHolder;
		double priceHolder;
		
		System.out.print("Please enter Automobile make: ");
		makeHolder = input.nextLine();
		
		System.out.print("Please enter Automobile model: ");
		modelHolder = input.nextLine();
		
		System.out.print("Please enter base price of " + (makeHolder + " " + modelHolder) + ": ");
		try {
			priceHolder = input.nextDouble();
		} catch (java.util.InputMismatchException imE) {
			throw new AutoException("Error: user entered invalid value");
		} finally {
			input.nextLine(); // clear scanner for next input
		}
		
		Automobile newAuto = new Automobile(makeHolder, modelHolder, priceHolder);
		
		readOptionSets(input, newAuto);
		
		automobiles.put(getKey(makeHolder, modelHolder), newAuto);
	}
	
	// helper methods for fix method
	protected void readOptionSets(Scanner input, Automobile newAuto) throws AutoException {
		String opsetNameHolder;
		String optionNameHolder;
		float priceHolder;
		String choice;
		
		System.out.print("Enter an option set name (or Q to quit): ");
		choice = input.nextLine();
		while (!choice.toUpperCase().equals("Q")) {
			opsetNameHolder = choice;
			newAuto.addOptionSet(opsetNameHolder);
			
			System.out.print("Enter an option name for " + opsetNameHolder + " (or Q to quit): ");
			choice = input.nextLine();
			while (!choice.toUpperCase().equals("Q")) {
				optionNameHolder = choice;
				System.out.print("Enter the price for the option " + optionNameHolder +": ");
				
				try {
					priceHolder = input.nextFloat();
				} catch (java.util.InputMismatchException imE) {
					throw new AutoException("Error: user entered invalid value");
				} finally {
					input.nextLine(); // clear scanner for next input
				}
				
				newAuto.addOption(opsetNameHolder, optionNameHolder, priceHolder);
				System.out.println(optionNameHolder + " added!\n");
				
				System.out.print("Enter an option name for " + opsetNameHolder + " (or Q to quit): ");
				choice = input.nextLine();
			}
			
			System.out.print("\nEnter an option set name (or Q to quit): ");
			choice = input.nextLine();
		}
	}
	
	
}
