package classes;


public class Postings {
	public double price;
	public String condition;
	public Integer userid;
	public User user;
	public Integer listingid;
	public String fname;
	public String lname;
	
	public Postings(double price, String condition, Integer userid, Integer listingid) {
		this.price = price;
		this.condition = condition;
		this.userid = userid;
		this.listingid = listingid;
	}
	
	public void setFname(String fname) {
		this.fname = fname;
	}
	public void setLname(String lname) {
		this.lname = lname;
	}	
	
	
}
