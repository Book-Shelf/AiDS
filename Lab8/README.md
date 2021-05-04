# Dijkstra

Jest do algorytm wyszukujący najkrótsze ścieżki z jednym źródłem dla grafów skierowanych, ważonych z nieujemnymi wagami.
+ W algorytmie wykorzystujemy dodatkową strukturę implementowaną jako kolejka priorytetowa typu MIN (wydajnie zaimplementowana kolejka znacznie poprawia działanie algorytmu). Nazwijmy ją  S. Kolejka ta przechowuje przetworzone wierzchołki, w kolejności wartości  d (odległości od źródła).
+ Algorytm polega na wielokrotnym wykonywaniu następujących operacji:
 Znajdź wierzchołek u  (V - S) o najmniejszym oszacowaniu wagi najkrótszej ścieżki d.
+ Wykonaj relaksację krawędzi wychodzących z u
+ Algorytm w pseudokodzie przedstawiony został poniżej


## Zadania do wykonania
Zaimplementuj algorytm Dijkstry dla reprezentacji grafowej, której używałaś/używałeś na poprzednich zajęciach.

Algorytm powinien być zaimplementowany jako szereg metod (zgodnie z metodami przedstawionymi w pseudokodzie) i zwracać strukturę zawierającą dwa elementy:

1. Odległości od wierzchołka źródłowego do każdego z zadanych
2. Czas wykonania całego programu


## Testowanie rozwiązania
Napisz program, który z linii poleceń będzie można wywołać w następujący sposób:
```bash
$ my_program path_to_graph_file starting_vertex ed_v_1 end_v_2
```
Działanie powyższego polecenia powinno:
+ wczytać z pliku path_to_graph_file graf w formacie jak w poprzednim zadaniu
+ oznaczyć starting_vertex jako wierzchołek startowy
+ wywołać metodę wykonującą algorytm Dijkstry
+ Wyświetlić odległości do ed_v_1 end_v_2
+ Wyświetlić Czas wykonywania w milisekundach.

Przykładowe działanie algorytmu:
```bash
$ my_program graph1 s t z
8 7
0.4 ms (lib)
```
