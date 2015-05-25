/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This singleton class holds a static LinkedHashMap ("Fleet") of automobiles.
 */
package model;

import java.util.Collections;
import java.util.Map;
import java.util.LinkedHashMap;

public class Fleet {
	private static final Fleet instance = new Fleet();
	private static final Object instanceLock = new Object();
	private static Map<String, Automobile> fleet; // is thread-safe
	
	/** private constructor ensures this Singleton Fleet will only be
	 * instantiated once; that one time it is instantiated is here */
	private Fleet() {
		// instantiate a thread-safe LinkedHashMap
		fleet = Collections.synchronizedMap(new LinkedHashMap<String, Automobile>());
	}
	
	// method for getting the singleton Fleet instance -------------------
	public static Fleet getInstance() {
		synchronized (instanceLock) {
			return instance;
		}
	}
	
	// private helper methods ------------------------------------------
//	private Automobile getAutoWithKey(String autoMake, String autoModel) {
//		return fleet.get(getKey(autoMake, autoModel));
//	}
	
	private String getKey(String autoMake, String autoModel) {
		StringBuilder key = new StringBuilder(autoMake);
		key.append(" ").append(autoModel);
		return key.toString();
	}
	
	// Create methods ----------------------------------------------------
	public boolean addAutomobile(Automobile auto) {
		String key = getKey(auto.getMake(), auto.getModel());
		
		if (fleet.containsKey(key)) {
			return false;
		} else {
			fleet.put(key, auto);
			return true;
		}
	}
	
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).addOptionSet(newOptionSetName);
		} // else
		return false;
	}
	
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName,
			float newOptionPrice) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).addOption(optionSetName, newOptionName, newOptionPrice);
		} // else
		return false;
	}
	
	// Read methods ------------------------------------------------------
	public Automobile getAuto(String autoMake, String autoModel) {
		return fleet.get(getKey(autoMake, autoModel));
	}
	
	// Update methods ----------------------------------------------------
	public boolean updateOptionSetName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newName
			) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).updateOptionSetName(optionSetName, newName);
		} // else
		return false;
	}
	
	public boolean updateOptionName(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName
			) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).updateOptionName(optionSetName, optionName, newName);
		} // else
		return false;
	}
	
	public boolean updateOptionPrice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			float newPrice
			) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).updateOptionPrice(optionSetName, optionName, newPrice);
		} // else
		return false;
	}
	
	public boolean updateOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName,
			String newName,
			float newPrice) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).updateOption(optionSetName, optionName, newName, newPrice);
		} // else
		return false;
	}
	
	public boolean updateOptionChoice(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName
			) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).updateOptionChoice(optionSetName, optionName);
		} // else
		return false;
	}
	
	// Delete methods ----------------------------------------------------
	public boolean deleteOptionSet(
			String autoMake,
			String autoModel,
			String optionSetName) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).deleteOptionSet(optionSetName);
		} // else
		return false;
	}
	
	public boolean deleteOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String optionName) {
		String key = getKey(autoMake, autoModel);
		
		if (fleet.containsKey(key)) {
			return fleet.get(key).deleteOption(optionSetName, optionName);
		} // else
		return false;
	}
	
	public boolean deleteAuto(
			String autoMake,
			String autoModel) {
		String key = getKey(autoMake, autoModel);
		// if remove was successful, return true; else, return false
		return (fleet.remove(key) != null ? true : false);
	}
}
