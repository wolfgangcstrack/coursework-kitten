/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoClientQueryHandler class
 */
package server;

public class AutoClientQueryHandler {
	private String query;
	
	protected AutoClientQueryHandler() {
		query = null;
	}
	
	protected String getQuery() { return query; }
	
	/**
	 * @return String: server's response to query parameter
	 */
	protected String handleQuery(String newQuery) {
		query = newQuery;
		
		if (query.contains("get")) {
			return handleGetStatement();
		} else if (query.contains("add")) {
			return handleAddStatement();
		} else if (query.contains("delete")) {
			return handleDeleteStatement();
		} else if (query.contains("edit")) {
			return handleEditStatement();
		}
		
		return null;
	}

	private String handleGetStatement() {
		// TODO Auto-generated method stub
		return null;
	}

	private String handleAddStatement() {
		// TODO Auto-generated method stub
		return null;
	}

	private String handleDeleteStatement() {
		// TODO Auto-generated method stub
		return null;
	}

	private String handleEditStatement() {
		// TODO Auto-generated method stub
		return null;
	}
}
