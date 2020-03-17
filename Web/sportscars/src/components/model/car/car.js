import getTemplate from '../../util.js';

const POWER_MAX = 1000; // max 1000hp, else overflow
const WEIGHT_MAX = 2500; // max 2500kg, else overflow
const RATIO_MAX = 1; // max 1kg/hp else overflow

export class CarComponent extends HTMLElement {

  static get observedAttributes() {
    return ['name', 'year', 'power', 'weight', 'ratio'];
  }

  constructor() {
    super();
    this.attachShadow({mode: 'open'});
    this.templatePromise = getTemplate('/components/model/car/car.html').then(template => {
        this.shadowRoot.appendChild(template.content.cloneNode(true));
    });
  }

  attributeChangedCallback(name, _oldValue, newValue) {
    this.templatePromise.then(() => {
      if(newValue !== 'undefined') {
        this.shadowRoot.querySelector(`.${name}`).innerText = newValue;
        if (['power', 'weight', 'ratio'].includes(name)) {
          let numberValue = +newValue;
          if (name === 'power') {
            numberValue = numberValue * 100 / POWER_MAX;
          }
          if (name === 'weight') {
            numberValue = numberValue * 100 / WEIGHT_MAX;
          }
          if (name === 'ratio') {
            numberValue = RATIO_MAX * 100 / numberValue;
          }
          this.shadowRoot.querySelector(
              `.bar-${name}`).style.width = `${numberValue}%`;
        }
      }
    });
  }
}

customElements.define('car-component', CarComponent);
