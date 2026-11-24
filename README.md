Petit projet de jeu 2D en vue du dessus
Utilisation de Tiled pour les 

Un chevalier qui défend son village contre des attaques de monstres.
Les monstres arrivent par vague que le joueur peut repousser via dif armes.



{
	épee	: semie rapide avec degat en arc de cercle
	lance	: tape tout droit mais loins vitesse semie rapide
	marteau	: gros degat de zone en cercle vitesse lent
}

avec arme secondaire arc : tire de loin semie rapide

Goblin (monstre de base)
araignée
Gros monstre (orc)

marchant pour changer les armes ou les améliorer

Organisation du projet :

MonJeu/
│
├── assets/
│   ├── textures/
│   │   ├── tileset.png	// en cour
│   │   └── player.png	// fait
│   │
│   ├── maps/
│   │   └── niveau1.tmj	// en cour
│   │
│   └── fonts/
│
├── include/
│   ├── Game.hpp
│   ├── Map.hpp
│   ├── Player.hpp
│   └── Camera.hpp
│
├── src/
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Map.cpp
│   ├── Player.cpp
│   └── Camera.cpp
│
├── CMakeLists.txt
└── README.md#


Reste a faire : 
enemies
armes
annimation
marchant
menus
Maps (en cour)
amélioration du déplacement
Spawn des ennemie
Levels
cinematique