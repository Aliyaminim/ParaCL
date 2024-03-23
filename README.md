# ParaCL interpreter

## About
ParaCL is a custom C-like language. 
This project provides an interpreter for the ParaCL language.

## Code snippet in ParaCL
```bash
n = ?;
fact = 1;
iter = 1;

while (iter <= n) {
    fact = fact * iter;
    iter = iter + 1;
}

print fact;
```
To run it after(!!) building the program:
```bash
./ParaCL ./test/factorial.in
```

## Supported language features
- arithmetic, logical, and comparison operations
- while loop
- if statement
- print statement
- ? scan statement
- chainable assignment

## How to build
```bash
git clone https://github.com/Aliyaminim/ParaCL.git
cd ParaCL
cmake -S ./ -B build/
cd build/
cmake --build .
```

## How to run the program
```bash
./ParaCL [file]
```

## How to test the program
```bash
make -s test
```
