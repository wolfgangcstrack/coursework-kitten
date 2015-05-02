/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * OS/Compiler: Windows 8/Java 8 with Eclipse
 * 
 * This is the AutoException class.
 */
package util;

import java.util.*;

public class AutoException extends Exception {
	private String errorMessage;
	private int errorNO;
	
	// constructors
	public AutoException() { super(); }
	public AutoException(String msg) { super(msg); }
	public AutoException(int errorno) { super(); errorNO = errorno; }
	public AutoException(String msg, int errorno) { super(msg); errorNO = errorno; }
	
	// getters
	public String getErrorMessage() { return errorMessage; }
	public int getErrorNO() { return errorNO; }
	
	// setters
	public void setErrorMessage(String msg) { errorMessage = msg; }
	public void setErrorNO(int errorno) { errorNO = errorno; }
	
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
