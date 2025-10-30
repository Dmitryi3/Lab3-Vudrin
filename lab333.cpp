#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char inf[256];
    int priority;
    struct node* next;
};

struct node* priority_head = NULL;
struct node* queue_head = NULL;
struct node* queue_tail = NULL;
struct node* stack_top = NULL;

// Функция создания элемента с приоритетом
struct node* get_struct(void) {
    struct node* p = NULL;
    int pr;

    p = (struct node*)malloc(sizeof(struct node));
    printf("Введите название объекта: \n");
    scanf("%255s", p->inf);
    printf("Введите приоритет (целое число): \n");
    scanf("%d", &pr);
    p->priority = pr;
    p->next = NULL;

    return p;
}

// Функция создания элемента без приоритета
struct node* get_struct_simple(void) {
    struct node* p = NULL;

    p = (struct node*)malloc(sizeof(struct node));
    printf("Введите название объекта: \n");
    scanf("%255s", p->inf);
    p->priority = 0;
    p->next = NULL;

    return p;
}

// ПРИОРИТЕТНАЯ ОЧЕРЕДЬ 

// Добавление элемента в приоритетную очередь
void priority_enqueue(void) {
    struct node* p = get_struct();

    // Если очередь пуста или новый элемент имеет высший приоритет чем голова
    if (priority_head == NULL || p->priority > priority_head->priority) {
        p->next = priority_head;
        priority_head = p;
    }
    else {
        struct node* current = priority_head;
        while (current->next != NULL && current->next->priority >= p->priority) {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
    }

    printf("Элемент добавлен в приоритетную очередь\n");
}

// Удаление элемента с наивысшим приоритетом
void priority_dequeue(void) {
    if (priority_head == NULL) {
        printf("Приоритетная очередь пуста!\n");
        return;
    }

    struct node* temp = priority_head;
    printf("Удален элемент: %s (приоритет: %d)\n", temp->inf, temp->priority);
    priority_head = priority_head->next;
    free(temp);
}

// Удаление элементов с выбранным приоритетом
void remove_by_priority(void) {
    int tpriority;
    printf("Введите приоритет для удаления: ");
    scanf("%d", &tpriority);

    struct node* current = priority_head;
    struct node* prev = NULL;
    int count = 0;

    while (current != NULL) {
        if (current->priority == tpriority) {
            struct node* temp = current;

            if (prev == NULL) {
                priority_head = current->next;
            }
            else {
                prev->next = current->next;
            }

            current = current->next;
            printf("Удален элемент: %s (приоритет: %d)\n", temp->inf, temp->priority);
            free(temp);
            count++;
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    if (count == 0) {
        printf("Элементы с приоритетом %d не найдены\n", tpriority);
    }
    else {
        printf("Удалено %d элементов с приоритетом %d\n", count, tpriority);
    }
}

// Просмотр приоритетной очереди
void review_priority(void) {
    if (priority_head == NULL) {
        printf("Приоритетная очередь пуста!\n");
        return;
    }

    struct node* struc = priority_head;
    printf("Содержимое приоритетной очереди:\n");
    while (struc) {
        printf("Имя - %s, Приоритет - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

// ОЧЕРЕДЬ 

// Добавление элемента в очередь
void enqueue(void) {
    struct node* p = get_struct_simple();
    if (queue_head == NULL) {
        queue_head = p;
        queue_tail = p;
    }
    else {
        queue_tail->next = p;
        queue_tail = p;
    }

    printf("Элемент добавлен в очередь\n");
}

// Удаление элемента из очереди
void dequeue(void) {
    if (queue_head == NULL) {
        printf("Очередь пуста!\n");
        return;
    }

    struct node* temp = queue_head;
    printf("Удален элемент: %s\n", temp->inf);
    queue_head = queue_head->next;

    if (queue_head == NULL) {
        queue_tail = NULL;
    }

    free(temp);
}

// Просмотр очереди
void review_queue(void) {
    if (queue_head == NULL) {
        printf("Очередь пуста!\n");
        return;
    }

    struct node* struc = queue_head;
    printf("Содержимое очереди:\n");
    while (struc) {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
}

// CТЕК 

// Добавление элемента в стек
void push(void) {
    struct node* p = get_struct_simple();
    p->next = stack_top;
    stack_top = p;

    printf("Элемент добавлен в стек\n");
}

// Удаление элемента из стека
void pop(void) {
    if (stack_top == NULL) {
        printf("Стек пуст!\n");
        return;
    }

    struct node* temp = stack_top;
    printf("Удален элемент: %s\n", temp->inf);
    stack_top = stack_top->next;
    free(temp);
}

// Смена первого и последнего элементов в стеке
void swap_first_last_stack(void) {
    if (stack_top == NULL) {
        printf("Стек пуст!\n");
        return;
    }

    if (stack_top->next == NULL) {
        printf("В стеке только один элемент!\n");
        return;
    }

    
    struct node* last = stack_top;
    struct node* prev = NULL;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

  
    if (stack_top->next == last) {
     
        last->next = stack_top;
        stack_top->next = NULL;
        stack_top = last;
    }
    else {
    
   
        struct node* second = stack_top->next;


        last->next = second;    
        prev->next = stack_top; 
        stack_top->next = NULL; 
        stack_top = last;       
    }

    printf("Первый и последний элементы стека поменялись местами\n");
}

// Просмотр стека
void review_stack(void) {
    if (stack_top == NULL) {
        printf("Стек пуст!\n");
        return;
    }

    struct node* struc = stack_top;
    printf("Содержимое стека:\n");
    while (struc) {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    int structure_choice;

    do {
        printf("\n ГЛАВНОЕ МЕНЮ \n");
        printf("1. Приоритетная очередь\n");
        printf("2. Очередь \n");
        printf("3. Стек \n");
        printf("0. Выход\n");
        printf("Выберите структуру данных: ");
        scanf("%d", &structure_choice);

        if (structure_choice == 0) {
            break;
        }

        do {
            printf("\n");
            switch (structure_choice) {
            case 1:
                printf("ПРИОРИТЕТНАЯ ОЧЕРЕДЬ\n");
                printf("1. Добавить элемент\n");
                printf("2. Удалить элемент \n");
                printf("3. Удалить элементы с выбранным приоритетом\n");
                printf("4. Просмотреть очередь\n");
                printf("0. Назад\n");
                break;
            case 2:
                printf("ОЧЕРЕДЬ\n");
                printf("1. Добавить элемент \n");
                printf("2. Удалить элемент \n");
                printf("3. Просмотреть очередь\n");
                printf("0. Назад\n");
                break;
            case 3:
                printf("СТЕК\n");
                printf("1. Добавить элемент \n");
                printf("2. Удалить элемент \n");
                printf("3. Поменять местами первый и последний элементы\n");
                printf("4. Просмотреть стек\n");
                printf("0. Назад\n");
                break;
            default:
                printf("Неверный выбор!\n");
                break;
            }

            printf("Выберите операцию: ");
            scanf("%d", &choice);

            switch (structure_choice) {
            case 1:
                switch (choice) {
                case 1:
                    priority_enqueue();
                    break;
                case 2:
                    priority_dequeue();
                    break;
                case 3:
                    remove_by_priority();
                    break;
                case 4:
                    review_priority();
                    break;
                case 0:
                    break;
                default:
                    printf("Неверный выбор!\n");
                }
                break;

            case 2:
                switch (choice) {
                case 1:
                    enqueue();
                    break;
                case 2:
                    dequeue();
                    break;
                case 3:
                    review_queue();
                    break;
                case 0:
                    break;
                default:
                    printf("Неверный выбор!\n");
                }
                break;

            case 3:
                switch (choice) {
                case 1:
                    push();
                    break;
                case 2:
                    pop();
                    break;
                case 3:
                    swap_first_last_stack();
                    break;
                case 4:
                    review_stack();
                    break;
                case 0:
                    break;
                default:
                    printf("Неверный выбор!\n");
                }
                break;
            }
        } while (choice != 0);

    } while (structure_choice != 0);
    return 0;
}