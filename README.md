# Jeu de destruction de ballons

![Language](https://img.shields.io/badge/Language-C++-blue.svg)
![Librairies](https://img.shields.io/badge/Librairies-OpenCV-green.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-red.svg)

Ce jeu est un jeu de destruction de ballons. Le but est de détruire les ballons qui apparaisent à l'écran en déplaçant le curseur de la souris sur eux à l'aide d'un objet de couleur verte. Le jeu se termine lorsqu'un ballon touche le plafond.

## Installation

###### Il faut une webcam.

Dans les paramètres du projet :

C/C++ > Général > Autres répertoires include : Ajouter le chemin vers le dossier include de la bibliothèque OpenCV

Éditeur de liens > Général > Répertoires de bibliothèques supplémentaires : Ajouter le chemin vers le dossier lib de la bibliothèque OpenCV

Éditeur de liens > Entrée > Dépendances supplémentaires : Ajouter les librairies suivantes :

opencv_world460d.lib opencv_world460.lib

## Démonstration

![Démonstration](demo.gif)