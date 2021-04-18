# Sortowanie topologiczne skierowanego grafu acyklicznego 

liniowe uporządkowanie wierzchołków, w którym jeśli istnieje krawędź skierowana prowadząca od wierzchołka x do y, to  x znajdzie się przed wierzchołkiem y.
Innymi słowy, każdy wierzchołek poprzedza wszystkie te wierzchołki, do których prowadzą wychodzące od niego krawędzie.

Wierzchołki w każdym grafie acyklicznym skierowanym można posortować topologicznie na jeden lub więcej sposobów.

![](https://github.com/Book-Shelf/AiDS/blob/main/Lab4/180px-Directed_acyclic_graph.png)

Możliwe wyniki sortowania topologicznego wierzchołków zadanego grafu:
+ 7,5,3,11,8,2,10,9
+ 7,5,11,2,3,10,8,9
+ 3,7,8,5,11,10,9,2

## Zadanie do wykonania
Użyj zaimplementowanego prze siebie wcześniej algorytmu DFS w celu posortowania topologicznego zadanego grafu.
Zaproponuj zestaw danych testowych dla swojego rozwiązania i podaj (i uzasadnij) jego złożoność obliczeniową a także pamięciową.


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
