<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<meta charset="UTF-8">
		<title>My Profile</title>
			<link href="css/bootstrap.min.css" rel="stylesheet">
			<style>
			h1 {
				margin-top: 0px;
			}
			
			/*The red bar you see at the top.*/
			#topBar {
				width: 100%;
				height: 60px;
				background: linear-gradient(rgb(156, 0, 0), rgb(209, 0, 0));
				border-bottom: 3px solid #ffc72c;
			}
			
				/*Div id for the longin and sign up buttons' "container"*/
			#menuBar {
				padding: 15px;
				height: 30px;
			}
			
				/*Using unordered lists to create some buttons in the menuBar div
				(log in and sign up).*/
			ul {
    			list-style-type: none;
    			margin: 0;
    			padding: 0;
			}
			
			li {
			    float: right;
			    margin-left: 5px;
			    margin-right: 5px;
			}
			
			li a, .dropButton {
			    display: block;
			    color: white;
			    text-align: center;
			    padding: 4px 16px;
			    text-decoration: none;
			    border: 2px solid white;
			    border-radius: 4px;
			}
			
			li a:hover, .dropDown:hover .dropButton {
			    background-color: rgb(219, 0, 0);
			    color: #ffc72c;
			}
			
			li.dropDown {
				display: inline-block;
			}
			
			.dropDownContent {
				display: none;
    			position: absolute;
    			background-color: #f9f9f9;
    			min-width: 160px;
    			box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
    			z-index: 1;
			}
			
			.dropDownContent a {
    			color: black;
				padding: 12px 16px;
				text-decoration: none;
				display: block;
				text-align: left;
			}
			
			.dropDownContent a:hover {
				background-color: #f1f1f1
			}

			.dropDown:hover .dropDownContent {
    			display: block;
			}
			
			
				/*Still trying to figure out the welcome box in the middle. I planned on putting a little
				description of the site and placing the search bar in here. (To get started, enter the 
				information of a book you would like to buy or sell here and find it in the search results
				below: [search box]). The background is currently set to yellow so you can see what the
				actual welcomeBox covers and play around with the styling.*/
			#welcomeBoxBackground {
				max-width: 100%;
				height: 250px;
				margin-right: auto;
				margin-left: auto;
				margin-top: 15px;
				margin-bottom: 15px;
				padding-left: 150px;
				padding-right: 150px;
				background-color: #ffc72c;
				
			}
			
			#welcomeBox {
				max-width: 100%;
				padding-left: 50px;
				padding-right: 50px;
				padding-top: 25px;
				padding-bottom: 25px;
				height: 200px;
				background-color: white;

			}
			
			input[type=text] {
			    width: 130px;
			    box-sizing: border-box;
			    border: 2px solid #ccc;
			    border-radius: 4px;
			    font-size: 16px;
			    background-color: white;
			    background-position: 10px 10px; 
			    background-repeat: no-repeat;
			    padding: 12px 20px 12px 40px;
			    -webkit-transition: width 0.4s ease-in-out;
			    transition: width 0.4s ease-in-out;
			    width:100%;
			}
		
			#content {
				max-width: 100%;
				padding-left: 50px;
				padding-right: 50px;
				padding-top: 125px;
				padding-bottom: 25px;
				height: 250px;
				background-color: white;

			}
			
			#searchform form input[type='text']{
				display:inline;
			    box-sizing: border-box;
			    border: 2px solid #ccc;
			    border-radius: 4px;
			    font-size: 16px;
			    background-color: white;
			    background-position: 10px 10px; 
			    background-repeat: no-repeat;
			    padding: 12px 20px 12px 40px;
			    -webkit-transition: width 0.4s ease-in-out;
			    transition: width 0.4s ease-in-out;
			    width:100%;
			}
			</style>

	<script>
	
	
	function verifycode(){
		var xhttp = new XMLHttpRequest();
		xhttp.open("GET", "verifycode.jsp?verify=" + document.verifyform.verify.value, false);
		xhttp.send(); 
		//response text is the response sent back by validate.jsp
		if (xhttp.responseText.trim().length > 0) {
			document.getElementById("verifyerror").innerHTML = xhttp.responseText;
			return false;
		} 
		return true;
	}
	</script>


	</head>
	
	<body style="margin: 0px; padding: 0px">
	<%
	String email = (String)session.getAttribute("verify");
	System.out.println("email code: "+ email );
	
	%>
		<div id="topBar" style="position: fixed;">
			<div id="menuBar">
				<ul>
					<li><form name="loginform" action="Login.jsp" method="POST"><button type="submit">Log in</button></form></li>
					<li><form name="signupform" action="Signup.jsp" method="POST"><button type="submit">Sign up</button></form></li>
				</ul>
			</div>
		</div>
		
		
		<div id="content" style="width:800px; margin:0 auto;">
			<h1 style="text-align: center">Welcome to Trojan's Textbooks!</h1>
					<p style="text-align:center">
					An email has been sent to <%=session.getAttribute("email") %>, please copy the verify code here.
					</p>
					<div id="verifyerror"></div>
					<div id="searchform">
						
						<form name="verifyform" method = "POST" action ="Account" onsubmit="return verifycode();" >
							<input type="text" name ="verify" />
							<input type="submit">
						</form>
					</div>
		</div>
	</body>
</html>