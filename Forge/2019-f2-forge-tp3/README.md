# Infos étudiant :
[![pipeline status](http://gitlab.isima.fr/maarquilli/2019-f2-forge-tp3/badges/master/pipeline.svg)](http://gitlab.isima.fr/maarquilli/2019-f2-forge-tp3/commits/master)

[![coverage report](http://gitlab.isima.fr/maarquilli/2019-f2-forge-tp3/badges/master/coverage.svg)](http://gitlab.isima.fr/maarquilli/2019-f2-forge-tp3/commits/master)
Par binôme Nom Prénom:
 * Arquilliere Mathieu
 * Zangla Jérémy

# TP 3

Le but de ce TP est de mettre en place un processus d'intégration continue en se basant sur le projet précédent.

## 1 Création d'un espace projet dédié sous gitlab
1. Pour mettre en place une chaine d'intégration continue initialisez un nouveau projet sous [GitLab](https://gitlab.isima.fr).
1. Ajouter dans la liste des développeurs votre binôme. (Settings/Members)
1. Ajouter en reporter `tjouve` et `iia_samorel`.
1. Ajoutez ce compte rendu comme readme de votre projet.
    * Vous pouvez le faire directement depuis l'interface avec *new File*
    * Copier le code markdown, il est possible d'editer le document via l'interface web directement sur gitlab
    * **Renseignez vos noms en haut du compte rendu**
1. Ajoutez une licence pour indiquer sous quels termes votre production est disponible
    * Cliquez sur **Add License**, il est possible de rédiger soi-même le contenu, ou de selectionner une licence existante (Apache, MIT, GNU ...). Le site [choose a license](https://choosealicense.com/licenses/) propose un comparatif entre les différentes liences les plus courantes.


## 2 Initialisation du projet
Pour prendre en charge la gestion des dépendances et l'automatisation de la construction de l'application nous utiliserons `Maven`.
Pour démarrer rapidement le projet nous allons faire du *scaffolding*. Pour ce faire nous utiliserons [Spring Boot](https://projects.spring.io/spring-boot/). Et plus particuliérement [Spring initializr](https://start.spring.io/).

### 2.1 Spring Initializer
1. Créer un squelette d'application avec [Spring initializr](https://start.spring.io/) :
    1. choisissez comme groupe id **isima.F2**
    2. comme nom d'artefact vous saisirez **TP3.`nom binome`**
    3. téléchargez ce template de projet.
1. clonez votre nouveau projet localement
    1. dézippez l'archive dans votre repo local, ce dernier ne devrait contenir que l'arborescence des sources, le pom et votre readme
    1. commitez et pushez sur le serveur


### 2.2 Utilisation de maven
Avant de reporter le code du TP2 nous allons nous familiariser avec *Maven*

#### 2.2.1 Convention over configuration
Pour permettre de développer plus rapidement des applications une bonne pratique est de respecter certaines normes.

Dans notre cas en utilisant **Spring Initializer** nous avons rapidement généré un squelette d'application utilisant maven et fournissant un certain nombre de fonctionnalitées transverses.
Notamment un framework de test **JUnit** et un framework de logging **Logback**


* A quoi correspondent les fichiers présents dans le zip ?
    * pom.xml
    * .gitignore
    * décrire l'arborescence de répertoire

 - pom.xml est le fichier de configuration de Maven
 - .gitignore est le fichier contenant les fichiers que l'on ne veut pas suivre avec git
 - A la racine du répertoire, il y a tous les fichiers de configuration, readme et license. Le dossier 'src' contient toutes les sources, d'un côté l'application développée et de l'autre les tests.
```
.
├── HELP.md
├── LICENSE
├── mvnw
├── mvnw.cmd
├── pom.xml
├── README.md
└── src
    ├── main
    │   ├── java
    │   │   └── isima
    │   │       └── F2
    │   │           └── TP3
    │   │               └── zanglaarquilliere
    │   │                   └── Application.java
    │   └── resources
    │       └── application.properties
    └── test
        └── java
            └── isima
                └── F2
                    └── TP3
                        └── zanglaarquilliere
                            └── ApplicationTests.java
```


#### 2.2.2 Gestion des dépendances

Dans le nouveau projet on retrouve une classe *Application.java* sous *src/main/java* dans le package *isima.F2.TP3.`nom binome`*
* Dans cette classe créez un logger et loggez un `Hello Word` en *warning*

```java
private static final Logger logger = LoggerFactory.getLogger(DemoApplication.class);

public static void main(String[] args) {
    SpringApplication.run(DemoApplication.class, args);
    logger.warn("Hello Word");

}
```

* Exécutez votre programme


  .   ____          _            __ _ _
 /\\ / ___'_ __ _ _(_)_ __  __ _ \ \ \ \
( ( )\___ | '_ | '_| | '_ \/ _` | \ \ \ \
 \\/  ___)| |_)| | | | | || (_| |  ) ) ) )
  '  |____| .__|_| |_|_| |_\__, | / / / /
 =========|_|==============|___/=/_/_/_/
 :: Spring Boot ::        (v2.2.4.RELEASE)

2020-02-20 15:20:12.846  INFO 18004 --- [           main] i.F2.TP3.zanglaarquilliere.Application   : Starting Application on gagoi-GP60-2QE with PID 18004 (/home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3/target/classes started by gagoi in /home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3)
2020-02-20 15:20:12.850  INFO 18004 --- [           main] i.F2.TP3.zanglaarquilliere.Application   : No active profile set, falling back to default profiles: default
2020-02-20 15:20:13.338  INFO 18004 --- [           main] i.F2.TP3.zanglaarquilliere.Application   : Started Application in 0.863 seconds (JVM running for 1.374)
2020-02-20 15:20:13.339  WARN 18004 --- [           main] i.F2.TP3.zanglaarquilliere.Application   : Hello World !!

Vous remarquerez qu'il n'est pas nécessaire d'ajouter la dépendance vers un logger (ici *logback*). C'est une dépendance classique d'un projet java. Elle est déjà présente dans le pom de *spring boot*.

Pour illustrer la gestion des dépendances automatiques vous ajouterez une dépendance vers la librairie **commons-lang3** de **apache**
* Ajout de la dépendance *Apache commons lang3*
    * Pour ce faire recherche `commons-lang3` sur [MVNrepository](https://mvnrepository.com).
    * selectionnez la derniére version
    * copiez la déclaration et collez là dans votre *pom.xml*
    * Décrivrez rapidement le fonctionnement de la résolution de dépendance
```
<!-- https://mvnrepository.com/artifact/org.apache.commons/commons-lang3 -->
<dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-lang3</artifactId>
    <version>3.9</version>
</dependency>
```
La résolution de dépendances se fait en indiquant ce dont on a besoin, pour le projet, dans le fichier pom.xml. Maven se charge ensuite de télécharger les packages nécessaires, ainsi que les inclures lors de l'exécution du projet.

* Utilisez la classe utilitaire `StringUtils` et sa méthode `reverse` pour afficher dans la log au niveau *debug* vos noms à la suite du Hello Word.
    * La ligne de log n'apparait pas dans la console car le niveau de trace par defaut est `WARN`.
    * [Spring boot logging](https://docs.spring.io/spring-boot/docs/current/reference/html/howto-logging.html) indique comment changer le niveau de trace. (Il n'est pas nécessaire d'ajouter la dépendance elle est déjà présente).
    * Un fois le niveau de trace par defaut changé vous devriez voir le résultat de votre commande.
    * Quel fichier de configuration est modifié ?

Nous avons modifié le fichier application.properties.

#### 2.2.3 Gestion du cycle de vie

Dans cette partie nous allons utiliser les commandes de build de manven. Ces commandes permettentent d'automatiser certaines taches.
[Maven Lyfe Cycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html) décrit l'ensemble des instructions et l'enchainement des différentes phases de **Maven**.

L'archive générée via spring initializer contient un répertoire `.mvn` et 2 scripts `mvnw` et `mvnw.bat`. Le projet contient par defaut un *wrapper* qui permet d'avoir une installation locale de maven pour ne pas être dépendant du systéme sur lequel on développe.

Il est possible de lancer directement des taches maven en appellant le script (`mvnw` pour *linux* et `mvnw.bat` pour *windows* ).

Par example `./mvnw.bat clean` permet de supprimer les classes compilées dans le repertoire target.

En utilisant la ligne de commande nous allons compiler, tester et packager l'application sous la forme d'un jar.

##### 2.2.3.1 Compilation
* Quelle est la commande à lancer pour compiler l'application ?
* Quelle est la commande à lancer pour compiler & éxécuter les tests ?
* Quel sont les fichiers / répertoires générés par cette commande ?
```
mvnw compile
mvnw test
```
Le dossier target ainsi que tout son contenu (les fichiers compilés par exemple), sont générés pas cette commande.

##### 2.2.3.2 Packaging
* Quelle est la commande à lancer ?
* Quel sont les fichiers / répertoires générés par cette commande ?

```
mvnw package
```
Le dossier target et son contenu sont encore une fois générés. Cependant cette fois-ci un .jar est présent.

### 2.3 Reportez le code du TP2           
* Reportez vos classes d'implémentation et de test dans le nouveau projet
    * Votre implémentation dans le repertoire src/main/java/*pakcage_name*/*Application*
    * Votre classe de test dans le repertoire src/test/java/*pakcage_name*/*ApplicationTests*
* Effectuez le packaging de votre application pour lancer la compilation et les tests.

```
$mvnw clean
[INFO] Scanning for projects...
[INFO] 
[INFO] ------------------< isima.F2:TP3.zangla-arquilliere >-------------------
[INFO] Building TP3.zangla-arquilliere 0.0.1-SNAPSHOT
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- maven-clean-plugin:3.1.0:clean (default-clean) @ TP3.zangla-arquilliere ---
[INFO] Deleting /home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3/target
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  0.543 s
[INFO] Finished at: 2020-02-17T14:29:40+01:00
[INFO] ------------------------------------------------------------------------
■[14:29:40] gagoi@gagoi-GP60-2QE:2019-f2-forge-tp3$ mvnw test
[INFO] Scanning for projects...
[INFO] 
[INFO] ------------------< isima.F2:TP3.zangla-arquilliere >-------------------
[INFO] Building TP3.zangla-arquilliere 0.0.1-SNAPSHOT
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- maven-resources-plugin:3.1.0:resources (default-resources) @ TP3.zangla-arquilliere ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] Copying 1 resource
[INFO] Copying 0 resource
[INFO] 
[INFO] --- maven-compiler-plugin:3.8.1:compile (default-compile) @ TP3.zangla-arquilliere ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 1 source file to /home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3/target/classes
[INFO] 
[INFO] --- maven-resources-plugin:3.1.0:testResources (default-testResources) @ TP3.zangla-arquilliere ---
[INFO] Using 'UTF-8' encoding to copy filtered resources.
[INFO] skip non existing resourceDirectory /home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3/src/test/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.8.1:testCompile (default-testCompile) @ TP3.zangla-arquilliere ---
[INFO] Changes detected - recompiling the module!
[INFO] Compiling 1 source file to /home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3/target/test-classes
[INFO] 
[INFO] --- maven-surefire-plugin:2.22.2:test (default-test) @ TP3.zangla-arquilliere ---
[INFO] 
[INFO] -------------------------------------------------------
[INFO]  T E S T S
[INFO] -------------------------------------------------------
[INFO] Running isima.F2.TP3.zanglaarquilliere.ApplicationTests
14:29:46.271 [main] DEBUG org.springframework.test.context.BootstrapUtils - Instantiating CacheAwareContextLoaderDelegate from class [org.springframework.test.context.cache.DefaultCacheAwareContextLoaderDelegate]
14:29:46.288 [main] DEBUG org.springframework.test.context.BootstrapUtils - Instantiating BootstrapContext using constructor [public org.springframework.test.context.support.DefaultBootstrapContext(java.lang.Class,org.springframework.test.context.CacheAwareContextLoaderDelegate)]
14:29:46.323 [main] DEBUG org.springframework.test.context.BootstrapUtils - Instantiating TestContextBootstrapper for test class [isima.F2.TP3.zanglaarquilliere.ApplicationTests] from class [org.springframework.boot.test.context.SpringBootTestContextBootstrapper]
14:29:46.341 [main] INFO org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Neither @ContextConfiguration nor @ContextHierarchy found for test class [isima.F2.TP3.zanglaarquilliere.ApplicationTests], using SpringBootContextLoader
14:29:46.346 [main] DEBUG org.springframework.test.context.support.AbstractContextLoader - Did not detect default resource location for test class [isima.F2.TP3.zanglaarquilliere.ApplicationTests]: class path resource [isima/F2/TP3/zanglaarquilliere/ApplicationTests-context.xml] does not exist
14:29:46.346 [main] DEBUG org.springframework.test.context.support.AbstractContextLoader - Did not detect default resource location for test class [isima.F2.TP3.zanglaarquilliere.ApplicationTests]: class path resource [isima/F2/TP3/zanglaarquilliere/ApplicationTestsContext.groovy] does not exist
14:29:46.347 [main] INFO org.springframework.test.context.support.AbstractContextLoader - Could not detect default resource locations for test class [isima.F2.TP3.zanglaarquilliere.ApplicationTests]: no resource found for suffixes {-context.xml, Context.groovy}.
14:29:46.348 [main] INFO org.springframework.test.context.support.AnnotationConfigContextLoaderUtils - Could not detect default configuration classes for test class [isima.F2.TP3.zanglaarquilliere.ApplicationTests]: ApplicationTests does not declare any static, non-private, non-final, nested classes annotated with @Configuration.
14:29:46.387 [main] DEBUG org.springframework.test.context.support.ActiveProfilesUtils - Could not find an 'annotation declaring class' for annotation type [org.springframework.test.context.ActiveProfiles] and class [isima.F2.TP3.zanglaarquilliere.ApplicationTests]
14:29:46.451 [main] DEBUG org.springframework.context.annotation.ClassPathScanningCandidateComponentProvider - Identified candidate component class: file [/home/gagoi/Documents/zz/ZZ2/Forge/2019-f2-forge-tp3/target/classes/isima/F2/TP3/zanglaarquilliere/Application.class]
14:29:46.452 [main] INFO org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Found @SpringBootConfiguration isima.F2.TP3.zanglaarquilliere.Application for test class isima.F2.TP3.zanglaarquilliere.ApplicationTests
14:29:46.536 [main] DEBUG org.springframework.boot.test.context.SpringBootTestContextBootstrapper - @TestExecutionListeners is not present for class [isima.F2.TP3.zanglaarquilliere.ApplicationTests]: using defaults.
14:29:46.537 [main] INFO org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Loaded default TestExecutionListener class names from location [META-INF/spring.factories]: [org.springframework.boot.test.mock.mockito.MockitoTestExecutionListener, org.springframework.boot.test.mock.mockito.ResetMocksTestExecutionListener, org.springframework.boot.test.autoconfigure.restdocs.RestDocsTestExecutionListener, org.springframework.boot.test.autoconfigure.web.client.MockRestServiceServerResetTestExecutionListener, org.springframework.boot.test.autoconfigure.web.servlet.MockMvcPrintOnlyOnFailureTestExecutionListener, org.springframework.boot.test.autoconfigure.web.servlet.WebDriverTestExecutionListener, org.springframework.test.context.web.ServletTestExecutionListener, org.springframework.test.context.support.DirtiesContextBeforeModesTestExecutionListener, org.springframework.test.context.support.DependencyInjectionTestExecutionListener, org.springframework.test.context.support.DirtiesContextTestExecutionListener, org.springframework.test.context.transaction.TransactionalTestExecutionListener, org.springframework.test.context.jdbc.SqlScriptsTestExecutionListener, org.springframework.test.context.event.EventPublishingTestExecutionListener]
14:29:46.545 [main] DEBUG org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Skipping candidate TestExecutionListener [org.springframework.test.context.web.ServletTestExecutionListener] due to a missing dependency. Specify custom listener classes or make the default listener classes and their required dependencies available. Offending class: [javax/servlet/ServletContext]
14:29:46.546 [main] DEBUG org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Skipping candidate TestExecutionListener [org.springframework.test.context.transaction.TransactionalTestExecutionListener] due to a missing dependency. Specify custom listener classes or make the default listener classes and their required dependencies available. Offending class: [org/springframework/transaction/interceptor/TransactionAttributeSource]
14:29:46.547 [main] DEBUG org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Skipping candidate TestExecutionListener [org.springframework.test.context.jdbc.SqlScriptsTestExecutionListener] due to a missing dependency. Specify custom listener classes or make the default listener classes and their required dependencies available. Offending class: [org/springframework/transaction/interceptor/TransactionAttribute]
14:29:46.547 [main] INFO org.springframework.boot.test.context.SpringBootTestContextBootstrapper - Using TestExecutionListeners: [org.springframework.test.context.support.DirtiesContextBeforeModesTestExecutionListener@456d6c1e, org.springframework.boot.test.mock.mockito.MockitoTestExecutionListener@1e13529a, org.springframework.boot.test.autoconfigure.SpringBootDependencyInjectionTestExecutionListener@1ec9bd38, org.springframework.test.context.support.DirtiesContextTestExecutionListener@452e19ca, org.springframework.test.context.event.EventPublishingTestExecutionListener@6b0d80ed, org.springframework.boot.test.mock.mockito.ResetMocksTestExecutionListener@6f8e8894, org.springframework.boot.test.autoconfigure.restdocs.RestDocsTestExecutionListener@3cfdd820, org.springframework.boot.test.autoconfigure.web.client.MockRestServiceServerResetTestExecutionListener@928763c, org.springframework.boot.test.autoconfigure.web.servlet.MockMvcPrintOnlyOnFailureTestExecutionListener@e25951c, org.springframework.boot.test.autoconfigure.web.servlet.WebDriverTestExecutionListener@15f47664]
14:29:46.551 [main] DEBUG org.springframework.test.context.support.AbstractDirtiesContextTestExecutionListener - Before test class: context [DefaultTestContext@2415fc55 testClass = ApplicationTests, testInstance = [null], testMethod = [null], testException = [null], mergedContextConfiguration = [MergedContextConfiguration@14f232c4 testClass = ApplicationTests, locations = '{}', classes = '{class isima.F2.TP3.zanglaarquilliere.Application}', contextInitializerClasses = '[]', activeProfiles = '{}', propertySourceLocations = '{}', propertySourceProperties = '{org.springframework.boot.test.context.SpringBootTestContextBootstrapper=true}', contextCustomizers = set[org.springframework.boot.test.context.filter.ExcludeFilterContextCustomizer@5aebe890, org.springframework.boot.test.json.DuplicateJsonObjectContextCustomizerFactory$DuplicateJsonObjectContextCustomizer@75db5df9, org.springframework.boot.test.mock.mockito.MockitoContextCustomizer@0, org.springframework.boot.test.web.client.TestRestTemplateContextCustomizer@10aa41f2, org.springframework.boot.test.autoconfigure.properties.PropertyMappingContextCustomizer@0, org.springframework.boot.test.autoconfigure.web.servlet.WebDriverContextCustomizerFactory$Customizer@610f7aa], contextLoader = 'org.springframework.boot.test.context.SpringBootContextLoader', parent = [null]], attributes = map[[empty]]], class annotated with @DirtiesContext [false] with mode [null].
14:29:46.564 [main] DEBUG org.springframework.test.context.support.DependencyInjectionTestExecutionListener - Performing dependency injection for test context [[DefaultTestContext@2415fc55 testClass = ApplicationTests, testInstance = isima.F2.TP3.zanglaarquilliere.ApplicationTests@5f77d0f9, testMethod = [null], testException = [null], mergedContextConfiguration = [MergedContextConfiguration@14f232c4 testClass = ApplicationTests, locations = '{}', classes = '{class isima.F2.TP3.zanglaarquilliere.Application}', contextInitializerClasses = '[]', activeProfiles = '{}', propertySourceLocations = '{}', propertySourceProperties = '{org.springframework.boot.test.context.SpringBootTestContextBootstrapper=true}', contextCustomizers = set[org.springframework.boot.test.context.filter.ExcludeFilterContextCustomizer@5aebe890, org.springframework.boot.test.json.DuplicateJsonObjectContextCustomizerFactory$DuplicateJsonObjectContextCustomizer@75db5df9, org.springframework.boot.test.mock.mockito.MockitoContextCustomizer@0, org.springframework.boot.test.web.client.TestRestTemplateContextCustomizer@10aa41f2, org.springframework.boot.test.autoconfigure.properties.PropertyMappingContextCustomizer@0, org.springframework.boot.test.autoconfigure.web.servlet.WebDriverContextCustomizerFactory$Customizer@610f7aa], contextLoader = 'org.springframework.boot.test.context.SpringBootContextLoader', parent = [null]], attributes = map[[empty]]]].
14:29:46.585 [main] DEBUG org.springframework.test.context.support.TestPropertySourceUtils - Adding inlined properties to environment: {spring.jmx.enabled=false, org.springframework.boot.test.context.SpringBootTestContextBootstrapper=true, server.port=-1}

  .   ____          _            __ _ _
 /\\ / ___'_ __ _ _(_)_ __  __ _ \ \ \ \
( ( )\___ | '_ | '_| | '_ \/ _` | \ \ \ \
 \\/  ___)| |_)| | | | | || (_| |  ) ) ) )
  '  |____| .__|_| |_|_| |_\__, | / / / /
 =========|_|==============|___/=/_/_/_/
 :: Spring Boot ::        (v2.2.4.RELEASE)

[INFO] Tests run: 1, Failures: 0, Errors: 0, Skipped: 0, Time elapsed: 1.405 s - in isima.F2.TP3.zanglaarquilliere.ApplicationTests
[INFO] 
[INFO] Results:
[INFO] 
[INFO] Tests run: 1, Failures: 0, Errors: 0, Skipped: 0
[INFO] 
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  4.557 s
[INFO] Finished at: 2020-02-17T14:29:47+01:00
[INFO] ------------------------------------------------------------------------
```  

## 3 Intégration continue

Gitlab permet de faire de l'intégration continue sur votre code.
Nous allons mettre en place un job permettant de réaliser la compilation,les test et le packaging à chaque commit en utilisant [Gitlab CI](https://about.gitlab.com/features/gitlab-ci-cd/)

### 3.1 Mettre en place une intégration continue en utilisant gitlab-ci

Liens utiles:
* [Gitlab CI](https://docs.gitlab.com/ce/ci/yaml/README.html#gitlab-ci-yml)

Sur la page d'acceuil de votre projet, à coté du bouton pour ajouter une licence, il y a un acces rapide pour créer à partir d'un template un fichier `.gitlab-ci.yml`.
On utilisera un template maven pour initialiser le descriptif des actions à réaliser.

* Désormais dans la partie CI/CD de votre projet vous pouvez voir vos pipelines en cours d'éxécution ou passé et leurs status.
* Le yml par defaut devrait faire echouer votre pipeline.
* Quelles est l'erreur ?

Springboot 2.x nécessite Java 8 (au minimum) pour fonctionner.

* Le script template proposé par defaut est relativement complexe.
* Pour la suite nous utiliserons le template suivant :

```yaml
variables:
  # This will supress any download for dependencies and plugins or upload messages which would clutter the console log.
  # `showDateTime` will show the passed time in milliseconds. You need to specify `--batch-mode` to make this work.
  MAVEN_OPTS: "-Dmaven.repo.local=.m2/repository -Dorg.slf4j.simpleLogger.log.org.apache.maven.cli.transfer.Slf4jMavenTransferListener=WARN -Dorg.slf4j.simpleLogger.showDateTime=true -Djava.awt.headless=true"
  # As of Maven 3.3.0 instead of this you may define these options in `.mvn/maven.config` so the same config is used
  # when running from the command line.
  # `installAtEnd` and `deployAtEnd` are only effective with recent version of the corresponding plugins.
  MAVEN_CLI_OPTS: "--batch-mode --errors --fail-at-end --show-version -DinstallAtEnd=true -DdeployAtEnd=true"

# Cache downloaded dependencies and plugins between builds.
# To keep cache across branches add 'key: "$CI_JOB_REF_NAME"'
cache:
  paths:
    - .m2/repository

#Definition des différentes étapes présent dans le pipeline
stages:
  - build
  - test

#Définition du job de compilation
compilation:
  image: maven:3.3.9-jdk-8
  stage: build
  script:
    - echo "A Completer";exit 1


validation:
  image: maven:3.3.9-jdk-8
  stage: test
  script:
      - echo "A Completer";exit 1
```

* Remplacez le `.gitlab-ci.yml` par celui-ci et completez le avec les commandes maven précédement utilisées pour réaliser la phase de build et de test

* Completez le `.gitlab-ci.yml` pour inclure un nouveau stage de packaging qui vas construire le jar de votre application

`Quels sont les lignes que vous avez rajouté dans votre déclaration de pipeline ?`   

#### 3.1.1 Badge

**Gilab** permet d'afficher dans votre readme le status de votre pipeline dynamiquement pour celà :
* Rendez vous dans la partie [Settings > CI/CD > General pipelines settings](https://docs.gitlab.com/ee/user/project/pipelines/settings.html) de votre projet. A l'aide de la documentation sur les [badges](https://docs.gitlab.com/ee/user/project/pipelines/settings.html#badges)
rajoutez un bdage indiquant le status de votre pipeline de build dans votre readme.

[![pipeline status](http://gitlab.isima.fr/maarquilli/2019-f2-forge-tp3/badges/master/pipeline.svg)](http://gitlab.isima.fr/maarquilli/2019-f2-forge-tp3/commits/master)

### 3.2 Couverture de code

Nous allons ajouter un outil permettant de réaliser des statistiques sur la qualité des tests. Il sagit ici de [jacoco](http://www.eclemma.org/jacoco/) une librairie permettant de réaliser des statistiques sur le taux de couverture de code par les tests unitaires.

* Ce plugin lors de la compilation vas modifier votre code pour injecter du code permettant de savoir quelles lignes sont exécutées ou non.
    * Pour ce faire il faut rajouter dans votre **pom.xml**, dans la partie *build/pulgins*, la déclaration suivante :

```xml
<plugin>
    <groupId>org.jacoco</groupId>
    <artifactId>jacoco-maven-plugin</artifactId>
    <version>0.8.0</version>
    <executions>
        <execution>
            <id>default-prepare-agent</id>
            <goals>
                <goal>prepare-agent</goal>
            </goals>
        </execution>
    </executions>
</plugin>
```

* Nous allons rajouter au readme du projet un badge indiquant le % de code couvert.
    * Sur gitlab, dans les settings de la partie CI/CD dans General pipeline settings, vous trouverez une zone de saisie pour **Test coverage parsing**.
En effet il est nécessaire d'indiquer à **Gitlab CI** où trouver l'information sur le pourcentage de code couvert : `A regular expression that will be used to find the test coverage output in the job trace.`
    * Cette information se trouve dans le rapport généré par jacoco. Par defaut le rapport n'est pas généré. Il faut donc modifier le paramètrage du plugin pour lui demander de générer le rapport.
Dans le code suivant on indique au plugin qu'il doit exécuter sa tache **report** lorsque de la phase **test** de maven.   

```xml
<execution>
    <id>default-report</id>
    <phase>test</phase>
    <goals>
        <goal>report</goal>
    </goals>
</execution>
```

* Le rapport est généré dans le repertoire target/site/jacoco sous la forme d'un fichier html.
    * Il faut dans la partie settings de votre CI indiquer l'expression réguliére permettant de retrouver le % de code couvert. Utilisez `Total.*?([0-9]{1,3})%`.
    * Ajoutez à votre `.gitlab-ci.yml` la commande permettant de faire apparaitre le contenu de ce fichier dans la log de votre job.

`Comment affichez vous l'information dans la log du job ?`

En rajoutant le badge correspondant.

* Rajoutez en début de votre readme le badge indiquant le pourcentage de couverture de code.

### 3.3 Analyse de code avec Sonar
Nous allons mettre en place à chaque éxécution de notre pipeline une analyse sonar.

Le serveur sonar à utiliser se trouve à l'adresse suivante : [ISIMA Sonar](http://40.89.147.107/)

Le compte permettant d'acceder à l'application est `isima`, le mot de passe `isima2019`.

* à la suite de la phase de test ajoutez dans votre job une analyse Sonar.
* Pour exécuter une analyse sonar il suffit de lancer la commande :

```
mvn sonar:sonar -Dsonar.host.url=http://40.89.147.107 -Dsonar.login=TOKEN
```

* Le token pour le user `isima` est `99ae2bca252a19b71d0886ed8338c768d5c2da95`.
* Une fois la première analyse lancée, rendez vous sur l'application pour constater quels sont les anomalies détectées et les indicateurs de qualimétrie de votre code.
* Corrigez votre code en conséquence pour obtenir la meilleur note possible.
* Il est possible de spécifier directement dans le pom.xml l'adresse du serveur cible
    * pour ce faire on ajoutera dans la balise properties une entrée tel que :

    ```xml
    <sonar.host.url>http://40.89.147.107</sonar.host.url>
    ```
    * on peux alors appeler directement `mvn sonar:sonar -Dsonar.login=TOKEN` l'URL du serveur est prise dans les properties de votre projet maven

* Pour le login il est possible de faire de même, mais en terme de sécurité ce n'est pas une bonne idée d'indiquer le token d'acces dans vos sources
    * Gitlab-ci permet d'injecter de manière caché certaines propriétés [secret variables](https://gitlab.isima.fr/help/ci/variables/README#secret-variables)
    * Définissez une variable secrete contenant le login et utilisez la dans votre .gitlab-ci.yml   
