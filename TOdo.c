#include <stdio.h>
#include <stdlib.h>

#define ID 30
#define LINES 5
#define LINES_LENGTH 50

int pick=0,day=0,month=0,year=0,last=0;

char TASKS[30][5][50];

void welcome();
void menu();
void add();
void MULTadd();
void display();

int main(){
    welcome();
    do
    {
        menu();
        switch (pick)
        {
        case 1:
            add();
            break;
        case 2:
            MULTadd();
        case 3:
            display();
        default:
            break;
        }
    } while (pick!=0);
    
    return 0;
}

// Program intro
void welcome(){
    system("cls");
    printf("\n\tHello this program can help you track , organize your tasks and more ...\n\n");
    printf("Can you please just provide today's date in this format (dd/mm/yyyy) : ");
    scanf("%d/%d/%d", &day, &month, &year);
    printf("\nToday's date is : %02d/%02d/%d\n",day,month,year);
    system("PAUSE");
}

// menue to pick your option 
void menu(){
    system("cls");
    printf("=========================================\n \
           ToDo tasks menu\n \
=========================================\n \
            [1] Add a new taks\n \
            [2] Add multiple tasks\n \
            [3] Display tasks\n \
            [4] Edit a task\n \
            [5] Delete a taks by ID\n \
            [6] Search a task\n \
            [7] Tasks statistics\n \
            [0] quiter \n \
=========================================\n"); 
    printf(" Pick your choice [1-6] : ");
    scanf("%d",&pick);
}

// Add new task
void add(){
    if (last >= ID) {
        printf("Sorry, you have reached the maximum number of tasks.\n");
        system("PAUSE");
        return;
    }
    for (int i = last; i < last+1; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            sprintf(TASKS[i][j], "%d", last);
            printf("Enter the taks title : ");
            scanf("%s",TASKS[i][j+1]);
            printf("Enter the taks description : ");
            scanf("%s",TASKS[i][j+2]);
            printf("Enter the taks dead line (dd/mm/yyyy) : ");
            scanf("%s",TASKS[i][j+3]);
            printf("Enter the taks status : \n \
            [1] To do\n \
            [2] Doing\n \
            [3] Done\n\n");
            printf(" Pick your choice [1-3] : ");
            scanf("%s",TASKS[i][j+4]);
            
        }
   
}
    last+=1;
    system("PAUSE");
}

// Add multiple tasks
void MULTadd(){
    // later
}

// Display tasks sorted by (alphabetically , by deadline , deadline is in 3 days or less)
void display(){
    for (int i = 0; i < last; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            printf("Task ID : %s \n",TASKS[i][j]);
            printf("Task title : %s\n",TASKS[i][j+1]);
            printf("Task description : %s\n",TASKS[i][j+2]);
            printf("Task dead line : %s\n",TASKS[i][j+3]);
            printf("Task status : %s\n",TASKS[i][j+4]);
        }
        printf("");
    }
    system("PAUSE");
}
