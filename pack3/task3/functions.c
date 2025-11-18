#include "header.h"

LinkedList create_list(void){
    
}
// Очистка содержимого списка (удаление всех элементов) 
void erase_list(LinkedList *list);
// Полное удаление списка (освобождение ресурсов)
void delete_list(LinkedList *list); 
// Добавление элемента в конец списка
void push_back_list(LinkedList *list, LIST_TYPE value);
// Добавление элемента в начало списка
void push_front_list(LinkedList *list, LIST_TYPE value);
// Удаление элемента с конца списка 
double pop_back_list(LinkedList *list); 
// Удаление элемента с начала списка 
double pop_front_list(LinkedList *list);
// Вставка элемента по индексу
void insert_at_list(LinkedList *list, size_t index, LIST_TYPE value);
// Удаление элемента по индексу
void delete_at_list(LinkedList *list, size_t index);
// Получение элемента по индексу
double get_at_list(const LinkedList *list, size_t index);
// Сравнение двух списков (лексикографически) 
// возвращает 1 — равны, 0 — не равны
int is_equal_list(const LinkedList *l1, const LinkedList *l2);
// ----------------- СТЕК ----------------- //
// Поместить элемент на вершину стека
void push_stack(LinkedList *stack, LIST_TYPE value);
// Извлечь элемент с вершины стека 
double pop_stack(LinkedList *stack);
// Получить элемент с вершины стека без удаления
double peek_stack(const LinkedList *stack); 
// ----------------- ОЧЕРЕДЬ -----------------
// Добавить элемент в очередь
void enqueue(LinkedList *queue, LIST_TYPE value);
// Извлечь элемент из очереди 
double dequeue(LinkedList *queue);
// Получить первый элемент очереди без удаления double
peek_queue(const LinkedList *queue);