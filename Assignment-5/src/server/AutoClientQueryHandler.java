/*
 * CIS 35B
 * Author: Wolfgang C. Strack
 * Compiler: Java 8 with Eclipse
 * 
 * This is the AutoClientQueryHandler class
 */
package server;

import adapter.BuildAuto;

public class AutoClientQueryHandler {
	private String query;
	BuildAuto autoServer;
	
	protected AutoClientQueryHandler() {
		query = null;
		autoServer = new BuildAuto();
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
		} else {
			return "Invalid query";
		}
	}

	private String handleGetStatement() {
		String autoDescription;
		
		if (query.contains("get auto ") && query.length() > 9) {
			String[] params = query.substring(9).split(" ");
			
			if (params.length < 2) {
				return "Invalid get query";
			}
			
			autoDescription = autoServer.readAuto(params[0], params[1]);
			
			if (autoDescription == null) {
				return "Automobile does not exist: "+params[0]+" "+params[1];
			}
			
			return autoDescription;
		} else if (query.equals("get all auto")) {
			autoDescription = autoServer.readAllAuto();
			
			if (autoDescription == null) {
				return "No automobiles to list";
			}
			
			return autoDescription;
		} else if (query.equals("get null")) {
			return null;
		} else {
			return "Invalid get query";
		}
	}

	private String handleAddStatement() {
		if (query.contains("add optionSet ") && query.length() > 14) {
			String[] params = query.substring(14).split(" ");
			
			if (params.length < 3) {
				return "Invalid add query";
			}
			
			if (autoServer.addOptionSet(params[0], params[1], params[2])) {
				return "Successful add of new option set";
			} else {
				return "Unsuccessful add of new option set";
			}
		} else if (query.contains("add option ") && query.length() > 11) {
			String[] params = query.substring(11).split(" ");
			
			if (params.length < 5) {
				return "Invalid add query";
			}
			
			try {
				if (autoServer.addOption(
						params[0], params[1], 
						params[2], params[3], 
						Float.parseFloat(params[4]))) {
					return "Successful add of new option";
				} else {
					return "Unsuccessful add of new option: option already exists or cannot be added";
				}
			} catch (NumberFormatException nfe) {
				return "Unsuccessful add of new option: invalid price argument";
			}
		} else {
			return "Invalid add query";
		}
	}

	private String handleDeleteStatement() {
		if (query.contains("delete optionSet ") && query.length() > 17) {
			String[] params = query.substring(17).split(" ");
			
			if (params.length < 3) {
				return "Invalid delete query";
			}
			
			if (autoServer.deleteOptionSet(params[0], params[1], params[2])) {
				return "Successful delete of option set";
			} else {
				return "Unsuccessful delete of option set";
			}
		} else if (query.contains("delete option ") && query.length() > 14) {
			String[] params = query.substring(14).split(" ");
			
			if (params.length < 4) {
				return "Invalid delete query";
			}
			
			if (autoServer.deleteOption(params[0], params[1], params[2], params[3])) {
				return "Successful delete of option";
			} else {
				return "Unsuccessful delete of option";
			}
		} else {
			return "Invalid delete query";
		}
	}

	private String handleEditStatement() {
		if (query.contains("edit option set choice ") && query.length() > 23) {
			String[] params = query.substring(23).split(" ");
			
			if (params.length < 4) {
				return "Invalid edit query";
			}
			
			if (autoServer.updateOptionChoice(params[0], params[1], params[2], params[3])) {
				return "Successful edit of option choice";
			} else {
				return "Unsuccessful edit of option choice";
			}
		} else if (query.contains("edit option ") && query.length() > 12) {
			String[] params = query.substring(12).split(" ");
			
			if (params.length < 6) {
				return "Invalid edit query";
			}
			
			try {
				if (autoServer.updateOption(
						params[0], params[1],
						params[2], params[3],
						params[4], Float.parseFloat(params[5]))) {
					return "Successful edit of option";
				} else {
					return "Unsuccessful edit of option";
				}
			} catch (NumberFormatException nfe) {
				return "Unsuccessful edit of option: invalid price argument";
			}
		} else {
			return "Invalid edit query";
		}
	}
}
