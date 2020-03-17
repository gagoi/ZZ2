package picasso;

import javafx.scene.Parent;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.layout.FlowPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

/**
 * Zone de dessein principal
 */
public class MyCanvas extends Parent {
	/** Largeur */
	private volatile int width;

	/** Longueur */
	private volatile int height;

	/** Gestionnaire des taches picasso */
	private ServicePicassoCalculator servicePicassoCalculator;

	/** attribut static => nombre max de rectangle a dessiner */
	public static final int MAX = 100000;

	/** indique si un tableau a deja ete realise */
	private boolean alreadyLaunched = false;

	/** hauteur minimum */
	public double minHeight(double width) {
		return 64;
	}

	/** hauteur maximum */
	public double maxHeight(double width) {
		return 1000;
	}

	@Override
	/** hauteur preferee */
	public double prefHeight(double width) {
		return minHeight(width);
	}

	@Override
	/** largeur minimum */
	public double minWidth(double height) {
		return 0;
	}

	@Override
	/** largeur maximum */
	public double maxWidth(double height) {
		return 10000;
	}

	@Override
	/**
	 * Rend le canvas dimensionnable
	 */
	public boolean isResizable() {
		return true;
	}

	/**
	 * Constructeur par defaut
	 */
	public MyCanvas() {
		servicePicassoCalculator = new ServicePicassoCalculator(this);
		servicePicassoCalculator.setOnSucceeded(e -> {
			this.getChildren().clear();
			alreadyLaunched = true;
			this.getChildren().add(servicePicassoCalculator.getValue());
			servicePicassoCalculator.reset();
		});
		displayFirstMessage();
	}

	@Override
	/**
	 * Methode lancer au moment du redimensionnement
	 * 
	 * @param inWidth  nouvelle largeur
	 * @param inHeight nouvelle hauteur
	 */
	public void resize(double inWidth, double inHeight) {
		if (inWidth != width || inHeight != height) {
			width = (int) inWidth;
			height = (int) inHeight;
			if (alreadyLaunched) {
				servicePicassoCalculator.cancel();
				peindre();
			} else {
				displayFirstMessage();
			}
		}
	}

	/**
	 * Affiche le message au moment du lancement
	 */
	private void displayFirstMessage() {
		this.getChildren().clear();
		Rectangle r = new Rectangle(0, 0, width, height);
		r.setFill(Color.WHITE);
		this.getChildren().add(r);
		Label l = new Label("Rien a afficher. lancer le calcul par le menu \"Art Abstrait\"");
		l.setTranslateY(height / 2);
		this.getChildren().add(l);
	}

	/**
	 * Lancement de la peinture
	 */
	public void peindre() {
		if (servicePicassoCalculator.isRunning()){
			this.getChildren().clear();
			servicePicassoCalculator.reset();
			servicePicassoCalculator.restart();
		} else {
			servicePicassoCalculator.start();
		}

		ProgressBar pb = new ProgressBar(MAX);
		pb.progressProperty().bind(servicePicassoCalculator.progressProperty());
		displayMessageWorking(pb);
	}

	/**
	 * Affichage du message de travail et de la progress bar
	 * 
	 * @param pg la progress bar
	 */
	private void displayMessageWorking(ProgressBar pg) {
		this.getChildren().clear();
		Rectangle r = new Rectangle(0, 0, width, height);
		r.setFill(Color.WHITE);
		this.getChildren().add(r);
		FlowPane fp = new FlowPane();
		fp.setTranslateY(height / 2);
		this.getChildren().add(fp);
		Label l = new Label("Calcul en cours. Patience !");
		fp.getChildren().add(l);
		fp.getChildren().add(pg);
	}

	/**
	 * Retourne la largeur de la zone de dessein
	 * 
	 * @return la largeur de la zone de dessein
	 */
	public final int getWidth() {
		return width;
	}

	/**
	 * Retourne la hauteur de la zone de dessein
	 * 
	 * @return la hauteur de la zone de dessein
	 */
	public final int getHeight() {
		return height;
	}
}