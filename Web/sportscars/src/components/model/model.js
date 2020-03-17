import React from 'react';

export class ModelComponent extends React.Component {

  constructor(props) {
    super(props);
  }

  render() {
    return (
      <div>
  <h3>
    <span className="brand">{this.props.brand}</span>&nbsp;
    <span className="model"></span></h3>
    <a className="image-link">
      <img />
    </a>
    <section className="car-content">

    </section>
    </div>
    )
  }
}

customElements.define('model-component', ModelComponent);
