import getTemplate from '/components/util.js';

export class ModelComponent extends HTMLElement {

  // Observed attribute triggers method attributeChangedCallback
  static get observedAttributes() {
    return ['brand', 'model', 'image-url'];
  }

  get cars() {
    return this._cars;
  }

  // cars property is initialized in index.js with model.car = ...
  set cars(value) {
    this._cars = value; // we set the private property
    
    this.templatePromise.then(() => { // we wait until DOM is loaded
      
      // for each car passed in property
      this._cars.forEach(car => {

        // instance of CarComponent is created as an HTML element
        const carComponent = document.createElement('car-component');
        carComponent.setAttribute('name', `${this.getAttribute('model')} ${car.name}`);
        carComponent.setAttribute('year', car.year);
        carComponent.setAttribute('ratio', car.ratio);
        carComponent.setAttribute('weight', car.weight);
        carComponent.setAttribute('power', car.power);
        this.shadowRoot.querySelector('.car-content').appendChild(
            carComponent);

      });
    });
  }

  constructor() {
    super();
    this.attachShadow({mode: 'open'}); // attach shadow DOM to the component

    // Load model.html from URL
    this.templatePromise = getTemplate('/components/model/model.html').then(template => {
      // clone model.html content and append it to the shadow DOM 
      this.shadowRoot.appendChild(template.content.cloneNode(true));
    });

    // Init property
    this._cars = [];
  }

  // each values passed to observed attributes are sent as newValue
  attributeChangedCallback(name, _oldValue, newValue) {
    this.templatePromise.then(() => { // we wait until DOM is loaded
      if(name && name != '' && newValue && newValue !== 'undefined') {
        switch (name) {

          case 'image-url':
            const img = this.shadowRoot.querySelector('img');
            img.src = newValue;
            break;
        
          default:
            this.shadowRoot.querySelector(`.${name}`).innerText = newValue;
            break;
        }
      }
    });
  }
}

// Define class as custom HTML element
customElements.define('model-component', ModelComponent);
