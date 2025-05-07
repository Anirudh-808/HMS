#include <stdio.h>
#include "login.c"
#include "signup.c"

char divider[] = "====================================\n";

int main() 
{
    /*using the srand() function to generate a random number
        everytime the program runs. The time function from the time
        header file is used to give a unique "seed" each time the program is run.
        The argument NULL is to ensure the time checked by the time() function
        isnt stored.
        
        CHECK ONLINE SOURCES FOR MORE INFO...*/

    srand(time(NULL));

    int login_signup;
    int screwed_up = 1;

    printf("%s" , divider);
    printf("WELCOME TO HOSPITAL MANAGEMENT SYSTEM\n");
    printf("%s" , divider);

    while (screwed_up == 1)
    {
        printf("LOGIN(1)                              SIGNUP(2)\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d" , &login_signup);

        if (login_signup == 1)
        {
            int option;
            printf("ARE YOU A PATIENT OR DOCTOR? ENTER 1 FOR PATIENT AND 2 FOR DOCTOR: ");
            scanf("%d" , &option);

            if (option == 1)
            {
                patient_login();
            }
            else if (option == 2)
            {
                doctor_login();
            }
            else
            {
                printf("INVALID ENTRY\n");
            }
            screwed_up = 0;
        }
        else if (login_signup == 2)
        {
            int option;
            printf("ARE YOU A PATIENT OR DOCTOR? ENTER 1 FOR PATIENT AND 2 FOR DOCTOR: ");
            scanf("%d" , &option);

            if (option == 1)
            {
                patient_signup();
            }
            else if (option == 2)
            {
                doctor_signup();
            }
            else
            {
                printf("INVALID ENTRY\n");
            }
            screwed_up = 0;
        }
        else
        {
            printf("INVALID CHOICE\n");
        }
    }

    return 0;
}