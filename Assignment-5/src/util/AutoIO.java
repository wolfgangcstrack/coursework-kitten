/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This class handles file IO when working with Automotive objects.
 */
package util;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import model.Automobile;

public class AutoIO {
	/**
	 * The buildAutoObject method takes a filename, reads from that file,
	 * and instantiates a new Automotive based on the information in the file.
	 * If the instantiation is successful the Automotive object is returned,
	 * otherwise null is returned
	 * 
	 * File format of filename is assumed to be formatted as follows:
	 * 
	 * Automotive name // must be first line of file
	 * base price // must be second line of file
	 * OptionSet name1
	 * {
	 *     Option name1|price
	 *     Option name2|price
	 * }
	 * OptionSet name2
	 * {
	 *     Option name3|price
	 * }
	 * .
	 * .
	 * .
	 */
	public Automobile buildAutoObject(String filename, boolean isPropertiesFile) throws AutoException {
		if (isPropertiesFile) {
			return buildAutoObject(filename);
		}
		
		StringBuilder errorMessage = new StringBuilder("Error in file ").append(filename);
		String line; // for reading file
		int lineNumber = 1;
		
		try (FileReader file = new FileReader(filename);
				BufferedReader buffer = new BufferedReader(file)) {
			boolean eof = false;
			
			// read the first three lines, which must be the Automotive make, model,
			// and base price and create a new Automotive based on this information
			Automobile newAuto = new 
					Automobile(
							buffer.readLine(),
							buffer.readLine(),
							Double.parseDouble(buffer.readLine()));
			
			while (!eof) {
				line = buffer.readLine();
				
				if (line == null)
					eof = true;
				else {
					String opsName = line; // save for adding Options to this OptionSet name
					newAuto.addOptionSet(opsName);
					
					line = buffer.readLine();
					lineNumber++;
					if (line.charAt(0) != '{') { // next line after OptionSet name must be a "{"
						errorMessage.append(": missing { bracket at line ").append(lineNumber);
						throw new AutoException(errorMessage.toString(), -3);
					}
					
					line = buffer.readLine();
					lineNumber++;
					
					while (line.charAt(0) != '}') { // stop reading Options at the next "}"
						if (line.charAt(0) != '\t') {
							errorMessage.append(": missing tab (\\t) at line ").append(lineNumber);
							throw new AutoException(errorMessage.toString(), -4);
						}
						
						// substring is called to skip the \t before the Option
						// which is formatted as such: name|price
						String option[] = line.substring(1).split("\\|");
						newAuto.addOption(opsName, option[0], Float.parseFloat(option[1]));
						line = buffer.readLine();
						lineNumber++;
					}
				}
			}
			
			return newAuto;
		} catch (IndexOutOfBoundsException iobE) {
			errorMessage.append(": at line ").append(lineNumber);
			throw new AutoException(errorMessage.toString(), -2);
		} catch (NumberFormatException nfE) {
			errorMessage.append(": price not parsable at line ").append(lineNumber);
			throw new AutoException(errorMessage.toString(), -1);
		} catch (FileNotFoundException fnfE) {
			errorMessage.append(": file not found");
			throw new AutoException (errorMessage.toString(), 1);
		} catch (IOException ioE) {
			errorMessage.append(": at line ").append(lineNumber);
			throw new AutoException(errorMessage.toString(), 2);
		}
	}
	
	private Automobile buildAutoObject(String propertiesFileName) throws AutoException {
		StringBuilder errorMessage = new StringBuilder("Error in file ");
		errorMessage.append(propertiesFileName);
		Properties properties = new Properties();
		
		try (FileInputStream in = new FileInputStream(propertiesFileName)) {
			properties.load(in);
			
			String key;
			String make, model;
			double baseprice;
			
			// get base properties of new auto
			key = "Make";
			make = properties.getProperty(key);
			properties.remove(key);
			key = "Model";
			model = properties.getProperty(key);
			properties.remove(key);
			key = "Baseprice";
			baseprice = Double.parseDouble(properties.getProperty(key));
			properties.remove(key);
			
			Automobile newAuto = new Automobile(make, model, baseprice);
			
			Map<Character, String> optionSets = new HashMap<Character, String>();
			Map<Character, ArrayList<String>> options = new HashMap<Character, ArrayList<String>>();
			
			// parse the option sets and semi-parse the options
			for (Object setKey : properties.keySet()) {
				key = (String) setKey;
				if (key.substring(0, 9) == "OptionSet") {
					optionSets.put(key.charAt(9), properties.getProperty(key));
				} else if (key.substring(0, 6) == "Option") {
					char optionSetLetter = key.charAt(6);
					
					// if key doesn't exist, instantiate a new list with the key
					if (!options.containsKey(optionSetLetter)) {
						options.put(optionSetLetter, new ArrayList<String>());
					}
					
					options.get(optionSetLetter).add(properties.getProperty(key));
				} else { // skip any keys that don't follow pattern
					continue;
				}
			}
			
			// complete parsing of options and add option sets and options to newAuto
			for (Character optionSetKey : options.keySet()) {
				String optionSet = optionSets.get(optionSetKey);
				newAuto.addOptionSet(optionSet);
				
				String[] parsedOption;
				for (String unparsedOption : options.get(optionSetKey)) {
					parsedOption = unparsedOption.split("\\|");
					newAuto.addOption(optionSet, parsedOption[0], Float.parseFloat(parsedOption[1]));
				}
			}
			
			return newAuto;
		} catch (NumberFormatException nfE) {
			errorMessage.append(": Baseprice property not parsable or missing");
			throw new AutoException(errorMessage.toString(), -1);
		} catch (FileNotFoundException fnfE) {
			errorMessage.append(": file not found");
			throw new AutoException (errorMessage.toString(), 1);
		} catch (IOException ioE) {
			throw new AutoException(errorMessage.toString(), 2);
		}
	}
	
	public void serializeAutoObject(String filename, Automobile auto) throws AutoException {
		try (FileOutputStream fos = new FileOutputStream(filename);
				ObjectOutputStream out = new ObjectOutputStream(fos)) {
			out.writeObject(auto);
		} catch (FileNotFoundException fnfE) {
			throw new AutoException(filename + " not found", 3);
		} catch (IOException ioE) {
			throw new AutoException("IOException in serialization file: " + filename, 4);
		}
	}
	
	public Automobile deserializeAutoObject(String filename) throws AutoException {
		Automobile result = null;
		
		try (FileInputStream fos = new FileInputStream(filename);
				ObjectInputStream in = new ObjectInputStream(fos)) {
			result = (Automobile) in.readObject();
		} catch (FileNotFoundException fnfe) {
			throw new AutoException(filename + " not found", 5);
		} catch (IOException ioe) {
			throw new AutoException("IOException in deserialization file: " + filename, 6);
		} catch (ClassNotFoundException cnfe) {
			throw new AutoException("Automobile class not found", 7);
		}
		
		return result;
	}
}
