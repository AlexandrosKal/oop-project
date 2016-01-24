# [K10](http://cgi.di.uoa.gr/~izambo/oop.html) - [Project assignment](http://cgi.di.uoa.gr/~izambo/OOPproj_2016.pdf)

[![Build Status](https://travis-ci.com/mariosal/oop-project.svg?token=xqRUQfavuqwatjTFWe8m&branch=master)](https://travis-ci.com/mariosal/oop-project)

## Requirements

- [GNU Compiler Collection](https://gcc.gnu.org/)
- [GNU Make](https://gnu.org/software/make/)

## Compilation

```sh
make
make test  # Optional: Executes the unit tests
```

## Execution

```sh
./build/project.out
./build/project_test.out  # Optional: Executed by `make test`
```

## Cleaning

```sh
make clean
```

## Methodology

A detailed description of the entities and the relationships can be found at
[docs/Specification.md](docs/Specification.md).

The
[behavior-driven development](https://en.wikipedia.org/wiki/Behavior-driven_development)
process was used in which, based on the specification,
[unit tests](https://en.wikipedia.org/wiki/Unit_testing) were written first and
then the corresponding entities were being implemented. The unit tests were
implemented using the [Google Test](https://github.com/google/googletest)
library.

[Git](https://git-scm.com/) was used as the
[version control system](https://en.wikipedia.org/wiki/Version_control) along
with [GitHub](https://github.com/). New features were being developed in
separate branches that were merged into the `master` branch afterwards using a
pull request. In addition, [Travis CI](https://travis-ci.org/) was used as the
continuous integration service.

### Operating systems

- [OS X](https://www.apple.com/osx/) 10.11.2
- [Ubuntu GNU/Linux](http://www.ubuntu.com/) 15.10

### Tools

- [Apple LLVM](https://developer.apple.com/library/mac/documentation/CompilerTools/Conceptual/LLVMCompilerOverview/)
  7.0.2
- Git 2.7.0
- GNU Compiler Collection 5.2.1
- GNU Make 3.81
- Google Test
- Travis CI

## Authors

- Alexandros Kalimeris <kalimerisalx@gmail.com> <sdi1400056@di.uoa.gr>
- Mario Saldinger <mariosaldinger@gmail.com> <sdi1400177@di.uoa.gr>
