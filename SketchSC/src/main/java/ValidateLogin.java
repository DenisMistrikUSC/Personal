import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/loginPage")
public class ValidateLogin extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	String name;  
	String pass; 

	protected void doPost(HttpServletRequest request, HttpServletResponse response) 
	{
		response.setContentType("text/html;charset=UTF-8");
		name = request.getParameter("user");
		pass = request.getParameter("pass");
		PrintWriter out = null; 
		try {
			out = response.getWriter();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}  
		
		if(validateLogin(name, pass))
			out.println("1"); 
		else
			out.println("0");
	}

	public static boolean validateLogin(String uname, String pword)
	{
		Connection con = null;
	      try {
	         con = DriverManager.
	         getConnection("jdbc:mysql://localhost:3306/Logins?useSSL=false", "root", "root");
	         System.out.println("Connection is successful !!!!!");
	      } catch(Exception e) {
	         e.printStackTrace();
	      }
		String db = "jdbc:mysql://localhost:3306/Logins";
		String user = "root"; 
		String pwd = "root"; 
		String sql1 = "SELECT * FROM login WHERE username=?";
	    try (Connection conn = DriverManager.getConnection(db, user, pwd);
	    PreparedStatement ps = conn.prepareStatement(sql1);) 
	    {
	    	ps.setString(1, uname);
	    	ResultSet rs = ps.executeQuery();
	    	while (rs.next())
	    	{
	    		return rs.getString("passwords").equals(pword); 
	    	}
	    } 
	    catch (SQLException ex) 
	    {
	    	System.out.println ("SQLException: " + ex.getMessage());
	    }
	   return false; 
	}
}
