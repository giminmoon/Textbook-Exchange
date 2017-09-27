
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.sql.DriverManager;
import java.sql.SQLException;
import classes.Postings;
import classes.Textbook;
import classes.User;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import classes.Textbook;

/**
 * Servlet implementation class ListingServlet
 */
@WebServlet("/ListingServlet")
public class ListingServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ListingServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String indexS= request.getParameter("index");
		Integer index = Integer.parseInt(indexS);
	
	
		Connection conn = null;
	    Statement st = null;
	    ResultSet rs = null;
	    List<Postings> posts = new ArrayList<Postings>();
	    Textbook textbook = null;
	    try {
	    	Class.forName("com.mysql.jdbc.Driver");
	        conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root&useSSL=false");
	        st = conn.createStatement();
       
        		rs = st.executeQuery("SELECT * from Listing where bookID ='" + index +"'");
        		
        		
        		while(rs.next()) {
        			Integer listID = rs.getInt("listingID");
        			Integer userID = rs.getInt("userID");
        			String bookCond = rs.getString("bookcondition");
        			double price = rs.getDouble("price");
        			
        			Statement st1 = conn.createStatement();
        			ResultSet rs1 = st1.executeQuery("SELECT * FROM User WHERE userID ='" + userID + "'");
        			rs1.next();
        			String fname = rs1.getString("fname");
        			String lname = rs1.getString("lname");
        			
        			Postings post = new Postings(price, bookCond, userID, listID);
        			post.setFname(fname);
        			post.setLname(lname);
        			posts.add(post);
        		}
        		rs = st.executeQuery("SELECT * from Book where bookID ='" + index +"'");
        		
        		String title = null, isbn = null, author = null, image = null,classs = null;
	    		
	    		//looping through the results
	        while (rs.next()) {
		       title = rs.getString("name");
		       isbn = rs.getString("isbn");
		       author = rs.getString("author");
		       image = rs.getString("bookimage");
		       classs = rs.getString("class");
	        }
        		
        		textbook = new Textbook(title ,isbn ,author,image,classs, index);
        		

	    }
	        catch (SQLException sqle) {
		    	System.out.println (sqle.getMessage());
		    } catch (ClassNotFoundException cnfe) {
		    	System.out.println (cnfe.getMessage());
		    } finally {
		    	try {
		    		if (rs != null) {
		    			rs.close();
		    		}
		    		if (st != null) {
		    			st.close();
		    		}
		    		if (conn != null) {
		    			conn.close();
		    		}
		    	} catch (SQLException sqle) {
		    		System.out.println(sqle.getMessage());
		    	}
		    }  
	
	    HttpSession session = request.getSession();
		session.setAttribute("posts", posts);
		session.setAttribute("book", textbook);
		String nextJSP = "/BookListing.jsp";
		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(nextJSP);
		dispatcher.forward(request,response); 

		
	}

}
