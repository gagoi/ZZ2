import React, { useEffect } from 'react';
import logo from './logo.svg';
import './App.css';
import HeaderComponent from './components/header/header.js';
const BASE_URL = 'https://sport-cars.cfapps.io';

function renderCars(data) {

  const modelContent = document.querySelector('.model-content');
  modelContent.innerHTML = '';
  let i = 0;

  data.forEach(brand => {
      brand.models.forEach(model => {
      const modelComponent = document.createElement('model-component');
      modelComponent.classList.add('card');

      // we can push brand and model as attribute because they are strings
      modelComponent.setAttribute('brand', brand.name);
      modelComponent.setAttribute('model', model.name);
      modelComponent.setAttribute('image-url', model.cars[0].imageUrl);

      // push car as property because it is an array
      modelComponent.cars = model.cars.map(car => ({
        name: car.name,
        year: car.startDate ? car.startDate.match(/\d{4}/g)[0] : undefined,
        ratio: Math.round(car.weight * 10 / car.power) / 10,
        weight: car.weight,
        power: car.power,
      }));

      modelContent.appendChild(modelComponent);
    });
  });
}

// Callback function for header search textbox
function searchCars(value) {

  const url = `${BASE_URL}/api/cars${value && value.trim() !== '' ? '/search/' + value : ''}`;
  fetch(url)
    .then(response => response.json())
    .then(data => {
      renderCars(data);
    });
}

// Callback function for header menu top10
function menuClick(what) {
  if (what === 'home') {
    searchCars();
  } else {
    fetch(`${BASE_URL}/api/cars/top/${what}/10`)
    .then(response => response.json())
    .then(data => {
      renderCars(data);
    });
  }
}

function App() {
  useEffect(() => {
    
  // Bind header component event on API functions
  const header = document.querySelector('header-component');
  header.onMenuSelect = menuClick;
  header.onSearchChange = searchCars;

  // Initialize data
  fetch(`${BASE_URL}/api/cars`)
    .then(response => response.json())
    .then(data => {
      renderCars(data);
    });

  });
  return (
    <div className="App">
        <section className="app-container">
          <header-component></header-component>
          <section className="model-content"></section>
          <div className="overlay"></div>
        </section>
      
    </div>
  );
}

export default App;
