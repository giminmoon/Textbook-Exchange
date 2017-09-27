

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayDeque;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import classes.Postings;
import classes.Textbook;

/**
 * Servlet implementation class addListing
 */
@WebServlet("/addListing")
public class addListing extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {	
			HttpSession session = request.getSession();
			Textbook textbook = (Textbook)session.getAttribute("book");
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root");
			String insertTableSQL = "INSERT INTO Listing"+ "(userID, bookID, bookcondition, price) VALUES"+ "(?,?,?,?)";
			
			PreparedStatement preparedStatement = conn.prepareStatement(insertTableSQL);
			preparedStatement.setInt(1, (int)session.getAttribute("userID"));
			preparedStatement.setInt(2, textbook.id);
			preparedStatement.setString(3, request.getParameter("condition"));
			preparedStatement.setInt(4, Integer.parseInt(request.getParameter("price")));
			preparedStatement.executeUpdate();
			
			ArrayDeque<Textbook> textbookqueue = new ArrayDeque<Textbook>(8);
			textbookqueue.add(textbook);
			
			Statement st = conn.createStatement();
			ResultSet rs = st.executeQuery("SELECT * FROM Listing WHERE userID='" + (int)session.getAttribute("userID") + "' AND bookID='"
					+ textbook.id + "'");
			rs.next();
			
			int listID = rs.getInt("listingID");
			
			Statement st1 = conn.createStatement();
			ResultSet rs1 = st1.executeQuery("SELECT * FROM User WHERE userID ='" + (int)session.getAttribute("userID") + "'");
			rs1.next();
			String fname = rs1.getString("fname");
			String lname = rs1.getString("lname");
			
			
			List<Postings> posts = (List<Postings>) session.getAttribute("posts");
			Postings post = new Postings(Integer.parseInt(request.getParameter("price")), request.getParameter("condition"), 
					(int)session.getAttribute("userID"), listID);
			post.setFname(fname);
			post.setLname(lname);
			posts.add(post);
			
			
			
			
			String next = "/ShowListings.jsp";
			RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
			dispatch.forward(request,response);
			
			
			
		} catch (SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		} catch (ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		}
	}

}
