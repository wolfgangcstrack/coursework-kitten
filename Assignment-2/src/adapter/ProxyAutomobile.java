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
	public void updateOptionSetName(
			String modelName,
			String optionSetName,
			String newName
			) {
		a1.updateOptionSetName(optionSetName, newName);
	}
	
	public void updateOptionName(
			String modelName,
			String optionSetName,
			String optionName,
			String newName
			) {
		a1.updateOptionName(optionSetName, optionName, newName);
	}
	
	public void updateOptionPrice(
			String modelName,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		a1.updateOptionPrice(optionSetName, optionName, newPrice);
	}
	
	// FixAuto interface methods -----------------------------------------
	/* This method is called in the event that 
	 * the user wants to build the Automobile
	 * manually instead of fixing the input file.
	 * In essence, this is the "fix" method.
	 */
	public model.Automobile manualBuild() {
		String nameHolder;
		double priceHolder;
		Scanner input = new Scanner(System.in);
		
		System.out.print("Please enter Automobile name: ");
		nameHolder = input.nextLine();
		System.out.print("Please enter base price of " + nameHolder + ": ");
		priceHolder = input.nextDouble();
		
		model.Automobile newAuto = new model.Automobile(nameHolder, priceHolder);
		
		readOptionSets(input, newAuto);
		
		input.close();
		return newAuto;
	}
	
	// helper methods for fix method
	private void readOptionSets(Scanner input, model.Automobile newAuto) {
		String opsetNameHolder;
		String optionNameHolder;
		float priceHolder;
		String choice;
		
		System.out.print("Enter an option set name (or Q to quit): ");
		choice = input.nextLine();
		while (!choice.equals("Q")) {
			opsetNameHolder = choice;
			newAuto.addOptionSet(opsetNameHolder);
			
			System.out.print("Enter an option name for " + opsetNameHolder + " (or Q to quit): ");
			choice = input.nextLine();
			while (!choice.equals("Q")) {
				optionNameHolder = choice;
				System.out.print("Enter the price for the option " + optionNameHolder +": ");
				priceHolder = input.nextFloat();
				newAuto.addOption(opsetNameHolder, optionNameHolder, priceHolder);
				System.out.println(optionNameHolder + " added!\n");
				
				System.out.print("Enter an option name for " + opsetNameHolder + " (or Q to quit): ");
				choice = input.nextLine();
			}
			
			System.out.print("Enter an option set name (or Q to quit): ");
			choice = input.nextLine();
		}
	}
}
