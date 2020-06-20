#include "function.h"
#include <ncurses.h>

int x_head=0, y_head=0, x_eaten=0, y_eaten=0;
int clock_new = 0;
bool eaten = false;
snake *iter =NULL;


// showing the walls
void walls()
{
	for(a=0; a<23; a++)
	{
		mvaddstr(a, 0, "#");
		mvaddstr(a, 79, "#");
	}
	for(b=0; b<80; b++)
	{
		mvaddstr(0, b, "#");
		mvaddstr(23, b, "#");		
	}
}


int main(void)
{	
	// initialisation of the food and snake's body
	starter();
	int direction = 'd';
	bool quit = false;
	int food_x = random_food(1,78);
	int food_y = random_food(1,22);
	int score = 0;


	// initialisation of the screen
	srand(time(NULL));
	WINDOW * mainwin;
	if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}
	noecho();
	cbreak();
	timeout(500);

	do {

	int change = 0;
	int c = getch();
	

	switch (c)
	{	
		case 'w':
		change=1;
		break;
		
		case 'a':
		change=1;
		break;

		case 's':
		change=1;
		break;

		case 'd':
		change=1;
		break;

		case 'q':
		quit = true;
		break;

		default:
		c = 1;
		break;
	}



	// checking the direction
	if((direction == 'a') && (c == 'd')){
		direction = 'a';
	}
	else if((direction == 'd') && (c == 'a')){
		direction = 'd';	
	}
	else if((direction == 's') && (c == 'w')){
		direction = 's';
	}
	else if((direction == 'w') && (c == 's')){
		direction = 'w';	
	}
	else if(change==1){direction=c;}
	
	
	iter=head;

	// moving the snake's body
	while(iter -> next  != NULL)
	{
		iter -> x = iter -> next -> x;
		iter -> y = iter -> next -> y;
		iter = iter -> next;
	} 
	
	
	// checking the direction where the snake should go
	iter=head;
	while(iter -> next != NULL)
	{
		iter = iter -> next;
	}
	
	if(direction=='d'){
		iter -> x+=1;
	}
	else if(direction=='a'){
		iter -> x-=1;	
	}
	else if(direction=='w'){
		iter -> y-=1;
	}
	else if(direction=='s'){
		iter -> y+=1;
	}

	// creating variables for head to check the collision
	x_head = iter->x;
	y_head = iter->y;


	// eating and getting bigger
	if(x_head==food_x && y_head==food_y){
		
		// checking whether you ate another food before getting longer		
		if(eaten == true)
		{
			clock_new = 0;
			push_front(x_eaten, y_eaten, body_sign);	
		}
		score += 1;
		eaten = true;
		x_eaten = food_x;
		y_eaten = food_y;

 		int check =1;

		// checking if food is in right place
		while (check != 0)
		{
		check = 0;
		food_x=random_food(1,78);
		food_y=random_food(1,22);
		
		iter=head;
		while(iter  != NULL)
		{ 
			if((food_x == iter -> x) && (food_y == iter -> y)) 
			{ 
			check += 1; 
			}
			iter = iter -> next;
		}
		
		}
	}	

	// adding body part after last part of tail went through the placement of food
	if(eaten == true)
	{
		clock_new += 1;
	}
	if(clock_new==score+4)
	{
		push_front(x_eaten, y_eaten, body_sign);
		clock_new = 0;
	}
	
	// collision with body or walls
	iter=head;
	while(iter -> next != NULL)
	{	
		if((x_head == iter->x) && (y_head == iter->y)){quit = true;}
		iter = iter->next;
	}
	if(x_head==0 || x_head==79 || y_head==0 || y_head==23){quit=true;}

	
	clear();
	
	// printing the body and walls
	walls();
	mvaddstr(food_y, food_x, "M");
	iter=head;
	while(iter != NULL){
		mvaddstr(iter -> y, iter -> x, &(iter->character));
		iter = iter -> next;
	}

	refresh();
	} while( ! quit );

	// clearing the screen after the game
	nocbreak();
	echo();
	refresh();
	delwin(mainwin);
	endwin();

	// printing the score
	printf("Your score is: %d\n", score);
	return EXIT_SUCCESS;
}
