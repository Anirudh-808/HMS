#include <stdio.h>
#include <string.h>

char divider1[] = "########################################\n";

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

void patient_login()
{
    char users_list[10][50] = {"anirudh"};
    char passwords_list[10][50] = {"ani123"};

    char username[50];
    char password[50];

    //user input
    printf("USERNAME: ");
    scanf("%s" , username);
    printf("PASSWORD: ");
    scanf("%s" , password);
    printf("%s" , divider1);

    //checking validity
    int flag = 0;
    for (int i = 0; i < sizeof(users_list)/sizeof(char); i++)
    {
        if (is_equal(users_list[i] , username) == 1)
        {
            if (is_equal(passwords_list[i] , password) == 1)
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
    char password[50];

    //database
    char users_id_list[][10] = {'123'};
    char passwords_list[10][50] = {"ani123"};

    //user input
    printf("ID: ");
    scanf("%s" , &user_id);
    printf("PASSWORD: ");
    scanf("%s" , password);
    printf("%s" , divider1);

    //checking validity
    int flag = 0;
    for (int i = 0; i < sizeof(users_id_list)/sizeof(char); i++)
    {
        if (is_equal(users_id_list[i] , user_id) == 1)
        {
            if (is_equal(passwords_list[i] , password) == 1)
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