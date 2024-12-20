# libcube

*Work in progress.*

---

## Goal

Learn to build something in C.

The objective is to make a simple and fast Rubik's cube library.
It should support moving the the cube, keeping track of oriented
and misoriented pieces as well as functionality for checking if the
cube is in a certain state (DR, HTR etc.).

Maybe I will create scramblers, solvers and so on
that builds on this in the future.

---

## Inspiration

I've used https://cube20.org/src/ and https://nissy.tronto.net/ for inspiration.


## Project structure:

- `src/`
    Source code duh.
- `tests/`
    I have used [Criterion](https://github.com/Snaipe/Criterion) for unit testing.

---

## Cube representation

todo

Representing the Rubik's cube as permutations and orientations of corners and edges:

```
                   +--------------+
                   |              |
                   |  0    0    1 |
                   |              |
                   |  3    U    1 |
                   |              |
                   |  3    2    2 |
                   |              |
    +--------------+--------------+--------------+--------------+
    |              |              |              |              |
    |              |              |              |              |
    |              |              |              |              |
    | 8     L   11 |      F       | 10    R    9 |       B      |
    |              |              |              |              |
    |              |              |              |              |
    |              |              |              |              |
    +--------------+--------------+--------------+--------------+
                   |              |
                   |  4    4    5 |
                   |              |
                   |  7    B    5 |
                   |              |
                   |  7    6    6 |
                   |              |
                   +--------------+
```



### Permutation of corners and edges:

- corners: 0 to 7
- edges: 0 to 11

### Orientation of corners and edges:bottom

- corners:
    0: oriented
    1: clockwise
    2: counter clockwise.
    - three axis:
        - cofb: invariant under <U2, D2, R2, L2,  F,  B>.
        - colr: invariant under <U2, D2,  R,  L, F2, B2>.
        - coud: invariant under < U,  D, R2, L2, F2, B2>.


- edges:
    0: oriented
    1: misoriented
    - three axis:
        - eofb: invariant under < U,  D,  R,  L, F2, B2>.
        - eolr: invariant under < U,  D, R2, L2,  F,  B>.
        - eoud: invariant under <U2, D2,  R,  L,  F,  B>.

