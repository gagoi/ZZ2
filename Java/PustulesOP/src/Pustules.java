import com.sun.glass.events.MouseEvent;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.FlowPane;
import javafx.stage.Stage;

public class Pustules extends Application {

	@Override
	public void start(Stage primaryStage) throws Exception {
		primaryStage.setTitle("Pustules");
		FlowPane layout = new FlowPane();
		primaryStage.setMinWidth(500);
		primaryStage.setMinHeight(500);
		primaryStage.setScene(new Scene(layout));

		primaryStage.show();
		for (int i = 0; i < 200; ++i)
		{
			Button but1 = new FxButton();
			but1.setOnAction(new EventHandler<ActionEvent>() {
				
				@Override
				public void handle(ActionEvent arg0) {
					layout.getChildren().add(new FxButton2());
				}
			});

			layout.getChildren().add(but1);
		}
	}

	public static void main(String[] args) {
		launch(args);
	}

}
