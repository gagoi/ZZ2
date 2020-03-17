package org.weightcars.repository;

import java.util.List;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import org.weightcars.domain.Car;


/**
 * Spring Data  repository for the Car entity.
 */
@SuppressWarnings("unused")
@Repository
public interface CarRepository extends JpaRepository<Car, Long> {

	public List<Car> findByOrderByPowerDesc();

	public List<Car> findByOrderByWeightAsc();
}
