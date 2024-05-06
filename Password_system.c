#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_LOGIN_ATTEMPTS 3
#define MAX_ID_LENGTH 10
#define MAX_PASSWORD_LENGTH 10

// Function prototypes
void password();
void heading();

// Password struct
struct User
{
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

// Main function
int main()
{
    password();
    return 0;
}

// Function to display heading
void heading()
{
    system("cls");
    printf("\n\n\t\t********************Welcome to Daffodil International University Library********************\n");
    fflush(stdin);
    getchar();
}

// Function to validate login
void password()
{
    heading();
    // Define usernames and passwords
    struct User users[MAX_USERS] = {{"shajan813", "shajan"}, {"user2", "password2"}, {"user3", "password3"}, {"user4", "password4"}, {"user5", "password5"}};
    // Input your password here mates
    char input_id[MAX_ID_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];
    int attempts = 0;

    do
    {
        printf("\n \t\t Enter ID: ");
        scanf("%s", input_id);

        printf("\n \t\t Enter Password: ");
        int i = 0;
        char ch;
        // Input password without displaying characters
        while (1)
        {
            ch = getch();
            if (ch == '\r') // Enter key
            {
                input_password[i] = '\0';
                break;
            }
            else if (ch == '\b') // Backspace key
            {
                if (i > 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
            else
            {
                input_password[i] = ch;
                printf("*"); // Display '*' instead of characters
                i++;
            }
        }

        int user_index;
        int found = 0;
        for (user_index = 0; user_index < MAX_USERS; user_index++)
        {
            if (strcmp(users[user_index].id, input_id) == 0)
            {
                found = 1;
                break;
            }
        }

        if (found && strcmp(users[user_index].password, input_password) == 0)
        {
            printf("\n\n \t\t Login Successful!\n");
            printf("\n\n \t\t Welcome, %s!\n", users[user_index].id);
            printf("\n \t\t Press any key..\n");
            break;
        }
        else
        {
            attempts++;
            printf("\n\n \t\t Invalid ID or Password!\n");
            printf("\n\n \t\t Remaining Attempts: %d\n", MAX_LOGIN_ATTEMPTS - attempts);
            if (attempts >= MAX_LOGIN_ATTEMPTS)
            {
                printf("\n\n \t\t Exceeded maximum login attempts. Please, Try again later!\n");
                exit(0);
            }
        }
    } while (attempts < MAX_LOGIN_ATTEMPTS);
    fflush(stdin);
    getchar();
}
