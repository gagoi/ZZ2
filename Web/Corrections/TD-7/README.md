# TD-7

Compléter le backend Java

## Exercice 1 : lancer l'application

1. Lancer la commande 
`gradlew.bat bootrun`

2. Lorsque vous voyez la ligne "Completed initialization in ..." vous pouvez voir si l'API répond bien sur l'URL :
http://localhost:8745/api/cars

3. Explorez la base de données sur l'URL : http://localhost:8745/h2-console
   Pour se connecter, modifier JDBC URL en `jdbc:h2:file:~/weightcars-h2;DB_CLOSE_DELAY=-1`

## Exercice 2 : implémenter l'API appelée par les boutons "TOP 10"

Vous devez implémenter : 
- une méthode dans le contrôleur `CarController` qui intercepte l'url de l'API
  - pour tester que la méthode est bien configurée, vous pouvez mettre un point d'arrêt dessus : un clic sur un des boutons doit déclencher le point d'arrêt
- cette méthode appelera une autre méthode de recherche que vous coderez dans ```CarRepository```
   - appuyez-vous sur la doc de [Spring Data](https://docs.spring.io/spring-data/jpa/docs/1.10.1.RELEASE/reference/html/#jpa.query-methods.query-creation)
   - **Attention** pour le calcul du ratio, vous devez ignorer les valeurs nulles de weight et power!


## Exercice 3 : implémenter l'API de filtre
Vous remarquerez un champs texte au dessus de la liste des voitures : ce champs texte appelle à chaque changement une API de filtre qui n'existe pas encore.
Vous devez implémenter cette API comme pour l'exercice précédent.
Le résultat doit être le suivant :  
- quand je tape du texte dans la partie _filter_, je dois voir apparaître uniquement les voitures dont _brand_, le _model_ ou _car_ comprends le texte, peu importe la casse (majuscules/minuscules)
- implémenter un test JUNIT qui valide le cas d'utilisation nominal : recherche avec un texte conforme qui ramène au moins 1 élément

## Exercice 4 (bonus) : implémenter un tri par défaut
On voudrait que la recherche initiale ```/api/cars``` et la recherche filtrée ```api/cars/search``` soient triées par défaut.
La logique de tri est l'ordre "naturel" :
- par ordre alphabétique sur le nom de la marque
- puis par ordre alphabétique sur le nom du modèle
- puis par ordre alphabétique sur le nom de la variante
- les valeurs nulles sont affichées en 1er
- on ignore la casse (majuscules/minuscules)
Il faut donc modifier les 2 API sans dupliquer le code de la logique de tri.
