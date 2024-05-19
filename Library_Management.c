#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h> // For getch()

#define MAX_USERS 5
#define MAX_LOGIN_ATTEMPTS 3
#define MAX_ID_LENGTH 10
#define MAX_PASSWORD_LENGTH 10

struct books
{
    int id;
    char book_name[50];
    char author_name[50];
    char date[15];
} b;

struct student
{
    int id;
    char stu_name[50];
    char stu_semester[5];
    int roll;
    char book_name[50];
    char date[15];
} s;

FILE *fp;

void add_initial_books();
int login();
void heading();
void menu();
void add_book();
void view_book_list();
void remove_book();
void issue_book();
void view_issue_book_list();
void remove_issued_book();

int main()
{
    add_initial_books();

    int k = login();
    if (k == 1)
    {
        printf("Login Successfully!!");
        heading();
        menu();
    }
    else
    {
        printf("\nTry again...");
    }

    return 0;
}

struct User
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int login()
{
    char username[20];
    char userpass[11];
    int i;
    printf("Please Login Here!!\n");
    printf("Enter your User ID : ");
    scanf("%s", username);

    printf("Enter your User Password : ");
    for (i = 0; i < 5; i++)
    {
        userpass[i] = getch();
        printf("*");
    }
    userpass[i] = '\0';

    if (!strcmp(username, "admin") && !strcmp(userpass, "admin"))
    {
        printf("\n\nLogged in Successfully\n");
        return 1;
    }
    else
    {
        printf("\n\nIncorrect username or password");
        return 0;
    }
}

// Function to display heading
void heading()
{
    system("cls");
    printf("\n\n");
    printf("\t\t\t***********************************************\n");
    printf("\t\t\t*                                             *\n");
    printf("\t\t\t*        ----------------------------         *\n");
    printf("\t\t\t*             WELCOME TO LIBRARY              *\n");
    printf("\t\t\t*        ----------------------------         *\n");
    printf("\t\t\t*                                             *\n");
    printf("\t\t\t***********************************************\n");
    printf("\n\n");
    printf("\t\t\t***********************************************\n");
    printf("\t\t\t*      DAFFODIL INTERNATIONAL UNIVERSITY      *\n");
    printf("\t\t\t*             Birulia, Savar, Dhaka           *\n");
    printf("\t\t\t*   Email: librarian@daffodilvarsity.edu.bd   *\n");
    printf("\t\t\t***********************************************\n");
}

// Function to display menu
void menu()
{
    int ch;
    while (1)
    {
        heading();
        printf("1. Add Book\n");
        printf("2. View Book List\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. View Issued Book List\n");
        printf("6. Remove Issued Book\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            printf("Thank You!!!");
            exit(0);
        case 1:
            add_book();
            break;
        case 2:
            view_book_list();
            break;
        case 3:
            remove_book();
            break;
        case 4:
            issue_book();
            break;
        case 5:
            view_issue_book_list();
            break;
        case 6:
            remove_issued_book();
            break;
        default:
            printf("Invalid Choice... Enter the right one!!\n\n");
        }
        printf("\n\nPress any key to continue...");
        getch();
    }
}

// Function to add initial books if the file is empty
void add_initial_books()
{
    fp = fopen("books.txt", "rb");
    if (fp == NULL || fgetc(fp) == EOF)
    {
        if (fp != NULL)
            fclose(fp);

        fp = fopen("books.txt", "wb");
        if (fp == NULL)
        {
            printf("Error opening file!\n");
            return;
        }

        struct books initial_books[10] = {
            {1, "To Kill a Mockingbird", "Harper Lee", "01/01/2022"},
            {2, "1984", "George Orwell", "02/01/2022"},
            {3, "Pride and Prejudice", "Jane Austen", "03/01/2022"},
            {4, "The Great Gatsby", "F. Scott Fitzgerald", "04/01/2022"},
            {5, "The Catcher in the Rye", "J.D. Salinger", "05/01/2022"},
            {6, "Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "06/01/2022"},
            {7, "The Hobbit", "J.R.R. Tolkien", "07/01/2022"},
            {8, "The Hunger Games", "Suzanne Collins", "08/01/2022"},
            {9, "The Lord of the Rings", "J.R.R. Tolkien", "09/01/2022"},
            {10, "A Game of Thrones", "George R.R. Martin", "10/01/2022"},
        };
        for (int i = 0; i < 10; i++)
        {
            fwrite(&initial_books[i], sizeof(struct books), 1, fp);
        }
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
}

// ADD BOOK
void add_book()
{
    char my_date[15];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(my_date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, my_date);

    fp = fopen("books.txt", "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar(); // Consume newline character left in the input buffer

    printf("Enter Book name: ");
    fgets(b.book_name, sizeof(b.book_name), stdin);
    b.book_name[strcspn(b.book_name, "\n")] = '\0';

    printf("Enter Author name: ");
    fgets(b.author_name, sizeof(b.author_name), stdin);
    b.author_name[strcspn(b.author_name, "\n")] = '\0';

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("Book Added Successfully!\n");
}

// VIEW BOOK LIST
void view_book_list()
{
    heading();
    printf("\n\t\t\t*************** Available Books ***************\n\n");
    printf("\t %-10s \t %-30s \t %-35s \t %s\n\n", "Book ID", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    if (fp == NULL)
    {
        printf("No Books available!\n");
        return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("\t %-10d \t %-30s \t %-35s \t %s\n", b.id, b.book_name, b.author_name, b.date);
    }

    fclose(fp);
}

// REMOVE BOOK
void remove_book()
{
    int id, f = 0;
    heading();
    printf("************* Remove Book *****************\n\n");
    printf("Enter Book ID to Remove: ");
    scanf("%d", &id);

    FILE *ft;
    fp = fopen("books.txt", "rb");
    ft = fopen("tmp.txt", "wb");
    if (fp == NULL || ft == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (id == b.id)
        {
            f = 1;
        }
        else
        {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    if (f == 1)
    {
        remove("books.txt");
        rename("tmp.txt", "books.txt");
        printf("Book removed successfully!\n");
    }
    else
    {
        remove("tmp.txt");
        printf("No Book found!\n");
    }
}

// ISSUE BOOK
void issue_book()
{
    char my_date[15];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(my_date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, my_date);

    int f = 0;
    heading();
    printf("************* Issue Books *****************\n\n");
    printf("Enter Book ID to Issue: ");
    scanf("%d", &s.id);

    fp = fopen("books.txt", "rb");
    if (fp == NULL)
    {
        printf("No Books available!\n");
        return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (b.id == s.id)
        {
            strcpy(s.book_name, b.book_name);
            f = 1;
            break;
        }
    }
    fclose(fp);

    if (f == 0)
    {
        printf("No Book found with this ID!\n");
        printf("Please try again...\n");
        return;
    }

    fp = fopen("issue.txt", "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student Name: ");
    getchar(); // Consume newline character left in the input buffer
    fgets(s.stu_name, sizeof(s.stu_name), stdin);
    s.stu_name[strcspn(s.stu_name, "\n")] = '\0';

    printf("Enter Student Semester: ");
    fgets(s.stu_semester, sizeof(s.stu_semester), stdin);
    s.stu_semester[strcspn(s.stu_semester, "\n")] = '\0';

    printf("Enter Student Roll: ");
    scanf("%d", &s.roll);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Book Issued Successfully!\n");
}

// VIEW ISSUED BOOK LIST
void view_issue_book_list()
{
    heading();
    printf("\t\t\t*************** Issued Book List ***************\n\n");
    printf("\t %-10s \t %-30s \t %-35s \t %-30s \t %-30s \t %s\n\n", "ID", "Name", "Semester", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    if (fp == NULL)
    {
        printf("No Issued Books available!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("\t %-10d \t %-30s \t %-35s \t %-30d \t %-30s \t %s\n", s.id, s.stu_name, s.stu_semester, s.roll, s.book_name, s.date);
    }

    fclose(fp);
}

// REMOVE ISSUED BOOK
void remove_issued_book()
{
    int id, f = 0;
    heading();
    printf("************* Remove Issued Book *****************\n\n");
    printf("Enter Book ID to Remove: ");
    scanf("%d", &id);

    FILE *ft;
    fp = fopen("issue.txt", "rb");
    ft = fopen("tmp.txt", "wb");
    if (fp == NULL || ft == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (id == s.id)
        {
            f = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    if (f == 1)
    {
        remove("issue.txt");
        rename("tmp.txt", "issue.txt");
        printf("Issued Book removed successfully!\n");
    }
    else
    {
        remove("tmp.txt");
        printf("No Issued Book found!\n");
    }
}
