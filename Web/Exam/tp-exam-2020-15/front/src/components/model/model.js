import React from 'react';
import './model.css';
import CarComponent from './car/car';

export default function ModelComponent(props) {

  const modelArticles = props.brand.models.map(model => {

    const carComponents = model.cars.map(car => (<CarComponent key={car.id} model={model} car={car}></CarComponent>));

    return (
      <article key={model.id} className="card">
        <link rel="stylesheet" href="components/model/model.css" />
        <h3><span className="brand">{props.brand.name}</span>&nbsp;<span className="model">{model.name}</span></h3>
        <a href={model.cars[0].imageUrl} className="image-link">
          <img alt="car" src={model.cars[0].imageUrl} />
        </a>
        <section className="car-content">
          {carComponents}
        </section>
      </article>
    );
  });

  return modelArticles;
}
