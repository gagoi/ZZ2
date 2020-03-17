# TD2
Décomposer les fichiers en web components réutilisables

## Serveur HTTP
Pour réaliser cette partie, on va devoir publier notre page web avec un serveur HTTP.
Voici une solution simple.
- installer _node.js_
- se positionner dans le répertoire racine du projet
- exécuter `npx http-serve .`
- vérifier que votre page s'affiche à l'URL http://localhost:8080/index.html

## Décomposition en web components
Plusieurs parties sont répétées dans l'application:
- 1 en-tête avec le titre, la recherche et les menus (en rouge dans `screenshot.png`)
- pour chaque modèle : 1 carte (en jaune dans `screenshot.png`)
  - pour chaque voiture : 1 panneau dépliable (en bleu dans `screenshot.png`)

On va donc créer 3 web components : 
- un dans le répertoire `components/header` : `header.js`  `header.html`  `header.css`
- un dans le répertoire `components/model` : `model.js`  `model.html`  `model.css`
  - qui en contient un autre dans le répertoire `components/model/car` : `car.js`  `car.html`  `car.css`


## Créer le Web component `<header-component>` pour l'en-tête
Un web component _standard_ est composé de 3 notions :
- le _custom element_ qui est une nouvelle balise HTML au nom du web component `<header-component></header-component>`
- la classe Javascript qui inclue le _shadow-DOM_ : si on utilise `<header-component></header-component>`, la balise contiendra une arborescence de balise HTML, le _shadow-DOM_
- le _template_ qui est le code HTML du web component. Il est inclu dans une balise `<template>code HTML de mon web component</template>`

### Fichier `header.js` : le _custom element_
- dans le fichier `header.js`, exporter une classe `HeaderComponent` qui étend `HTMLElement`
- enregistrer l'élément avec `customElements.define('header-component', HeaderComponent);`
- inclure le fichier `header.js` dans `index.html` comme ceci : 
  `<script type="module" src="components/header/header.js"></script>`
- le type _module_ permet de déclarer des classes et fonctions avec l'instruction `export`
- tester votre web component le déclarant dans `index.html` : `<header-component></header-component>`
  - vérifier qu'il n'y a pas d'erreur dans la console javascript du navigateur
  - inspecter l'élément header-component : vous devriez voir le pseudo element shadow-root à l'intérieur

### Fichier HTML : le _template_

#### Fichiers `header.html` et `header.css`
- copier/coller le code HTML/CSS dans les fichiers correspondants.
- Inclure `header.css` dans `header.html` avec la balise `<link>`
- Encapsuler tout le contenu de `header.html` dans une balise `<template>`
- supprime le code HTML/CSS de l'en-tête de `index.html` et `index.css`

#### Récupérer ces fichiers dans `<mon web component>.js`
- importer la fonction `getTemplate` fournie dans `utils.js` et appeler-la dans le constructeur de votre web component :
```
    this.attachShadow({mode: 'open'});
    this.templatePromise = getTemplate('/components/header/header.html').then(template => {
        this.shadowRoot.appendChild(template.content.cloneNode(true));
    });
```
- vérifier l'affichage : vous devriez voir le HTML avec les styles CSS, comme au début du TD.


## Créer les web components _car_ et _model_

### Web component _car_
Suivez la même procédure que pour le web component _header_

### Passer des données en paramètre
Passer des données en paramètre d'un web component s'appelle le _data binding_, car non seulement on les passe pour initialiser celui-ci, mais aussi à chaque fois qu'elles seront mises à jour. Les données sont _liées_ au web component.

### Attributs
Les attributs sont les noms des paramètres d'une balise HTML, par exemple `src`est un attribut de `img` dans `<img src="toto.jpg">`

Déterminer quels sont les attributs nécessaires à votre web component pour afficher les données du véhicule.

Passer ces attributs en paramètre de la balise de votre web component.

Pour indiquer au navigateur que l'on veut mettre à jour le web component à chaque modification des données, déclarer dans la classe du web component la méthode statique suivante :
```
  // Liste des attributs "observés", c'est à dire qui appeleront la méthode "attributeChangedCallback" à chaque modification
  static get observedAttributes() {
    return ['attr1', 'attr2', ...];
  }
```

### Mise à jour
On va maintenant déclarer la méthode `attributeChangedCallback` dans la classe :

```
    attributeChangedCallback(attributeName, _oldValue, newValue) { // On ne se servira pas de _oldValue
        this.templatePromise.then(() => {
        ...
        });
    }
```
Cette méthode sera appelée pour chaque attribut que vous avez listé.
Utilisez le code Javascript du TD1 pour mettre à jour les données dans votre _template_. Pour récupérer les éléments il faudra utiliser :
`this.shadowRoot.querySelector(...)` 

Tester l'affichage des données en déclarant le web component avec des données en dur.

### Web component _model_
Suivez la même procédure que pour le web component _car_

### Création dynamique des _models_
Dans `index.js`, créer une boucle sur les données JSON pour ajouter tous les _models_ avec `document.createElement` et `appendChild`.
Vous devriez voir la liste des cartes comme dans `screenshot.png`, sans les données de _car_.

Dans `model.js`, il faut créer la même boucle pour ajouter toutes les _cars_. Cependant on ne dispose pas des données JSON du _model_ dans la classe de _model_.

On ne peut pas récupérer des données JSON en attribut car leurs valeurs doivent être des chaînes de caractères.

On va donc utiliser la notion de _propriété_.

### Création d'une propriété
La propriété _cars_ du composant _model_ prendra le tableau des voitures du modèle.

Dans `model.js`, déclarer la propriété comme ceci avec ses _getter_ et _setter_ :
```
  get cars() {
    return this._cars;
  }

  set cars(value) {
    this._cars = value;
  }

  constructor() {
    super();
    this._cars = [];
```

Dans `index.js` passer le tableau après avoir créer l'élément avec `document.createElement`
`theModel.cars = ...`

### Création dynamique des _cars_
Vous pouvez maintenant créer un élément _car_ dans le _setter_ de la propriété 
```
  set cars(value) {
    this._cars = value;
    this.templatePromise.then(() => {
        // insertion des éléments "car"
    });
```

## Conclusion
L'application devrait à présent ressembler à la capture d'écran qui correspond aux données JSON.


