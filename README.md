[![test](https://github.com/olooeez/commanloo/actions/workflows/test.yml/badge.svg)](https://github.com/olooeez/commanloo/actions/workflows/test.yml)

# commanloo

This is a project I did for Algorithm and Data Structure at the Federal University of Viçosa. In it, we have a simple game in which the objective is to reach the end in a certain number of tries, using data structures to store the movements.

## Demo

![Demo of commanloo](https://raw.githubusercontent.com/olooeez/commanloo/main/img/demo.png)

## Usage

Below is how you can use commanloo. Feel free to fork or copy them, but be aware of the limitations that this repository license implies.

You can use the following options to use commanloo:

1. [Run in your machine](#run-in-your-machine)
2. [Run in a Docker container](#run-in-a-docker-container)

### Run in your machine

#### Clone the repo

To run commanloo, you must clone this repository with the following command:

```
git clone https://github.com/olooeez/commanloo.git
```

#### Enter the cloned repository

After cloning, you must enter the local repository using the following command:

```
cd commanloo
```

#### Use GNU Make to compile the project

Install [GNU Make](https://gnu.org/software/make) on your system and run it with the command bellow:

```
make
```

#### Run the project

Finally use the command below to run the project:

```
./bin/commanloo
```

### Run in a Docker container

#### Clone the repo

To run the program in a docker container, clone the repository to your machine first:

```
git clone https://github.com/olooeez/commanloo.git
```

#### Enter the cloned repository

After cloning, you must enter the local repository using the following command:

```
cd commanloo
```

#### Build the docker image

Then, use the command below to build the Docker image:

```
docker build -t olooeez/commanloo:latest .
```

#### Run the image in a container

Then, to run the image in a container, use the following command:

```
docker run -it --rm olooeez/commanloo:latest
```

## Contributing

If you would like to contribute to this project, please feel free to open a pull request. All contributions are welcome!

## License

This project is licensed under the [MIT](https://github.com/olooeez/commanloo/blob/main/LICENSE) License. See the LICENSE file for details.
