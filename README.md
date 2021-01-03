# Skeleton

## Purpose
This project illustrates a base structure of projects which we can easily write, test, run, watch code coverage and checks UB (using `ASAN/UBSAN`).
It used to copy it `as is` to save my time when creating new projects.

### Structure: 
- `skeleton` - main executable target, links with the `common`, `dataapi` and uses its functionality
- `dataapi` - contains functionality of the project
- `dataapitests` - tests written using gtest library, tests `dataapi` and `common`
- `common` - static library containing common helpful functionality shared between all other targets
- `dataapi_sanitized` - sanitized version of library, used to linking with `dataapitests_sanitized`
- `common_sanitized` - sanitized version of library, used to linking with `dataapitests_sanitized`
- `dataapitests_sanitized` - sanitized version of test cases, used to check `UB` in code
- `coverage` - runs test cases and checks code coverage (also creates `html` file with information about covered and non covered code regions)
- `test` - runs test cases
- `package` - creates `rpm` package

### Generate project
1. `cmake -B build` or
2. `cmake -B build -DBUILD_TESTS=ON` if we want to build tests

### Building
1. `cmake --build build -j16` - just to build all targets
2. `cmake --build build -j16 --target test` - builds and runs all test cases (will work if we generated project with `BUILD_TESTS=ON` key)
3. `cmake --build build -j16 --target coverage` - builds and runs all test cases, then shows us up a table with code coverage (also you can open `./build/dataapitests/coverate.html` to watch which regions of code your test cases covered)
4. `cmake --build build -j16 --target dataapitests_sanitized` - builds and runs all test cases with sanitizers (`ASAN/UBSAN`)
5. `cmake --build build -j16 --target package` - creates `RPM` package
