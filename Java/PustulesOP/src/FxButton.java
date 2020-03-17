import java.util.Random;

import javafx.scene.control.Button;

public class FxButton extends Button {

	private static int cpt = 0;

	public FxButton() {
		setText("" + ++cpt);
		setColor();
	}
	
	public void setColor() {
		setStyle("-fx-background-color:#" + hexGen()+ ";-fx-text-fill: #" + hexGen());
	}

	private static String hexGen() {
		String hex = "";
		char[] c = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

		for (int i = 0; i < 6; ++i) {
			hex = hex + c[new Random().nextInt(16)];
		}

		return hex;
	}
}
