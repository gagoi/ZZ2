package org.weightcars.service;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import org.weightcars.domain.Car;
import org.weightcars.domain.CarImage;
import org.weightcars.repository.CarRepository;
import org.weightcars.service.async.ImageService;

/**
 * TD7 : manage Car images
 */
@Service
public class CarService {

    private final static Logger LOGGER = LoggerFactory.getLogger(CarService.class);
    private static final String CARIMAGERY_COM_API = "http://www.carimagery.com/api.asmx/GetImageUrl?searchTerm=";

    private final ImageService imageService;
    private final CarRepository carRepository;

    public CarService(ImageService imageService, CarRepository carRepository) {
        this.imageService = imageService;
        this.carRepository = carRepository;
    }

    /**
     * Refresh given car image from carimagery
     */
    public Car refreshCarImage(Car car) {

        if (car.getImageUrl() == null) {
            // Get image url
            String searchTerms = car.getModel().getBrand().getName();
            if (car.getModel().getName() != null && !car.getModel().getName().isEmpty()) {
                searchTerms += " " + car.getModel().getName();
            }
            if (car.getName() != null && !car.getName().isEmpty()) {
                searchTerms += " " + car.getName();
            }
            try {
                searchTerms = URLEncoder.encode(searchTerms, "UTF-8");
            } catch (UnsupportedEncodingException e) {
                LOGGER.error(null, e);
            }
            LOGGER.info("refreshCarImage with url {}", CARIMAGERY_COM_API + searchTerms);
            CarImage response = new RestTemplate().getForObject(CARIMAGERY_COM_API + searchTerms, CarImage.class);
            car.setImageUrl(response != null ? response.getUrl() : null);
            imageService.recordImage(car.getId(), response.getUrl());

            car = carRepository.save(car);
        }

        return car;
    }

    /**
     * Batch refresh database images
     */
    @Scheduled(fixedDelay = 24 * 3600 * 1000) // each days
    public void refreshAllCarImages() {
        LOGGER.info("refresh all car images");
        carRepository.findAll().forEach(this::refreshCarImage);
    }
}
