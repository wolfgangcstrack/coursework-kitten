/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the CarModelOptionsIO class.
 */
package client;

import java.io.*;
import java.util.*;

import util.*;

public class CarModelOptionsIO {
	public Properties readData(String propertiesFilename) throws AutoException {
		try (FileInputStream fis = new FileInputStream(propertiesFilename)) {
			Properties result = new Properties();
			result.load(fis);
			return result;
		} catch (Exception e) {
			throw new AutoException("Properties file " + propertiesFilename + " unable to be loaded.");
		}
	}
}
