package classes;

import java.util.List;

public class Textbook {
	public String title;
	public String isbn;
	public String authors;
	public List<Postings> postings;
	public String image;
	public String classs;
	public Integer id;
	
	public Textbook(String title, String isbn, String authors, List<Postings> postings,String image, String classs, Integer id) {
		this.title = title;
		this.isbn = isbn;
		this.authors = authors;
		this.postings = postings;
		this.image = image;
		this.classs = classs;
		this.id = id;
	}
	
	public Textbook(String title, String isbn, String authors, String image, String classs, Integer id) {
		this.title = title;
		this.isbn = isbn;
		this.authors = authors;
		this.image = image;
		this.classs = classs;
		this.id = id;
	}
	
}
