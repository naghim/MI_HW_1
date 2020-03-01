# MI_HW_1
Mesterséges Intelligencia házi feladat #1
_CSP - Constraint Satisfaction Problem_

The __readme__ is also available in English [here](#task).

## Feladat
### Követelmények
A kért követelmények közül a megvalósított program a következőket teljesíti:
- [x] A program a parancssor argumentumain keresztül vegye át a feladat méretét(n) és a használt megoldási módszert(1, 2 vagy 3).

*Megjegyzés:* A mi problémánk túlságosan is komplex ahhoz, hogy a parancssorról olvassa be a méretet, ehelyett a beolvasott fájlban lehet megadni a méreteket a megszorításokkal

- [x] A program a standard kimenetre írja ki a backtrackingben történt értékadások számát.

Az agrumentumlistában beadott érték szerint a következő módokban tudjon lefutni:
- [x] nyers backtracking
- [x] backtracking + MVR + forward checking
- [x] backtracking + MVR + AC-3
- [x] Mindhárom esetben az első megoldás megtalálásáig fusson a program. Feltéve, hogy létezik megoldás.

### Választott probléma
Az általunk választott probléma egy szobabeosztási feladat, ahol meghatározott kritériumok alapján kell a diákokat egy bentlakásba beosztani. A folyósok és az épületek méretei megadhatóak, illetve a szobák típusa és a mennyiségük is. 

Figyelembe vettünk különböző megszorítási kategóriákat:
* garzon, illetve apartman típusú szobák
* északi, illetve déli fekvésű szobák
* ki kivel szeretne lakni
* ki kivel nem szeretne lakni

Mindegyik feltétel kötelező érvényű, tehát egyiknek sincs prioritása a másik felett. A megszorításokat egy fájlból olvashatjuk be, ennek szerkeszetét a későbbiekben tárgyaljuk.
Amennyiben a feltételek nem teljesülnek, úgy tekintjük, hogy a feladatnak nincs megoldása.

**A megoldás c++ nyelven íródott, [CodeBlocks](http://www.codeblocks.org/) környezetben. Ajánlatos abban futtatni. Tesztelve volt Visual Studio 2019-ben is, de valamiért ott másképp értelemzi a fájl struktúráját, így helytelenül fut le.**

### Eredmények
* Sima backtracking:
Az algoritmus lefutott 142 lépéssel.
Végrehajtási idő: 0.076 s

* Backtracking + MVR + forward checking:
Az algoritmus lefutott 134 lépéssel.
Végrehajtási idő: 0.070 s

* Backtracking + MVR + AC-3:
Az algoritmus lefutott 128 lépéssel.
Végrehajtási idő: 0.063 s
___
___

## Task 
### Requirements
The implemented program fulfills the following requirements:
- [x] Use the command line arguments to take the task size (n) and the solution method (1, 2, or 3) used. 

*Note:* our problem is too complex to take its size from the command line, instead specify it in the input file with the constraints.

- [x] The program outputs the number of steps taken to the standard output.

Depending on the value entered, the code can run in the following ways:
- [x] simple backtracking
- [x] backtracking + MVR + forward checking
- [x] backtracking + MVR + AC-3
- [x] In all three cases, the program runs until the first solution is found. As long as the solution exists.

### The Chosen Problem
The problem we have chosen is a room allocation task where students are assigned to rooms in a dorm according to specific criteria. The dimensions of corridors and buildings can be specified, as well as the type and quantity of rooms.

We took into account different categories of constraints:
* studio or apartment rooms
* north or south facing rooms
* whom you want to live with
* whom you don't want to live with

Each condition is binding, so no one has priority over the other. The constraints can be read from a file. If the conditions are not met, the task is considered to have no solution.

**The code was written in C++ in [CodeBlocks](http://www.codeblocks.org/). It is highly recommended to be run in that IDE. It was tested in Visual Studio 2019, but for some reason, it interprets the file structure differently, so the code does not execute properly.**

### Results
* Simple backtracking:
Steps: 142.
Execution time: 0.076 s

* Backtracking + MVR + forward checking:
Steps: 134.
Execution time: 0.070 s

* Backtracking + MVR + AC-3:
Steps: 128
Execution time: 0.063 s

