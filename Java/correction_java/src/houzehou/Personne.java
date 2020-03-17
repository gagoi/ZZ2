package houzehou;

public class Personne {
	private String nom;
	private String prenom;
	private int annee;
	private String langage;
	private static int COMPTEUR;
	
	static {
		COMPTEUR = 0;
		System.out.println("initialisation de compteur à "+COMPTEUR);
	}
	
	public Personne() {
		++COMPTEUR;
		System.out.println("Incrementation de compteur. Il vaut maintenant :"+COMPTEUR);
	}

	public Personne(String inNom, String inPrenom, int inAnnee, String inLangage) {
		this();
		nom = inNom;
		prenom = inPrenom;
		langage = inLangage;
		annee = inAnnee;
		System.out.println("constructeur complet de personne. Il vaut maintenant "+COMPTEUR);
	}
	
	public static void printCompteur() {
		System.out.println(COMPTEUR);
	}
	
	public final static int getCompteur() {
		return COMPTEUR;
	}

	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer("");
		sb.append(nom)
		  .append(":")
		  .append(prenom)
		  .append(":")
		  .append(langage)
		  .append(":")
		  .append(annee);
		return sb.toString();
	}

	public String getNom() {
		return nom;
	}

	public String getPrenom() {
		return prenom;
	}

	public int getAnnee() {
		return annee;
	}

	public String getLangage() {
		return langage;
	}
}
