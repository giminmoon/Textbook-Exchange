

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import classes.User;
import classes.hashpassword;

/**
 * Servlet implementation class Account
 */
@WebServlet("/Account")
public class Account extends HttpServlet {
	private static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {	
			HttpSession session = request.getSession();
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root");
			String insertTableSQL = "INSERT INTO User"+ "(email, password, fname, lname, profilepic, major, phone) VALUES"+ "(?,?,?,?,?,?,?)";
			
			String rawpassword = (String)session.getAttribute("password");
			char[] rawchar = rawpassword.toCharArray();
			hashpassword hash = new hashpassword();
			
			String hashedpassword = hash.hash(rawchar);
			System.out.println(hashedpassword);
			PreparedStatement preparedStatement = conn.prepareStatement(insertTableSQL);
			preparedStatement.setString(1, (String)session.getAttribute("email"));
			preparedStatement.setString(2, hashedpassword);
			preparedStatement.setString(3, (String)session.getAttribute("fname"));
			preparedStatement.setString(4, (String)session.getAttribute("lname"));
			preparedStatement.setString(5, "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_1280.png");
			preparedStatement.setString(6, (String)session.getAttribute("major"));
			preparedStatement.setString(7, (String)session.getAttribute("phone"));
			preparedStatement.executeUpdate();
			
			Statement st = conn.createStatement();
			ResultSet rs = st.executeQuery("SELECT * FROM User WHERE email = '"+ (String)session.getAttribute("email") +"';");
			int userID = -1;;
			rs.next();
			userID = rs.getInt("userID");

			rs.close();
			st.close();
			conn.close();
			session.setAttribute("userID", userID);
			
			User user = new User((String)session.getAttribute("email"), (String)session.getAttribute("fname"), (String)session.getAttribute("lname"));
			
			HashMap<Integer, User> myMap = new HashMap<Integer, User>();
			
			myMap.put(userID, user);
			
			session.setAttribute("mymap", myMap);
			session.setAttribute("user", user);
			
			String next = "/home.jsp";
			RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
			dispatch.forward(request,response);
			
			
			
			
			
		} catch (SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		} catch (ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		}
	}
}
