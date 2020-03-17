
# TD-6

Ré-écriture du header et gestion des évènements utilisateur
Pour lancer ce TD, taper les commandes suivantes :

``` 
npm install
``` 

Puis :

``` 
npm run start
``` 


## _Header_

Migrer _header_ en composant classe en utilisant le même principe que pour le TD-5.

## Gestion des évènements

Avec les web components W3C, les évènements étaient passés à des propriétés `onSearchChange` et `onMenuSelect`.
Cela ne change pas beaucoup avec React car ces propriétés seront contenues dans l'objet `props`.

Pour les menus on aura donc : 

```
<nav className="top10-weight" onClick={() => this.props.onMenuSelect('weight')}>
```

L'appel du composant depuis App.js ne change pas :

```
<HeaderComponent onMenuSelect={ menu => menuClick(setData, menu) } onSearchChange={ val => searchCars(setData, val) }>
```

Pour la recherche, on va devoir gérer les variables `filterInputTimeout` et `previousFilterValue` dans le state du composant Header.
On utilisera ces variables dans une méthode `handleKeyUp` de ce composant qui sera appelé depuis l'évènement `onKeyUp` de l'élément `<input>`. Cette méthode se chargera de faire le traitement avant d'appeler 

```
this.props.onSearchChange(event.target.value)
```
