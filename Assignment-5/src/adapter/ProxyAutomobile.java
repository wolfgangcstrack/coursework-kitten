/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the ProxyAutomobile class.
 */
package adapter;

import java.util.*;
import java.io.*;

import util.*;
import model.*;

public abstract class ProxyAutomobile {
	protected static Fleet fleet = Fleet.getInstance(); // holds LinkedHashMap of automobiles
	
	// CreateAuto interface methods --------------------------------------
	public void buildAuto(String filename, int fileType) throws AutoException {
		// Construct a new Automobile from filename
		AutoIO autoIO = new AutoIO();
		Automobile newAuto = autoIO.buildAutoObject(filename, fileType);
		
		fleet.addAutomobile(newAuto);
	}
	
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName) {
		return fleet.addOptionSet(autoMake, autoModel, newOptionSetName);
	}
	
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName,
			float newOptionPrice) {
		return fleet.addOption(autoMake, autoModel, optionSetName, newOptionName, newOptionPrice);
	}
	
	// ReadAuto interface methods ----------------------------------------
	public String getListOfAutos() {
		Collection<Automobile> allAutos = fleet.getAllAuto();
		StringBuilder autoList = new StringBuilder();
		String comma_space = ", ";
		char newline = '\n';
		
		for (Automobile auto : allAutos) {
			autoList.append(auto.getMake()).append(comma_space)
			.append(auto.getModel()).append(newline);
		}
		
		return autoList.toString();
	}
	
	public String readAuto(String autoMake, String autoModel) {
		Automobile auto = fleet.getAuto(autoMake, autoModel);
		return (auto != null ? auto.toString() : null);
	}
	
	public String readAllAuto() {
		Collection<Automobile> allAutos = fleet.getAllAuto();
		
		if (allAutos.isEmpty()) {
			return null;
		}
		
		StringBuilder allAutoStrings = new StringBuilder();
		char newline = '\n';
		
		for (Automobile auto : allAutos) {
			allAutoStrings.append(auto.toString()).append(newline);
		}
		
		return allAutoStrings.toString();
	}
	
	public boolean containsOptionSet(
			String autoMake,
			String autoModel,
			String optionSetName) {
		Automobile auto = fleet.getAuto(autoMake, autoModel);
		return (auto != null ? auto.containsOptionSet(optionSetName) : false);
	}
	
	public boolean containsOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName) {
		Automobile auto = fleet.getAuto(autoMake, autoModel);
		return (auto != null ? auto.containsOption(optionSetName, optionName) : false);
	}
	
	public void printAuto(String autoMake, String autoModel) {
		synchronized (System.out) {
			System.out.println(readAuto(autoMake, autoModel));
		}
	}
	
	public void printAllAuto() {
		synchronized (System.out) {
			System.out.println(readAllAuto());
		}
	}
	
	// UpdateAuto interface methods --------------------------------------
	public boolean updateOptionSetName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newName
			) {
		return fleet.updateOptionSetName(autoMake, autoModel, optionSetName, newName);
	}
	
	public boolean updateOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			) {
		return fleet.updateOptionName(autoMake, autoModel, optionSetName, optionName, newName);
	}
	
	public boolean updateOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		return fleet.updateOptionPrice(autoMake, autoModel, optionSetName, optionName, newPrice);
	}
	
	public boolean updateOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName,
			float newPrice) {
		return fleet.updateOption(autoMake, autoModel, optionSetName, optionName, newName, newPrice);
	}
	
	public boolean updateOptionChoice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName
			) {
		return fleet.updateOptionChoice(autoMake, autoModel, optionSetName, optionName);
	}
	
	// DeleteAuto interface methods --------------------------------------
	public boolean deleteOptionSet(
			String autoMake,
			String autoModel,
			String optionSetName) {
		return fleet.deleteOptionSet(autoMake, autoModel, optionSetName);
	}
	
	public boolean deleteOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName) {
		return fleet.deleteOption(autoMake, autoModel, optionSetName, optionName);
	}
	
	public boolean deleteAuto(
			String autoMake,
			String autoModel) {
		return fleet.deleteAuto(autoMake, autoModel);
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
		
		synchronized (System.out) {
			synchronized (input) {
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
			}
		}
		
		Automobile newAuto = new Automobile(makeHolder, modelHolder, priceHolder);
		readOptionSets(input, newAuto);
		
		fleet.addAutomobile(newAuto);
	}
	
	// helper methods for fix method
	protected void readOptionSets(Scanner input, Automobile newAuto) throws AutoException {
		String opsetNameHolder;
		String optionNameHolder;
		float priceHolder;
		String choice;
		
		synchronized (System.out) {
			synchronized (input) {
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
					} // end while
					
					System.out.print("\nEnter an option set name (or Q to quit): ");
					choice = input.nextLine();
				} // end while
			} // end synchronized (input)
		} // end synchronized (System.out)
	}
	
	// AutoServer interface methods --------------------------------------
	public Automobile createAuto(FileReader formattedFileReader) throws AutoException {
		return new AutoIO().buildAutoObject(formattedFileReader);
	}
	public Automobile createAuto(Properties properties) throws AutoException {
		return new AutoIO().buildAutoObject(properties);
	}
	
	public boolean addAuto(Automobile auto) {
		return fleet.addAutomobile(auto);
	}
}
