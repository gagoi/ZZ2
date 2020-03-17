import javafx.event.ActionEvent;
import javafx.scene.layout.FlowPane;

public class FxButton5 extends FxButton {

	public FxButton5() {
		super();
		setOnAction((ActionEvent e) -> ((FlowPane) ((FxButton5) e.getSource()).getParent()).getChildren().add(new FxButton()));
	}
}
