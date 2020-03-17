package picasso;
	
import java.util.Random;

import javafx.application.Application;
import javafx.event.Event;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

/**
 * Classe principale de l'application Picasso
 */
public class FXPicasso extends Application {
	/** Composant qui va contenir les rectangles  */
	private MyCanvas canvas;
	
	/** Generateur pseudo-aleatoire */
	public static Random RAND; 
	
	/**
	 * Methode principale
	 * @param args arguments donnes au lancement du programme
	 */
	public static void main(String[] args) {
		RAND = new Random(1);
		launch(args);
	}

	/**
	 * Methode principale de JavFX
	 * @param primaryStage Fenetre principale
	 */
	@Override
	public void start(Stage primaryStage) {
		// layout de type borderpane
		BorderPane root = new BorderPane();
		
		// ajout au centre de la zone de dessin
		canvas = new MyCanvas();
		root.setCenter(canvas);
		
		// creation et ajout dans la partie superieure de la barre de menu
		MenuBar menuBar = new MenuBar();
		
		// ajout du menu dessin 
		Menu menuDessin = new Menu("Dessin");
		menuBar.getMenus().add(menuDessin);
		
		// ajout du sous-menu rafraichir qui permet de relancer une peinture
		MenuItem menuRafraichir = new MenuItem("Rafraichir");
		menuRafraichir.setAccelerator(new KeyCodeCombination(KeyCode.R, KeyCombination.CONTROL_ANY));
		menuRafraichir.setOnAction(actionEvent -> {canvas.peindre();});
		menuDessin.getItems().add(menuRafraichir);
		
		// ajout du sous-menu quitter qui permet de quitter proprement l'appli
		MenuItem menuQuitter = new MenuItem("Quitter");
		menuQuitter.setAccelerator(new KeyCodeCombination(KeyCode.Q, KeyCombination.CONTROL_ANY));
		menuQuitter.setOnAction(this::quit);
		menuDessin.getItems().add(menuQuitter);
		root.setTop(menuBar);
		
		// creation de la scene principale
		Scene scene = new Scene(root,640,480);
		// gestion de l'appui sur la croix
	    primaryStage.setOnCloseRequest(this::quit);
	    // association de la fenetre et de la scene et ajout d'un titre
		setStage(primaryStage, scene, "FX Picasso 0.1");
	}
	
	/**
	 * Methode permettant de gerer proprement la demande de quitter l'application
	 * @param e Evenement qui a declencher l'action
	 */
	private void quit(Event e) {
		Alert alert = new Alert(AlertType.ERROR, "Etes-vous de vouloir quitter ?", ButtonType.YES, ButtonType.NO);
		alert.showAndWait();

		if (alert.getResult() == ButtonType.NO) {
			e.consume();
		}
	}
	
	/**
	 * Methode permettant d'associer la fenetre a la scene et d'ajouter un titre
	 * @param stage la fenetre
	 * @param scene la scene
	 * @param title le titre
	 */
	private void setStage(Stage stage, Scene scene, String title) {
		stage.setScene(scene);
		stage.setTitle(title);
		stage.show();
	}
}
