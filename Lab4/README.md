# BFS/DFS

Zaimplementuj algorytm przeszukiwania wszerz z wykorzystaniem grafu zaimplementowanego w poprzednim tygodniu. Implementacja powinna udostępniać metody:

+ Graph BFS(Graph graph, Vertex start) która zwraca drzewo przeszukiwania wszerz (tutaj dla uproszczenia zapisane w postaci grafu skierowanego -- jeśli ktoś ma implementacje drzewa, można ją użyć). W przypadku drzewa korzeń automatycznie będzie punktem startowym, dla grafu tą informację trzeba przechować w jakiejś dodatkowej zmiennej, np root
+ List<Vertex> get_path(Vertex end) która zwraca listę zawierającą kolejne wierzchołki, które należy przejść aby dojść z wierzchołka root do wierzchołka end, lub null gdy nie ma takiej ścieżki.
+ int get_hops(Vertex end) która działa jak powyżej, tylko zwraca długość ścieżki od root do end. Gdy nie ma takiej ścieżki zwracane jest -1. Zwróć uwagę, że algorytm BFS zakłada, że długość ścieżki można zapisać w wierzchołku w postaci dodatkowego pola (linia 15).

## Testowanie rozwiązania
1. Napisz program, który z linii poleceń będzie można wywołać w następujący sposób:

 ```bash
 $ my_program path_to_graph_file starting_vertex_id end_vertex_id1 end_vertex_id2 ... 
 ```
  
Działanie powyższego polecenia powinno:
1. wczytać z pliku path_to_graph_file graf w formacie ja kw poprzednim zadaniu
2. wywołać metodę BFS ze startowym wierzchołkiem o identyfikatorze starting_vertex_id
3. Policzyć i wyświetlić na ekranie długości ścieżek z starting_vertex_id do kolejnych wierzchołków na liście parametrów.
4. 
Przykładowe działanie algorytmu:
``` bash
my_program graph1 s s u t w o:

0 3 2 1 -1
```

##### Initial Graph

<p align="center">
  <img src="https://github.com/Book-Shelf/AiDS/blob/main/Lab4/graph.png" />
</p>

##### After BFS

<p align="center">
  <img src="https://github.com/Book-Shelf/AiDS/blob/main/Lab4/tree.png" 
       title="After BFS"/>
</p>

##### After DFS

<p align="center">
  <img src="https://github.com/Book-Shelf/AiDS/blob/main/Lab4/treeDFS.png" 
       title="After DFS"/>
</p>
