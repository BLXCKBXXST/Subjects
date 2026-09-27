#include <stdio.h>
#include <string.h>

struct NOTE {
    char fio[50];
    char phone[20];     
    char birthday[20];
};

int input(struct NOTE arr[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        if (scanf(" %49[^\n]", arr[i].fio) != 1 ||
            scanf(" %19[^\n]", arr[i].phone) != 1 ||
            scanf(" %19[^\n]", arr[i].birthday) != 1)
            return 0;
    }
    return 1;
}

int find(struct NOTE arr[], int n, char tel[]) {
    int i;
    for(i = 0; i < n; i++) {
        if(strcmp(arr[i].phone, tel) == 0) {
            return i;    
        }
    }
    return -1;   
}

int main() {
    struct NOTE notes[8];
    char search[20];
    int index;   
     
    printf("Введите 8 записей (ФИО, телефон, день рождения):\n");
    if (!input(notes, 8)) {
        fprintf(stderr, "Не удалось прочитать записи\n");
        return 1;
    }
    
    printf("Введите телефон для поиска: ");
    if (scanf(" %19[^\n]", search) != 1) {
        fprintf(stderr, "Не удалось прочитать телефон\n");
        return 1;
    }
    
    index = find(notes, 8, search);
    
    if(index != -1) {
        printf("Найден:\n");
        printf("  ФИО: %s\n", notes[index].fio);
        printf("  Телефон: %s\n", notes[index].phone);
        printf("  День рождения: %s\n", notes[index].birthday);
    } else {
        printf("Человек с таким телефоном не найден.\n");
    }
    
    return 0;
}
