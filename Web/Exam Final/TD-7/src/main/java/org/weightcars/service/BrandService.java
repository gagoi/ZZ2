package org.weightcars.service;

import org.springframework.stereotype.Service;
import org.weightcars.repository.BrandRepository;

/**
 * TD7 : manage Car images
 */
@Service
public class BrandService {
	
    private final BrandRepository brandRepository;

    public BrandService(BrandRepository brandRepository) {
        this.brandRepository = brandRepository;
    }
}
