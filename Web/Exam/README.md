# Examen de développement Web

Pour cet examen, utiliser une version récente de Chrome ou Firefox, Git et NodeJS.

## Version de node

1. Taper la commande :
`node -v`
2. La version doit être supérieure à 10.

## Test de http-serve 

1. Taper la commande : 
`npx http-serve .`
2. Ouvrez l'url http://localhost:8080/test.html, vous devez voir apparaître "Hello World!"
3. Modifier le fichier, sauvegarder et rafraîchir la page avec ctrl+F5.
4. Vous devez voir vos modifications.

## Test de node

1. Taper la commande :
`node test.js`
2. Vous devez voir apparaître "Hello World!"

## Test de babel

1. Taper la commande :
`npm install`
Cela va installer Babel, un outil qui sait convertir le code JSX
2. Taper la commande :
`npx babel --watch test-babel --out-dir . --presets react-app/prod`
Babel va transpiler les fichiers présents dans le répertoire "test-babel" en code JS interprétable par le navigateur. 
Ce script reste en écoute pour transpiler les fichiers à chaque modification.
3. Relancer http-serve si vous l'aviez arrêté
4. Ouvrez l'url http://localhost:8080/test-babel.html, vous devez voir apparaître "Hello React!"

## Test de git
1. Créez une branche <prenom>.<nom> et faire un push sur le repository
