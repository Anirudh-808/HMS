#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char divider2[] = "----------------------------------------\n";
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

void file_write_patient(FILE *fptr , char *u , char *pass)
{
    char entry[100];
    strcpy(entry ,u);
    strcat(entry , ",");
    strcat(entry , pass);

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

    printf("SIGNED UP SUCCESSFULLY!\n");
}

void patient_signup()
{
    printf("%s" , divider2);
    printf("HOSPITAL MANAGEMEMNT SYSTEM\n");
    printf("%s" , divider2);

    printf("WELCOME TO THE SIGNUP PAGE!\n");
    printf("PLEASE ENTER YOUR USERNAME AND PASSWORD OF CHOICE\n");
    printf("%s" , divider2);
    printf("USERNAME: ");
    scanf("%s" , username_choice);
    printf("PASSWORD: ");
    scanf("%s" , password_choice);

    //writing to file
    FILE *file = fopen("patient_data.txt" , "a+");
    if (file == NULL){printf("ERROR. FILE NOT OPENED");}
    else
    {
        file_write_patient(file , username_choice , password_choice);
        fclose(file);
    }

    printf("%s" , divider2);

    printf("SIGNED UP SUCCESSFULLY!\n");

}