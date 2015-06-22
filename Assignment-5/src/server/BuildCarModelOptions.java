/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the BuildCarModelOptionsClass.
 */
package server;

import java.util.Properties;
import java.io.*;

import model.Automobile;
import util.*;
import adapter.BuildAuto;

public class BuildCarModelOptions implements AutoServer {
	public BuildCarModelOptions() {}
	
	public Automobile createAuto(Properties properties) throws AutoException {
		return new BuildAuto().createAuto(properties);
	}
	
	public Automobile createAuto(FileReader formattedFileReader) throws AutoException {
		return new BuildAuto().createAuto(formattedFileReader);
	}
	
	public void addAuto(Automobile auto) {
		new BuildAuto().addAuto(auto);
	}
}
