import javafx.event.ActionEvent;
import javafx.scene.layout.FlowPane;

public class FxButton4 extends FxButton {
	public FxButton4() {
		super();
		setOnAction(FxButton4::handler);
	}
	
	public static void handler(ActionEvent arg0) {
		FlowPane p = (FlowPane) ((FxButton4) arg0.getSource()).getParent();
		p.getChildren().add(new FxButton5());
	}
}
