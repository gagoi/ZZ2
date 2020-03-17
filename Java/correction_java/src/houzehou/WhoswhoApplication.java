package houzehou;

public class WhoswhoApplication {

	public static void main(String[] args) {
		if(Personne.getCompteur() == 0) {
			System.out.println("Pas d'instance de personne de cree");
		}
		else {
			System.out.println("Probleme : " + Personne.getCompteur() + " instances de personne de cree initialement");
		}
		
		Personne p = new Personne("Backus","John",1957,"FORTRAN");
		
		if(Personne.getCompteur() == 1) {
			System.out.println("Une instance de personne de cree");
		}
		else {
			System.out.println("Probleme : " + Personne.getCompteur() + " instances de personne de cree au lieu de 1");
		}
		
		System.out.println(p.toString());
		
		Personne p2 = new Personne("Goldfarb","Charles",1969,"GML");
		
		Whoswho whoswho = new Whoswho();
		whoswho.addPersonne(p);
		whoswho.addPersonne(p2);
		
		whoswho.ecrireTxtFile("save.txt");
		whoswho.lireTxtFile("save.txt");
		System.out.println(whoswho.toString());
		whoswho.ecrireXmlFile("save.xml");
		whoswho.lireXmlFile("save.xml");
		System.out.println(whoswho.toString());
	}

}
