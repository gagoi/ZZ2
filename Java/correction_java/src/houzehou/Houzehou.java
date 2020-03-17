package houzehou;
	
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.Event;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

/**
 * Classe principale de l'application Houzehou
 */
public class Houzehou extends Application {
	
	private TableView table = new TableView();
	
	/**
	 * Methode principale
	 * @param args arguments donnes au lancement du programme
	 */
	public static void main(String[] args) {
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
		table = new TableView();
		root.setCenter(table);
		
        TableColumn nomCol = new TableColumn("Nom");
        nomCol.setCellValueFactory(new PropertyValueFactory<PersonneToDisplay, String>("nom"));
        TableColumn prenomCol = new TableColumn("Prenom");
        prenomCol.setCellValueFactory(new PropertyValueFactory<PersonneToDisplay, String>("prenom"));
        TableColumn langageCol = new TableColumn("Langage");
        langageCol.setCellValueFactory(new PropertyValueFactory<PersonneToDisplay, String>("langage"));
        TableColumn anneeCol = new TableColumn("Annee");
        anneeCol.setCellValueFactory(new PropertyValueFactory<PersonneToDisplay, Integer>("annee"));
        
        ObservableList<PersonneToDisplay> data = FXCollections.observableArrayList(
        	    new PersonneToDisplay("Backus","John",1957,"FORTRAN"),
        	    new PersonneToDisplay("Goldfarb","Charles",1969,"GML")
        	);
        table.setItems(data);
        table.getColumns().addAll(nomCol, prenomCol, langageCol, anneeCol);
        
		// creation de la scene principale
		Scene scene = new Scene(root,640,480);
		// gestion de l'appui sur la croix
	    primaryStage.setOnCloseRequest(this::quit);
	    // association de la fenetre et de la scene et ajout d'un titre
		setStage(primaryStage, scene, "houzehou");
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
