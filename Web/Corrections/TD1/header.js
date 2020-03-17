constructor() {
    super();
    this.attachShadow({mode: 'open'});   // attache le shadow-DOM
    getTemplate('/components/header/header.html').then(template => {
        this.shadowRoot.appendChild(template.content.cloneNode(true));
    })
}