<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%
	//javacode
	String password = request.getParameter("password");
	String confirmpassword = request.getParameter("confirmpassword");
	String errorMessage = "";
	if(password == null || password.trim().length() == 0){
		errorMessage += "<font color=\"red\">Please enter a password longer than 8 characters.</font><br />";
	} else if(password.trim().length() < 8) {
		errorMessage += "<font color=\"red\">Please enter a password longer than 8 characters.</font><br />";
	} else {
		if(!password.equals(confirmpassword)) {
			errorMessage += "<font color=\"red\">Confirm password does not match.</font><br />";
		}
	}
	
%>
<%= errorMessage %>