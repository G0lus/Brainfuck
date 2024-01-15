# Brainfuck interpreter

Simple project of creating the [Brainfuck](https://esolangs.org/wiki/Brainfuck) interpreter. This project was made only to challenge myself. Create nice-looking code that works and is also testable (yes, I created tests for it :D).

# Compiling

Project uses cmake. To compile create new folder, eg. build
`mkdir build`

go to that folder `cd build` and write `cmake ..`. If there is compiler path in PATH enviroment variable, it should build just fine.

## Debug version

`cmake -DCMAKE_BUILD_TYPE:STRING=Debug ..`

Debug version has additional debug information that are printed onto the terminal. Unless someone wants them, compile using *__RELEASE__* profile.

## Release version

`cmake -DCMAKE_BUILD_TYPE:STRING=Release ..`

## Generator

Doesn't matter, I compiled using ninja.

`-G <Generator>`, eg. using ninja `-G Ninja`