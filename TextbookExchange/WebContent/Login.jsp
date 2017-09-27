<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    
<%@ page import="java.io.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Log in</title>
<link href="css/bootstrap.min.css" rel="stylesheet">
<style>

body {
	font-family: verdana;
	font-size: 12px;
}


input[type=text], input[type=password] {
	width: 100%;
	padding: 12px 20px;
	margin: 8px 0;
	display: inline-block;
	border: 1px solid #ccc;
	box-sizing: border-box;
}

#loginform{
	padding-top:30px;
	width: 500px;
	border: 3px solid #f1f1f1;
	margin: 0 auto;
}

#loginform button {
	background-color: #9d2235;
	color: white;
	padding: 14px 20px;
	margin: 8px 0;
	border: none;
	cursor: pointer;
	width: 100%;
}



button:hover {
	opacity: 0.8;
}

.cancelbtn {
	width: auto;
	padding: 10px 18px;
	background-color: #9d2235;
}

.forgotpass {
	width: auto;
	padding: 10px 18px;
	background-color: #9d2235;
	float: right;
}

.imgcontainer {
	text-align: center;
	margin: 24px 0 12px 0;
}

img.avatar {
	width: 40%;
	border-radius: 50%;
}
.title{
	font-size:25px;
	font-weight: bold;
	margin:0 auto;
	text-align: center;
}

.content {
	padding-top:100px;
}

.container {
	width: 100%;
    padding: 16px;
}

span.psw {
    float: right;
    padding-top: 16px;
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
/* Change styles for span and cancel button on extra small screens */
@media screen and (max-width: 300px) {
    span.psw {
       display: block;
       float: none;
    }
    .cancelbtn {
       width: 100%;
    }
    .forgotpass {
       width: 100%;
    }
}
</style>
<script>
	function validate() {
		var xhttp = new XMLHttpRequest();
		xhttp.open("GET", "validatelogin.jsp?email=" + document.loginform.email.value 
				+ "&password=" + document.loginform.password.value, false);
		xhttp.send();
		//response text is the response sent back by validate.jsp
		if (xhttp.responseText.trim().length > 0) {
			document.getElementById("loginerror").innerHTML = xhttp.responseText;
			return false;
		}
		return true;
	}
</script>
</head>
<body>
	<div id="topBar" style="position: fixed;">
		<div id="menuBar">
			<ul>
				<li><form name="login" action="Login.jsp" method="POST"><button type="submit">Log in</button></form></li>
				<li><form name="signup" action="Signup.jsp" method="POST"><button type="submit">Sign up</button></form></li>
				<li><form name="home" action="home.jsp" method="POST"><button type="submit">Home</button></form></li>
			</ul>
		</div>
	</div>
	<div class="content">
		<form name="loginform" id="loginform" action= "login" method="POST" onsubmit="return validate();">
			<div class="title">Login Form</div>
			<div class="imgcontainer">
			<img src="http://reignoftroy.com/files/2016/04/11869977-1.jpeg" alt="Avatar" class="avatar">
			</div>
			
			<div class="container">
			<div id="loginerror"></div>
			<label><b>USC Email</b></label>
			<input type="text" placeholder="Enter Email" name="email" required>
			<label><b>Password</b></label>
			<input type="password" placeholder="Enter Password" name="password" required>
			      
			<button type="submit">Login</button>
			</div>
			
		</form>
	</div>
</body>
</html>