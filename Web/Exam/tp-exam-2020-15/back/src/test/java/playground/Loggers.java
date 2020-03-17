package playground;

import static playground.CollectionLoop.myObjects;

import java.util.Arrays;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.weightcars.WeightCarsApplication;

@RunWith(SpringRunner.class) // Nécessaire pour charger la config de log depuis application.properties
@SpringBootTest(classes = WeightCarsApplication.class)
public class Loggers {

    Logger logger = LoggerFactory.getLogger(Loggers.class);

    @Test
    public void testLogForLoop() {
        myObjects.forEach(myObject -> logger.info(myObject.toString()));
    }

    @Test
    public void testLogException() {
        try {
            int i = 0;
            int j = 3 / i;
        } catch (Exception e) {
            logger.error("Une erreur est survenue", e);
        }
    }

    @Test
    public void testLogLevel() {
        logger.warn("Start");
        logLevels();
        logger.warn("End");
    }

    private void logLevels() {
        for (String s : Arrays.asList("A", "B", "C")) {
            logger.info(s);
            for (int j = 1; j <= 3; j++) {
                String element = s + j;
                logger.debug(element);
            }
        }
    }
}
