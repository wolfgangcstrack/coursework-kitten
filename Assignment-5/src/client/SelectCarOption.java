/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the SelectCarOption class.
 */
package client;

import java.io.*;

import adapter.*;

public class SelectCarOption {
	private ObjectInputStream in;
	private ObjectOutputStream out;
	
	private BufferedReader stdIn;
	
	protected SelectCarOption(ObjectInputStream in, ObjectOutputStream out, BufferedReader brIn) {
		this.in = in;
		this.out = out;
		stdIn = brIn;
	}
	
	protected void selectOperation() throws IOException {
		String choice = "";
		
		while (!choice.equals("0")) {
			printMenu(1);
			
			choice = stdIn.readLine();
			
			switch (choice) {
			case "0": break;
			case "1": performOperation(1); break;
			case "2": performOperation(2); break;
			case "3": performOperation(3); break;
			default: System.out.println("Invalid operation choice.\n");
			}
		}
	}
	
	/*
	 * Menu numbers:
	 * 1 - Select Operation
	 * 2 - Select editing choice
	 */
	private void printMenu(int menuNumber) {
		switch (menuNumber) {
		case 1:
			System.out.println("Select a search/edit operation below by entering the number of your choice:\n");
			
			System.out.println("1\tSearch for an automobile on server by make and model");
			System.out.println("2\tList all automobiles on server");
			System.out.println("3\tEdit an automobile's options");
			System.out.println("0\tQuit searching/editing automobiles\n");
			
			break;
		case 2:
			System.out.println("Select an editing operation below by entering the number of your choice:\n");
			
			System.out.println("1\tShow full list of options for the selected automobile");
			System.out.println("2\tAdd an option set");
			System.out.println("3\tAdd an option to an option set");
			System.out.println("4\tEdit an existing option");
			System.out.println("5\tEdit option set choice");
			System.out.println("6\tDelete an option");
			System.out.println("7\tDelete an option set");
			System.out.println("0\tReturn to search/edit menu");
			
			break;
		default:
			System.out.println("Invalid menu number");
		}
	}
	
	private void performOperation(int optionChoice) throws IOException {
		ReadAuto readAuto = new BuildAuto();
		
		switch (optionChoice) {
		case 1:
			System.out.print("Enter make: ");
			String make = stdIn.readLine();
			System.out.println("Enter model: ");
			String model = stdIn.readLine();
			
			String auto = readAuto.readAuto(make, model);
			if (auto == null) {
				auto = "Automobile with make " + make + " and model " + model + " was not found";
			}
			
			System.out.println(auto);
			
			break;
		case 2:
			String autoList = readAuto.getListOfAutos();
			if (autoList == null) {
				autoList = "No automobiles on server";
			}
			
			System.out.println(autoList);
			
			break;
		case 3:
			editAutomobile();
			break;
		default: System.out.println("Invalid operation choice.\n");
		}
	}

	private void editAutomobile() throws IOException {
		System.out.print("Enter make of automobile to edit: ");
		String make = stdIn.readLine();
		System.out.print("Enter model of automobile to edit: ");
		String model = stdIn.readLine();
		
		BuildAuto autoServer = new BuildAuto();
		String fullAutoDescription = autoServer.readAuto(make, model);
		
		if (fullAutoDescription == null) {
			System.out.println("Automobile with make " + make + " and model " + model + " was not found");
			return;
		}
		
		System.out.println("Automobile with make " + make + " and model " + model + " found:\n");
		System.out.println(fullAutoDescription + '\n');
		
		String choice ="", optionSet, option;
		float optionPrice; // input variables
		
		while (!choice.equals("0")) {
			printMenu(2);
			
			System.out.print("\nEnter choice number: ");
			choice = stdIn.readLine();
			System.out.println();
			
			switch (choice) {
			case "1":
				System.out.println(fullAutoDescription + '\n');
				
				break;
			case "2":
				System.out.print("Enter new option set name: ");
				optionSet = stdIn.readLine();
				
				System.out.print("\nThe option set " + optionSet);
				if (autoServer.addOptionSet(make, model, optionSet)) {
					System.out.println(" was successfully added");
				} else {
					System.out.println(" already exists or could not be added");
				}
				
				break;
			case "3":
				addOption(make, model, autoServer);
				
				break;
			case "4":
				editOption(make, model, autoServer);
				
				break;
			case "5":
				editOptionSetChoice(make, model, autoServer);
				
				break;
			}
		}
	}
	
	private void addOption(String make, String model, BuildAuto autoServer) throws IOException {
		String optionSet, option;
		float optionPrice;
		
		System.out.print("Enter name of option set to add new option to: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		if (!autoServer.containsOptionSet(make, model, optionSet)) {
			System.out.println("Error: Option set " + optionSet + " does not exist");
			return;
		}
		
		System.out.print("Enter name of new option to add to " + optionSet + ": ");
		option = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter price of new option " + option + ": ");
		try {
			optionPrice = Float.parseFloat(stdIn.readLine());
		} catch (NumberFormatException nfe) {
			System.out.println("Error: invalid value entered for price");
			return;
		}
		System.out.println();
		
		System.out.print("The option " + optionSet +"."+option + " ");
		if (autoServer.addOption(make, model, optionSet, option, optionPrice)) {
			System.out.println(" was successfully added");
		} else {
			System.out.println(" already exists or could not be added");
		}
	}
	
	private void editOption(String make, String model, BuildAuto autoServer) throws IOException {
		String optionSet, option, newOptionName;
		float newOptionPrice;
		
		System.out.print("Enter name of option set with the option you want to edit: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		if (!autoServer.containsOptionSet(make, model, optionSet)) {
			System.out.println("Error: Option set " + optionSet + " does not exist");
			return;
		}
		
		System.out.print("Enter name of option to edit from " + optionSet + ": ");
		option = stdIn.readLine();
		System.out.println();
		
		if (!autoServer.containsOption(make, model, optionSet, option)) {
			System.out.println("Error: Option " + optionSet+"."+option + " does not exist");
			return;
		}
		
		System.out.print("Enter new option name for " + option + ": ");
		newOptionName = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter new price for option " + newOptionName + ": ");
		try {
			newOptionPrice = Float.parseFloat(stdIn.readLine());
		} catch (NumberFormatException nfe) {
			System.out.println("Error: invalid value entered for price");
			return;
		}
		System.out.println();
		
		System.out.print("The edit of option " + optionSet +"."+option + " to " + optionSet+"."+newOptionName);
		if (autoServer.updateOption(make, model, optionSet, option, newOptionName, newOptionPrice)) {
			System.out.println(" was successful");
		} else {
			System.out.println(" was unsuccessful");
		}
	}
	
	private void editOptionSetChoice(String make, String model, BuildAuto autoServer) throws IOException {
		String optionSet, newOptionChoice;
		
		System.out.print("Enter name of option set whose choice you want to set: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		if (!autoServer.containsOptionSet(make, model, optionSet)) {
			System.out.println("Error: Option set " + optionSet + " does not exist");
			return;
		}
		
		System.out.print("Enter name of option from option set " + optionSet + " to set as choice: ");
		newOptionChoice = stdIn.readLine();
		System.out.println();
		
		System.out.print("The setting of option set " + optionSet + "\'s choice to " + newOptionChoice);
		if (autoServer.updateOptionChoice(make, model, optionSet, newOptionChoice)) {
			System.out.println(" was successful");
		} else {
			System.out.println(" was unsuccessful");
		}
	}
}
