<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Sign up</title>
<link href="css/bootstrap.min.css" rel="stylesheet">
<style>
body {
	font-family: verdana;
	font-size: 12px;
}

input[type=text], input[type=password] {
	width: 100%;
	padding: 10px 15px;
	margin: 8px 0;
	height: 10px;
	display: inline-block;
	border: 1px solid #ccc;
	box-sizing: border-box;
}

#signupform{
	padding-top:30px;
	width: 500px;
	border: 3px solid #f1f1f1;
	margin: 0 auto;
}

#signupform button {
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
	width: 90px;
	border-radius: 50%;
	text-align:center;
}
.title{
	font-size:25px;
	font-weight: bold;
	margin:0 auto;
	text-align: center;
}

.content {
	padding-top:65px;
}

.container {
    padding: 16px;
    width: 100%;
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
		xhttp.open("GET", "validateemail.jsp?email=" + document.signupform.email.value, false);
		xhttp.send();
		var flag = false;
		//response text is the response sent back by validate.jsp
		if (xhttp.responseText.trim().length > 0) {
			document.getElementById("emailerror").innerHTML = xhttp.responseText;
			flag = true;
		} else {
			document.getElementById("emailerror").innerHTML = "";
		}
		
		var passwordxhttp = new XMLHttpRequest();
		passwordxhttp.open("GET", "validatepassword.jsp?password=" + document.signupform.password.value + "&confirmpassword="
				+ document.signupform.confirmpassword.value , false);
		passwordxhttp.send();
		//response text is the response sent back by validate.jsp
		if (passwordxhttp.responseText.trim().length > 0) {
			document.getElementById("passworderror").innerHTML = passwordxhttp.responseText;
			flag = true;
		} else {
			document.getElementById("passworderror").innerHTML = "";
		}
		
		if (flag){
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
		<form name="signupform" id="signupform" action="SendVerifyEmail" method="POST" onsubmit="return validate();">
			<div class="title">Signup</div>
		
			<div class="imgcontainer">
			<img src="http://reignoftroy.com/files/2016/04/11869977-1.jpeg" alt="Avatar" class="avatar">
			</div>
			
			<div class="container">
				<div id="emailerror"></div>
				<label><b>USC Email</b></label>
				<input type="text" placeholder="Enter email" name="email" required>
				
				<div id="passworderror"></div>
				<label><b>Password</b></label>
				<input type="password" placeholder="Enter password" name="password" required>
				<label><b>Confirm Password</b></label>
				<input type="password" placeholder="Confirm password" name="confirmpassword" required>
				
				<label><b>First name</b></label>
				<input type="text" placeholder="Enter first name" name="fname" required>
				<label><b>Last name</b></label>
				<input type="text" placeholder="Enter last name" name="lname" required>
				
				<label><b>Major (Prefix)</b></label>
				<input type="text" placeholder="Enter major (optional)" name="major" >
				<label><b>Phone number</b></label>
				<input type="text" placeholder="Enter phone number (optional)" name="phone" >
				
				<button type="submit">Sign up!</button>
			</div>
		</form>
	</div>
</body>
</html>