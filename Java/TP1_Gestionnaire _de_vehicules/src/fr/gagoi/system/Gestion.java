package fr.gagoi.system;

import fr.gagoi.system.vehicles.Car;
import fr.gagoi.system.vehicles.Truck;
import fr.gagoi.system.vehicles.Vehicle;

public class Gestion {

	public static void main(String[] args) {
		Car c1 = new Car("AA222BB", 5, 4);
		c1.afficher();
		c1.avancer();
		
		Truck t1 = new Truck("BB111AA", 18);
		t1.afficher();
		t1.avancer();
		
		//((Car) ((Vehicle) t1)).afficher();
	}

}
