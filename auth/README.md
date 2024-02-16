# Simple Authentication System in C++

## The Project
This project is meant for helping me to learn C++. It is a simple authentication system that uses [Crow](https://crowcpp.org/master/getting_started/setup/linux/) under the hood for the HTTP layer.

The project offers **4 simple routes**, which are:
```bash
[GET] /health
```
```bash
[POST] /signup
```
```bash
[POST] /signin
```
```bash
[GET] /users
```

## How to run
To run the project, clone it to your system and then run the following command in the root directory of the project:
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . && cmake --build . && ./main
```



