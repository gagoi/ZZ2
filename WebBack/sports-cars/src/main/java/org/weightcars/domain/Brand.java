package org.weightcars.domain;


import java.io.Serializable;
import java.util.List;
import java.util.Objects;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Transient;

/**
 * A Brand.
 */
@Entity
@Table(name = "brand")
public class Brand implements Serializable, Comparable<Brand> {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @Transient // Tells JPA to ignore this field
    private List<Model> models;

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

    public List<Model> getModels() {
        return models;
    }

    public void setModels(List<Model> models) {
        this.models = models;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        Brand brand = (Brand) o;
        if (brand.getId() == null || getId() == null) {
            return false;
        }
        return Objects.equals(getId(), brand.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(getId());
    }

    @Override
    public String toString() {
        return "Manufacturer{" +
            "id=" + getId() +
            ", name='" + getName() + "'" +
            "}";
    }


    @Override
    public int compareTo(Brand other) {
        // null first
        return other == null || other.getName() == null ? -1 :
            other.getName().equalsIgnoreCase(this.getName()) ? 0 : other.getName().compareTo(this.getName());
    }
}
