<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "java.util.List, java.util.ArrayList, classes.Textbook, classes.User, classes.Postings" %>
    
 <% List<Postings> posts = (List<Postings>) session.getAttribute("posts");    
 	
 	Textbook textbook = (Textbook) session.getAttribute("book");
 	
 	%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<meta charset="ISO-8859-1">
		<title>Title</title>
		<style>
		#listing {
    			border: 1px solid black;
			}		
			h4 {
				margin-top: 5px;
				margin-bottom: 5px;
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
			
			li a {
			    display: block;
			    color: white;
			    text-align: center;
			    padding: 4px 16px;
			    text-decoration: none;
			    border: 2px solid white;
			    border-radius: 4px;
			}
			
			li a:hover {
			    background-color: rgb(219, 0, 0);
			    color: #ffc72c;
			}
			
				/*Red background you see behind the book tiles. Middle part gets covered by bookDisplay div.*/
			#bookDisplayBackground {
				width: 100%;
				height: 1000px;
				background: linear-gradient(rgb(209, 0, 0), rgb(156, 0, 0));
			}
			
				/*Div that holds all the book tiles. Still need to make it so the height is set dynamically
				based on the number of book tiles are in the div.*/
				
			#bookDisplay {
				margin-right: auto;
				margin-left: auto;
				max-width: 90%;
				height: 95%;
				background-color: white;
				padding-left: 20px;
				padding-right: 20px;
			}
			
				/*Still trying to figure out the welcome box in the middle. I planned on putting a little
				description of the site and placing the search bar in here. (To get started, enter the 
				information of a book you would like to buy or sell here and find it in the search results
				below: [search box]). The background is currently set to yellow so you can see what the
				actual welcomeBox covers and play around with the styling.*/
			#welcomeBoxBackground {
				max-width: 100%;
				height: 350px;
				margin-right: auto;
				margin-left: auto;
				margin-top: 15px;
				margin-bottom: 15px;
				padding-left: 200px;
				padding-right: 200px;
				background-color: #ffc72c;
				
			}
			
			#welcomeBox {
				max-width: 100%;
				padding-left: 100px;
				padding-right: 100px;
				padding-top: 25px;
				padding-bottom: 25px;
				height: 300px;
				background-color: white;
				/*border-left: 5px solid #e8af12;
				border-right: 5px solid #e8af12;*/
			}
			
				/*Image gallery code I grabbed from w3schools. Could still use some tweaking to
				make the text be centered no matter the size of the image. The width of the image 
				is set and the height is dynamically set based on the proportions of the image.*/
			div.gallery {
    			margin: 20px;
    			border: 2px groove rgb(209, 0, 0);
    			border-radius: 5px;
    			float: left;
    			width: 220px;
    			height: 340px;
			}
			div.gallery:hover {
    			border: 2px groove yellow;
    			border-radius: 5px;
			}
			
			div.gallery img {
			    width: 100%;
			    height: auto;
			}
			
			div.desc {
			    padding: 15px;
			    height: 56px;
			    width: 190px;
			    text-align: center;
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
			
			.bookTable {
				width: 100%;
			}
			
			div.bookDisplay {
				left: 20%;
				top: 20%; 
				float: left;
				margin-right: 75px;
				border: 10px solid #a5a5a5;
			}
			
			div.bookInfo {
				left: 50%;
				top: 20%; 
				float: left;
				border: 2px groove black;
				border-radius: 5px;
				padding-left: 50px;
				padding-right: 50px;
			}
			
			div.bookTitle {
				top: 10%; 
				text-align: center;
				width:100%;
				
			}
			
			
			
		</style>
	</head>
	<body style="margin: 0px; padding: 0px">
		<div id="topBar" style="position: fixed;">
			<div id="menuBar">
				<ul>
					<li class="dropDown"><a href="javascript:void(0)" class="dropButton">ttrojan@usc.edu</a>
							<div class="dropDownContent">
								<a href="">Profile</a>
								<a href="">My Listings</a>
								<a href="">Settings</a>
							</div>
					</li>
					<li><a href="Signup.jsp">Log Out</a></li>
				</ul>
			</div>
		</div>
		<div id="topBar"></div>
		<div id="welcomeBoxBackground">
			<div id="welcomeBox">
				<div class="bookDisplay" >
					<img src="<%out.print(textbook.image); %>" alt="OHMYGOD A BOOK" width="250" height="300">
				</div>
				
				<div class="bookInfo">
					<form id = "newPost">
						<input type = "text" value = "Price">
						<input type = "text" value = "Condition">
						<input type = "text" value = "Types">
					</form>
				</div>
				<form name = "view" method = "POST" action ="newListingForm?book=<%out.print(textbook.title); %>">
					<input type = "submit" value = "New Listing">
				</form>
			</div>
		</div>
	
	</body>
</html>