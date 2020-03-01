# MI_HW_1
Mesterséges Intelligencia házi feladat #1
_CSP - Constraint Satisfaction Problem_

## Feladat
### Követelmények
A kért követelmények közül a megvalósított program a következőket teljesíti:
- [x] A program a parancssor argumentumain keresztül vegye át a feladat méretét(n) és a használt megoldási módszert(1, 2 vagy 3).
- [x] A program a standard kimenetre írja ki a backtrackingben történt értékadások számát.

Az agrumentumlistában beadott érték szerint a következő módokban tudjon lefutni:
- [x] nyersbacktracking
- [x] backtracking + MVR + forwardchecking
- [x] backtracking + MVR + AC-3
- [x] Mindhárom esetben az első megoldás megtalálásáig fusson a program.

### Választott probléma
Az általunk választott probléma egy szobabeosztási feladat, ahol meghatározott kritériumok alapján kell a diákokat egy bentlakásba beosztani. A folyósok és az épületek méretei megadhatóak, illetve a szobák típusa és a mennyiségük is. 

Figyelembe vettünk különböző megszorítási kategóriákat:
* garzon, illetve apartman típusú szobák
* északi, illetve déli fekvésű szobák
* ki kivel szeretne lakni
* ki kivel nem szeretne lakni

Mindegyik feltétel kötelező érvényű, tehát egyiknek sincs prioritása a másik felett. A megszorításokat egy fájlból olvashatjuk be, ennek szerkeszetét a későbbiekben tárgyaljuk.
Amennyiben a feltételek nem teljesülnek, úgy tekintjük, hogy a feladatnak nincs megoldása.
A megoldás c++ nyelven íródott. 
