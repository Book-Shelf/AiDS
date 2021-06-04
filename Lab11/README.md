## Zadania do wykonania (Prima/Kruskala)
1. W ramach zadania należy zaimplementować algorytm Prima z wykorzystaniem kolejki priorytetowej.

Algorytm powinien być zaimplementowany jako szereg metod i zwracać strukturę reprezentującą minimalne drzewo rozpinające. Drzewo to może być reprezentowane jako graf.

### Testowanie rozwiązania
Napisz program, który z linii poleceń będzie można wywołać w następujący sposób:
```bash
my_program path_to_graph_file  starting_vertex 
```
Działanie powyższego polecenia powinno:
+ wczytać z pliku path_to_graph_file graf w formacie jak w poprzednim zadaniu
+ wywołać metodę wykonującą algorytm Prima dla wierzchołka początkowego określonego jako starting_vertex
+ Wypisać na standardowym wyjśćiu wagę znalezionego minimalnego drzewa rozpinajacego
Przykładowe działanie algorytmu dla rysunku z treści lab dla wywołania:
```bash
my_program graph1 i output_file
Weight of MST: 37.000000
```

2. W ramach zadania należy zaimplementować algorytm Kruskala z wykorzystaniem operacji na zbiorach.

Algorytm powinien być zaimplementowany jako szereg metod i zwracać strukturę reprezentującą minimalne drzewo rozpinające. Drzewo to może być reprezentowane jako graf.

### Testowanie rozwiązania
Napisz program, który z linii poleceń będzie można wywołać w następujący sposób:
```bash 
my_program path_to_graph_file output_file
```
Działanie powyższego polecenia powinno:
+ wczytać z pliku path_to_graph_file graf w formacie jak w poprzednim zadaniu w pliku output_file
+ wywołać metodę wykonującą algorytm Kruskala
+ Zapisać do pliku graf reprezentujący minimalne drzewo rozpinające zgodnie z formatem CSV używanym do tej pory
Przykładowe działanie algorytmu dla rysunku z treści lab dla wywołania:
```bash 
my_program graph1 
```
Zawartość pliku output_file
```
a,b,4.0
a,h,8.0
h,g,1.0
c,d,7.0
c,f,4.0
i,c,2.0
g,f,2.0
d,e,9.0
```
