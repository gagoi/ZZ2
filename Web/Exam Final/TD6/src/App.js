import React, { useState, useEffect } from 'react';
import './App.css';
import HeaderComponent from './components/header/header';
import ModelComponent from './components/model/model';
import BrandComponent from './components/brand/brand';


const BASE_URL = 'http://localhost:8745/';

function menuClick(setData, menu) {
    if (menu === 'home') {
        searchCars(setData, null);
    } else {
        top10Click(setData, menu);
    }
}

function searchCars(setData, value) {

    const url = `${BASE_URL}/api/cars${value && value.trim() !== '' ? '/search/' + value : ''}`;
    fetch(url)
        .then(response => response.json())
        .then(data => {
          setData(data);
    });
}

function top10Click(setData, what) {

    fetch(`${BASE_URL}/api/cars/top/${what}/10`)
        .then(response => response.json())
        .then(data => {
          setData(data);
    });
}

function carsByBrand(setData, id) {
  fetch(`${BASE_URL}/api/cars/brand/${id}`)
        .then(response => response.json())
        .then(data => {
          console.log(data);
          setData(data);
    });
}

function App() {

  const [data, setData] = useState([]);
  const [brandDatas, setBrandDatas] = useState([]);

  useEffect(() => {
    fetch(`${BASE_URL}/api/cars`)
      .then(response => response.json())
      .then(data => {
          setData(data);
      });

    fetch(`${BASE_URL}/api/brands`)
      .then(response => response.json())
      .then(data => {
          setBrandDatas(data);
      });
  }, []);

  const modelComponents = data.map(brand => <ModelComponent key={ brand.id } brand={ brand }></ModelComponent>);
  const brandComponents = brandDatas.map(brand => <BrandComponent name={brand.name} selectBrand={() => {carsByBrand(setData, brand.id)}}></BrandComponent>);

  return (
    <div className="App">
      <HeaderComponent onMenuSelect={ menu => menuClick(setData, menu) } onSearchChange={ val => searchCars(setData, val) }></HeaderComponent>
      <section className="brand-list">{brandComponents}</section>
      <section className="model-content">{ modelComponents }</section>
    </div>
  );
}

export default App;
