import React from 'react';
import './car.css';

const POWER_MAX = 1000; // max 1000hp, else overflow
const WEIGHT_MAX = 2500; // max 2500kg, else overflow
const RATIO_MAX = 1; // max 1kg/hp else overflow

export default function CarComponent(props) {

  const ratio = Math.round(RATIO_MAX * props.car.power * 100 / props.car.weight);
  const year = props.car.startDate ? props.car.startDate.substr(0, 4) : undefined;

  const barPowerStyle = {
    width: `${props.car.power * 100 / POWER_MAX}%`
  };

  const barWeightStyle = {
    width: `${props.car.weight * 100 / WEIGHT_MAX}%`
  };

  const barRatioStyle = {
    width: `${ratio}%`
  };

  return (
    <details className="car-details">
      <summary className="car-summary">
        <span className="name">{ props.model.name } { props.car.name }</span>&nbsp;-&nbsp;<span className="year">{ year }</span>
      </summary>
      <section className="bars">
        <div className="bar-title"><label>Weight</label><span><span className="weight">{ props.car.weight }</span>kg</span></div>
        <div className="bar bar-weight" style={barWeightStyle}></div>
        <div className="bar-title"><label>Power</label><span><span className="power">{ props.car.power }</span>hp</span></div>
        <div className="bar bar-power" style={barPowerStyle}></div>
        <div className="bar-title"><label>Ratio</label><span><span className="ratio">{ ratio }</span>kg/hp</span></div>
        <div className="bar bar-ratio" style={barRatioStyle}></div>
      </section>
    </details>
  );
}


