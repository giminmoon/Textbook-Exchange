

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet implementation class SendVerifyEmail
 */
@WebServlet("/SendVerifyEmail")
public class SendVerifyEmail extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private static VerificationCodeGenerator code = new VerificationCodeGenerator();
	//Stackoverflow says making a SecureRandom object (see VerificationCodeGenerator's code) is a bit costly, so 
	//We would just want to make one VerificationCodeGenerator object and then call .nextSession() everytime we need
	//a new code.
	
	public static void sendMessage(PrintWriter pw, String message) {
		pw.println(message);
		pw.flush();
	}
	
	
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String verify = code.nextSessionId();
		
		Socket s = new Socket("localhost", 6789);
		BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
		PrintWriter pw = new PrintWriter(s.getOutputStream());
		sendMessage(pw, request.getParameter("email"));
		sendMessage(pw, verify);
		
		
		s.close();
		
		HttpSession session = request.getSession();
		session.setAttribute("email", request.getParameter("email"));
		session.setAttribute("password", request.getParameter("password"));
		session.setAttribute("fname", request.getParameter("fname"));
		session.setAttribute("lname", request.getParameter("lname"));
		session.setAttribute("major", request.getParameter("major"));
		session.setAttribute("phone", request.getParameter("phone"));
		session.setAttribute("verify", verify);
		
		
		String next = "/VerifyEmail.jsp";
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request,response);
		
	}

}
