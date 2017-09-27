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
	String returnMessage = "";	
	String email = request.getParameter("email");	
	String verify = request.getParameter("verify");	
	String oldverify = (String)session.getAttribute("verify");
	
	if(!verify.equals(oldverify)){
		returnMessage += "<font color=\"red\">The verification code does not match.</font><br />";
	}
	
%>

<%= returnMessage %>