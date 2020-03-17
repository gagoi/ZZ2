import React, { useState, useEffect } from 'react';
import './App.css';
import HeaderComponent from './components/header/header';
import ModelComponent from './components/model/model';


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

function App() {

  const [data, setData] = useState([]);

  useEffect(() => {
    fetch(`${BASE_URL}/api/cars`)
      .then(response => response.json())
      .then(data => {
          setData(data);
      });
  }, []);
  

  const modelComponents = data.map(brand => <ModelComponent key={ brand.id } brand={ brand }></ModelComponent>);

  return (
    <div className="App">
      <HeaderComponent onMenuSelect={ menu => menuClick(setData, menu) } onSearchChange={ val => searchCars(setData, val) }></HeaderComponent>
      <section className="model-content">{ modelComponents }</section>
    </div>
  );
}

export default App;
