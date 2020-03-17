package playground;

import org.junit.Test;

public class Exceptions {

    @Test
    public void testCatchException() {
        try {
            int i = 0;
            int j = 3 / i;
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    // @Test
    public void testCausedBy() {
        try {
            int i = 0;
            int j = 3 / i;
        } catch (Exception e) {
            throw new RuntimeException("Une erreur est survenue", e);
        }
    }
}
