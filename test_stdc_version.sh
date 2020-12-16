#!/usr/bin/env bash

for std in c89 c90 iso9899:1990 iso9899:199409 c99 c9x iso9899:1999 c11 c1x iso9899:2011 c17 c18 iso9899:2017 iso9899:2018 c2x gnu89 gnu90 gnu99 gnu9x gnu11 gnu1x gnu17 gnu18 gnu2x
do
    echo $std
    gcc -std=$std determine_stdc_version.c -o stdc_ver
    ./stdc_ver
    echo
done

echo default
gcc determine_stdc_version.c -o stdc_default_ver
./stdc_default_ver