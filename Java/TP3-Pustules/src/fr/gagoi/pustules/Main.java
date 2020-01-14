package fr.gagoi.pustules;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
 
public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Hello World!");
        Button btn = new ButtonPustule("Wesh");
        
        
        CanvasPicasso c = new CanvasPicasso(1280, 720);
        c.pain();
       
        
        StackPane root = new StackPane();
       // root.getChildren().add(btn);
        root.getChildren().add(c);
        primaryStage.setScene(new Scene(root, 1280, 720));
        primaryStage.show();
    }
}