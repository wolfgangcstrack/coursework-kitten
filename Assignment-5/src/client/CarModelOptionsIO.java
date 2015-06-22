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

public class CarModelOptionsIO {
	/*
	 * File types:
	 * 1 - Formatted file (see util.AutoIO)
	 * 2 - Properties file
	 */
	public Object readData(String filename, int fileType) throws FileNotFoundException, IOException {
		switch (fileType) {
		case 1:
			FileReader filereader = new FileReader(filename);
			return filereader;
		case 2:
			FileInputStream fis = new FileInputStream(filename);
			Properties properties = new Properties();
			properties.load(fis);
			return properties;
		default:
			return null;
		}
	}
}
