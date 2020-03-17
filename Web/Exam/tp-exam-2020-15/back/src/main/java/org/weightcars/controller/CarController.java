package org.weightcars.controller;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.data.domain.Sort;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.weightcars.domain.Brand;
import org.weightcars.domain.Car;
import org.weightcars.domain.Model;
import org.weightcars.repository.CarRepository;
import org.weightcars.service.CarService;

/**
 * REST controller for managing Car.
 */
@RestController
@RequestMapping("/api")
@CrossOrigin
public class CarController {

    public static final int MAX_RESULT = 10;
    private final static Logger LOGGER = LoggerFactory.getLogger(CarController.class);

    private final CarRepository carRepository;

    private final CarService carService;

    CarController(CarRepository carRepository, CarService carService) {
        this.carRepository = carRepository;
        this.carService = carService;
    }

    /**
     * GET  /cars : get all the cars.
     *
     * @return the ResponseEntity with status 200 (OK) and the list of cars in body
     */
    @GetMapping("/cars")
    public Set<Brand> getAllCars() {
        LOGGER.debug("REST request to get all Cars grouped by Brands and Models");
        List<Car> cars = carRepository.findAll().stream()
            .sorted(Comparator.naturalOrder())
            .limit(MAX_RESULT)
            .map(carService::refreshCarImage)
            .collect(Collectors.toList());
        return carsGroupByBrandModel(cars);
    }

    /**
     * GET  /cars : search cars from given search string.
     *
     * @param searchString String that match any car information (variant, option, model, brand)
     * @return the ResponseEntity with status 200 (OK) and the list of cars in body
     */
	@GetMapping("/cars/search/{searchString}")
    public Set<Brand> searchCarsByString(@PathVariable String searchString) {
        LOGGER.debug("REST request to get Cars from given string {}", searchString);

        final List<Car> filteredCars = carRepository.findAll().stream().filter((Car c) -> {
        		return c.getName().toLowerCase().contains(searchString.toLowerCase()) 
        						|| c.getModel().getBrand().getName().toLowerCase().contains(searchString.toLowerCase())
        						|| c.getModel().getName().toLowerCase().contains(searchString.toLowerCase());}).collect(Collectors.toList());
 
        return carsGroupByBrandModel(filteredCars);
    }

    /**
     * GET  /cars : search cars from given search string.
     *
     * @param criteria String that match one of 'weight', 'ratio' or 'power'
     * @param number Max number of cars returned
     * @return the ResponseEntity with status 200 (OK) and the list of brands, including models including cars in body
     */
    @GetMapping("/cars/top/{criteria}/{number}")
    public Set<Brand> topCars(@PathVariable String criteria, @PathVariable Integer number) {
        LOGGER.debug("REST request to get {} top cars regarding {}", number, criteria);


        List<Car> cars = null;
        
        switch (criteria)
        {
        case "power":
        	cars = carRepository.findAll(Sort.by(Sort.Direction.DESC, "power"));
        	break;
        case "weight":
        	cars = carRepository.findByOrderByWeightAsc();
        	break;
        case "ratio":
        	cars = carRepository.findAll();
        	Collections.sort(cars, new Comparator<Car>() {

				@Override
				public int compare(Car o1, Car o2) {
					return Double.valueOf(o1.getWeight()/o1.getPower()).compareTo(Double.valueOf(o2.getWeight()/o2.getPower()));
				}
			});
        	break;
        default:
        	cars = carRepository.findAll();
        }
        for (Car car : cars) {
			System.out.println(car);
		}
        return carsGroupByBrandModel(cars.subList(0, number));
    }

    private Set<Brand> carsGroupByBrandModel(List<Car> cars) {
      Set<Model> models = cars.stream().map(car -> car.getModel()).collect(Collectors.toSet());
      Set<Brand> brands = models.stream().map(model -> model.getBrand()).collect(Collectors.toSet());
      models.forEach(model -> model.setCars(cars.stream().filter(car -> car.getModel().equals(model)).collect(Collectors.toList())));
      brands.forEach(brand -> brand.setModels(models.stream().filter(model -> model.getBrand().equals(brand)).collect(Collectors.toList())));

      return brands;
    }
}
