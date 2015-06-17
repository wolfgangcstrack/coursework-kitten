/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the BuildCarModelOptionsClass.
 */
package server;

import model.Automobile;
import util.*;

import java.util.Properties;
import adapter.BuildAuto;

public class BuildCarModelOptions implements AutoServer {
	public Automobile createAuto(Properties properties) throws AutoException {
		return new BuildAuto().createAuto(properties);
	}
	
	public void addAuto(Properties properties) throws AutoException {
		new BuildAuto().addAuto(properties);
	}
	
	public void addAuto(Automobile auto) {
		new BuildAuto().addAuto(auto);
	}
}
