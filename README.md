# Codexion

A concurrency simulation in C with POSIX threads, in the spirit of the dining philosophers problem.

Several coders sit in a circle. Between each pair there is one USB dongle. A coder needs the two dongles next to them to compile, then debugs, then refactors, and starts again. A monitor thread stops the simulation if a coder burns out (too long without compiling).

## What it shows

- One thread per coder, plus one monitor thread.
- Dongles protected by mutexes and condition variables, with a cooldown after each release.
- Burnout detection and a clean stop.

## Build and run

```sh
make
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Times are in milliseconds. `scheduler` must be `fifo` or `edf`: the argument is validated, but the scheduling policies are not implemented yet. Example:

```sh
./codexion 5 800 200 200 200 3 50 fifo
```

## Status

Work in progress. The simulation builds and runs, but the `fifo` and `edf` policies are not implemented yet, and the program still prints debug lines next to the event log.

Written as a project of the 42 curriculum.
