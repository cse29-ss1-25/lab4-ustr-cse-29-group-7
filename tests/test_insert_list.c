#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
void print_list(const List* list) {
    for (int i = 0; i < list->size; i++) {
        printf("[%d] %s\n", i, list->data[i].contents);
    }
}

int main(){

List list;
    list.size = 0;
    list.capacity = 4;
    list.data = calloc(list.capacity, sizeof(UStr));

    char line[1024];
    int index = 0;

    printf("Enter strings:\n");

    while (fgets(line, sizeof(line), stdin)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0'; 
        }

        UStr u = new_ustr(line);
        
	printf("Enter index: ");

	if(scanf("%d", &index) != 1){
		free(u.contents);
		break;
	}
	while (getchar() != '\n');

	int8_t result = insert(&list,u, index);

        printf("%u\n", result);
    }

    print_list(&list);

    for (int i = 0; i < list.size; i++) {
        free_ustr(list.data[i]);
    }
    free(list.data);

    return 0;
}

