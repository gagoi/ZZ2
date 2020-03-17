package org.weightcars.domain;

import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlValue;

@XmlRootElement(namespace = "http://carimagery.com/", name = "string")
public class CarImage {

    private String url;

    @XmlValue
    public String getUrl() {
        return url;
    }

    public void setUrl(String el) {
        this.url = el;
    }
}
