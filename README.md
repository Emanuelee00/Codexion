# Codexion

A concurrency simulation in C with POSIX threads, in the spirit of the dining philosophers problem.

Several coders sit in a circle. Between each pair there is one USB dongle. A coder needs the two dongles next to them to compile, then debugs, then refactors, and starts again. A monitor thread stops the simulation if a coder burns out (too long without compiling).

## What it shows

- One thread per coder, plus one monitor thread.
- Dongles protected by mutexes and condition variables, with a cooldown after each release.
- Two scheduling policies for who gets a dongle first: `fifo` and `edf` (earliest deadline first).
- Burnout detection and a clean stop.

## Build and run

```sh
make
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Times are in milliseconds. `scheduler` is `fifo` or `edf`. Example:

```sh
./codexion 5 800 200 200 200 3 50 fifo
```

## Status

Work in progress. The simulation runs, but the program still prints debug lines next to the event log.

Written as a project of the 42 curriculum.
