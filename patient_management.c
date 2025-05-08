#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int patient_management() 
{
    char name[100], address[200], gender[10], illness[200], phone[10];
    int age;
    printf("----- Enter Patient Information -----\n");
    printf("Name: \n");
    /*fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;*/
    scanf("\n%[^\n]s",name);
    printf("Age: \n");
    scanf("%d", &age);
    getchar();  
    printf("Address: \n");
    scanf("\n%[^\n]s",address);
    /*fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;*/
    printf("Gender: \n");
    scanf("\n%[^\n]s",gender);
    /*fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = 0;*/
    printf("Any Previous Illness': \n");
    scanf("\n%[^\n]s",illness);
    /*fgets(illness, sizeof(illness), stdin);
    illness[strcspn(illness, "\n")] = 0;*/
    printf("Phone Number: \n");
    scanf("\n%[^\n]s",phone);
    /*fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;*/
    FILE *f = fopen("patients.csv", "a+");
    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    fseek(f, 0, SEEK_END); //fseek seeks the cursor to any point of the file, SEEK_END: seeks to end of file
    long size = ftell(f); //ftell- used to get current position of file pointer within a file
    if (size == 0) {
        fprintf(f, "Name,Age,Address,Gender,Previous Illness,Phone\n");
    }

  
    fprintf(f, "\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\"\n", name, age, address, gender, illness, phone);

    fclose(f);
    printf("\n Patient information saved. Proceed to appointment booking.\n");

    return 0;
}