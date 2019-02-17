#!/bin/bash

docker build -t usim-builder .
docker run -it -u ${UID} -v `pwd`:/usim usim-builder /bin/bash -c "make $@"
