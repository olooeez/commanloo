FROM debian:latest
MAINTAINER Luiz Felipe <luizfelipecastrovb@gmail.com>

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install -y make gcc

WORKDIR /app

RUN mkdir include src

COPY ./include include/
COPY ./src src/
COPY ./Makefile /app/

RUN make

ENTRYPOINT ["./bin/loop_command"]
