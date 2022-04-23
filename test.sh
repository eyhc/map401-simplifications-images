#!/bin/bash

time ./simplification images/zebres-1000x0750.pbm 1 0
echo ==================================================
time ./simplification images/zebres-2000x1500.pbm 1 0
echo ==================================================
time ./simplification images/zebres-3000x2250.pbm 1 0
echo ==================================================
time ./simplification images/zebres-4000x3000.pbm 1 0

echo
echo ==================================================
echo

time ./simplification images/courbe_hilbert_7.pbm 1 0
echo ==================================================
time ./simplification images/courbe_hilbert_8.pbm 1 0
echo ==================================================
time ./simplification images/courbe_hilbert_9.pbm 1 0
echo ==================================================
time ./simplification images/courbe_hilbert_10.pbm 1 0


echo 
echo
echo "**************************************************"
echo
echo


fichiers="Asterix3.pbm lettre-L-cursive.pbm Picasso-ColombesDeLaPaix.pbm"
courbes="1 2 3"
dist="0 0.5 1. 2. 4. 8. 16."

for f in $fichiers
    do
    for c in $courbes
        do
        for d in $dist
        do
            ./simplification images/$f $c $d
        done
        echo "***********************************"
    done
    echo ===============================================================
done
