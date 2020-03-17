package fr.gagoi.system.vehicles;

public class Truck extends Vehicle {

	private float capa;

	public Truck(final String immatriculation, final float capa) {
		super(immatriculation);
		this.capa = capa;
	}

	public Truck() {
		this("OO000OO", 0);
	}

	final public float getCapa() {
		return capa;
	}

	@Override
	public void afficher() {
		System.out.println("Camion : " + getImmatriculation() + " a une capacité de " + capa + ".");
	}

}
