# Specification

## Classes

The classes **must** contain *at least* the following members. The data types
are not binding and equivalents may be used.

### Freeway

Variable  |Description
:---------|:----------
`cars`    |`vector<Car*>` Expandable
`segments`|`vector<Segment*>` Constant

Method     |Description
:----------|:----------
`Freeway(num_segments, toll_pass_limit, segment_ready_percent, segment_capacities)`|Prints `Αυτοκινητόδρομος σε λειτουργία` and constructs its data members
`Operate()`                                                                        |Calls the `Operate()` method of each `Segment` from end to start and prints the `Car` number

### Segment

|Attribute  |Description|
|-----------|-----------|
|`Operate()`|Test       |

### Junction

|Attribute  |Description|
|-----------|-----------|
|`Operate()`|Test       |

### Toll

Variable|Description
:-------|:----------
`cars`  |`vector<Car*>`

Method            |Description
:-----------------|:----------
`Toll()`          |Creates a random number of `Cars`
`Add(car)`        |`void`
`Remove(num_cars)`|`void`

### Car

Variable       |Description
:--------------|:----------
`exit_junction`|`size_t`
`ready`        |`bool`
`segment`      |`Segment*` Points to the current `Segment` or `NULL` if not inside a `Segment`

Method                       |Description
:----------------------------|:-----------------
`Car(exit_junction, segment)`|`ready` is `false`

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
