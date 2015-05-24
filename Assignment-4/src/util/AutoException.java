/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoException class.
 */
package util;

public class AutoException extends Exception {
	private static final long serialVersionUID = 1877211652275504063L;
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
}
