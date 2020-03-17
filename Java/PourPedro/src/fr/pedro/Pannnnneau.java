package fr.pedro;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Pannnnneau extends JPanel {
	
	private List<MonRectangle> rectangles;
	private static Random random = new Random();
	
	
	public Pannnnneau() {
		rectangles = new ArrayList<MonRectangle>();
		
		addMouseListener(new MouseAdapter() { // Ajout d'un event pour les clics
			@Override
			public void mouseClicked(MouseEvent e) {
				int x = e.getX(); 	// Coordonnée horizontale du clic
				int y = e.getY(); 	// Coordonnée verticale du clic
				int w = 60;			// Taille horizontale
				int h = 20; 		// Taille verticale
				Color c = new Color(random.nextFloat(), random.nextFloat(), random.nextFloat()); // Création d'une couleur aléatoire
				
				rectangles.add(new MonRectangle(x, y, w, h, c)); // Ajout du rectangle a ma liste
				repaint();
			}
		});
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		System.out.println("Paint");
		for (MonRectangle monRectangle : rectangles) {
			monRectangle.draw(g);
		}
	}
}
