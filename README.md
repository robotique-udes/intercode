# Points intéressants
## Niveaux de difficulté
La librairie aura deux ou trois niveaux de difficulté
1. FACILE -> les fonctions haut-niveau existent et sont très faciles à utiliser.
Elles devront être bien documentées, car c'est ce qu'utiliseront la plupart des élèves qui n'ont jamais programmé.
    -   Suivre la ligne jusqu'à une jonction
    -   Tourner à gauche/droite
    -   Obtenir valeur de succès (booléenne) du capteur X, peu importe le capteur
    -   (Voir fonction `implementation_attendue` dans `main.cpp`)
2. MOYEN (à voir) -> les fonctions bas-niveau existent et sont disponibles, elles font une abstraction du hardware, sans plus.
Ces fonctions seront utilisés par notre implémentation haut-niveau, mais seront `private` en mode facile.
3. DIFFICILE -> les élèves qui veulent un défi peuvent utiliser directement les API hardware.
Ils pourront s'inspirer de notre code du niveau MOYEN, donc celui-ci devra être très bien documenté pour servir de référence dans ce cas.
On pourra leur faciliter un peu la vie en mettant les fonctions et enums les plus utils dans un namespace pour faciliter l'exploration à l'aide de l'autocomplétion, à voir.

### Choix du niveau de difficulté
Par défaut, la difficulté sera FACILE
Les élèves pourront choisir un niveau de difficulté plus élevé avec un `#define DIFFICULTE_MOYEN` ou `#define DIFFICULTE_DIFFICILE`, par exemple.
## Le bouton
1. Appuyer sur le bouton permet de partir le code.
2. Appuyer à nouveau sur le bouton permet de stopper le code
3. Appuyer à nouveau sur le bouton recommence le code au début

## La DEL
La DEL donnera la rétroaction lors du parcours: elle s'allumera pour signifier un succès.
Elle pourra aussi être utilisée avec des patrons de clignotement pour communiquer à l'utilisateur en cas d'erreur, par exemple.

## L'API
On met toutes les fonctions utiles dans une classe (inspiré de la librairie pour le projet de S1).
Cela va permettre aux élèves d'utiliser l'autocomplétion dans VSCode pour explorer plus facilement les possibilités.
En fonction du niveau de difficulté choisi, on cache certaines fonctions de l'API en les mettant `private` ou `protected` dans la classe.

## IDE utilisé
Nous suggérons d'utiliser VSCode avec PlatformIO.
Nous fournirons un projet de départ avec le *boilerplate* déjà fait.
VSCode et PlatformIO sont plus faciles à utiliser que Arduino IDE grâce à la qualité de l'autocomplétion.
Il est aussi plus facile de les configurer.
Par exemple, on peut fournir un fichier `platformio.ini` avec les paramètres de compilation pour le robot, et les dépendances à installer.
Il est aussi possible d'inclure un dossier `.vscode` avec des paramètres suggérés pour VSCode, les extensions à installer, etc.

# En mode facile
On fait le setup et loop nous mêmes, cachés; ils ont juste à faire une fonction `faireParcours`.
On gère l'état du bouton et tout ça caché dans un .cpp DE LA LIBRAIRIE.
On leur fournir un exemple/template avec une fonction `faireParcours` vide et les `#include` de la librairie, par exemple.
## Au démarrage
1. On bloque en attendant le bouton.
2. Le bouton est appuyé: on lance le parcours
3. À la fin du parcours, le robot s'arrête. Appuyer à nouveau sur le bouton le relance (ou ne fait rien, et on doit appuyer sur le RESET du Arduino pour le relancer.)

# En mode moyen
À partir de ce niveau, les élèves implémentent eux-mêmes les fonctions `setup` et `loop`.
On pourra fournir un exemple/template avec ces fonctions et les `#include`.
On pourra choisir d'offrir une fonction toute faite pour la gestion du bouton à ce niveau, ou pas.
Si on l'offre, on devrait aussi offrir les fonctions bas-niveau de la gestion du bouton, pour leur permettre de l'implémenter eux-mêmes en partie s'ils le souhaitent.

# En mode difficile
Les élèves peuvent s'inspirer de notre implémentation pour tout faire à partir des librairies de base Arduino et des capteurs/moteurs.
On pourra fournir un exemple/template.
