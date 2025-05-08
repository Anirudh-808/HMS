#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Doctor {
  int experience;
  int age;
  int id;
  int consultation_fee;
  char specialization[100];
  char name[100];
  int phone_no;
} Doctor;

typedef struct Appointment {
  int app_no;
  int d_id;
  float start_time;
  char patient[100];
  char status[100];
  char notes[500];
} Appointment;


int menu()
{
  int option;
  printf("\nWelcome! Please choose an option:\n");
  printf("---------------------------------------------------\n");
  printf("1. Update Doctor Details\n");
  printf("2. Update Status of Appointment / Add Case Notes\n");
  printf("3. Access Patient's Medical Records\n");
  printf("---------------------------------------------------\n\n");
  printf("Option:");
  scanf("%d",&option);
  printf("\n----------------------------------------------------\n");
  return option;
}

Doctor doctors[500];
int count=0;

/*int generate_id()
{
  FILE *fp=fopen("doctors.csv","r");
  if (fp == NULL)
  {
    return 1;
  }
  char line[1024];
  int max_id=0;
  if (fgets(line,sizeof(line),fp)==NULL)
  {
    fclose(fp);
    return 1;
  }
  while(fgets(line,sizeof(line),fp));
  {
    int id=0;
    if(sscanf(line,"%d,",&id)==1)
    {
      if (id>max_id)
      {
        max_id=id;
      }
    }
  }
  fclose(fp);
  return max_id+1;
}*/

void add_doctor(int id)
{
  Doctor d;
  d.id=id;
  printf("Doctor ID: %d\n",d.id);

  printf("Enter the name:");
  scanf("\n%[^\n]s",d.name);

  printf("Enter age:");
  scanf("%d",&d.age);

  printf("Enter phone number:");
  scanf("%d",&d.phone_no);

  printf("Enter specialization:");
  scanf("\n%[^\n]s",d.specialization);

  printf("Enter years of experience:");
  scanf("%d",&d.experience);

  printf("Enter consultation_fee:");
  scanf("%d",&d.consultation_fee);

  //Appending to file
  FILE *file_pointer = fopen("doctors.csv", "a+");
  if (file_pointer == NULL) 
  {
    printf("Error opening file.\n");
    return;
  }
  
  fseek(file_pointer,0, SEEK_END);
  if (ftell(file_pointer)==0)
  {
    fprintf(file_pointer, "ID,Name,Specialization,Experience,Age,Phone Number,Consultation fee\n");
  }

  fprintf(file_pointer,"%d,%s,%s,%d,%d,%d,%d\n", d.id,d.name,d.specialization,d.experience,d.age,d.consultation_fee,d.phone_no);
  fclose(file_pointer);
  printf("Doctor has been added.\n");
}

void update()
{
  int id;
  int field;
  int doctor_count=0;
  char line[1024];
  printf("\nWelcome! PLease enter doctor's ID:");
  scanf("%d",&id);

  printf("\nPlease choose a field to update:\n");
  printf("---------------------------------------------------\n");
  printf("1. Name\n");
  printf("2. Specialization\n");
  printf("3. Experience\n");
  printf("4. Age\n");
  printf("5. Consultation fee\n");
  printf("6. Phone number\n");
  printf("---------------------------------------------------\n\n");
  printf("Field to be updated:");
  scanf("%d",&field);
  printf("\n----------------------------------------------------\n");

  FILE *fp = fopen("doctors.csv", "r");
  if(fp==NULL)
  {
    printf("Doctor database not found.\n");
    return;
  }
  
  if(fgets(line,sizeof(line),fp)==NULL)
  {
    fclose(fp);
    return;
  }
  
 while (fgets(line,sizeof(line),fp) && doctor_count< 500)
  {
    sscanf(line,"%d,%50[^,],%50[^,],%d,%d,%d,%d",&doctors[doctor_count].id,doctors[doctor_count].name,doctors[doctor_count].specialization,&doctors[doctor_count].experience,&doctors[doctor_count].age,&doctors[doctor_count].consultation_fee,&doctors[doctor_count].phone_no);
    doctor_count++;
  }
  fclose(fp);

  for (int i=0;i<doctor_count;i++)
  {
    if (doctors[i].id==id)
    {
      switch (field)
      {
       case 1:
          {
            printf("Enter new name:");
            scanf("\n%[^\n]s",doctors[i].name);
            break;
          }
        case 2:
          {
            printf("Enter new specialization:");
            scanf("\n%[^\n]s",doctors[i].specialization);
            break;
          }
        case 3:
          {
            printf("Enter experience:");
            scanf("%d",&doctors[i].experience);
            break;
          }
        case 4:
          {
            printf("Enter age:");
            scanf("%d",&doctors[i].age);
            break;
          }
        case 5:
          {
            printf("Enter new consultation fee:");
            scanf("%d",&doctors[i].consultation_fee);
            break;
          }
        case 6:
          {
            printf("Enter new phone number:");
            scanf("%d",&doctors[i].phone_no);
            break;
          }

        default:
          {
            printf("Invalid field.\n");
            return;
          }
      }
     //Rewriting file with updated stuff 
      FILE *fp = fopen("doctors.csv", "w");
      if (fp==NULL)
      {
        printf("Error opening file to update.\n");
        return;
      }
      fprintf(fp,"ID,Name,Specialization,Experience,Age,Consultation fee,Phone Number\n");
      for (int j=0;j<doctor_count;j++)
      {
        fprintf(fp,"%d,%s,%s,%d,%d,%d,%d\n", doctors[j].id,doctors[j].name,doctors[j].specialization,doctors[j].experience,doctors[j].age,doctors[j].consultation_fee,doctors[j].phone_no);
      }
      fclose(fp);
      printf("Update successful.\n");
      return;
    }
  }
}

void appointment_status()
{ 
  Appointment appointments[1000];
  char line[1024];
  int input_id;
  int app_no=0;
  printf("\nEnter doctor's ID:");
  scanf("%d",&input_id);

  FILE *fp=fopen("appointments.csv","r");
  if(fp==NULL)
  {
    printf("File not found.\n");
    return;
  }
  if (fgets(line,sizeof(line),fp)==NULL)
  {
    fclose(fp);
    return;
  }

  while(fgets(line,sizeof(line),fp) && app_no<1000)
  {
    sscanf(line,"%d,%f,%d,%100[^,],%100[^,],%500[^\n]",&appointments[app_no].app_no,&appointments[app_no].start_time,&appointments[app_no].d_id,appointments[app_no].patient,appointments[app_no].status,appointments[app_no].notes);
    app_no++;
  }
  fclose(fp);
 
  int result=0;
  //Displaying open appointments for the doctor
  for (int i=0;i<app_no;i++)
  {
    if (input_id==appointments[i].d_id && strcasecmp(appointments[i].status,"open")==0)
    {
      printf("\nAppointment Number:%d, Start time:%.2f, Patient Name:%s, Appointment Status:%s\n\n",appointments[i].app_no,appointments[i].start_time,appointments[i].patient,appointments[i].status);
      result=1;
    }
  }
  
  if (!result)
  {
    printf("No appointments scheduled!\n");
  }
  if (result)
  {
    int input_app_no=0;
    printf("Enter the appointment number:");
    scanf("%d",&input_app_no);
  
  //updating the appointment status and the case notes
  for (int i=0;i<app_no;i++)
  {
    if (input_app_no==appointments[i].app_no)
    {
        printf("Enter status of appointment (open/closed):");
        scanf("\n%[^\n]s",appointments[i].status);

        printf("Enter case notes:");
        scanf("\n%[^\n]s",appointments[i].notes);
        break;
    }
  }
  
  //Writing everything back to the csv file
  FILE *file=fopen("appointments.csv","w");
  if (file==NULL)
  {
    printf("Unable to open the file.");
    return;
  }
  fprintf(file,"Appointment Number,Start Time,Doctor ID,Patient Name,Status,Case Notes\n");
  for (int j=0;j<app_no;j++)
  {
    fprintf(file,"%d,%.2f,%d,%s,%s,%s\n",appointments[j].app_no,appointments[j].start_time,appointments[j].d_id,appointments[j].patient,appointments[j].status,appointments[j].notes);
  }
  fclose(file);
  printf("Successfully updated.\n");
  return;
}
}

void access_records()
{
  Appointment appointments[1000];
  char line[1024];
  int app_no=0;
  char input_patient[100];

  printf("Enter the patient's name:");
  scanf("\n%[^\n]s",input_patient);

  FILE *fp=fopen("appointments.csv","r");
  if (fp == NULL)
  {
    printf("File not found.");
    return;
  }

  if (fgets(line,sizeof(line),fp)==NULL)
  {
    fclose(fp);
    return;
  }

  while (fgets(line,sizeof(line),fp) && app_no<1000)
  {
    sscanf(line, "%d,%f,%d,%100[^,],%100[^,],%50[^\n]",&appointments[app_no].app_no,&appointments[app_no].start_time,&appointments[app_no].d_id,appointments[app_no].patient,appointments[app_no].status,appointments[app_no].notes);
    app_no++;
  }
  fclose(fp);

  int found=0;
  for (int i=0;i<app_no;i++)
  {
    if (strcmp(appointments[i].patient,input_patient)==0)
    {
      printf("\nAppointment Number: %d\nCase Notes: %s\n",appointments[i].app_no,appointments[i].notes);
      found=1;
    }
  }
  if (!found)
  {
    printf("No case notes found for this patient.\n");
  }
}