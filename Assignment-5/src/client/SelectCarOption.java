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
	private ObjectInputStream fromServer;
	private ObjectOutputStream toServer;
	
	private BufferedReader stdIn;
	
	protected SelectCarOption(ObjectInputStream in, ObjectOutputStream out, BufferedReader brIn) {
		this.fromServer = in;
		this.toServer = out;
		stdIn = brIn;
	}
	
	protected void run() throws IOException, ClassNotFoundException {
		String choice = "";
		String serverResponse = null;
		
		while (!choice.equals("0")) {
			if (serverResponse != null) {
				System.out.print("Server: ");
				if (serverResponse.contains("\n")) {
					System.out.println("\n\n" + serverResponse);
				} else {
					System.out.println(serverResponse);
				}
			}
			
			printMenu(1);
			
			choice = stdIn.readLine();
			
			switch (choice) {
			case "0": break;
			case "1":
				System.out.print("Enter make: ");
				String make = stdIn.readLine();
				System.out.println("Enter model: ");
				String model = stdIn.readLine();
				
				// send server query for requested automobile
				toServer.writeObject("get auto " + make + " " + model);
				
				break;
			case "2":
				toServer.writeObject("get all auto");
				
				break;
			case "3":
				editAutomobile(); // gets its own server response
				serverResponse = null;
				continue; // skip to beginning of while loop
			default: System.out.println("Invalid operation choice.\n");
			}
			
			System.out.println();
			
			serverResponse = (String) fromServer.readObject();
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

	private void editAutomobile() throws IOException, ClassNotFoundException {
		System.out.print("Enter make of automobile to edit: ");
		String make = stdIn.readLine();
		System.out.print("Enter model of automobile to edit: ");
		String model = stdIn.readLine();
		
		toServer.writeObject("get auto " + make + " " + model);
		String fullAutoDescription = (String) fromServer.readObject();
		
		if (fullAutoDescription == null) {
			System.out.println("Server: Automobile with make " + make + " and model " + model + " was not found");
			return;
		}
		
		System.out.println("Server: Automobile with make " + make + " and model " + model + " found:\n");
		System.out.println(fullAutoDescription + '\n');
		
		String choice = "", optionSet, serverResponse = null;
		
		while (!choice.equals("0")) {
			
			System.out.println();
			
			if (serverResponse != null) {
				System.out.println("Server: " + serverResponse);
			}
			
			printMenu(2);
			
			System.out.print("\nEnter choice number: ");
			choice = stdIn.readLine();
			System.out.println();
			
			switch (choice) {
			case "0": break;
			case "1":
				System.out.println(fullAutoDescription + '\n');
				serverResponse = null;
				
				continue; // skip to top of while loop
			case "2":
				System.out.print("Enter new option set name: ");
				optionSet = stdIn.readLine();
				
				toServer.writeObject("add optionSet "+make+" "+model+" "+optionSet);

				break;
			case "3":
				addOption(make, model);

				break;
			case "4":
				editOption(make, model);
				
				break;
			case "5":
				editOptionSetChoice(make, model);
				
				break;
			case "6":
				deleteOption(make, model);
				
				break;
			case "7":
				System.out.print("Enter name of option set to delete: ");
				optionSet = stdIn.readLine();
				
				toServer.writeObject("delete optionSet "+make+" "+model+" "+optionSet);
				
				break;
			default:
				System.out.println("Invalid edit choice");
				serverResponse = null;
				continue; // skip to top of while loop
			}
			
			serverResponse = (String) fromServer.readObject();
		}
	}
	
	private void addOption(String make, String model) throws IOException {
		String optionSet, option;
		float optionPrice;
		
		System.out.print("Enter name of option set to add new option to: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter name of new option to add to " + optionSet + ": ");
		option = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter price of new option " + option + ": ");
		try {
			optionPrice = Float.parseFloat(stdIn.readLine());
			System.out.println();
		} catch (NumberFormatException nfe) {
			System.out.println("Error: invalid value entered for price");
			toServer.writeObject("get null");
			return;
		}
		
		toServer.writeObject("add option "+make+" "+model+" "+optionSet+" "+option+" "+optionPrice);
	}
	
	private void editOption(String make, String model) throws IOException {
		String optionSet, option, newOptionName;
		float newOptionPrice;
		
		System.out.print("Enter name of option set with the option you want to edit: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter name of option to edit from " + optionSet + ": ");
		option = stdIn.readLine();
		System.out.println();
		
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
		
		toServer.writeObject("edit option "
				+ make + " "
				+ model + " "
				+ optionSet + " "
				+ option + " "
				+ newOptionName + " "
				+ newOptionPrice);
	}
	
	private void editOptionSetChoice(String make, String model) throws IOException {
		String optionSet, newOptionChoice;
		
		System.out.print("Enter name of option set whose choice you want to set: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter name of option from option set " + optionSet + " to set as choice: ");
		newOptionChoice = stdIn.readLine();
		System.out.println();
		
		toServer.writeObject("edit option set choice "+make+" "+model+" "+optionSet+" "+newOptionChoice);
	}
	
	private void deleteOption(String make, String model) throws IOException {
		String optionSet, option;
		
		System.out.print("Enter name of option set with option you want to delete: ");
		optionSet = stdIn.readLine();
		System.out.println();
		
		System.out.print("Enter name of option from option set " + optionSet + " to delete: ");
		option = stdIn.readLine();
		System.out.println();
		
		toServer.writeObject("delete option "+make+" "+model+" "+optionSet+" "+option);
	}
}
