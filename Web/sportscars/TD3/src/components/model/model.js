import React from 'react'
import './model.css'; 
import CarComponent from './car/car';;

export default class ModelComponent extends React.Component {

  constructor(props) {
    super(props);
  }

  render() {

    return (
      <section className="card">
        <h3><span>{ this.props.brand.name }</span>&nbsp;<span>{ this.props.model.name }</span></h3>
        <a className="image-link">
          <img src={ this.props.model.cars[0].imageUrl }/>
        </a>
        <section className="car-content">

        </section>
      </section>
    );

  }
}
