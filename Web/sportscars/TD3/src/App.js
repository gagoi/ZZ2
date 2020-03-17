import React, { useState, useEffect } from 'react';
import './App.css';
import HeaderComponent from './components/header/header';
import ModelComponent from './components/model/model';

const BASE_URL = 'https://sport-cars.cfapps.io/';

export default class App extends React.Component {

  constructor(props) {
    super(props);
    this.state = {data: []};
  }

  componentDidMount() {

    // Bind header component event on API functions
    const header = document.querySelector('header-component');
    header.onMenuSelect = menu => {
      if (menu === 'home') {
        this.searchCars('');
      } else {
        this.menuClick(menu);
      }
    };

    header.onSearchChange = val => {
      this.searchCars(val);
    };

    fetch(`${BASE_URL}/api/cars`)
      .then(response => response.json())
      .then(data => {
        this.setState({ data });
      });
  }
  
  render() {
    const modelComponents = this.state.data
      .map(brand => brand.models.map(model => <ModelComponent key={ model.id } brand={ brand } model={ model }></ModelComponent>))
      .flat();

    return (
      <div className="App">
        <header-component></header-component>
        <section className="model-content">{ modelComponents }</section>
      </div>
    );
  }

  menuClick(menu) {
      if (menu === 'home') {
        this.searchCars('');
      } else {
        this.top10Click(menu);
      }
  }

  searchCars(value) {

    const url = `${BASE_URL}/api/cars${value && value.trim() !== '' ? '/search/' + value : ''}`;
    fetch(url)
        .then(response => response.json())
        .then(data => {
          this.setState({ data });
    });
  }

  top10Click(what) {

    fetch(`${BASE_URL}/api/cars/top/${what}/10`)
        .then(response => response.json())
        .then(data => {
          this.setState({ data });
    });
  }
}

