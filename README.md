# MonJeu

Petit jeu 2D en C++ avec SFML 3, en vue du dessus pour l'instant (vue 3/4 envisagée). Les cartes sont créées avec [Tiled](https://www.mapeditor.org/).

Un chevalier défend son village contre des vagues de monstres. Entre deux vagues, un marchand permet d'acheter et d'améliorer des armes.

---

## Concept

- **Boucle de jeu** : vague de monstres → phase calme → marchand → vague suivante
- **Enjeu** : protéger le village (barre de vie du village) tout en gardant le chevalier en vie
- **Argent** : les monstres laissent de l'or, à ramasser et à dépenser chez le marchand
- **Esquive** : roulade courte avec brève invincibilité et cooldown

---

## Commandes

| Action | Clavier / souris | Manette |
|---|---|---|
| Se déplacer | Z Q S D (position physique) | stick gauche |
| Viser / s'orienter | direction de marche | stick droit |
| Attaque (arme principale) | Espace / clic gauche | bouton 0 |
| Tirer à l'arc | clic droit | gâchette droite |
| Changer d'arme | à définir | à définir |
| Esquive | à définir | à définir |
| Pause / menu | Échap | Start |
| Mode éditeur (debug) | F1 | |
| Recharger les stats (debug) | F5 | |

> Les axes du stick droit dépendent de la manette (`Z`/`R` ou `U`/`V`). Ils sont regroupés en constantes dans `Player.hpp`.

---

## Armes

| Arme | Zone | Vitesse | Dégâts | Particularité |
|---|---|---|---|---|
| **Épée** | arc de 160°, portée moyenne | moyenne | modérés | polyvalente, arc blanc visible à l'écran |
| **Lance** | arc très étroit, grande portée | la plus rapide | modérés (à équilibrer) | touche plusieurs ennemis alignés |
| **Marteau** | cercle placé **devant** le joueur | lente | élevés | grande zone, repousse les ennemis |
| **Arc** | projectile en ligne droite | cooldown moyen | modérés | toujours équipé, bouton dédié (peut devenir un pistolet à poudre noire) |

Les armes partagent la même structure (`WeaponStats` : dégâts, portée, angle, cooldown). Un type de zone (`Arc` ou `Cercle`) et un décalage permettent de couvrir le marteau.

---

## Ennemis et comportements

Chaque ennemi suit une machine à états : **Poursuite → Préparation (signal visuel) → Attaque → Récupération**. La phase de préparation rend chaque attaque lisible, et donc esquivable ou contrable.

| Ennemi | Comportement |
|---|---|
| **Goblin** (de base) | Fonce vers le joueur. À portée, il s'arrête brièvement, lève son arme, puis frappe. Faible en vie, nombreux. |
| **Araignée** | Rapide. S'arrête un peu avant le joueur, puis lui **saute dessus** en ligne droite. Le saut peut être **contré** d'un coup bien placé ou **esquivé** par une roulade. Vulnérable pendant sa récupération. |
| **Orc** (gros monstre) | Lent, beaucoup de vie, peu repoussé. Frappe en zone au sol, avec une zone d'avertissement bien visible. Sert de mini-boss (par exemple toutes les 5 vagues). |

Idées pour plus tard :
- goblin archer (garde ses distances) ;
- ennemis qui visent le village plutôt que le joueur, et n'attaquent le joueur que s'il est proche ;
- ennemis qui se déplacent en groupe ou se contournent entre eux.

---

## Ressenti des coups

- l'ennemi clignote en blanc quand il est touché
- repoussement à l'impact (fort avec le marteau)
- léger tremblement de l'écran pour les gros coups
- sons d'impact, de mort et de ramassage d'or

---

## Vagues et marchand

- **Vagues** : goblins seuls au début, puis mélange avec des araignées, un orc régulièrement
- **Points d'apparition** : placés dans Tiled avec une couche d'objets
- **Marchand** : apparaît entre les vagues, vend des armes et des améliorations contre de l'or

---

## Menus et états du jeu

Le jeu est organisé en **états** (un `enum class State` dans `Game`). Chaque état a ses propres `événements / update / draw`, et un état de menu met le jeu en pause.

| État | Contenu |
|---|---|
| **Menu principal** | Jouer, Options, Quitter |
| **Jeu** | partie en cours (déplacement, combat, vagues) |
| **Pause** | Reprendre, Options, Retour au menu (Échap pendant la partie) |
| **Boutique** | marchand entre deux vagues : achat et amélioration des armes |
| **Options** | volume, plein écran, configuration des touches et de la manette |
| **Game over / Victoire** | résumé (vague atteinte, or gagné), Rejouer, Menu |
| **Éditeur** | voir la section suivante (développement uniquement) |

Principes :
- navigation **au clavier, à la souris et à la manette** (haut/bas, valider, retour)
- une petite classe `Menu` réutilisable (liste de boutons avec sélection), pour ne pas réécrire la logique à chaque écran
- l'interface (vie, argent, numéro de vague, menus) est dessinée avec la **vue par défaut** (`window.getDefaultView()`), pour rester collée à l'écran au lieu de suivre la caméra
- une police dans `assets/fonts/`
- Échap ouvre la pause au lieu de fermer la fenêtre

---

## Mode éditeur

Un mode de développement pour modifier des éléments **pendant que le jeu tourne**, et régler l'équilibrage sans recompiler. Activé avec **F1**, uniquement en build debug (`#ifndef NDEBUG`).

En mode éditeur, le joueur et les ennemis ne sont pas mis à jour (le jeu est en pause) : on lit la souris et le clavier pour éditer.

### Fonctions prévues

1. **Affichage de debug** : hitboxes, zones d'attaque, grille de tuiles, tuiles solides en rouge semi-transparent, FPS
2. **Réglage des valeurs en direct** : vitesse du joueur, dégâts et cooldown des armes, vie et vitesse des ennemis
3. **Édition de la collision** : clic gauche pour poser une case bloquante, clic droit pour l'effacer
4. **Placement d'ennemis** à la souris pour tester un comportement
5. **Caméra libre**, détachée du joueur

### Techniques

- **Souris dans le monde** : `window.mapPixelToCoords(sf::Mouse::getPosition(window), vue)`, puis `floor(position / TILE_SIZE)` pour trouver la case (nécessite un accesseur sur la vue dans `Camera`, et `Map::setSolid(x, y, bool)`)
- **Stats dans des fichiers JSON** (`assets/data/weapons.json`, `enemies.json`) lus avec nlohmann/json, avec **rechargement à chaud** sur **F5** : on modifie un chiffre dans un éditeur de texte, on appuie sur F5, c'est pris en compte
- **Dear ImGui** (via ImGui-SFML) envisagé en dernier pour avoir de vrais panneaux (curseurs, champs de saisie). À vérifier : compatibilité de la version choisie avec SFML 3

### Précautions

- **Tiled reste la source de vérité de la carte.** Ne pas sauvegarder depuis le jeu dans le `.tmj` (cela écraserait le travail fait dans Tiled) : écrire les modifications d'éditeur dans un fichier séparé, ou limiter l'éditeur à la collision et aux ennemis.
- Garder l'éditeur hors de la version finale.

### Ordre de réalisation

1. `enum Mode { Jeu, Editeur }`, F1 pour basculer, jeu en pause en mode éditeur
2. affichage de debug (hitboxes, tuiles solides)
3. souris dans le monde, pose et effacement de cases de collision
4. stats en JSON avec rechargement à chaud (F5)
5. placement d'ennemis à la souris
6. Dear ImGui (optionnel)

---

## Organisation du projet

```
MonJeu/
│
├── assets/
│   ├── textures/
│   │   ├── MC32pxTextures1.png   // tileset (tuiles 32x32, espacement 2 px, 58 colonnes)
│   │   ├── chevalier.png         // joueur
│   │   └── gobelin.png           // goblin
│   │
│   ├── maps/
│   │   └── test.tmj              // carte Tiled (en cours, niveau1.tmj à venir)
│   │
│   ├── data/                     // weapons.json, enemies.json (prévu)
│   │
│   └── fonts/                    // police des menus (prévu)
│
├── include/
│   ├── Game.hpp
│   ├── Map.hpp
│   ├── Player.hpp
│   ├── Camera.hpp
│   └── Ennemies.hpp
│
├── src/
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Map.cpp
│   ├── Player.cpp
│   ├── Camera.cpp
│   └── Ennemies.cpp
│
├── CMakeLists.txt
├── run.ps1
└── README.md
```

### Rôle des classes

| Classe | Responsabilité |
|---|---|
| `Game` | fenêtre, boucle principale (`événements → update → draw`), liste des ennemis, textures partagées |
| `Player` | déplacement (clavier + manette), orientation, collisions, attaque |
| `Camera` | `sf::View` qui suit le joueur |
| `Map` | chargement du `.tmj`, dessin des tuiles, calque de collision |
| `Ennemies` | poursuite du joueur, vie, dégâts (comportements à étendre) |

### Format des cartes (Tiled)

- carte orthogonale, tuiles de 32×32, couches enregistrées en **CSV**
- une couche de tuiles pour le décor
- une couche de tuiles nommée **`collision`** : une tuile posée = case bloquante (jamais dessinée)
- les valeurs de la couche de décor sont des GID bruts (`0` = case vide)

---

## Compilation

### Prérequis

- CMake
- un compilateur C++17 : MinGW (MSYS2 UCRT64) avec Ninja, ou Visual Studio Build Tools
- Git (SFML et nlohmann/json sont téléchargés automatiquement par CMake)
- connexion internet au premier build

### Commandes

```powershell
cmake -B build -G Ninja
cmake --build build
.\build\MonJeu.exe
```

Ou lancer `run.ps1` (configure, compile et lance le jeu). Dans VS Code, **Ctrl+Shift+B** exécute la tâche « Build and Run ».

### Problèmes courants

- **Projet déplacé** : supprimer le dossier `build/` (le cache CMake mémorise l'ancien chemin).
- **Changement de générateur** : supprimer `build/` également.
- **Erreur `Compatibility with CMake < 3.5`** (CMake 4.x) : le `CMakeLists.txt` contient `set(CMAKE_POLICY_VERSION_MINIMUM 3.5)`.
- Les chemins des assets sont relatifs au dossier de lancement : lancer le jeu depuis la racine du projet.
- Ne jamais versionner `build/` (l'ajouter au `.gitignore`).

---

## État d'avancement

### Fait
- [x] fenêtre, boucle de jeu, `deltaTime`
- [x] classes `Game`, `Player`, `Camera`, `Map`
- [x] chargement d'une carte Tiled avec tileset à textures
- [x] collisions joueur/décor (couche `collision`, déplacement axe par axe)
- [x] sprite du joueur, orientation, clavier et manette (stick droit pour viser)
- [x] premier ennemi qui poursuit le joueur

### En cours
- [ ] épée : cooldown, zone d'attaque en arc, dégâts, mort des ennemis
- [ ] carte (`niveau1.tmj`) et tileset

### À faire (dans cet ordre)
1. vie du joueur et attaque du goblin (avec phase de préparation)
2. ressenti des coups (clignotement, repoussement)
3. lance et marteau, changement d'arme
4. arc et projectiles
5. araignée et orc (machine à états)
6. vagues et points d'apparition
7. argent, marchand, améliorations
8. esquive du joueur
9. interface en jeu (vie, argent, numéro de vague)
10. états du jeu et menus (principal, pause, options, game over, boutique)
11. mode éditeur : debug, stats en JSON avec rechargement à chaud, édition de la collision
12. animations et sprites directionnels (vue 3/4, tri par profondeur, hitbox aux pieds)
13. sons, cinématiques
14. pathfinding (A*) pour éviter que les ennemis se coincent derrière les murs

> Les étapes 2 et 11 (stats en JSON, affichage de debug) sont plus utiles une fois l'épée terminée : il y a alors des zones d'attaque et des valeurs à régler. L'étape 11 peut être avancée à tout moment pour la partie « debug ».

---

## Notes de conception

- **Vue 3/4** envisagée : personnages vus de face ou de profil, sprites par direction et animations. `m_facing` reste le cœur du système (il choisit le sprite et oriente les armes). La rotation du sprite actuelle est provisoire.
- Le jeu doit d'abord être amusant avec des formes simples, les animations viennent ensuite.
- Les textures sont chargées **une seule fois** et partagées par référence, car un `sf::Sprite` garde un pointeur vers sa texture.
