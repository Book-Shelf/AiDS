# PriorityQueue

### Cel zajęć

Kolejka taka umożliwia następujące operacje:

- void InsertElement(element e) -- Wstawia element do kolejki
- int getMaxPriority() -- pobiera wartość najwyższego priorytetu
- Element Pop() -- Pobiera i usuwa z kolejki element o najwyższym priorytecie. W przypadku istnienia wielu jednakowych elementów, zwraca dowolny element o najwyższym priorytecie.
- IncreasePriority(element e , int priority) -- zwiększa priorytet elementu. W przypadku istnienia wielu jednakowych elementów, zwiększa priorytet wszystkim 
Klasa Element powinna być reprezentowana przez klasę pair z biblioteki standardowej, gdzie pierwszym elementem w parze jest wartość, a drugim jego priorytet. Priorytet reprezentowany jest przez liczbę całkowitą.

### Testowanie rozwiązania

Napisz program testujący działanie programu, który ma następującą funkcjonalność:

1. Program powinien przyjmować z parametry z linii poleceń w formie par (wartosc,priorytet), np: 
```bash
$ my_program  '(kota,3)' '(ala,10)' '(ma,5)' 
```
2. Program powinien wstawić każdy z elementów do kolejki a następnie ściągać każdy element z kolejki zgodnie z priorytetem i wypisywać go na ekranie. 
3. Wynik działania dla przykładu z pkt. 1 powinien zatem wyglądać następująca: ala ma kota
