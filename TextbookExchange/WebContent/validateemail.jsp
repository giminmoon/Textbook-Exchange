<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%@ page import="java.util.*" %>
<%@ page import="java.io.*" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.DriverManager" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="java.sql.SQLException" %>
<%@ page import="java.sql.Statement" %>
<%@ page import="javax.servlet.ServletException" %>
<%@ page import="javax.servlet.annotation.WebServlet" %>
<%@ page import="javax.servlet.http.HttpServlet" %>
<%@ page import="javax.servlet.http.HttpServletRequest" %>
<%@ page import="javax.servlet.http.HttpServletResponse" %>

<%
	String email = request.getParameter("email");	
	
	String[] address = email.split("@");
	
	String returnMessage = "";
	
	if(address.length != 2){
		returnMessage += "<font color=\"red\">Please enter a valid USC email</font><br />";
	}else if(!address[1].equals("usc.edu")){
		returnMessage += "<font color=\"red\">Please enter a valid USC email</font><br />";
	} else {
		try {
			
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root");
			Statement st = conn.createStatement();
			ResultSet rs = st.executeQuery("SELECT email FROM User;");
			while(rs.next()) {
				String existemail = rs.getString("email");
				if(existemail.equals(email)){
					returnMessage += "<font color=\"red\">This USC address is already registered.</font><br />";
				}
			}
			rs.close();
			st.close();
			conn.close();
		} catch (SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		} catch (ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		}	
		
		
		
		
	}
%>

<%= returnMessage %>