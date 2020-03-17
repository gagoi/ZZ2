package fr.pedro;

import java.awt.Dimension;

import javax.swing.JFrame;

@SuppressWarnings("serial")
public class Fenetre extends JFrame {

	public Fenetre() {
		setPreferredSize(new Dimension(500, 500));
		getContentPane().add(new Pannnnneau());
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}
}
