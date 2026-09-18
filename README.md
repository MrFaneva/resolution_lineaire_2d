# Optimiseur Linéaire 2D (Programmation Linéaire)
![Langage C](https://img.shields.io/badge/Language-C99-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Code Quality](https://img.shields.io/badge/cppcheck-passing-orange.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

Programme en langage C permettant de résoudre des problèmes d'optimisation linéaire à deux variables ($x$ et $y$) sous contraintes (maximisation ou minimisation d'une fonction objectif de type $z = c_1x + c_2y$).

## Fonctionnalités du programme (`Méthode_graphique.c`)
- Saisie interactive dynamique du nombre de contraintes et de la fonction objectif (`MAX` ou `MIN`).
- Gestion des signes de contraintes ($\le$ ou $\ge$).
- Calcul automatique des intersections géométriques entre les droites de contraintes et les axes de non-négativité ($x \ge 0, y \ge 0$).
- Intégration d'une tolérance numérique (`EPS`, `DET_EPS`) pour gérer les approximations de virgule flottante.
- Détection des domaines vides, des solutions uniques ou multiples, et des solutions non bornées.

## Prérequis

Assurez-vous d'avoir un compilateur C (`gcc`) et l'outil d'analyse statique `cppcheck` installés sur ta machine Linux :
    ```bash
        sudo apt update
        sudo apt install build-essential cppcheck
## Compilation et Utilisation

1. Compiler le projet :
    ```bash
        make
2. Vérifier la qualité du code (Analyse statique) :
    ```bash
        make check
3. Exécuter le programme:
    ```bash
        ./optimiseur_lineaire
4. Nettoyer les fichiers binaires:
    ```bash
        make clean
    
👤 Auteur:
 - Henintsoa Faneva — Étudiant en double cursus Physique et Application à l'Université d'Antananarivo  & Informatique (IGGLIA / ISPM ).
        
    

