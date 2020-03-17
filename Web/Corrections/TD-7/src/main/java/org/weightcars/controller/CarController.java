package org.weightcars.controller;

import java.util.*;
import java.util.stream.Collectors;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
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
            .sorted(Comparator.naturalOrder())  // Sort using Car.equals()
            .limit(MAX_RESULT)                  // Limit number of cars
            .map(carService::refreshCarImage)   // Call CarService.refreshCarImage for each car
            .collect(Collectors.toList());      // Build a list
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

        String like = String.format("%%%s%%", searchString);

        // Search cars by manufacture name
        List<Car> carsByBrand = carRepository.findByModel_Brand_nameLikeIgnoreCase(like);

        // Search cars by model name
        List<Car> carsByModel = carRepository.findByModel_nameLikeIgnoreCase(like);

        // Search cars by variant name
        List<Car> carsByName = carRepository.findByNameLikeIgnoreCase(like);

        // Add all cars to new result set. We use set to avoid duplicates.
        Set<Car> cars = new HashSet<>();
        cars.addAll(carsByBrand);
        cars.addAll(carsByModel);
        cars.addAll(carsByName);

        final List<Car> filteredCars = cars.stream()
                .sorted(Comparator.naturalOrder()) // Sort using Car.equals()
                .limit(MAX_RESULT)                 // Limit number of cars
                .map(carService::refreshCarImage)  // Call CarService.refreshCarImage for each car
                .collect(Collectors.toList());     // Build a list
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

        List<Car> topCars = null;
        switch (criteria) {
            case "weight":
                topCars = carRepository.findTop10ByOrderByWeightAsc();
                break;
            case "power":
                topCars = carRepository.findTop10ByOrderByPowerDesc();
                break;
            case "ratio":
                topCars = carRepository.findAllOrderByRatio();
                break;
            default:
                throw new UnsupportedOperationException();
        }

        final List<Car> cars = topCars.stream()
            .limit(MAX_RESULT)                 // Limit number of cars
            .map(carService::refreshCarImage)  // Call CarService.refreshCarImage for each car
            .collect(Collectors.toList());     // Build a list

        return carsGroupByBrandModel(cars);
    }

    private Set<Brand> carsGroupByBrandModel(List<Car> cars) {
      Set<Model> models = cars.stream().map(car -> car.getModel()).collect(Collectors.toSet());
      Set<Brand> brands = models.stream().map(model -> model.getBrand()).collect(Collectors.toSet());
      models.forEach(model -> model.setCars(cars.stream().filter(car -> car.getModel().equals(model)).collect(Collectors.toList())));
      brands.forEach(brand -> brand.setModels(models.stream().filter(model -> model.getBrand().equals(brand)).collect(Collectors.toList())));

      return brands;
    }
}
