package fr.gagoi.system.vehicles;

public abstract class Vehicle {

	final private String immatriculation;

	public Vehicle(final String immatriculation) {
		this.immatriculation = new String(immatriculation);
	}

	final public String getImmatriculation() {
		return immatriculation;
	}

	abstract public void afficher();

	public void avancer() {
		System.out.println(immatriculation + " avance.");
	}
	
	public void avancer(int dist) {
		avancer((float) dist);
	}
	
	public void avancer(float dist) {
		System.out.println(immatriculation + " avance de " + dist + "m.");
	}
}
