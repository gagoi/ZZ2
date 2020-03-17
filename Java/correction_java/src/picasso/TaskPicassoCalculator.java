package picasso;

import javafx.concurrent.Task;
import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class TaskPicassoCalculator extends Task<Group> {
	public static int MAX_PER_THREAD = 1000;
	/** largeur de la toile */
	private int width;

	/** hauteur de la toile */
	private int height;

	/**
	 * Constructeur
	 * 
	 * @param inWidth  largeur de la toile
	 * @param inHeight hauteur de la toile
	 */
	public TaskPicassoCalculator(int inWidth, int inHeight) {
		width = inWidth;
		height = inHeight;
	}

	@Override
	/**
	 * action de la tache
	 */
	protected Group call() throws Exception {
		Group thread_group = new Group();
		for (int i = 0; i < MyCanvas.MAX; ++i) {
			Rectangle r = new Rectangle(FXPicasso.RAND.nextInt(width), FXPicasso.RAND.nextInt(height),
					FXPicasso.RAND.nextInt(100), FXPicasso.RAND.nextInt(100));
			r.setFill(new Color(FXPicasso.RAND.nextDouble(), FXPicasso.RAND.nextDouble(), FXPicasso.RAND.nextDouble(),
					FXPicasso.RAND.nextDouble()));
			thread_group.getChildren().add(r);
			updateProgress(i, MyCanvas.MAX);
		}
		return thread_group;
	}
}
