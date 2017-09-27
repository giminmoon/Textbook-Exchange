import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Dictionary;
import java.util.HashSet;

public class MailServer {
	public static void main(String [] args) {
		try {
			ServerSocket ss = new ServerSocket(6789);
			
			while(true) {
				System.out.println("Waiting for connection...");
				Socket s = ss.accept();
				System.out.println("Connection from " + s.getInetAddress());
				ServerThread st = new ServerThread(s);
				
				st.start();		
			}
		} catch (IOException ioe) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("ioe: " + ioe.getMessage());
		}	
	}
}

class ServerThread extends Thread{
	private Socket s;
	private BufferedReader br;
	private PrintWriter pw;
	
	public ServerThread(Socket s) {
		this.s = s;
		try {
			this.br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			this.pw = new PrintWriter(s.getOutputStream());
		} catch (IOException ioe) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("ioe: " + ioe.getMessage());
		}	
		
	}
	
	public void run() {
		try {
			String email = br.readLine();
			String verify = br.readLine();
			if(email != null && !email.equals("null")) {
				System.out.println("Sending verification to: " + email);
			} else {
				throw new IOException("disconnected");
			}

			
			String fromEmail = "trojanstextbooks@gmail.com";
			String password = "ReadingIsFun!";
			String toEmail = email;
			String subject = "Welcome to Trojan's Textbooks!";
			String message = "Thank you for signing up to use our website! Please submit the following code to verify your email address: ";
			message += verify;
			SendMail.send(fromEmail, password, toEmail, subject, message);
			
			
		} catch (IOException ioe) {
			System.out.println("ioe: " + ioe.getMessage());
		}
	}
}
