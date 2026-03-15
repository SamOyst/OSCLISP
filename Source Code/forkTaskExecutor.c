//Created by Sam Oystreck A00478278

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//Method responsible for switching and executing programs as selected in main()
int runProcess(int selection)
{
    pid_t pid = fork();
    //Checking for an error on fork
    if (pid < 0)
    {
        printf("Error enountered at fork");
        return (1);
    }
    //Child process - becomes the new process
    else if (pid == 0)
    {
        if (selection == 1)
        {
            execl("./factorial", "factorial", NULL);
        }
        else
        {
            execl("./sorting", "sorting", NULL);
        }
        perror("execl failed");
        _exit(1);
    }
    else
    //Parent process, waits for child and resumes execution
    {
        wait(NULL);
        printf("Process execution complete.\n");
        return (0);
    }
}

//Facilitates process execution
int main()
{
    //Should never terminate short of user termination
    while (1 == 1)
    {
        //Prints menu and waits for selection
        printf("Fork Task Executor:\n1. Factorial Calculation\n");
        printf("2. Sorting Numbers\n0. Quit\n\nPlease input selection: ");
        int selection;
        scanf("%d", &selection);

        //Determines which process to run (if any)
        if (selection == 0)
        {
            printf("Exiting program.\n");
            return (0);
        }
        else if (selection == 1)
        {
            printf("Initializing Factorial Calculation:\n");
            runProcess(selection);
        }
        else if (selection == 2)
        {
            printf("Initializing Sorting Numbers:\n");
            runProcess(selection);
        }
        else
        {
            printf("Input not recognized.\n\n");
        }
    }
}