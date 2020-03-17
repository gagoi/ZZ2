import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.layout.FlowPane;

public class ActionHandler implements EventHandler<ActionEvent> {

	@Override
	public void handle(ActionEvent arg0) {
		FxButton3 but = (FxButton3) arg0.getSource();
		if (but.getText().equals("3")) {
			FlowPane pane = (FlowPane) but.getParent();
			pane.getChildren().add(new FxButton4());
		}
	}

}
