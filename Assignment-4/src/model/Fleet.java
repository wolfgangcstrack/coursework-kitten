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
	private static final Fleet fleet = new Fleet();
	private static Map<String, Automobile> automobiles;
	
	/** private constructor ensures this Singleton Fleet will only be
	 * instantiated once; that one time it is instantiated is here */
	private Fleet() {
		// instantiate a synchronized LinkedHashMap
		automobiles = Collections.synchronizedMap(new LinkedHashMap<String, Automobile>());
	}
	
	// method for getting the singleton Fleet instance -------------------
	public synchronized static Fleet getInstance() { return fleet; }
	
	// private helper methods ------------------------------------------
	private Automobile getAutoWithKey(String autoMake, String autoModel) {
		return automobiles.get(getKey(autoMake, autoModel));
	}
	
	private String getKey(String autoMake, String autoModel) {
		StringBuilder key = new StringBuilder(autoMake);
		key.append(" ").append(autoModel);
		return key.toString();
	}
	
	// Create methods ----------------------------------------------------
	public synchronized boolean addAutomobile(Automobile auto) {
		String key = getKey(auto.getMake(), auto.getModel());
		
		if (automobiles.containsKey(key)) {
			return false;
		} else {
			automobiles.put(key, auto);
			return true;
		}
	}
	
	public boolean addOptionSet(
			String autoMake,
			String autoModel,
			String newOptionSetName) {
		String key = getKey(autoMake, autoModel);
		
		synchronized (automobiles) {
			if (automobiles.containsKey(key)) {
				return automobiles.get(key).addOptionSet(newOptionSetName);
			} // else
			return false;
		}
	}
	
	public boolean addOption(
			String autoMake,
			String autoModel,
			String optionSetName,
			String newOptionName,
			float newOptionPrice) {
		String key = getKey(autoMake, autoModel);
		
		synchronized (automobiles) {
			if (automobiles.containsKey(key)) {
				return automobiles.get(key).addOption(optionSetName, newOptionName, newOptionPrice);
			} // else
			return false;
		}
	}
	
	// Read methods ------------------------------------------------------
//	public synchronized Automobile getAuto(String autoMake, String autoModel) {
//		return this.getAutoWithKey(autoMake, autoModel);
//	}
}
