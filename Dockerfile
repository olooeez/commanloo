FROM debian:stable-slim

MAINTAINER Luiz Felipe <luizfelipecastrovb@gmail.com>

RUN apt-get -y update
RUN apt-get -y install make gcc libcriterion-dev gcovr

WORKDIR /app

RUN mkdir include src

COPY . /app

RUN make

ENTRYPOINT ["./bin/commanloo"]
