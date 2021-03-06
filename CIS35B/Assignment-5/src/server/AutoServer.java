/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoServer interface.
 */
package server;

import java.io.FileReader;
import java.util.Properties;

import model.Automobile;
import util.AutoException;

public interface AutoServer {
	public Automobile createAuto(FileReader formattedFileReader) throws AutoException;
	public Automobile createAuto(Properties properties) throws AutoException;
	public boolean addAuto(Automobile auto);
}
