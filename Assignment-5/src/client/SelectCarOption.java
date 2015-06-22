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
	
	protected void selectOperation() {
		String choice = "";
		
		while (!choice.equals("0")) {
			printMenu();
			
			try {
				choice = stdIn.readLine();
			} catch (IOException e) {
				e.printStackTrace();
				break;
			}
			
			switch (choice) {
			case "0": break;
			case "1": performOperation(1); break;
			case "2": performOperation(2); break;
			case "3": performOperation(3); break;
			default: System.out.println("Invalid operation choice.\n");
			}
		}
	}
	
	private void printMenu() {
		System.out.println("Select an option below by entering the number of your choice:\n");
		
		System.out.println("1\tSearch for an automobile on server by make and model");
		System.out.println("2\tList all automobiles on server");
		System.out.println("3\tEdit an automobile's options");
		System.out.println("0\tQuit searching/editing automobiles\n");
	}
	
	private void performOperation(int optionChoice) {
		switch (optionChoice) {
		case 1:			
			try {
				System.out.print("Enter make: ");
				String make = stdIn.readLine();
				System.out.println("Enter model: ");
				String model = stdIn.readLine();
				
				ReadAuto readAuto = new BuildAuto();
				String auto = readAuto.readAuto(make, model);
				if (auto == null) {
					auto = "Automobile with make " + make + " and model " + model + " was not found";
				}
				
				System.out.println(auto);
				
			} catch (IOException ioe) {
				System.out.println(ioe.toString());
			}
			
			break;
		case 2:
			ReadAuto readAuto = new BuildAuto();
			System.out.println(readAuto.getListOfAutos());
			
			break;
		case 3:
			editAutomobile();
			break;
		default: System.out.println("Invalid operation choice.\n");
		}
	}

	private void editAutomobile() {
		
	}
}
