/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoServer interface.
 */
package server;

import java.util.Properties;

import model.Automobile;
import util.AutoException;

public interface AutoServer {
	public Automobile createAuto(Properties properties) throws AutoException;
	
	public void addAuto(Properties properties) throws AutoException;
	public void addAuto(Automobile auto);
}
