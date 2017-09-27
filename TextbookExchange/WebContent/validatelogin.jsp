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
<%@ page import="classes.hashpassword" %>
<%
	String email = request.getParameter("email");	
	String password = request.getParameter("password");	
	String returnMessage = "";
	char[] passchar = password.toCharArray();
	hashpassword hash = new hashpassword();
	
	try {
		
		Class.forName("com.mysql.jdbc.Driver");
		Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root");
		Statement st = conn.createStatement();
		ResultSet rs = st.executeQuery("SELECT * FROM User;");
		int userID = -1;
		boolean flag = false;
		
		
		while(rs.next()) {
			String dbemail = rs.getString("email");
			String dbpassword = rs.getString("password");
			
			if(dbemail.equals(email) && hash.authenticate(passchar, dbpassword)){
				//email, password, fname, lname, profilepic, major, phone
				userID = rs.getInt("userID");
				session = request.getSession();
				session.setAttribute("userID", userID);
				session.setAttribute("email", rs.getString("email"));
				session.setAttribute("fname", rs.getString("fname"));
				session.setAttribute("lname", rs.getString("lname"));
				session.setAttribute("phone", rs.getString("phone"));
				session.setAttribute("profilepic", rs.getString("profilepic"));
				session.setAttribute("major", rs.getString("major"));
				flag = true;
			}
		}
		
		if(!flag){
			returnMessage += "<font color=\"red\">Incorrect email and password combination.</font><br />";
		}
		
		rs.close();
		st.close();
		conn.close();
	} catch (SQLException sqle) {
		System.out.println("sqle: " + sqle.getMessage());
	} catch (ClassNotFoundException cnfe) {
		System.out.println("cnfe: " + cnfe.getMessage());
	}	
		
%>

<%= returnMessage %>