package picasso;

import javafx.concurrent.Service;
import javafx.concurrent.Task;
import javafx.scene.Group;

/**
 * Gestionnaire des taches
 */
public class ServicePicassoCalculator extends Service<Group> {
	/** Reference vers la toile */
	private MyCanvas myCanvas;
	
	/**
	 * Constructeur
	 * @param inMyCanvas reference vers la toile
	 */
	public ServicePicassoCalculator(MyCanvas inMyCanvas) {
		myCanvas = inMyCanvas;
	}
	
	@Override
	/**
	 * Creation de la tache
	 */
	protected Task<Group> createTask() {
		return new TaskPicassoCalculator(myCanvas.getWidth(), myCanvas.getHeight());// a completer
	}
}
