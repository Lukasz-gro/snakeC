#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NOT_ENOUGH_MEMORY -1

typedef struct snake{
	int x;
	int y;
	char character;
	struct snake *next;
}snake;

snake *head = NULL;
char head_sign = 'O';
char body_sign = 'X';
int a=0, b=0;


int random_food(int min, int max){
    int number = min + rand() % (max - min);
    return number; 
}


void push_front(int x_eat, int y_eat, char chr) {
    
    snake *element = (snake*)malloc(sizeof(snake));
    snake *tmp = NULL;
    element -> x = x_eat;
    element -> y = y_eat;
    element -> character = chr;

    element -> next = NULL;

		if (element == NULL ) {
    fprintf(stderr, "Not enough memory!\n");
    exit(NOT_ENOUGH_MEMORY);
 		}
		

    if (head == NULL)
    {
        head = element;
    }

    else
    {
        tmp = head;
        head = element;
        head -> next = tmp;
    }

}

void starter()
{
	push_front(3, 10, head_sign);	
	push_front(2, 10, body_sign);
	push_front(1,10, body_sign);
	push_front(0,10, body_sign);
}






