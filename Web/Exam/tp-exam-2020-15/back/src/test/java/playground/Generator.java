package playground;

import java.time.LocalDate;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Generator {

    private static final Logger LOGGER = LoggerFactory.getLogger(Generator.class);

    @Test
    public void testGenerator1() {
        Film h2g2 = new Film("The hitchhiker's guide to the galaxy",
            50_000_000, LocalDate.of(2005, 8, 18));
        LOGGER.info(h2g2.toString());
    }

    @Test
    public void testGenerator2() {
        Film snatch = new Film()
            .setName("Snatch")
            .setDate(LocalDate.of(2000, 11, 15))
            .setBudget(10_000_000);
        LOGGER.info(snatch.toString());
    }

}

class Film {

    String name;
    Integer budget;
    LocalDate date;

    public Film(String name, Integer budget, LocalDate date) {
        this.name = name;
        this.budget = budget;
        this.date = date;
    }

    public Film() {
    }

    public String getName() {
        return name;
    }

    public Film setName(String name) {
        this.name = name;
        return this;
    }

    public Integer getBudget() {
        return budget;
    }

    public Film setBudget(Integer budget) {
        this.budget = budget;
        return this;
    }

    public LocalDate getDate() {
        return date;
    }

    public Film setDate(LocalDate date) {
        this.date = date;
        return this;
    }
}

