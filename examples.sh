#!/bin/bash

cd src
make simplification

# Les fichiers
cd ../images_tests
fichiers=$(echo *)
cd ..

# Les différents paramètres testés
courbes="1 2 3"
dist="0 0.5 1 2 4 8 16"

# On effectue chaque simplification
for f in $fichiers
    do
    for c in $courbes
        do
        for d in $dist
            do
            ./src/simplification "images_tests/$f" $c $d "images_simp/$f-$c-$d.eps"
        done
        echo "***********************************"
    done
    echo ===============================================================
done