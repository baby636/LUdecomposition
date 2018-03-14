# LUdecomposition
Sparse matrix LU decomposition

LU decomposition application written in c++. Test data (BBmtx.txt): matrix with 2491 elements (stored in memory, without compression).


Macierz przejścia dla modelu formowania węzła ma 2491 elementów (jest względnie mała) dlatego przechowywano ją w dwuwymiarowej tablicy bez kompresji.
 Algorytmy zaimplementowano w języku C dla liczb rzeczywistych o pojedynczej precyzji.

Results:

|  CPU / gcc | time | relative error
|---|---|---|
| Pentium III 1GHz gcc v. 3.3.2 | 136, 92s | 2, 205377e−3
|---|---|---|
| Pentium M 735 (1.7 GHz) gcc v. 3.4.2 | 50, 49s | 4, 048849e−3
|---|---|---|
| Pentium IV 733 MHz | 98, 89s | 3, 69610e−3
|---|---|---|
| Athlon XP 3.2GHz gcc v. 3.3.4 | 89, 63s | 2, 643332e−3
|---|---|---|
| Intel Core i7 2.3 GHz (3615QM) g++ v. 7.3.0 | 44, 79s | 5, 188407e-2
|---|---|---|
| Intel(R) Xeon(R) CPU E5-1650 v2 3.50GHz gcc v. 4.9.2 | 39, 31s | 2, 270877e-8