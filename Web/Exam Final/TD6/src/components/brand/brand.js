import React from 'react';
import './brand.css';

export default function BrandComponent(props) {


  return (
  <h2 onClick={() => props.selectBrand(props.id)}>{props.name}</h2>
  );
}


