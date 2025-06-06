#include <stdio.h>
#include <string.h>

//using a preprocessor directive to define a constant number of users
#define MAX_USERS 1000

char divider1[] = "====================================\n";
char users_list[MAX_USERS][100];
char users_id_list[MAX_USERS][100];
char passwords_list[MAX_USERS][100];

//function to check if 2 strings are equal
int is_equal(char *str1 , char *str2)
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

void file_read_patient(FILE *fptr)
{
    char entry[100];
    char username[100];
    char password[100];
    int j = 0;
    while (fgets(entry , sizeof(entry) , fptr) != NULL)
    {
        char *comma = strchr(entry , ',');
        char *newline = strchr(entry , '\n');

        // Get the index of the comma
        int index = comma - entry;
        int index2 = newline - comma;

        // Copy part before comma
        strncpy(username, entry, index);
        username[index] = '\0';  // Null-terminate the string

        // Copy part after comma
        strncpy(password, comma+1, index2);
        password[index2-1] = '\0';  // Null-terminate the string
        strcpy(users_list[j] , username);
        strcpy(passwords_list[j] , password);
        j++;
    }
}

void file_read_doctor(FILE *fptr)
{
    char entry[100];
    char userid[100];
    char password[100];
    int j = 0;
    while (fgets(entry , sizeof(entry) , fptr) != NULL)
    {
        char *comma = strchr(entry , ',');
        char *newline = strchr(entry , '\n');

        // Get the index of the comma
        int index = comma - entry;
        int index2 = newline - comma;

        // Copy part before comma
        strncpy(userid, entry, index);
        userid[index] = '\0';  // Null-terminate the string

        // Copy part after comma
        strncpy(password, comma+1, index2);
        password[index2-1] = '\0';  // Null-terminate the string
        strcpy(users_id_list[j] , userid);
        strcpy(passwords_list[j] , password);
        j++;
    }
}

int patient_login()
{
    char username_input[50];
    char password_input[50];

    //reading from file and creating arrays
    FILE *file = fopen("patient_data.txt" , "r");
    if (file == NULL) {printf("ERROR, FILE DOES NOT EXIST");}
    else
    {
        file_read_patient(file);
        fclose(file);
    }

    //user input
    printf("USERNAME: ");
    scanf("%s" , username_input);
    printf("PASSWORD: ");
    scanf("%s" , password_input);
    printf("%s" , divider1);

    //checking validity
    int flag = 0;
    for (int i = 0; i < sizeof(users_list)/sizeof(users_list[0]); i++)
    {
        if (is_equal(users_list[i] , username_input) == 1)
        {
            if (is_equal(passwords_list[i] , password_input) == 1)
            {   
                flag = 1;
                printf("LOGIN SUCCESSFUL!\n");
                return 1;
                break;
            }
            else
            {   
                flag = 2;
                break;
            }
        }
        else
        {
            continue;
        }
    }

    if (flag == 0)
    {
        printf("INVALID USERNAME\n");
        return 0;
    }
    else if (flag == 2)
    {
        printf("INVALID PASSWORD\n");
        return 0;
    }
}

int doctor_login()
{
    //user data
    char user_id[10];
    char password_input[50];

    //user input
    printf("ID: ");
    scanf("%s" , &user_id);
    printf("PASSWORD: ");
    scanf("%s" , password_input);
    printf("%s" , divider1);

    //reading from file and creating arrays
    FILE *file = fopen("doctor_data.txt" , "r");
    if (file == NULL) {printf("ERROR, FILE DOES NOT EXIST");}
    else
    {
        file_read_doctor(file);
        fclose(file);
    }

    //checking validity
    int flag = 0;
    for (int i = 0; i < sizeof(users_id_list)/sizeof(users_id_list[0]); i++)
    {
        if (is_equal(users_id_list[i] , user_id) == 1)
        {
            if (is_equal(passwords_list[i] , password_input) == 1)
            {   
                flag = 1;
                printf("LOGIN SUCCESSFUL!\n");
                return 2;
            }
            else
            {   
                flag = 2;
                break;
            }
        }
        else
        {
            continue;
        }
    }

    if (flag == 0)
    {
        printf("INVALID USERID\n");
        return 0;
    }
    else if (flag == 2)
    {
        printf("INVLAID PASSWORD\n");
        return 0;
    }
}