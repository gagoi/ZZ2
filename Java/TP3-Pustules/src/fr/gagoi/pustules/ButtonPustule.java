package fr.gagoi.pustules;

import javafx.event.ActionEvent;
import javafx.scene.control.Button;

public class ButtonPustule extends Button {

	private int cpt = 0;
	
	public ButtonPustule(String text) {
		super();
		setText("" + cpt);
		String s = "efef";
		setOnAction(this::inc);
		
	}
	
	private void inc(ActionEvent arg) {
		++cpt;
		setText("" + cpt);
	}
}
