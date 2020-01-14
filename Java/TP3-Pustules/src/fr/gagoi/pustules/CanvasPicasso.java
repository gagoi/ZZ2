package fr.gagoi.pustules;

import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;

public class CanvasPicasso extends Canvas{

	public CanvasPicasso(int w, int h) {
		super(w, h);
		pain();
	}
	
	public void pain() {
		GraphicsContext gc = getGraphicsContext2D();
		gc.setFill(Color.RED);
        gc.setStroke(Color.BLUE);
        gc.setLineWidth(5);
		gc.fillRect(50,  50,  100,  200);
		gc.fill();
	}

}
