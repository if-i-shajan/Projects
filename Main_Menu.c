#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    char stu_class[5];
    int roll;
    char book_name[50];
    char date[15];
} s;

FILE *fp;

int main()
{
    int ch;
    while (1)
    {
        system("cls");
        printf("\n\n");
        printf("\t\t\t***********************************************\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t*        ----------------------------         *\n");
        printf("\t\t\t*             WELCOME TO LIBRARY              *\n");
        printf("\t\t\t*        ----------------------------         *\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t***********************************************\n");
        printf("\n\n");
        printf("\t\t\t***********************************************\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t*   ---------------------------------------   *\n");
        printf("\t\t\t*      DAFFODIL INTERNATIONAL UNIVERSITY      *\n");
        printf("\t\t\t*   ---------------------------------------   *\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t*             Birulia,Savar,Dhaka             *\n");
        printf("\t\t\t*   Email: librarian@daffodilvarsity.edu.bd   *\n");
        printf("\t\t\t*                                             *\n");
        printf("\t\t\t***********************************************\n");
        printf("1. Add Book\n");
        printf("2. View Book List\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. View Issued Book List\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: \n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
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
        default:
            printf("Invalid Choice...Enter the right one!!\n\n");
        }
        printf("\n\nPress any key to continue...");
        getch();

        system("cls");
    }
    return 0;
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

    printf("Enter Book ID: \n");
    scanf("%d", &b.id);
    getchar(); // Consume newline character left in the input buffer

    printf("Enter Book name: \n");
    fgets(b.book_name, sizeof(b.book_name), stdin);
    b.book_name[strcspn(b.book_name, "\n")] = '\0';

    printf("Enter Author name: ");
    fgets(b.author_name, sizeof(b.author_name), stdin);
    b.author_name[strcspn(b.author_name, "\n")] = '\0';

    printf("Book Added Successfully!\n");
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

// VIEW BOOK LIST
void view_book_list()
{
    system("cls");
    printf("\t\t\t*************** Available Books ***************\n\n");
    printf("\t %-20s \t %-20s \t %-20s \t %s\n\n", "Book ID", "Book Name", "Author", "Date");

    fp = fopen("book.txt", "rb");

    if (fp == NULL)
    {
        printf("No Books available!\n");
        return;
    }
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("%-10s %-20s %-20s %s\n", b.id, b.book_name, b.author_name, b.date);
    }

    fclose(fp);
}

// REMOVE BOOK
void remove_book()
{
    int id, f = 0;
    system("cls");
    printf("***************** Remove Book *****************");
    printf("Enter ID to Remove Book: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("tmp.txt", "wb");

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

    if (f == 1)
    {
        printf("\n\nBook remove successfully!");
    }
    else
    {
        printf("\n\nNo Book found!");
    }
    fclose(fp);
    fclose(ft);

    remove("book.txt");
    rename("tmp.txt", "books.txt");
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
    system("cls");
    printf("***************** Issue Books *****************");
    printf("Enter Book ID to Issue: \n");
    scanf("%d", &s.id);

    fp = fopen("books.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (b.id == s.id)
        {
            strcpy(s.book_name, b.book_name);
            f = 1;
            break;
        }
    }

    if (f == 0)
    {
        printf("No Book found with this ID!\n");
        printf("Please try again..,\n");
        return;
    }

    fp = fopen("issue.txt", "ab");
    printf("Enter Student Name: \n");
    fflush(stdin);
    gets(s.stu_name);

    printf("Enter Strudent Class: \n");
    fflush(stdin);
    gets(s.stu_class);

    printf("Enter Student Roll: ");
    scanf("%d", &s.roll);

    fwrite(&s, sizeof(b), 1, fp);
    fclose(fp);
}

// VEIW ISSUE BOOK LIST
void view_issue_book_list()
{
    system("cls");
    printf("\t\t\t*************** Issued Book List ***************\n\n");
    printf("\t %-20s \t %-20s \t %-20s \t %-20s \t %s\n\n", "s.id", "Name", "Claas", "Roll", "Book_name", "Date");

    fp = fopen("issue.txt", "rb");

    if (fp == NULL)
    {
        printf("No Books available!\n");
        return;
    }
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("\t %-20d \t %-20s \t %-20s \t %-20s \t %s\n\n", s.id, s.stu_name, s.stu_class, s.roll, s.book_name, s.date);
    }

    fclose(fp);
}
