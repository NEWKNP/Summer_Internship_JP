#/bin/bash
mpirun  -output-filename log \
    -np 3 \
    -host as-wn032 \
    ./bin/PTSdemo  $1