#include <stdio.h>
#include <string.h>

char divider1[] = "########################################\n";
char users_list[][100] = {'ADMIN'};
char users_id_list[][100] = {'ADMIN'};
char passwords_list[][100] = {'admin123'};

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
        char *check_c = entry;
        for (int i = 0; i < sizeof(entry); i++ , check_c++)
        {
            if (*check_c == ',')
            {
                *check_c = '\0';
                strcpy(username , entry);
                strcpy(users_list[j] , username);
                strcpy(password , check_c + 1);
                strcpy(passwords_list[j] , password);
                break;
            }
        }
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
        char *check_c = entry;
        for (int i = 0; i < sizeof(entry); i++ , check_c++)
        {
            if (*check_c == ',')
            {
                *check_c = '\0';
                strcpy(userid , entry);
                strcpy(users_id_list[j] , userid);
                strcpy(password , check_c + 1);
                strcpy(passwords_list[j] , password);
                break;
            }
        }
        j++;
    }
}

void patient_login()
{
    char username_input[50];
    char password_input[50];

    //user input
    printf("USERNAME: ");
    scanf("%s" , username_input);
    printf("PASSWORD: ");
    scanf("%s" , password_input);
    printf("%s" , divider1);

    //checking validity
    int flag = 0;
    for (int i = 0; i < sizeof(users_list)/sizeof(char); i++)
    {
        if (is_equal(users_list[i] , username_input) == 1)
        {
            if (is_equal(passwords_list[i] , password_input) == 1)
            {   
                flag = 1;
                printf("LOGIN SUCCESSFUL!\n");
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
    }
    else if (flag == 2)
    {
        printf("INVLAID PASSWORD\n");
    }
}

void doctor_login()
{
    //user data
    char user_id[10];
    char password_input[50];

    //database
    char users_id_list[][10] = {'123'};
    char passwords_list[10][50] = {"ani123"};

    //user input
    printf("ID: ");
    scanf("%s" , &user_id);
    printf("PASSWORD: ");
    scanf("%s" , password_input);
    printf("%s" , divider1);

    //checking validity
    int flag = 0;
    for (int i = 0; i < sizeof(users_id_list)/sizeof(char); i++)
    {
        if (is_equal(users_id_list[i] , user_id) == 1)
        {
            if (is_equal(passwords_list[i] , password_input) == 1)
            {   
                flag = 1;
                printf("LOGIN SUCCESSFUL!\n");
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
    }
    else if (flag == 2)
    {
        printf("INVLAID PASSWORD\n");
    }
}