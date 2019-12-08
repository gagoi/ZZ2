package fr.gagoi.system.vehicles;

public class Car extends Vehicle {

	final private int nbPlaces;
	private int color;
	
	public Car(final String immatriculation, final int nbPlaces, final int color) {
		super(immatriculation);
		this.nbPlaces = nbPlaces;
		this.color = color;
	}
	
	public Car() {
		this("OO000OO", 0, 0);
	}

	final public int getNbPlaces() {
		return nbPlaces;
	}
	
	final public int getColor() {
		return color;
	}
	
	final public void setColor(int color) {
		this.color = color;
	}
	
	
	@Override
	public void afficher() {
		System.out.println("Voiture : " + getImmatriculation() + " a " + nbPlaces + " places et est de couleur " + color + ".");
	}

}
