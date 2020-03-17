package org.weightcars.service.async;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;
import org.weightcars.repository.CarRepository;
import org.weightcars.service.CarService;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.URL;

@Service
public class ImageService {

    private final static Logger LOGGER = LoggerFactory.getLogger(CarService.class);

    private final CarRepository carRepository;

    public ImageService(CarRepository carRepository) {
        this.carRepository = carRepository;
    }

    @Async("processExecutor")
    public void recordImage(Long carId, String url) {
        // Get image from url
        try {
            if (url != null) {
                BufferedImage image = ImageIO.read(new URL(url));
                if (image != null) {
                    // Save image as byte array
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();
                    ImageIO.write(image, "jpg", baos);
                    baos.flush();
                    final byte[] imageInByte = baos.toByteArray();
                    carRepository.findById(carId).ifPresent(car -> {
                        car.setImage(imageInByte);
                        carRepository.save(car);
                    });
                    baos.close();
                }
            }
        } catch (IOException e) {
            LOGGER.error(null, e);
        }
    }

}
