package org.weightcars.repository;

import java.util.List;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import org.weightcars.domain.Car;


/**
 * Spring Data  repository for the Car entity.
 */
@Repository
public interface CarRepository extends JpaRepository<Car, Long> { // Car is "select from" entity. Long is type of Car.id 

    /** 
     * Simples queries without joins. Start from Car entity as defined above (JpaRepository<Car, Long>)
     * 1st "By" is required even without filter.
     */
    List<Car> findTop10ByOrderByPowerDesc();
    List<Car> findTop10ByOrderByWeightAsc();

    /** Query with "where" */
    List<Car> findByNameLikeIgnoreCase(String name);
    
    
    /**
     * Query with "joins" and "where"
     * About joins: 
     *  - browse object model separated by "_" 
     *  - entity names begin with uppercase letter but final attribute by lowercase
     */
    List<Car> findByModel_Brand_nameLikeIgnoreCase(String name);

    List<Car> findByModel_nameLikeIgnoreCase(String name);

    /**
     * JPQL Query. Syntaxe is like SQL. Some differences :
     * - "select" is optional
     * - use class name instead of table name
     * - use class attribute instead of column name
     * - no need to make joins manually, all joined entities are available since they are mapped with oneToMany, manyToOne, ... 
     *   for example: @Query("from Car where model.brand.name = 'tutu'") is valid
     */
    @Query("from Car where weight is not null and weight <> 0 and power is not null and power <> 0 order by weight/power asc")
    List<Car> findAllOrderByRatio();
    
    List<Car> findByModel_Brand_id(Long id);
}
