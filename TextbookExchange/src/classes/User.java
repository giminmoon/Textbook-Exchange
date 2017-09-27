package classes;



import java.util.HashSet;
import java.util.Queue;
import java.util.Vector;

public class User {
	public String fname;
	public String lname;
	public String email;
	public Vector<Postings> postings;
	public double reviewRating;
	public Queue<String> latestMessages;
	public String password;
	
	//one possible constructor
	public User(String email, String fname, String lname) {
		this.email = email;
		this.fname = fname;
		this.lname = lname;
	}

	public void addPosting(Postings posting) {
		postings.addElement(posting);
	}
	
}
