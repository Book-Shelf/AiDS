# Set

### Cel zajęć

W ramach zajęć zaimplementuj typ abstrakcyjny Set, realizujący funkcjonalność zbioru (zobacz Set)

Klasa reprezentująca Set powinna być zaimplementowana z użyciem szablonu i powinna implementować następujące metody:

- Union -- suma dwóch zbiorów
- Intersection -- przecięcie dwóch zbiorów
- Difference -- różnica 
- Insert -- wstawianie do zbioru
- IsMember - sprawdzanie czy element jest w zbiorze
- Pop -- pobieranie i usuwanie ze zbioru

z użyciem wektora.

### Testowanie rozwiązania

Program powinien realizować funkcjonalność jak poniżej.

1. Pobiera z linii poleceń listę parametrów, będących kolejnymi elementami typu podanego jako pierwszy parametr. Dopuszczalne wartości string/integer np: 
my_program integer 1 2 3 -4 4 3 1 1  2 [0-255]
my_program string ala ma kota a kot ma ale (max 5 char in string)
2. Dodaje parametry programu do obiektu klasy Set i wypisuje zawartość zbioru. Na przykład dla powyższego wynikiem powinno być  1 2 3 -4 4 (niekoniecznie w tej kolejności
