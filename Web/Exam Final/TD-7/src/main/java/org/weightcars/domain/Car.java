package org.weightcars.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import java.io.Serializable;
import java.time.LocalDate;
import java.util.Base64;
import java.util.Objects;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

/**
 * A Car.
 */
@Entity
@Table(name = "car")
public class Car implements Serializable, Comparable<Car> {

    private static final long serialVersionUID = 1L;

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "variant")
    private String name;

    @Column(name = "power")
    private Double power;

    @Column(name = "real_weight")
    private Double weight;

    @Column(name = "options")
    private String options;

    @Column(name = "start_date")
    private LocalDate startDate;

    @Column(name = "image_url")
    private String imageUrl;

    @Column(name = "image")
    private byte[] image;

    @ManyToOne(cascade = {CascadeType.ALL})
    @JsonIgnore
    private Model model;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public Car variant(String variant) {
        this.name = variant;
        return this;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Double getPower() {
        return power;
    }

    public Car power(Double power) {
        this.power = power;
        return this;
    }

    public void setPower(Double power) {
        this.power = power;
    }

    public Double getWeight() {
        return weight;
    }

    public void setWeight(Double weight) {
        this.weight = weight;
    }

    public String getOptions() {
        return options;
    }

    public Car options(String options) {
        this.options = options;
        return this;
    }

    public void setOptions(String options) {
        this.options = options;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public Car startDate(LocalDate startDate) {
        this.startDate = startDate;
        return this;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    public Model getModel() {
        return model;
    }

    public Car setModel(Model model) {
        this.model = model;
        return this;
    }

    /**
     * TD7
     *
     * @return image as base64 for frontend
     */
    public String getImage() {
        if (image != null) {
            return Base64.getEncoder().encodeToString(image);
        } else {
            return null;
        }
    }

    public void setImage(byte[] image) {
        this.image = image;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        Car car = (Car) o;
        if (car.getId() == null || getId() == null) {
            return false;
        }
        return Objects.equals(getId(), car.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(getId());
    }

    @Override
    public String toString() {
        return "Car{" +
            "id=" + getId() +
            ", variant='" + getName() + "'" +
            ", power=" + getPower() +
            ", weight=" + getWeight() +
            ", options='" + getOptions() + "'" +
            ", startDate='" + getStartDate() + "'" +
            "}";
    }

    @Override
    public int compareTo(Car other) {
        // null first
        return other == null || other.getName() == null ? -1 :
            other.getName().equalsIgnoreCase(this.getName()) ? 0 : other.getName().compareTo(this.getName());
    }
}
