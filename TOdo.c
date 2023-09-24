#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 30
#define LINES 5
#define LINES_LENGTH 50

char TASKS[ID][LINES][LINES_LENGTH];

// Global variables
int pick = 0, last = 0, update = 0, incompleated = 0, completed = 0, remaining_days = 0;
int nextTaskID = 0;

int Title_IDs[ID];
char Titles[ID][LINES_LENGTH];

int Ranked_Days[ID][2];

// Function prototypes
void welcome();
void menu();
void add();
void MULTadd();
void IDdisplay();
void displayall();
void sortTasksAlphabetically();
void sortTasksByDeadline();
void display();
void taskedit();
void DELETEbyID();
void search();
void statistics();

int main()
{
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
            break;
        case 3:
            display();
            break;
        case 4:
            taskedit();
            break;
        case 5:
            DELETEbyID();
            break;
        case 6:
            search();
            break;
        case 7:
            statistics();
            break;
        default:
            break;
        }
    } while (pick != 0);

    return 0;
}

// Program introduction
void welcome()
{
    int day = 0, month = 0, year = 0;
    system("cls");
    printf("\n\tHello, this program can help you track and organize your tasks and more...\n\n");
    printf("Please provide today's date in this format (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);
    printf("\nToday's date is: %02d/%02d/%d\n", day, month, year);
    update = year * 360 + month * 30 + day;
    system("PAUSE");
}

// Menu for selecting options
void menu()
{
    system("cls");
    printf("=========================================\n \
           ToDo tasks menu\n \
=========================================\n \
            [1] Add a new task\n \
            [2] Add multiple tasks\n \
            [3] Display tasks\n \
            [4] Edit a task\n \
            [5] Delete a task by ID\n \
            [6] Search a task\n \
            [7] Tasks statistics\n \
            [0] Quit\n \
=========================================\n");
    printf("Pick your choice [1-7]: ");
    scanf("%d", &pick);
}

// Add a new task
void add()
{
    int choice;
    if (last >= ID)
    {
        printf("Sorry, you have reached the maximum number of tasks.\n");
        system("PAUSE");
        return;
    }
    int taskID = nextTaskID;
    for (int i = last; i < last + 1; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            sprintf(TASKS[i][j], "%d", taskID);
            printf("Enter the task title: ");
            scanf(" %[^\n]", TASKS[i][j + 1]);
            printf("Enter the task description: ");
            scanf(" %[^\n]", TASKS[i][j + 2]);
            printf("Enter the task deadline (dd/mm/yyyy): ");
            scanf("%s", TASKS[i][j + 3]);
            printf("Enter the task status:\n \
            [1] To do\n \
            [2] Doing\n \
            [3] Done\n\n");
            printf("Pick your choice [1-3]: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                strcpy(TASKS[i][j + 4], "To do");
                incompleated++;
            }
            else if (choice == 2)
            {
                strcpy(TASKS[i][j + 4], "Doing");
                incompleated++;
            }
            else if (choice == 3)
            {
                strcpy(TASKS[i][j + 4], "Done");
                completed++;
            }
            else
            {
                printf("You must pick your choice [1-3]\n");
            }
        }
    }
    last += 1;
    nextTaskID++;
    system("PAUSE");
}

// Add multiple tasks
void MULTadd()
{
    int n;
    printf("How many tasks do you want to add: ");
    scanf("%d", &n);
    while (n > 0)
    {
        add();
        n--;
    }
}

// Function to sort tasks alphabetically
void sortTasksAlphabetically()
{

    char chartemp[LINES_LENGTH];
    int tempID;

    // Copy task IDs and titles to temporary arrays
    for (int i = 0; i < last; i++)
    {
        sscanf(TASKS[i][0], "%d", &Title_IDs[i]);
        strcpy(Titles[i], TASKS[i][1]);
    }

    // Sort tasks alphabetically using bubble sort
    for (int i = 0; i < last - 1; i++)
    {
        for (int j = 0; j < last - i - 1; j++)
        {
            if (strcmp(Titles[j], Titles[j + 1]) > 0)
            {
                // Swap Titles[j] and Titles[j+1]
                strcpy(chartemp, Titles[j]);
                strcpy(Titles[j], Titles[j + 1]);
                strcpy(Titles[j + 1], chartemp);

                // Swap Title_IDs[j] and Title_IDs[j+1]
                tempID = Title_IDs[j];
                Title_IDs[j] = Title_IDs[j + 1];
                Title_IDs[j + 1] = tempID;
            }
        }
    }
}


// Function to sort tasks by deadline
void sortTasksByDeadline()
{
    int taskDay = 0, taskMonth = 0, taskYear = 0, ConvToDays = 0;

    // Calculate ConvToDays for each task
    for (int i = 0; i < last; i++)
    {
        sscanf(TASKS[i][3], "%d/%d/%d", &taskDay, &taskMonth, &taskYear);
        ConvToDays = taskYear * 360 + taskMonth * 30 + taskDay;
        Ranked_Days[i][0] = i;
        Ranked_Days[i][1] = ConvToDays;
    }

    // Sort tasks by deadline using bubble sort
    int temp;
    for (int i = 0; i < last - 1; i++)
    {
        for (int j = 0; j < last - i - 1; j++)
        {
            if (Ranked_Days[j][1] > Ranked_Days[j + 1][1])
            {
                // Swap Ranked_Days[j] and Ranked_Days[j+1]
                temp = Ranked_Days[j][1];
                Ranked_Days[j][1] = Ranked_Days[j + 1][1];
                Ranked_Days[j + 1][1] = temp;

                temp = Ranked_Days[j][0];
                Ranked_Days[j][0] = Ranked_Days[j + 1][0];
                Ranked_Days[j + 1][0] = temp;
            }
        }
    }
}

// Display tasks based on user's choice
void display()
{
    system("cls");
    displayall();
    int choice;
    printf("Pick the sort of your display:\n \
            [1] Sort alphabetically\n \
            [2] Sort by deadline\n \
            [3] Show tasks whose deadline is in 3 days or less\n\n");
    printf("Pick your choice [1-3]: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        sortTasksAlphabetically();
        // Display tasks in sorted order
        for (int i = 0; i < last; i++)
        {
            int index = Title_IDs[i];
            printf("Task ID: %s\n", TASKS[index][0]);
            printf("Task Name: %s\n", TASKS[index][1]);
            printf("Task Description: %s\n", TASKS[index][2]);
            printf("Task Deadline: %s\n", TASKS[index][3]);
            printf("Task Status: %s\n", TASKS[index][4]);
            printf("\n");
        }
    }
    else if (choice == 2)
    {
        sortTasksByDeadline();
        // Display tasks in sorted order
        for (int i = 0; i < last; i++)
        {
            int index = Ranked_Days[i][0];
            printf("Task ID: %s\n", TASKS[index][0]);
            printf("Task Name: %s\n", TASKS[index][1]);
            printf("Task Description: %s\n", TASKS[index][2]);
            printf("Task Deadline: %s\n", TASKS[index][3]);
            printf("Task Status: %s\n", TASKS[index][4]);
            printf("\n");
        }
    }
    else if (choice == 3)
    {
        int found = 0;
        for (int i = 0; i < last; i++)
        {
            remaining_days = Ranked_Days[i][1] - update;
            if (remaining_days <= 3 && remaining_days >= 0)
            {
                IDdisplay(Ranked_Days[i][0]);
                found = 1;
            }
        }
        if (!found)
        {
            printf("No deadlines less than 3 days are found\n");
        }
    }
    else
    {
        printf("You must pick your choice [1-3]\n");
    }
    system("PAUSE");
}

// Delete a task by ID
void DELETEbyID()
{
    int d_ID; // Task ID to delete
    printf("Enter the task ID you want to delete: ");
    scanf("%d", &d_ID);

    if (d_ID >= last || d_ID < 0) // Check if the ID is out of range
    {
        printf("Invalid ID\n");
    }
    else
    {
        if (strcmp(TASKS[d_ID][4], "To do") == 0 || strcmp(TASKS[d_ID][4], "Doing") == 0)
        {
            incompleated--; // Decrement incompleated if the task was incomplete
        }
        else if (strcmp(TASKS[d_ID][4], "Done") == 0)
        {
            completed--; // Decrement completed if the task was completed
        }

        // Overwrite the 3D table to delete the task
        for (int i = d_ID; i < last; i++)
        {
            for (int j = 0; j < LINES; j++)
            {
                strcpy(TASKS[i][j], TASKS[i + 1][j]);
            }
        }
        printf("The task has been deleted successfully\n");
        last--;
    }
    system("PAUSE");
}

// Search for a task by ID or title
void search()
{
    int choice;
    printf("Choose the type of search:\n");
    printf("[1] Search for a task by its ID\n");
    printf("[2] Search for a task by its title\n\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int chosenID;
        printf("Enter the task ID: ");
        scanf("%d", &chosenID);

        if (chosenID >= 0 && chosenID < last)
        {
            IDdisplay(chosenID); // Display the task if it exists
        }
        else
        {
            printf("Invalid ID\n");
        }
    }
    else if (choice == 2)
    {
        char tempTitle[LINES_LENGTH];
        int found = 0;

        printf("Enter the title to search for: ");
        scanf(" %[^\n]", tempTitle);

        for (int i = 0; i < last; i++)
        {
            if (strcmp(TASKS[i][1], tempTitle) == 0)
            {
                IDdisplay(i);
                found = 1;
            }
        }

        if (!found)
        {
            printf("No tasks found with this title.\n");
        }
    }
    else
    {
        printf("Invalid choice. Please select either 1 or 2.\n");
    }

    system("PAUSE");
}

// Display a task by its index in the TASKS array
void IDdisplay(int x)
{
    printf("Task ID: %s \n", TASKS[x][0]);
    printf("Task title: %s\n", TASKS[x][1]);
    printf("Task description: %s\n", TASKS[x][2]);
    printf("Task deadline: %s\n", TASKS[x][3]);
    printf("Task status: %s\n", TASKS[x][4]);
    printf("\n");
}

// Display all tasks
void displayall()
{
    for (int i = 0; i < last; i++)
    {
        IDdisplay(i);
        printf("\n");
    }
}

// Edit a task's description, status, or deadline
void taskedit()
{
    system("cls");
    int choice, chosenTASK;
    char EditedValue[LINES_LENGTH];

    printf("Enter the task ID you want to edit: ");
    scanf("%d", &chosenTASK);
    if (chosenTASK > ID || chosenTASK >= last)
    {
        printf("Invalid ID\n");
        system("PAUSE");
        return;
    }
    printf("Pick the task value that you want to modify:\n \
            [1] Edit the description of a task\n \
            [2] Edit the status of a task\n \
            [3] Edit the deadline for a task\n\n");
    printf("Pick your choice [1-3]: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter the new value: ");
        scanf(" %[^\n]", EditedValue);
        strcpy(TASKS[chosenTASK][2], EditedValue);
    }
    else if (choice == 2)
    {
        printf("Enter new task status:\n \
            [1] To do\n \
            [2] Doing\n \
            [3] Done\n\n");
        int newStatus;
        printf("Pick your choice [1-3]: ");
        scanf("%d", &newStatus);
        if (newStatus == 1)
        {
            if (strcmp(TASKS[chosenTASK][4], "Done") == 0)
            {
                completed--;
            }

            strcpy(TASKS[chosenTASK][4], "To do");
            incompleated++;
        }
        else if (newStatus == 2)
        {
            if (strcmp(TASKS[chosenTASK][4], "Done") == 0)
            {
                completed--;
            }
            strcpy(TASKS[chosenTASK][4], "Doing");
            incompleated++;
        }
        else if (newStatus == 3)
        {
            if (strcmp(TASKS[chosenTASK][4], "To do") == 0 || strcmp(TASKS[chosenTASK][4], "Doing") == 0)
            {
                incompleated--;
            }
            strcpy(TASKS[chosenTASK][4], "Done");
            completed++;
        }
        else
        {
            printf("You must pick your choice [1-3]\n");
        }
    }
    else if (choice == 3)
    {

        printf("Enter the new value in this format (dd/mm/yyyy): ");
        scanf(" %[^\n]", EditedValue);
        strcpy(TASKS[chosenTASK][3], EditedValue);
    }
    system("PAUSE");
}

// Display statistics about tasks
void statistics()
{
    system("cls");
    int choice;
    printf("Choose the statistics you want to display:\n \
            [1] Show the total number of tasks\n \
            [2] Show the number of completed and incomplete tasks\n \
            [3] Show the number of days remaining until each task's deadline\n\n");
    printf("Pick your choice [1-3]: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("The total tasks are: %d\n", last);
    }
    else if (choice == 2)
    {
        printf("The completed tasks: %d\n", completed);
        printf("The incomplete tasks: %d\n", incompleated);
    }
    else if (choice == 3)
    {
        sortTasksByDeadline();
        for (int i = 0; i < last; i++)
        {
            remaining_days = Ranked_Days[i][1] - update;
            printf("The remaining days for task number %d are: %d\n", Ranked_Days[i][0], remaining_days);
        }
    }

    system("PAUSE");
}
