# Optimisation

```bash
brew install git-lfs

git init
git lfs install

git lfs track "*.txt"
```

## Combinatorial Optimisation

Combinatorial optimization is the process of searching for maxima (or minima) of an objective function F whose domain is a discrete but large configuration space (as opposed to an N-dimensional continuous space).

### C++

Primitive data types:

- `int`: integer numbers
- `double`: the default type for floating point numbers
  - high absolute value range ($10^{-308}$, $10^{308}$)
  - high precision (14 significant digits)
  - high memory requirement (8 bytes)
- `float`: floating point numbers
  - low absolute value range ($10^{-38}$, $10^{38}$)
  - low precision (6 significant digits)
  - low memory requirement (4 bytes)
- `bool`:
  - Boolean expressions evaluated left to right: order conditions
    - logical and `&&`: by probability of failure
    - logical OR `||`: by probability of success

Warning: uninitialized variables carry a random value!

Casting:

- Integer division: `double division = 9 / 2;`
- Floating point division: `double division = (double) 9 / 2;`.

- ```cpp
  double a = 2.5;
  float b = (float) a;
  int two = (int) a;  // truncation!!!
  ```

Post vs. pre-increment (/decrement): speedups on some processors, may be translated into less machine instructions than a separate `i = i + 1;` statement.

```cpp
int i = 0;
bool zero = (0 == i++);  // zero = true, i = 1
bool zero = (++i == 0);  // i = 1, zero = false
```

Looping control statements: No `<condition>` = infinite loop.

- ```cpp
  for (<statement 1>; <condition>; <statement 2>) {
    <body>
  }
  ```

- ```cpp
  <statement 1>;
  while (<condition>) {
    <body>
    <statement 2>;
  }
  ```

Compilation: Source (`.cpp`) + header (`.h`) files => C++ pre-processor (handles pre-processor directives `#include, #define, #ifdef`, etc.) => Expansion into single intermediary file (still C++ source code) => C++ compiler => Executable.

Overloading: functions with equal names are allowed in the same context only if their argument lists differ:

```cpp
#include <math.h> // contains floor
#include <stdio.h> // contains printf

int round (double number) {
  return (int) (floor(number + 0.5));
}

int round (float number) {
  return (int) (floor(number + 0.5));
}
```

Memory management:

- the stack: a limited "supply" of memory that grows and shrinks during the execution of a program
- the heap: an unlimited supply of memory that can be addressed dynamically during the execution of the program. It is mainly used (by the programmer!) to store large data structures

Arrays:

- Static initialization: `int a[20];`
  - Array space allocated on the stack
  - Size must be known at compile time
  - Memory is freed automatically
  - Member access: `int secondElement = a[1];`
  - _Faster in execution; danger of stack overflow_!
- Dynamic initialization: `int *a = new int[20];` (an explicit pointer, a physical address, to an integer, i.e. to the first element of the array)
  - Array space allocated on the heap
  - Size must be known at run time (i.e. declared size can be variable)
  - Memory is freed manually: `delete a;`
  - Member access: `int secondElement = a[1];`
  - _Memory requirements not limited by stack, slower in execution; danger of memory leaks_ - every `new` statement should have a complementing `delete` statement!

2-dimensional arrays:

- static initialization:

  ```cpp
  int matrix[2][3];
  ```

- dynamic initialization:

  ```cpp
  int **matrix = new int *[2];
  for (int i = 0; i != 2; i++) {
    matrix[i] = new int[3];
  }
  ```

Arrays of dimension > 2:

- static initialization:

  ```cpp
  int cube[2][3][4];
  ```

- dynamic initialization:

  ```cpp
  int ***cube = new int **[2];
  for (int i = 0; i != 2; i++) {
    cube[i] = new int * [3];
    for (int j = 0; j != 3; j++) {
      cube[i][j] = new int [4];
    }
  }

  for (int i=0; i!=2; i++) {
    for (int j=0; j!=3; j++) {
      delete cube[i][j];
    }
    delete cube[i];
  }
  delete cube;
  ```

Copying arrays:

```cpp
int *a = new int[2];
a[0] = 0; a[1] = 1;
```

- Shallow copy:

  ```cpp
  int *b = a;  // pointer assignment!
  ```

  - If you modify the elements of the array pointed to by `b`, you modify the elements of the array pointed to by `a` (both pointers point to the same array)

- Deep copy:

  ```cpp
  int *b = new int[2];
  for (int i=0; i!=2; i++) b[i] = a[i];  // elementwise copy
  ```

  - `a` and `b` point to different arrays on the heap, so modifying the elements of one array does not alter the other array

Recursion:

- In short, recursion allows you to solve a difficult problem by decomposing it into subproblems.
- The subproblems are either trivial cases or problems of the same complexity as the main problem.
- The latter problems can be further decomposed until a trivial case has been obtained.
- The solution to the original problem can be constructed by combining the solutions obtained for the subproblems.
- _If your recursion does not stop, expect a
  stack overflow_!

C: procedural programming is limited:

- Low degree of structuring: for (very) small programs
- Extensibility not important
- Complex data structures not important
- Graphical user interface (GUI) not required

Access rules (`public, protected, private`) are checked at compile time.

Member functions can be divided into two categories:

- Mutators (may) change the state of an object and do not return a result
- Inspectors are queries for an object's state and return a result, but do not change the state of any object
- Mixing mutator and inspector behaviour is considered very bad programming practice.

Pointer variables – the arrow notation:

```cpp
Vector *myVector = new Vector();  // object creation
myVector->addElement(25);  // function call
int currentCapacity = myVector->capacity;  // member access
```

Advantages of macros:

- Compile-Time Optimization: Logs below the specified level are stripped out during compilation.
- Minimal Runtime Overhead: Contextual information is injected at compile time using predefined macros.
- Flexibility: Variadic macros allow dynamic message formatting similar to `printf`.

Limitations of macros:

- Debugging Complexity: Since macros are expanded at compile time, debugging them can be challenging.
- Error-Prone Argument Handling: Repeated evaluation of macro arguments can lead to unintended side effects.
- Limited Type Safety: Unlike functions, macros do not enforce type checking.

Graphical user interfaces (GUIs):

- Single Document Interface (SDI):
  - Assumes only a single document is open at the same time (example: Paint, Notepad)
  - No child windows
- Multiple Document Interface (MDI):
  - Multiple documents may be open at the same time (example: MS Word)
  - Child window support

Performance improvements:

- Program logic.
- Binary calculations!

### Branch-and-Bound Algorithms

Branch-and-bound algorithms are used to solve NP-hard problems where the solution space can be systematically explored and pruned using bounds.

- P = problems solvable in polynomial time on a deterministic computer $\mathcal{O}(nk)$
- NP = problems solvable in polynomial time on a nondeterministic computer
- NP-complete: all problems in NP that can be translated in polynomial time to all other NP- complete problems - if any of them can be solved in polynomial time, all of them can

Complete enumeration (of all possibilities) is often intractable. Branch-and-bound algorithms skip solutions that cannot be optimal.

Two steps (minimization problem):

- Branching: splitting the set $S$ of candidate solutions in two or more smaller subsets $S_1, S_2, \dots$ whose union covers $S$. The minimum of $f(x)$ over $S$ is $\min{v1, v2, \dots}$ where each $v_i$ is the minimum of $f(x)$ over $S_i$.
  - Preferably, the subsets are non-overlapping.
- Bounding: computing upper and lower bounds for the minimum value of $f(x)$ within each subset of $S$ such that some subsets of $S$ can be safely discarded from further examination (pruning) if the corresponding lower bound is larger than the upper bound of another subset.

#### Branching strategies

Dept-first / backtracking:

- Advantages:
  - Relatively little memory required (open nodes can be organized on a stack)
  - A (good) feasible solution is found very quickly
  - Part of the current situation can be restored automatically (faster per node)
- Disadvantages:
  - More nodes than necessary have to be considered

Best-first:

- Advantages:
  - First leaf node gives the optimal solution (if the found solution is equal to the node's Lower Bound)
  - Minimal number of nodes have to be considered
- Disadvantages:
  - No feasible solution is provided before the search is ended
  - Quite some information has to be stored (and restored) for each node
  - The number of open nodes can become enormous: the required amount of memory is huge

Beam search:

- Advantages:
  - A (good) feasible solution is found very quickly during the search
  - The search quickly moves on to quite different search areas
- Disadvantages:
  - The number of open nodes can be enormous
  - More nodes than strictly required need to be considered

For each problem there are many possible ways of branching. This decision has a huge impact on the resulting computation times.

- If possible, try to make subsets with strong bounds:
  - E.g., how many nodes should have resulted if the branching decision in the machine scheduling problem indicated which job to be processed first (instead of last)?
- If possible, try to make sure that the subsets are non-overlapping
- If possible, try to create subsets of the same size (= balanced branching)

Truncated Branch-and-Bound:

- Stop the branch-and-bound procedure after a limited time period or after a limited number of nodes
- Very good if beam search is used, also good with depth-first search
- Very good results if the size of the problem doesn't differ too much from the size of a problem that can be solved to optimality
- Requires a lot of computer memory (certainly if beam search is used)

#### Dominance rules

One can go to great lengths in order to prune nodes on the basis of lower bound calculations. There is a trade-off between the complexity of the lower bound calculations and the number of nodes that can be pruned. The effect on the required computation time might be unclear (and depends on the problem set).

Sometimes it is possible to prove that continuing from a certain node always results in solutions that are never better than the solutions that were found in a previously considered node: this results in dominance pruning.

Dominance rules often exploit symmetry!

### Metaheuristics

Metaheuristic algorithms are used to solve complex optimization problems that are difficult or impossible to address using traditional deterministic methods.

Metaheuristics rely on strategies like exploration (diversification) to search globally and exploitation (intensification) to refine solutions locally. They do not guarantee finding globally optimal solutions but aim for near-optimal solutions efficiently.

The Local Neighbourhood $N(x, \sigma)$ of a solution $x$ is a set of solutions that can be reached from $x$ by a simple operation $\sigma$:

- removing or adding objects
- changing the position of objects
- switching objects

Metaheuristics Strategy: Alternate between Diversification and Local Search

- Identify good regions
- Move towards best schedule in the neighbourhood

#### Simulated annealing

Metropolis (1953): Repetitively warming and cooling material in order to obtain a minimal energy level ($\delta E$ = change in energy level, $k$ = Boltzmann constant, $T$ = temperature):

$$p(\delta E) = \exp\bigg( \frac{- \delta E}{kT} \bigg)$$

Decisions to take:

- Initial temperature
- Cooling scheme ($nrep$ and $\alpha(t)$)
- Stopping condition
- Space of feasible solutions
- The form of the cost function
- Neighbourhood structure: reachability

#### Tabu search

Glover (1986): Flexible memory:

- Tabu move: forbidden neighbourhood in order to avoid cycling
- Aspiration criterion: Overrule tabu move if you are sure that there is no cycling possible (e.g., current solution is best one reached so far)
- Length of the tabu list:
- Static: $t = 7$ or $t = \sqrt(n)$
- Dynamic: $t \in [3, 11]$ or $t \in [0.3 * \sqrt(n), 3 * \sqrt(n)]$
- Intensification and diversification:
  - Intensification: aggressively encouraging the incorporation of 'good attributes':
    - Short term: choosing best non-tabu neighbour
    - Intermediate to long term: incorporating attributes from elite solutions
  - Diversification: looking for solutions that haven't been considered previously
    - Short term: adding penalty based on frequency information
    - Intermediate to long term: incorporating attributes with low frequency counts

#### Genetic algorithms

Holland (1975): Survival of the fittest - genetic structure of a chromosome

- Solutions = chromosomes
- Variables = genes
- Possible values of variables = alleles
- Position of a variable = locus
- Structure = genotype
- Physical expression of the structure = phenotype

- Crossover:
  - P1: `1010010` P2: `0111001` Crossover point = `3`
  - O1: `1011001` O2: `0110010`
- Fitness value
- $2^n$ distinct Schemata:
  - P1 in P2: `**1*0**`
  - O1 in O2: `**1*0**`
- Population size
- Seeding

| ID  | Representation | $x$    | Fitness value $f(x)$ | $P_\text{select}$ |
| --- | -------------- | ------ | -------------------- | ----------------- |
| 1   | `10011`        | $19$   | $2399$               | $0.206$           |
| 2   | `00101`        | $5$    | $3225$               | $0.277$           |
| 3   | `11010`        | $26$   | $516$                | $0.044$           |
| 4   | `10101`        | $21$   | $1801$               | $0.155$           |
| 5   | `01110`        | $3684$ | $2399$               | $0.206$           |

$$f(x) = x^3 - 60 x^2 + 900 x + 100$$

```python
f = lambda x: x**3 - 60 * x**2 + 900 * x + 100
fitness_values = [f(x) for x in [
    0b10011,
    0b00101,
    0b11010,
    0b10101,
    0b01110,
]]
avg_fitness = sum(fitness_values) / len(fitness_values)
selection_proba = [round(val / sum(fitness_values), 3) for val in fitness_values]
```

Average fitness = $2325.0$

| Step | Parent 1 | Parent 2 | Crossover Point | Mutation? | Offspring | $x$  | $f(x)$ |
| ---- | -------- | -------- | --------------- | --------- | --------- | ---- | ------ |
| 1    | 1        | 2        | 4               | No        | `10011`   | $19$ | $2399$ |
| 2    | 5        | 3        | 2               | No        | `01010`   | $10$ | $4100$ |
| 3    | 5        | 2        | 3               | No        | `01101`   | $13$ | $3857$ |
| 4    | 4        | 2        | 1               | Yes (4)   | `10111`   | $23$ | $1227$ |
| 5    | 2        | 5        | 4               | No        | `00100`   | $4$  | $2804$ |

```python
fitness_values = [f(x) for x in [0b10011, 0b01010, 0b01101, 0b10111, 0b00100]]
avg_fitness = sum(fitness_values) / len(fitness_values)
```

Average fitness = $2877.4$
