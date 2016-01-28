# Specification

## Classes

### Freeway

Method     |Description
:----------|:----------
`Freeway(num_segments, toll_pass_limit, segment_ready_percent, segment_capacities)`|Prints `Αυτοκινητόδρομος σε λειτουργία` and constructs its data members
`Operate()`                                                                        |`void` Calls the `Operate()` method of each `Segment` from end to start and prints the `Car` number
`num_cars()`                                                                       |`size_t`
`segments()`                                                                       |`vector<Segment*>`

### Segment

Variable        |Description
:---------------|:----------
`kMaxCars`      |`size_t`

Method                                                                         |Description
:------------------------------------------------------------------------------|:----------
`Segment(capacity, prev, ready_percent, num_junctions, toll_pass_limit)`       |Randomly creates `Cars` that run into the `Segment`
`Enter()`                                                                      |`void` Max possible `Cars` enter from `Tolls` and previous `Segment`
`Exit()`                                                                       |`void` Max possible `Cars` exit the `Freeway`
`Operate()`                                                                    |`void` Calls `Exit()`, `Enter()` and randomly sets `ready_percent`% cars as `ready`
`Pass(size_t)`                                                                 |`void` Max possible `Cars` exit the `Segment` and enter the next one
`cars()`                                                                       |`vector<Car*>`
`num_cars()`                                                                   |`size_t`
`ready_cars()`                                                                 |`vector<Car*>`
`capacity()`                                                                   |`size_t`
`enter_junction()`                                                             |`size_t`
`set_next()`                                                                   |`void`

### Junction

Variable           |Description
:------------------|:----------
`kMaxTollsPerType` |`size_t`
`kMaxCarsPerToll`  |`size_t`

Method                                              |Description
:---------------------------------------------------|:----------
`Junction(num_junctions, pass_limit)`               |Creates a random number of `Tolls`
`Operate(max_allowed_cars)`                         |`vector<Car*>` `Cars` enter the `Segment` respecting the `capacity` and the `pass_limit`. If a number of `Cars` lower than `3 * pass_limit` can enter, the `pass_limit` is decreased. If exactly `3 * pass_limit` cars enter then the `pass_limit` is increased. Finally, `Cars` are added in each `Toll`.
`Cars()`                                            |`vector<Car*>`
`NumCars()`                                         |`size_t`
`current_id()`                                      |`size_t`
`id()`                                              |`size_t`
`pass_limit()`                                      |`size_t`

### Toll

Variable  |Description
:---------|:----------
`kMaxCars`|`size_t` Max number of cars generated in each `Toll` `>= 1`

Method                                 |Description
:--------------------------------------|:----------
`Toll(current_junction, num_junctions)`|Creates a random number of `Cars`
`Add(car)`                             |`void`
`Remove()        `                     |`vector<Car*>` Removes all `Cars`
`Remove(num_cars)`                     |`vector<Car*>` Removes at most `num_cars` `Cars`
`cars()`                               |`vector<Car*>`
`num_cars()`                           |`size_t`

### Car

Method                       |Description
:----------------------------|:----------
`Car(exit_junction, segment)`|`ready` becomes `false`
`exit_junction()`            |`size_t`
`set_ready(ready)`           |`void`
`ready()`                    |`bool`
`set_segment(segment)`       |`void`
`segment()`                  |`Segment*`

-------------------------------------------------------------------------------

## Usage

The executable file, e.g. `build/project.out`, receives from the command line
the following **case sensitive** arguments:

Argument |Description
:--------|:----------
`seed`   |`uint` Randomness seed
`N`      |`int` Simulation steps number
`NSegs`  |`size_t` Freeway segments number
`K`      |`size_t` Initial maximum car number that can pass a manned toll station
`Percent`|`int` Car percent on a segment that becomes `ready` in the next step

If any of these arguments is not provided, a default value **must** be used.

During the execution, `NSegs` numbers (`size_t`) are read from the standard
input correspoding to the `capacity` of each `Segment`.

E.g:

```sh
~/cs/oop-project $ ./build/project.out -N 30 -NSegs 5 -K 3 -Percent 30
50 100 60 60 70
```

An instance of `Freeway` should be constructed given the above data and then the
`Operate()` method should be called `N` times.
