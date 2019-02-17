FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install -y git make gcc gcc-arm-none-eabi
    
RUN apt-get install -y g++ python-pip

RUN pip install shyaml

WORKDIR /usim/src
CMD make
