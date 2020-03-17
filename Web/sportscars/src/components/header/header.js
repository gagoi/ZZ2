import getTemplate from '../util.js';
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

      // bind menu click on callback properties
      this.shadowRoot.querySelector('.top10-weight').addEventListener('click',() => this._onMenuSelect('weight'));
      this.shadowRoot.querySelector('.top10-power').addEventListener('click', () => this._onMenuSelect('power'));
      this.shadowRoot.querySelector('.top10-ratio').addEventListener('click', () => this._onMenuSelect('ratio'));
      
      this.shadowRoot.querySelector('.search-filter').addEventListener('keyup', () => { // this code will be called each time keyboard is used
        
        // Get text from textbox
        const input = this.shadowRoot.querySelector('.search-filter');

        if (input.value !== this.previousFilterValue) { // if text has changed
          
          clearTimeout(this.filterInputTimeout); // this will interrupt previous search
          const timer = setTimeout(() => this._onSearchChange(input.value), FILTER_INPUT_TIMEOUT); // this will trigger new search some delay
          
          // we save timer and values for later calls
          this.filterInputTimeout = timer;
          this.previousFilterValue = input.value;
        
        }
      });
    });

    // initialize callback properties (will be defined by index.js)
    this._onMenuSelect = null; 
    this._onSearchChange = null;
  }

}

customElements.define('header-component', HeaderComponent);


