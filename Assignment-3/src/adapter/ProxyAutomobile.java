/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the ProxyAutomobile class.
 */
package adapter;

import java.util.Scanner;

import util.*;
import model.*;

public abstract class ProxyAutomobile {
	private Automobile a1;
	
	// CreateAuto interface methods --------------------------------------
	public void buildAuto(String filename) throws AutoException {
		AutoIO autoIO = new AutoIO();
		a1 = autoIO.buildAutoObject(filename);
	}
	
	public void printAuto(String modelName) {
		System.out.println(a1.toString());
	}
	
	// UpdateAuto interface methods --------------------------------------
	public boolean updateOptionSetName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newName
			) {
		return a1.updateOptionSetName(optionSetName, newName);
	}
	
	public boolean updateOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			) {
		return a1.updateOptionName(optionSetName, optionName, newName);
	}
	
	public boolean updateOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		return a1.updateOptionPrice(optionSetName, optionName, newPrice);
	}
	
	public boolean updateOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName,
			float newPrice) {
		return a1.updateOption(optionSetName, optionName, newName, newPrice);
	}
	
	public boolean updateOptionChoice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName
			) {
		return a1.updateOptionChoice(optionSetName, optionName);
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
		
		a1 = new Automobile(makeHolder, modelHolder, priceHolder);
		
		readOptionSets(input);
		
		input.close();
	}
	
	// helper methods for fix method
	private void readOptionSets(Scanner input) throws AutoException {
		String opsetNameHolder;
		String optionNameHolder;
		float priceHolder;
		String choice;
		
		System.out.print("Enter an option set name (or Q to quit): ");
		choice = input.nextLine();
		while (!choice.toUpperCase().equals("Q")) {
			opsetNameHolder = choice;
			a1.addOptionSet(opsetNameHolder);
			
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
				
				a1.addOption(opsetNameHolder, optionNameHolder, priceHolder);
				System.out.println(optionNameHolder + " added!\n");
				
				System.out.print("Enter an option name for " + opsetNameHolder + " (or Q to quit): ");
				choice = input.nextLine();
			}
			
			System.out.print("\nEnter an option set name (or Q to quit): ");
			choice = input.nextLine();
		}
	}
	
	// AddAuto interface methods -----------------------------------------
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName) {
		return a1.addOptionSet(newOptionSetName);
	}
	
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName,
			float newOptionPrice) {
		return a1.addOption(optionSetName, newOptionName, newOptionPrice);
	}
	
	// DeleteAuto interface methods --------------------------------------
	public boolean deleteOptionSet(
			String autoMake,
			String autoModel,
			String optionSetName) {
		return a1.deleteOptionSet(optionSetName);
	}
	
	public boolean deleteOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName) {
		return a1.deleteOption(optionSetName, optionName);
	}
}
