#include <stdio.h>
#include <string.h>
#include<stdlib.h>


int appointments() 
{
    FILE *file;
    char line[512], *token;
    char specializations[50][100];
    int spec_count = 0;
    int choice;
    int dchoice;

    file = fopen("doctor_management.csv", "r");
    if (file == NULL) 
    {
        printf("ERROR WHILE OPENING FILE.\n");
        return 1;
    }

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) 
    {
        token = strtok(line, ","); 
        token = strtok(NULL, ","); 

        if (token != NULL) 
        {
            token[strcspn(token, "\n")] = 0; 

            int duplicate = 0;
            for (int i = 0; i < spec_count; i++) 
            {
                if (strcmp(specializations[i], token) == 0) 
                {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate && spec_count < 50) 
            {
                strcpy(specializations[spec_count], token);
                spec_count++;
            }
        }
    }
    fclose(file);

    printf("AVAILABLE SPECIALIZATIONS:\n");
    for (int i = 0; i < spec_count; i++) 
    {
        printf("%d. %s\n", i + 1, specializations[i]);
    }

    printf("\nENTER CHOICE OF SPECIALIZATION: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > spec_count) 
    {
        printf("INVALID.\n");
        return 1;
    }

    file = fopen("doctor_management.csv", "r");
    if (file == NULL) {
        printf("ERROR WHILE OPENING FILE.\n");
        return 1;
    }

    fgets(line, sizeof(line), file); 

    printf("\nDOCTORS IN %s:\n", specializations[choice - 1]);
    int dcount=0;
    while (fgets(line, sizeof(line), file)) 
    {
        char name[100], spec[100];
        int experience;

        token = strtok(line, ",");
        strcpy(name, token);

        token = strtok(NULL, ",");
        strcpy(spec, token);

        token = strtok(NULL, ",");
        experience = atoi(token);

        if (strcmp(spec, specializations[choice - 1]) == 0) 
        {
            dcount++;
            printf("%d. %s - %d YEARS OF EXPERIENCE\n", dcount,name, experience);
        }
    }

    fclose(file);

    printf("\nENTER CHOICE OF DOCTOR: ");
    scanf("%d", &dchoice);

    file = fopen("doctor_management.csv", "r");
    if (file == NULL) {
        printf("ERROR IN OPENING FILE.\n");
        return 1;
    }

    fgets(line, sizeof(line), file); 

    dcount=0;
    while (fgets(line, sizeof(line), file)) 
    {
        char name[100], spec[100];
        int experience;
        int age;
        int fees;


        token = strtok(line, ",");
        strcpy(name, token);

        token = strtok(NULL, ",");
        strcpy(spec, token);

        token = strtok(NULL, ",");
        experience = atoi(token);

        token = strtok(NULL, ",");
        age = atoi(token);

        token = strtok(NULL, ",");
        fees = atoi(token);


        if (strcmp(spec, specializations[choice - 1]) == 0) 
        {
            dcount++;
            if(dcount == dchoice)
                printf("%s \nTOTAL FEES - %d\n", name,fees);            
        }
    }

    fclose(file);
    return 0;
}