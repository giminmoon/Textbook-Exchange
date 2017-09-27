
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

/**
 * Servlet implementation class search
 */
@WebServlet("/search")
public class search extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public search() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		
		String userInput = request.getParameter("userinput");
		String type = request.getParameter("selectType");
	

		Connection conn = null;
	    Statement st = null;
	    ResultSet rs = null;
	    
	    try {
	    	Class.forName("com.mysql.jdbc.Driver");
	        conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root&useSSL=false");
	        st = conn.createStatement();
	        
	        //depending on type, change the scripts
	        if (type.equals("Author")) {
	        		rs = st.executeQuery("SELECT * FROM Book WHERE author='" + userInput +"'");
	        }
	        else if(type.equals("Title")){
	        		rs = st.executeQuery("SELECT * FROM Book WHERE name='" + userInput +"'");
	        }
	        else if(type.equals("ISBN")) {
	        		rs = st.executeQuery("SELECT * FROM Book WHERE isbn='" + userInput +"'");
	        }
	        
	        
	        ArrayList<Textbook> books = new ArrayList<Textbook>();
	        List<String> titles = new ArrayList<String>();
	        List<String> isbns = new ArrayList<String>();
	        List<String> authors = new ArrayList<String>();
	    		List<Integer> ids = new ArrayList<Integer>();
	    		List<String> images = new ArrayList<String>();
	    		List<String> classes = new ArrayList<String>();
	    	
	    		Integer id;
	    		String title, isbn, author, image,classs, bookid;
	    		
	    		//looping through the results
	        while (rs.next()) {
		       title = rs.getString("name");
		       isbn = rs.getString("isbn");
		       author = rs.getString("author");
		       id = rs.getInt("bookID");
		       image = rs.getString("bookimage");
		       classs = rs.getString("class");
		       ids.add(id); 
		       titles.add(title);
		       isbns.add(isbn);
		       authors.add(author);
		       images.add(image);
		       classes.add(classs);
	        }
	            
	        //loop to match bookid in listings
	        List<Integer> useridstore = new ArrayList<Integer>();
	        for(int i = 0; i < ids.size(); i++) {
	        		List<Postings> postings = new ArrayList<Postings>();
	        		rs = st.executeQuery("SELECT * from Listing where bookID ='" + ids.get(i)+ "'");
	        		while(rs.next()) {
	        			String condition = rs.getString("bookcondition");
	        			int price = rs.getInt("price");
	        			Integer userid = rs.getInt("userID");
	        			Integer listingid = rs.getInt("listingID");
	        			useridstore.add(userid);
	        			Postings posting = new Postings(price, condition, userid, listingid);
	        			postings.add(posting);
	        		}
	        		Textbook textbook = new Textbook(titles.get(i),isbns.get(i),authors.get(i),postings,images.get(i),classes.get(i), ids.get(i));
	        		books.add(textbook);
	        }
     
	        //loops through userid and find / place it to the right postings
	        for(int i = 0; i < useridstore.size(); i++) {
	        		rs = st.executeQuery("SELECT * from User where userID ='" + useridstore.get(i)+"'");
	        		while(rs.next()) {
	        			String email = rs.getString("email");
	        			String fname = rs.getString("fname");
	        			String lname = rs.getString("lname");
	        			
	        			User user = new User(email, fname, lname);
	        			for(int j = 0; j < books.size(); j++) {
	        				for(int k = 0; k < books.get(j).postings.size(); k++){
	        					if(books.get(j).postings.get(k).userid.equals(useridstore.get(i))){
	        						books.get(j).postings.get(k).user = user;
	        					}
	        				}
	        			}
	        		}
	        }

	    request.setAttribute("books", books);
	    //System.out.println(books.get(0).authors);

	    } catch (SQLException sqle) {
	    	System.out.println ("sqle :"+sqle.getMessage());
	    } catch (ClassNotFoundException cnfe) {
	    	System.out.println ("cnfe " +cnfe.getMessage());
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
	    		System.out.println("sqle" + sqle.getMessage());
	    	}
	    }  
	    
	    

	    String nextJSP = "/searching.jsp";
	    //response.setContentType("text/jsp");
		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(nextJSP);
		dispatcher.forward(request,response); 
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

