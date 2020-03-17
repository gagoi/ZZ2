package org.weightcars.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import java.io.Serializable;
import java.util.List;
import java.util.Objects;
import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.Transient;

/**
 * A Model.
 */
@Entity
@Table(name = "model")
public class Model implements Serializable, Comparable<Model> {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    @ManyToOne(cascade = {CascadeType.ALL})
    @JsonIgnore
    private Brand brand;

    /**
     * List of filtered cars to send back to client
     */
    @Transient  // Tells JPA to ignore this field
    private List<Car> cars;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Brand getBrand() {
        return brand;
    }

    public Model setBrand(Brand brand) {
        this.brand = brand;
        return this;
    }

    public List<Car> getCars() {
        return cars;
    }

    public void setCars(List<Car> cars) {
        this.cars = cars;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        Model model = (Model) o;
        if (model.getId() == null || getId() == null) {
            return false;
        }
        return Objects.equals(getId(), model.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(getId());
    }

    @Override
    public String toString() {
        return "Model{" +
            "id=" + getId() +
            ", name='" + getName() + "'" +
            "}";
    }

    @Override
    public int compareTo(Model other) {
        // null first
        return other == null || other.getName() == null ? -1 :
            other.getName().equalsIgnoreCase(this.getName()) ? 0 : other.getName().compareTo(this.getName());
    }
}
