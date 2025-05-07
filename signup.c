#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char divider2[] = "====================================\n";
char username_choice[50];
char password_choice[50];
int doctor_id;

int id_gen()
{
    /*using the srand() function to generate a random number
        everytime the program runs. The time function from the time
        header file is used to give a unique "seed" each time the program is run.
        The argument NULL is to ensure the time checked by the time() function
        isnt stored.
        
        CHECK ONLINE SOURCES FOR MORE INFO...*/

    srand(time(NULL));

    int id = 0;
    for (int i = 0; i < 3; i++)
    {
        id = id * 10 + (rand() % 10);
    }

    return id;
}

void file_write(FILE *fptr , char *u , char *pass)
{
    char entry[100];
    strcpy(entry ,u);
    strcat(entry , ",");
    strcat(entry , pass);
    strcat(entry , "\n");

    fputs(entry , fptr);
}

void doctor_signup()
{
    printf("%s" , divider2);
    printf("HOSPITAL MANAGEMEMNT SYSTEM\n");
    printf("WELCOME TO THE SIGNUP PAGE!\n");
    printf("%s" , divider2);

    printf("GENERATING AN ID FOR YOU...\n");
    doctor_id = id_gen();
    printf("YOUR ID IS: %d\n" , doctor_id);

    printf("ENTER YOUR PASSWORD OF CHOICE\n");
    printf("PASSWORD: ");
    scanf("%s" , password_choice);

    //writing to file
    FILE *file = fopen("doctor_data.txt" , "a+");
    if (file == NULL){printf("ERROR. FILE NOT OPENED");}
    else
    {
        //coverting the id to string using snprintf()
        char doctor_id_str[10];
        snprintf(doctor_id_str , sizeof(doctor_id_str) , "%d" , doctor_id);

        file_write(file , doctor_id_str , password_choice);
        fclose(file);
        
    }

    printf("SIGNED UP SUCCESSFULLY!\n");
}

void patient_signup()
{
    char user_check_list[][100] = {"ADMIN"};
    printf("%s" , divider2);
    printf("HOSPITAL MANAGEMEMNT SYSTEM\n");

    printf("WELCOME TO THE SIGNUP PAGE!\n");
    /*printf("PLEASE ENTER YOUR USERNAME AND PASSWORD OF CHOICE\n");
    printf("%s" , divider2);
    printf("USERNAME: ");
    scanf("%s" , username_choice);
    printf("PASSWORD: ");
    scanf("%s" , password_choice);*/

    //checking for duplicates in file
    FILE *file1 = fopen("patient_data.txt" , "r");
    if (file1 == NULL) {printf("ERROR. FILE DOES NOT EXIST");}
    else
    {
        char entry[100];
        char username[100];
        int j = 1;
        while (fgets(entry , sizeof(entry) , file1) != NULL)
        {
            char *comma = strchr(entry , ',');

            // Get the index of the comma
            int index = comma - entry;

            // Copy part before comma
            strncpy(username, entry, index);
            username[index] = '\0';  // Null-terminate the string

            strcpy(user_check_list[j] , username);
            j++;
        }
    }
    fclose(file1);

    //cross verifying input for duplicates
    int quit_check = 0;
    while (quit_check == 0)
    {
        printf("PLEASE ENTER YOUR USERNAME AND PASSWORD OF CHOICE\n");
        printf("%s" , divider2);
        printf("USERNAME: ");
        scanf("%s" , username_choice);
        printf("PASSWORD: ");
        scanf("%s" , password_choice);
        for (int i = 0; i < sizeof(user_check_list)/sizeof(user_check_list[0][0]); i++)
        {
            if (is_equal(user_check_list[i] , username_choice) == 1)
            {
                printf("USERNAME ALREADY EXISTS. PLEASE CHOOSE ANOTHER ONE\n");
                printf("--------------------------------\n");
            }
            else
            {
                quit_check = 1;
                break;
            }
        }
    }

    //writing to file
    FILE *file = fopen("patient_data.txt" , "a+");
    if (file == NULL){printf("ERROR. FILE NOT OPENED");}
    else
    {
        file_write(file , username_choice , password_choice);
        fclose(file);
    }

    printf("%s" , divider2);

    printf("SIGNED UP SUCCESSFULLY!\n");

}