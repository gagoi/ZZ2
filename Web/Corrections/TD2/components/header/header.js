import getTemplate from '/components/util.js';

export default class HeaderComponent extends HTMLElement {

  constructor() {
    super();

    this.filterInputTimeout = 0;
    this.previousFilterValue = '';
    this.attachShadow({mode: 'open'});
    
    getTemplate('/components/header/header.html').then(template => {
      this.shadowRoot.appendChild(template.content.cloneNode(true));
    });

  }

}

customElements.define('header-component', HeaderComponent);


