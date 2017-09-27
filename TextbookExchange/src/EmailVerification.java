
public class EmailVerification {
	public static void main(String[] args) {
		VerificationCodeGenerator code = new VerificationCodeGenerator();
		//Stackoverflow says making a SecureRandom object (see VerificationCodeGenerator's code) is a bit costly, so 
		//We would just want to make one VerificationCodeGenerator object and then call .nextSession() everytime we need
		//a new code.
		String verify = code.nextSessionId();
		String fromEmail = "trojanstextbooks@gmail.com";
		String password = "ReadingIsFun!";
		String toEmail = "aliciascruggs@outlook.com";
		String subject = "Welcome to Trojan's Textbooks!";
		String message = "Thank you for signing up to use our website! Please submit the following code to verify your email address: ";
		message += verify;
		SendMail.send(fromEmail, password, toEmail, subject, message);
	}
}
