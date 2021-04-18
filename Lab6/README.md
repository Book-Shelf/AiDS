## Zadania do wykonania
Zaimplementuj algorytm wyszukiwania silnych spójnych składowych grafu.

1. Wynikiem działa programu powinna być liczba silnie spójnych składowych w badanym grafie.
2. Zwróć uwagę, że wynikiem działania samej procedury jest graf tak jak w przypadku DFS (jest to bądź co bądź podwójne wywołanie procerudy DFS). 

## Testowanie rozwiązania
Napisz program, który z linii poleceń będzie można wywołać w następujący sposób:
./my_program path_to_graph_file 

Działanie powyższego polecenia powinno:
+ wczytać z pliku path_to_graph_file graf w formacie jak w poprzednim zadaniu
+ wywołać metodę obliczającą silnie spójne składowe
+ Wyświetlić ilość silnie spójnych składowych

Przykładowe działanie algorytmu:
./my_program graph1 
4
