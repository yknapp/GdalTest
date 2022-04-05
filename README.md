# GDAL test program


## General
This repo is for investigating the performance drop of GDAL from `3.4.1` to `3.4.2`.  
To replicate the results (see `Performance logs` below), two vcpkg exports containing the different GDAL versions and the OSM database are provided here: [https://drive.google.com/drive/folders/11TYCflrL2rzybpejnd9Gs7V3zjrGdvon?usp=sharing](https://drive.google.com/drive/folders/11TYCflrL2rzybpejnd9Gs7V3zjrGdvon?usp=sharing).

## Build

`cmake.exe -S {PATH_TO_PROJECT}/gdalTest -B {BUILD_FOLDER} -DCMAKE_TOOLCHAIN_FILE={PATH_TO_VCPKG}/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows`

Example: `C:\Qt\Tools\CMake_64\bin\cmake.exe -S C:/workspace/gdalTest -B C:/workspace/build -DCMAKE_TOOLCHAIN_FILE=C:\workspace\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows`

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
