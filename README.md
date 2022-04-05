# GDAL test program


## General
This repo is for investigating the performance drop of GDAL from `3.4.1` to `3.4.2`.
To replicate the following results, two vcpkg exports are provided [here](https://drive.google.com/drive/folders/11TYCflrL2rzybpejnd9Gs7V3zjrGdvon?usp=sharing) containing the two different GDAL versions and also the OpenStreetMap database.

## Performance logs

### GDAL 3.4.1
```
Opening spatial database "germany-latest.spatialite_osm_map"
"Search streets with name 'Markt' in city with ID '2783849'"
Time needed:  11 ms
Found street: ID:  27831438 ; name: Marktplatz
Time needed:  0 ms
Found street: ID:  27831444 ; name: Marktplatz
Time needed:  4 ms
Found street: ID:  85428337 ; name: Marktplatz
Time needed:  0 ms
Found street: ID:  85428341 ; name: Marktstraße
Time needed:  1 ms
Found street: ID:  124092250 ; name: Marktplatz
Time needed:  3 ms
Found street: ID:  266826145 ; name: Marktstraße
Time needed:  1 ms
Found street: ID:  332573522 ; name: Marktplatz
Closing spatial database
searchStreet: Time needed: 35ms
```

### GDAL 3.4.2
```
Opening spatial database "germany-latest.spatialite_osm_map"
"Search streets with name 'Markt' in city with ID '2783849'"
Time needed:  268 ms
Found street: ID:  27831438 ; name: Marktplatz
Time needed:  0 ms
Found street: ID:  27831444 ; name: Marktplatz
Time needed:  503 ms
Found street: ID:  85428337 ; name: Marktplatz
Time needed:  0 ms
Found street: ID:  85428341 ; name: Marktstraße
Time needed:  166 ms
Found street: ID:  124092250 ; name: Marktplatz
Time needed:  490 ms
Found street: ID:  266826145 ; name: Marktstraße
Time needed:  152 ms
Found street: ID:  332573522 ; name: Marktplatz
Closing spatial database
searchStreet: Time needed: 2383ms
```
