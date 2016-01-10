# [Κ10](http://cgi.di.uoa.gr/~izambo/oop.html) - [Εργασία μαθήματος](http://cgi.di.uoa.gr/~izambo/OOPproj_2016.pdf) [![Build Status](https://travis-ci.com/mariosal/oop-project.svg?token=xqRUQfavuqwatjTFWe8m&branch=master)](https://travis-ci.com/mariosal/oop-project)

## Απαιτούμενα

- [GNU Compiler Collection](https://gcc.gnu.org/)
- [GNU Make](https://gnu.org/software/make/)

## Μεταγλώττιση

```sh
make
make test  # Προαιρετικό: Εκτελεί τα unit tests
```

## Εκτέλεση

```sh
./build/project.out
./build/project_test.out  # Προαιρετικό: Εκτελείται από το `make test`
```

## Εκκαθάριση

```sh
make clean
```

## Μεθοδολογία

Η αναλυτική περιγραφή των οντοτήτων και των συσχετίσεών τους βρίσκεται στο
[docs/Specification.md](docs/Specification.md).

Η ανάπτυξη του λογισμικού βασίστηκε στην διαδικασία [behavior-driven
development](https://en.wikipedia.org/wiki/Behavior-driven_development) όπου
βάσει του specification πρώτα γινόταν η συγγραφή καταλλήλων [unit
tests](https://en.wikipedia.org/wiki/Unit_testing) και έπειτα υλοποιούνταν οι
αντίστοιχες οντότητες της εργασίας. Τα unit tests υλοποιήθηκαν με την βιβλιοθήκη
[Google Test](https://github.com/google/googletest).

Χρησιμοποιήθκε το [version control
system](https://en.wikipedia.org/wiki/Version_control)
[Git](https://git-scm.com/) σε συνδυασμό με την υπηρεσία
[GitHub](https://github.com/). Η ανάπτυξη νέων λειτουργιών γινόταν σε ξεχωριστό
branch που έπειτα συγχωνευόταν στο master μέσω pull request. Καθ' όλη την
διάρκεια υπήρχε continuous integration με την υπηρεσία [Travis
CI](https://travis-ci.org/).

### Λειτουργικά συστήματα

- [Ubuntu GNU/Linux](http://www.ubuntu.com/) 15.10
- [OS X](https://www.apple.com/osx/) 10.11.2

### Εργαλεία

- [Apple
  LLVM](https://developer.apple.com/library/mac/documentation/CompilerTools/Conceptual/LLVMCompilerOverview/)
  7.0.2
- Git 2.7.0
- GNU Compiler Collection 5.2.1
- GNU Make 3.81
- Google Test
- Travis CI

## Συγγραφείς

- Αλέξανδρος Καλημέρης <kalimerisalx@gmail.com> <sdi1400056@di.uoa.gr>
- Μάριο Σάλντιγκερ <mariosaldinger@gmail.com> <sdi1400177@di.uoa.gr>
