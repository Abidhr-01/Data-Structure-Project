#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node node;

struct Node
{
    char name[20];
    char add[20]; 
    char phone[20];
    char email[30];

    node *next;
} list, *head = NULL;

FILE *file,*f1;
int k = 0;
void saved_data()
{
    node *temp, *new_node;
    
    head = NULL;
    rewind(file);
    while ((fread(&list, sizeof(list), 1, file)) == 1)
    {
        temp = (node *)malloc(sizeof(node));
        strcpy(temp->name, list.name);
        strcpy(temp->phone, list.phone);
        strcpy(temp->email, list.email);
        strcpy(temp->add, list.add);

        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
            new_node = temp;
        }
        else
        {
            new_node->next = temp;
            new_node = temp;
        }
    }
}
void addrecord()
{
    char check = 'y';
    while (check == 'y' || check == 'Y')
    {
        k++;
        printf("Contact %d:\n", k);
        fflush(stdin);
        printf("Enter Name: ");
        gets(list.name);
        fflush(stdin);
        printf("\nEnter Mobile No: ");
        gets(list.phone);
        fflush(stdin);
        printf("\nEnter E-Mail: ");
        gets(list.email);
        fflush(stdin);
        printf("\nEnter Address: ");
        scanf("%s", list.add);
        fwrite(&list, sizeof(list), 1, file);
        printf("\nDo You Want to Add More (y/n): ");

        getchar();
        check = getchar();
        printf("\n");
    }
}
void print_title()
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\tCONTACT MANAGEMENT SYSTEM\n");
    printf("\t\t\t=========================================\n");
    printf("\n\n");
}
void edit()
{
    print_title();
    int check = 0;
    char name1[100];
    printf("\n\t\tEnter Name to Edit:");
    scanf("%s", name1);

    rewind(file);
    while ((fread(&list, sizeof(list), 1, file) == 1))
    {
        if (strcmp(name1, list.name) == 0)
        {
            check = 1;
            break;
        }
    }
    if (check == 0)
        printf("\n\t\tRecord not found!!!\n\n");
    else
    {
        fseek(file, sizeof(list), SEEK_CUR);
        printf("\n\t\tEnter new data :\n\n");

        fflush(stdin);
        printf("\t\t\t\tEnter Name:");
        gets(list.name);

        fflush(stdin);
        printf("\n\t\t\t\tEnter Mobile No:");
        gets(list.phone);

        fflush(stdin);
        printf("\n\t\t\t\tEnter E-Mail:");
        gets(list.email);
        
        fflush(stdin);
        printf("\n\t\t\t\tEnter ADDRESS:");
        scanf("%s", list.add);

        fwrite(&list, sizeof(list), 1, file);
    }
    if (check == 1)
    {
        printf("\n\t\tRecord was changed successfully.\n");
    }
    printf("\n");
    system("pause");
}

void display_contact()
{
    print_title();
    saved_data();
    node *c = head;

    if (head != NULL)
    {
        printf("\n\n\n%-20s %-20s %-20s %-30s\n","NAME","PHONE","E-Mail","ADDRESS");
        printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n\n");
    }
    while (c != NULL)
    {
        printf("\n%-20s %-20s %-20s %-30s\n",c->name, c->phone, c->email, c->add);
        c = c->next;
    }

    printf("\n");
    system("pause");
}

void deleteee()
{

    print_title();
    char name1[100];
    FILE *tmp;
    if ((tmp = fopen("tmp.txt", "w")) == NULL)
    {
        printf("\n\t\tCan not be opened");
    }
    printf("\n\t\tEnter Name that to be delete:");
    scanf("%s", name1);
    int check = 0;
    rewind(file);

    while ((fread(&list, sizeof(list), 1, file)) == 1)
    {
        if (strcmp(list.name, name1) == 0)
        {
            check = 1;
        }
        else
        {
            fwrite(&list, sizeof(list), 1, tmp);
        }
    }
    fclose(file);
    fclose(tmp);
    remove("Contact.txt");
    rename("tmp.txt", "Contact.txt");
    if ((file = fopen("Contact.txt", "rb+")) == NULL)
    {
        printf("Can not be opened.");
    }
    if (check == 1)
    {
        printf("\n\t\tThe record has been deleted successfully.\n");
    }
    if (check == 0)
        printf("\n\t\t\tERROR!!Record Not Found..\n");

    printf("\n");
    system("pause");
}

void search_record()
{
    print_title();
    saved_data();

    char flag = 'y';
    do{
        node *c = head, *temp = NULL;
        char name1[100];
        printf("\n\t\t\tEnter Name:");
        scanf("%s", name1);
        printf("\n");
        while (c != NULL){
            if (strcmp(c->name, name1) == 0){
                temp = c;
                break;
            }
            c = c->next;
        }
        if (temp == NULL)
            printf("\t\tRecord Not found!!!\n\n");
        else{
            printf("\n\t\tContact\tName: %s\n", temp->name);
            printf("\n\t\tContact\tMobile_N0: %s\n", temp->phone);
            printf("\n\t\tContact\tE-mail: %s\n", temp->email);
            printf("\n\t\tContact\tADDRESS: %s\n", temp->add);
        }
        getchar();
        printf("Do you want to search more (Y/N) :");
        scanf("%c", &flag);
    } while (flag == 'y' || flag == 'Y');

    printf("\n");
    system("pause");
}

int main()
{

    if ((file = fopen("Contact.txt", "rb+")) == NULL)
    {
        if ((file = fopen("Contact.txt", "w")) == NULL)
        {
            printf("The file can not be opened\n");
        }
    }
    while (1)
    {

        int press;
        printf("\n");
        print_title();

        printf("\t\t [ Main Menu ]\n\n");
        printf("\t\t[1]. Add Records\n");
        printf("\t\t[2]. Display All Contact\n");
        printf("\t\t[3]. Delete Records\n");
        printf("\t\t[4]. Search and View Records\n");
        printf("\t\t[5]. Edit Records\n");
        printf("\t\t[6]. Exit\n");

        int choice;
        printf("\n\t\t\tEnter Option:");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                addrecord();
            }
            break;
            case 2:
            {
                display_contact();
            }
            break;
            case 3:
            {
                deleteee();
            }
            break;
            case 4:
            {
                search_record();
            }
            break;

            case 5:
            {
                edit();
            }
            break;
            case 6:
            {
                system("cls");
                exit(0);
            }
            break;
            default:
            {
                printf("404 NOT FOUND!!!\n");
            }
        }
    }
    return 0;
}