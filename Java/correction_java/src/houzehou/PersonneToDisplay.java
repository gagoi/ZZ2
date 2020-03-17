package houzehou;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

public class PersonneToDisplay {
	private SimpleStringProperty nom;
	private SimpleStringProperty prenom;
	private SimpleIntegerProperty annee;
	private SimpleStringProperty langage;

	public PersonneToDisplay(String inNom, String inPrenom, int inAnnee, String inLangage) {
		nom = new SimpleStringProperty(inNom);
		prenom = new SimpleStringProperty(inPrenom);
		langage = new SimpleStringProperty(inLangage);
		annee = new SimpleIntegerProperty(inAnnee);
	}
	
    public String getNom() {
	  return nom.get();
    }

    public void setNom(String inNom) {
	  nom.set(inNom);
	}
    
    public String getPrenom() {
	  return prenom.get();
    }

    public void setPrenom(String inPrenom) {
	  prenom.set(inPrenom);
	}
    
    public String getLangage() {
	  return langage.get();
    }

    public void setLangage(String inLangage) {
	  langage.set(inLangage);
	}
    
    public int getAnnee() {
	  return annee.get();
    }

    public void setAnnee(int inAnnee) {
	  annee.set(inAnnee);
	}
}
