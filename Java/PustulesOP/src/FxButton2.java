import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.layout.FlowPane;

public class FxButton2 extends FxButton implements EventHandler<ActionEvent> {

	public FxButton2() {
		super();
		setOnAction(this);
	}

	@Override
	public void handle(ActionEvent arg0) {
		FlowPane p = (FlowPane) this.getParent();
		p.getChildren().add(new FxButton3());
	}
}
