package org.weightcars.controller;

import java.util.Comparator;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.weightcars.domain.Brand;
import org.weightcars.repository.BrandRepository;
import org.weightcars.service.BrandService;

/**
 * REST controller for managing Car.
 */
@RestController
@RequestMapping("/api")
@CrossOrigin
public class BrandController {

    public static final int MAX_RESULT = 10;
    private final static Logger LOGGER = LoggerFactory.getLogger(BrandController.class);

    private final BrandRepository brandRepository;

    private final BrandService brandService;

    BrandController (BrandRepository brandRepository, BrandService brandService) {
        this.brandRepository = brandRepository;
        this.brandService = brandService;
    }

    /**
     * GET  /brands : get all the brands.
     *
     * @return the ResponseEntity with status 200 (OK) and the list of brands in body
     */
    @GetMapping("/brands")
    public List<Brand> getAllBrands() {
    	List<Brand> brands = brandRepository.findAll();
        return brands.stream().sorted((Brand b1, Brand b2) -> {return b1.getName().toUpperCase().compareTo(b2.getName().toUpperCase());}).collect(Collectors.toList());
    }

}
