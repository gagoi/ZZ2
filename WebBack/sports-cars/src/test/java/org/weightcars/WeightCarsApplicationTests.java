package org.weightcars;

import static org.junit.Assert.assertTrue;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.weightcars.controller.CarController;
import org.weightcars.domain.Car;

@RunWith(SpringRunner.class)
@SpringBootTest
public class WeightCarsApplicationTests {

	@Autowired
	CarController repo;
	
    @Test
    public void contextLoads() {
    }

    @Test
    public void search() {
    	assertTrue(((Car) repo.searchCarsByString("/cars/search/206").toArray()[0]).getModel().getName().toLowerCase().contains("206".toLowerCase()));
    }
}
