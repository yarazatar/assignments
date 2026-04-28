#include <stdio.h>
#include <string.h>

#define SIZE 15 

typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("[!] Buffer Overflow: %c\n", data);
        return;
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
}

char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        return '\0';
    }
    char data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[50];
    char suffix[] = " CE-ESY";
    char fullName[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    strcpy(fullName, name);
    strcat(fullName, suffix);

    for (int i = 0; i < (int)strlen(fullName); i++) {
        write(&cb, fullName[i]);
    }

    printf("\nResult from buffer: ");
    while (!isEmpty(&cb)) {
        char c = read(&cb);
        if (c != '\0') {
            printf("%c", c);
        }
    }
    printf("\n");

    return 0;
}
