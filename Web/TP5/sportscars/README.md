# TD3
Intégrer la maquette à l'API REST fournie et gérer les évènement utilisateurs.

## Intégration API REST
L'appel à l'API se fera avec la fonction Javascript `fetch`. Documentation : https://devhints.io/js-fetch
Cette fonction retourne une promesse. Documentation : https://devhints.io/es6#promises

L'url de base de l'API est :
- https://sport-cars.cfapps.io/api/cars
Site de secours si le 1er est HS ou trop chargé : 
- https://sports-cars-accountable-civet.cfapps.io/api/cars

Il faut faire un GET pour récupérer l'équivalent du JSON fourni.

### Bonus
Remplacer la syntaxe `then()` par des fonction `async/await`.

## Gérer les évènements utilisateur
Pour déclencher un traitement sur un évènement utilisateur (par ex. un clic), utiliser :
`<element cliqué>.addEventListener('click',() => <action à effectuer>)`

### Menus TOP 10
Lorsque l'utilisateur clique sur un menu, appeler l'API suivante : 
`${url de base}/api/cars/top/${menu}/10`

Afficher le résultat dans la page.

### Champs de recherche
Lorsque l'utilisateur tape du texte dans le champs de recherche et appuie ensuite sur entrée, envoyer le texte saisi à l'API suivante :
`${url de base}//api/cars/search/${texte saisi}`

Afficher le résultat dans la page.

#### Bonus 1
Pour éviter d'avoir à taper sur entrée, lancer la recherche lorsque l'utilisateur commence à taper. Laisser une latence de 1 seconde.

#### Bonus 2
Les évènements utilisateurs devraient être remonté au fichier parent `index.js` pour factoriser le code et pour favoriser la réutilisation des web components.
Pour cela, il faut passer en _propriété_ du web component une fonction qui sera appelée par l'évènement.

index.js :
```
header.onTop10Click = () => {
    // Appel API
};
```

header.js :
```
element.addEventListener('click', () => this._onTop10Click());
```
