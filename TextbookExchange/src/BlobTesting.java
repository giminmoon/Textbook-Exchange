
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.imageio.ImageIO;

public class BlobTesting {
	public static void main(String[] args) {
		try {
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/blobTest?user=root&password=root"); //Replace blobTest with database name
			conn.setAutoCommit(false);
			Statement st = conn.createStatement();
			
			byte[] imageInByte;
			//Load image as BufferedImage
			BufferedImage originalImage = ImageIO.read(new File("C:/Eclipse/Eclipse_Workspace/SQLTesting/src/blobTesting/images/book.jpg"));

			// convert BufferedImage to byte array
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			ImageIO.write(originalImage, "jpg", baos);
			baos.flush();
			imageInByte = baos.toByteArray();
			baos.close();
			
			//Add byte array and any other variables to the table
			String query = "INSERT INTO blobTestTable (imageID, image) VALUES (?, ?)";
			PreparedStatement ps = conn.prepareStatement(query);
			ps.setInt(1, 1);
			ps.setBytes(2, imageInByte);
			ps.execute();
			
			//Get byte array back from database
			ResultSet rs = st.executeQuery("SELECT * FROM blobTestTable;");
			rs.next();
			
			// convert byte array back to BufferedImage
			InputStream in = rs.getBinaryStream("image");
			BufferedImage bImageFromConvert = ImageIO.read(in);

			ImageIO.write(bImageFromConvert, "jpg", new File("C:/Eclipse/Eclipse_Workspace/SQLTesting/src/blobTesting/images/new_book.jpg"));
			
			rs.close();
			st.close();
			conn.close();
		} catch(SQLException sqle) {
			System.out.println("sqle: " + sqle.getMessage());
		} catch(ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
	}
}
