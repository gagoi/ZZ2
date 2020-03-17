import getTemplate from '/components/util.js';

export class ModelComponent extends HTMLElement {

  static get observedAttributes() {
    return ['brand', 'model', 'image-url'];
  }

  get cars() {
    return this._cars;
  }

  set cars(value) {
    this._cars = value;
    this.templatePromise.then(() => {
      this._cars.forEach(car => {

        // object car to insert as child element
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
    this.attachShadow({mode: 'open'});
    this.templatePromise = getTemplate('/components/model/model.html').then(template => {
      this.shadowRoot.appendChild(template.content.cloneNode(true));
    });
    this._cars = [];
  }

  attributeChangedCallback(name, _oldValue, newValue) {
    this.templatePromise.then(() => {
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

customElements.define('model-component', ModelComponent);
