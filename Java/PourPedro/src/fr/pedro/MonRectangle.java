package fr.pedro;

import java.awt.Color;
import java.awt.Graphics;

public class MonRectangle {

	private final int 	x, y, w, h;
	private final Color color;
	
	public MonRectangle(int x, int y, int w, int h, Color color) {
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		this.color = color;
	}
	
	public void draw(Graphics g) {
		g.setColor(color);
		g.fillRect(x, y, w, h);
	}
}
