import getTemplate from '../util';
const FILTER_INPUT_TIMEOUT = 500;
export default class HeaderComponent extends HTMLElement {

  get onMenuSelect() {
    return this._onMenuSelect;
  }

  set onMenuSelect(value) {
    this._onMenuSelect = value;
  }

  get onSearchChange() {
    return this._onSearchChange;
  }

  set onSearchChange(value) {
    this._onSearchChange = value;
  }

  constructor() {
    super();

    this.filterInputTimeout = 0;
    this.previousFilterValue = '';
    this.attachShadow({mode: 'open'});
    
    getTemplate('/components/header/header.html').then(template => {
      this.shadowRoot.appendChild(template.content.cloneNode(true));
      this.shadowRoot.querySelector('.home').addEventListener('click',() => this._onMenuSelect('home'));
      this.shadowRoot.querySelector('.top10-weight').addEventListener('click',() => this._onMenuSelect('weight'));
      this.shadowRoot.querySelector('.top10-power').addEventListener('click', () => this._onMenuSelect('power'));
      this.shadowRoot.querySelector('.top10-ratio').addEventListener('click', () => this._onMenuSelect('ratio'));
      this.shadowRoot.querySelector('.search-filter').addEventListener('keyup', () => {
        const input = this.shadowRoot.querySelector('.search-filter');
        if (input.value !== this.previousFilterValue) {
          clearTimeout(this.filterInputTimeout);
          const timer = setTimeout(() => this._onSearchChange(input.value), FILTER_INPUT_TIMEOUT);
          this.filterInputTimeout = timer;
          this.previousFilterValue = input.value;
        }
      });
    });

    this._onMenuSelect = function (menu) {}; // callback defined by parent
    this._onSearchChange = function (value) {}; // callback defined by parent
  }

}

customElements.define('header-component', HeaderComponent);


