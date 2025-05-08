#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//using a preprocessor directive to define a constant number of users
#define MAX_USERS 1000

char divider2[] = "====================================\n";
char username_choice[50];
char password_choice[50];
int doctor_id;

int is_equal2(char *str1 , char *str2)
{
    if (strcmp(str1, str2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int id_gen()
{
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

char * check_id(char *id_str , char check_list[MAX_USERS][100] , int l)
{
    int sign = 0;
    int id;
    for (int i = 0; i < l; i++)
    {
        if (is_equal2(check_list[i] , id_str) == 1)
        {
            id = id_gen();
            //coverting the id to string using snprintf()
            snprintf(id_str , sizeof(id_str) , "%d" , id);
            sign = 1;
            break;
        }
        else
        {
            continue;
        }
    }
    if (sign == 1)
    {
        return check_id(id_str , check_list , l);
    }
    else
    {
        return id_str;
    }
}

int doctor_signup()
{
    char userid_check_list[MAX_USERS][100];
    printf("%s" , divider2);
    printf("HOSPITAL MANAGEMEMNT SYSTEM\n");
    printf("WELCOME TO THE SIGNUP PAGE!\n");
    printf("%s" , divider2);

    printf("GENERATING AN ID FOR YOU...\n");
    doctor_id = id_gen();
    //coverting the id to string using snprintf()
    char doctor_id_str[10];
    snprintf(doctor_id_str , sizeof(doctor_id_str) , "%d" , doctor_id);

    //checking for duplicates in file
    FILE *file1 = fopen("doctor_data.txt" , "r");
    if (file1 == NULL) {printf("ERROR. FILE DOES NOT EXIST");}
    else
    {
        char entry[100];
        char userid[100];
        int j = 0;
        while (fgets(entry , sizeof(entry) , file1) != NULL && j < MAX_USERS)
        {
            char *comma = strchr(entry , ',');

            // Get the index of the comma
            int index = comma - entry;

            // Copy part before comma
            strncpy(userid, entry, index);
            userid[index] = '\0';  // Null-terminate the string

            strcpy(userid_check_list[j] , userid);
            j++;
        }
    }
    fclose(file1);

    //cross verifying input for duplicates and getting valid id
    int length = sizeof(userid_check_list)/sizeof(userid_check_list[0]);
    strcpy(doctor_id_str , check_id(doctor_id_str , userid_check_list , length));

    printf("YOUR ID IS: %s\n" , doctor_id_str);
    printf("ENTER YOUR PASSWORD OF CHOICE\n");
    printf("PASSWORD: ");
    scanf("%s" , password_choice);

    //writing to file
    FILE *file = fopen("doctor_data.txt" , "a+");
    if (file == NULL){printf("ERROR. FILE NOT OPENED");}
    else
    {
        file_write(file , doctor_id_str , password_choice);
        fclose(file);
        
    }

    printf("SIGNED UP SUCCESSFULLY!\n");
    printf("%s" , divider2);
    return atoi(doctor_id_str);
}

void patient_signup()
{
    char user_check_list[MAX_USERS][100];
    printf("%s" , divider2);
    printf("HOSPITAL MANAGEMEMNT SYSTEM\n");

    printf("WELCOME TO THE SIGNUP PAGE!\n");

    //checking for duplicates in file
    FILE *file1 = fopen("patient_data.txt" , "r");
    if (file1 == NULL) {printf("ERROR. FILE DOES NOT EXIST");}
    else
    {
        char entry[100];
        char username[100];
        int j = 0;
        while (fgets(entry , sizeof(entry) , file1) != NULL && j < MAX_USERS)
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
        int flag = 0;
        for (int i = 0; i < sizeof(user_check_list)/sizeof(user_check_list[0]); i++)
        {
            if (is_equal2(user_check_list[i] , username_choice) == 1)
            {
                printf("USERNAME ALREADY EXISTS. PLEASE CHOOSE ANOTHER ONE\n");
                printf("--------------------------------\n");
                flag = 1;
                break;
            }
            else
            {
                continue;
            }
        }
        if (flag == 0)
        {
            //writing to file
            FILE *file = fopen("patient_data.txt" , "a+");
            if (file == NULL){printf("ERROR. FILE NOT OPENED");}
            else
            {
                file_write(file , username_choice , password_choice);
                fclose(file);
            }

            printf("SIGNED UP SUCCESSFULLY!\n");
            printf("%s" , divider2);
            quit_check = 1;
            break;
        }
        else
        {
            continue;
        }
    }
}