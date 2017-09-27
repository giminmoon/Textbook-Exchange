

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet implementation class Editprofile
 */
@WebServlet("/Editprofile")
public class Editprofile extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {	
			HttpSession session = request.getSession();
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/textbookexchange?user=root&password=root");
			String s = "UPDATE User SET phone=? WHERE userID=?";
			PreparedStatement preparedStatement = conn.prepareStatement(s);
			preparedStatement.setString(1, request.getParameter("phone"));
			preparedStatement.setInt(2, (int)session.getAttribute("userID"));
			preparedStatement.executeUpdate();
			
			session.setAttribute("phone", request.getParameter("phone"));
			
			s = "UPDATE User SET major=? WHERE userID=?";
			preparedStatement = conn.prepareStatement(s);
			
			preparedStatement.setString(1, request.getParameter("major"));
			preparedStatement.setInt(2, (int)session.getAttribute("userID"));
			preparedStatement.executeUpdate();
			
			session.setAttribute("major", request.getParameter("major"));
			
			conn.close();
			
			
			String next = "/ProfilePage.jsp";
			RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
			dispatch.forward(request,response);
			
			
			
		} catch (SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		} catch (ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		}
	}

}
