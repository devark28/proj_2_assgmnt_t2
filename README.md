# Data Structures — Project 2

C programs of binary heaps, Kruskal's MST, BFS, and Bellman-Ford
shortest paths. Each question lives in its own folder with a `main.c` and the
small set of headers it needs.

## Layout

```
.
├── q1/  Max-heap of cloud jobs
├── q2/  Max-heap of airport passengers
├── q3/  Kruskal's MST for a fiber-optic backbone
├── q4/  BFS to find one-hop peers of a compromised workstation
├── q5/  Bellman-Ford shortest paths in a banking network
├── docs/
│   ├── assgmt_prompt.txt
│   ├── assgmt_rubrics.txt
│   └── images/   graph_q3.png, graph_q4.png, graph_q5.png
└── README.md
```

## Build & Run

Each program compiles with a single `gcc` command. From the project root:

```
gcc -Wall -Wextra -o q1/main q1/main.c && ./q1/main
gcc -Wall -Wextra -o q2/main q2/main.c && ./q2/main
gcc -Wall -Wextra -o q3/main q3/main.c && ./q3/main
gcc -Wall -Wextra -o q4/main q4/main.c && ./q4/main
gcc -Wall -Wextra -o q5/main q5/main.c && ./q5/main
```

Q4 reads one character from stdin (the suspected workstation). Pipe a letter
in non-interactively, e.g. `echo D | ./q4/main`.

---

## Q1 — Cloud Job Scheduler (Max-Heap)

Input priorities `P = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88}`. Each
priority is paired with a sequential job ID (`A`, `B`, …, `K`). The new
urgent job at priority 100 is assigned `L`.

Heap is stored as a flat array with parent/child arithmetic
(`parent(i) = (i-1)/2`, `left = 2i+1`, `right = 2i+2`). The program shows the
heap after each step: raw tree from the input, after `buildMaxHeap`, after
inserting priority 100, and after removing priority 100.

* Header `job_heap.h` carries the `Job` and `JobHeap` types plus
  `siftUp`/`siftDown`, `buildMaxHeap`, `heapInsert`, `findIndexByPriority`,
  `heapDeleteAt`, and the array/tree printers.

## Q2 — Airport Screening (Max-Heap of Passengers)

Six passengers (Alice, Brian, Chen, Fatima, Noah, Sofia) with risk scores
are inserted, heapified, then drained through `extractMax` to produce the
screening order. The arriving passenger at risk score 98 is inserted and
later removed.

* Header `passenger_heap.h` mirrors the structure of Q1 but stores
  `(name, riskScore)` pairs. The screening queue is produced by copying the
  heap into a snapshot so the original heap survives for the insert/delete
  steps.

## Q3 — Fiber-Optic MST (Kruskal's Algorithm)

Graph image: `docs/images/graph_q3.png`.

Hubs: A, B, C, D, E, F, G. Edges (cost in millions):

| Edge | Cost |
|------|------|
| A–B  | 6    |
| B–C  | 11   |
| B–D  | 5    |
| C–D  | 17   |
| C–G  | 25   |
| D–E  | 22   |
| E–F  | 10   |
| F–G  | 22   |

> The image also shows lines from A–D and D–F whose weight labels were not
> clearly legible. The MST below is unchanged if their weights are ≥ 17
> (since the spanning tree picks the next-best edges anyway).

The program prints the adjacency matrix, the sorted edge list, every
Kruskal decision (accept/skip-cycle), the final MST, and the total cost.

MST edges chosen: B–D (5), A–B (6), E–F (10), B–C (11), D–E (22), F–G (22).
**Total: 76 million USD.**

* `graph.h` — `HubGraph` with the adjacency matrix and edge collection.
* `union_find.h` — disjoint-set with path compression and union-by-rank, used
  to reject cycle-forming edges.

## Q4 — BFS for a Breached Workstation

Graph image: `docs/images/graph_q4.png` (same topology as Q3 here).

The program prints the list of workstations, prompts the user to enter the
suspected compromised one, runs a BFS one level deep, lists each direct
peer with its data-transfer time, and reports the peer with the highest
weight as the most at-risk.

Example:

```
$ echo D | ./q4/main
...
BFS from workstation D
Directly connected workstations (one-hop neighbors):
  D --[5 min]--> B
  D --[17 min]--> C
  D --[22 min]--> E

Highest-risk peer: E (data transfer time = 22 minutes)
```

* `graph.h` — `CommGraph` with adjacency matrix + label lookup.
* `queue.h` — plain integer queue backing the BFS frontier.

## Q5 — Banking Risk Propagation (Bellman-Ford)

Graph image: `docs/images/graph_q5.png`.

Branches: A, B, C, D, E, F, G, H, I, J. Edges (undirected):

| Edge | Weight |
|------|--------|
| A–B  | 4      |
| A–D  | 16     |
| B–C  | 6      |
| B–D  | 6      |
| B–J  | 7      |
| C–G  | 9      |
| D–E  | 7      |
| E–F  | 10     |
| E–I  | 2      |
| F–I  | 10     |
| F–J  | 3      |
| G–H  | 13     |

Each undirected edge is added as a pair of directed edges so the Bellman-Ford
edge-relaxation loop sees them in both directions. After `|V| − 1` relaxation
passes the program does one extra pass to detect a negative-weight cycle.

Sample output (source = A):

```
A -> B : cost = 4    path = A -> B
A -> C : cost = 10   path = A -> B -> C
A -> D : cost = 10   path = A -> B -> D
A -> E : cost = 17   path = A -> B -> D -> E
A -> F : cost = 14   path = A -> B -> J -> F
A -> G : cost = 19   path = A -> B -> C -> G
A -> H : cost = 32   path = A -> B -> C -> G -> H
A -> I : cost = 19   path = A -> B -> D -> E -> I
A -> J : cost = 11   path = A -> B -> J
```

No negative cycle is detected (the supplied graph has only positive
weights). The detection step is still run and reported, since the algorithm
must be able to flag one if it appears.

* `graph.h` — `BankGraph` with a flat edge list, plus a helper that adds an
  undirected edge as two directed ones.
* `bellman_ford.h` — relaxation loop, negative-cycle check, predecessor
  array, and `printPath` for reconstructing the route from source to target.
