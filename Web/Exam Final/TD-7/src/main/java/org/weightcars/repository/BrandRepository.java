package org.weightcars.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import org.weightcars.domain.Brand;


/**
 * Spring Data  repository for the Brand entity.
 */
@SuppressWarnings("unused")
@Repository
public interface BrandRepository extends JpaRepository<Brand, String> {

	@Query("from Brand order by Name desc")
	public List<Brand> findAll();
}
