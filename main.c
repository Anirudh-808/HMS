#include <stdio.h>
#include "login.c"
#include "signup.c"
#include "doctor_management.c"
#include "patient_management.c"
#include "appointments.c"
#include <stdlib.h>
#include <time.h>

char divider[] = "====================================\n";

int token = 0;

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
                token = patient_login();
            }
            else if (option == 2)
            {
                token = doctor_login();
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
                int id = doctor_signup();
                add_doctor(id);
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

    if (token == 0) {}
    else if (token == 1)
    {
        //open a menu of available options for patients
        int choice = 0;
        printf("MENU\n");
        printf("1. Book an appointment\n");
        printf("2. Patient info\n");
        printf("ENTER PREFFERED CHOICE: ");
        scanf("%d" , &choice);
        if (choice == 1)
        {
            //ananya r
            appointments();
        }
        else if (choice == 2)
        {
            //archita
            patient_management();
        }
    }
    else if (token == 2)
    {
        //for doctor features
        int option = menu();
        switch (option)
        {
            case 1:
            {
                update();
                break;
            }
            case 2:
            {
                appointment_status();
                break;
            }
            case 3:
            {
                access_records();
                break;
            }
        }
    }

    return 0;
}