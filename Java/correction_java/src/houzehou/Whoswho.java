package houzehou;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.LinkedList;
import java.util.List;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.StaxDriver;

public class Whoswho {
	private List<Personne> listPersonne;
	
	public Whoswho(){
		listPersonne = new LinkedList<Personne>();
	}
	
	public void addPersonne(Personne personneToAdd) {
		listPersonne.add(personneToAdd);
	}
	
	@Override
	public String toString() {
		StringBuffer sbf = new StringBuffer();
		for(Personne p : listPersonne) {
			sbf.append(p.toString()).append("\n");
		}
		return sbf.toString();
	}
	
	public void lireTxtFile(String inFileName) {
		listPersonne = new LinkedList<Personne>();
		try(FileReader fr = new FileReader(inFileName);BufferedReader br = new BufferedReader(fr);){
			String lecture;
			String[] str;			
			while ((lecture = br.readLine())!=null) {
				str = lecture.split(":");
				listPersonne.add(new Personne(str[0],str[1], Integer.valueOf(str[3]),str[2]));
			}
		}
		catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public void ecrireTxtFile(String inFileName) {
		File fic = new File(inFileName);
		try(FileOutputStream  fos = new FileOutputStream(fic);PrintStream ps = new PrintStream(fos);){
			for(Personne p : listPersonne) {
				ps.println(p.toString());				
			}
		}catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void ecrireXmlFile(String inFileName) {
		XStream xstream = null;
		try(FileOutputStream fos = new FileOutputStream(inFileName)) {
		   xstream = new XStream(new StaxDriver());
		   xstream.toXML(listPersonne, fos);  
		} catch (Exception e) {
		   e.printStackTrace(); 
		}
	}
	
	public void lireXmlFile(String inFileName) {
		XStream           xstream = null;
		try(FileInputStream fis = new FileInputStream(inFileName);) {
			xstream = new XStream(new StaxDriver());
		      
		   listPersonne = (LinkedList<Personne>)xstream.fromXML(fis);
		} catch (Exception e) {
		   e.printStackTrace(); 
		}
	}
	

}
