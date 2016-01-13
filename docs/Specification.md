# Specification

## Classes

### Freeway

|Attribute  |Description|
|-----------|-----------|
|`Operate()`|Test       |

### Segment

|Attribute  |Description|
|-----------|-----------|
|`Operate()`|Test       |

### Junction

|Attribute  |Description|
|-----------|-----------|
|`Operate()`|Test       |

### Toll

|Attribute  |Description|
|-----------|-----------|
|`Operate()`|Test       |

### Car

|Variable       |Description                                                                   |
|:--------------|:-----------------------------------------------------------------------------|
|`ready`        |`bool`                                                                        |
|`exit_junction`|`Junction*`                                                                   |
|`segment`      |`Segment*` Points to the current `Segment` or `NULL` if not inside a `Segment`|

-------------------------------------------------------------------------------

## Usage

The executable file, e.g. `build/project.out`, receives from the command line
the following **case insensitive** arguments:

|Argument |Description                                                            |
|:--------|:----------------------------------------------------------------------|
|`n`      |`int` Simulation steps number                                          |
|`nsegs`  |`size_t` Freeway segments number                                       |
|`k`      |`size_t` Initial maximum car number that can pass a manned toll station|
|`percent`|`int` Car percent on a segment that becomes `ready` in the next step   |

If any of these arguments is not provided, a default value **must** be used.

During the execution, `nsegs` numbers (`size_t`) are read from the standard
input correspoding to the `capacity` of each `Segment`.

E.g:

```sh
~/cs/oop-project $ ./build/project.out -n 30 -nsegs 5 -k 3 -percent 30
50 100 60 60 70
```

An instance of `Freeway` should be constructed given the above data and then the
`Operate()` method should be called `n` times.
