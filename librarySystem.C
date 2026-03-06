#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SizeMember 4
#define SizeBook 8
#define PhoneNumberLeng 11
#define nameLeng 25
#define titleLeng 30
#define authorLeng 30
#define bookIdLeng 6

struct Member
{ // Structure to hold member information
    int memberID;
    char phone[PhoneNumberLeng];
    char name[nameLeng];
};

struct Book // Structure to hold book information
{
    int YearOfPublication;
    int memberID;
    char bookID[bookIdLeng];
    char Title[titleLeng];
    char Author[authorLeng];
};

struct Member members[SizeMember]; // array of membesr
struct Book books[SizeBook];       // array of books
int indexMember = 0;               // count the number of members
int indexBook = 0;                 // count the number of books

void addMember() // funcation for add new member
{
    if (indexMember >= SizeMember) // chack if number of member is reached
    {
        printf("%s", "Cannot add more members, list is full!\n");
        return;
    }
    struct Member *member = &members[indexMember]; // Pointer to the new member
    printf("%s", "Enter your ID, name, phone:\n\nID: ");
    scanf("%d", &member->memberID);

    if (indexMember != 0) // if was the firts member , it will skip the condition
    {
        for (int i = 0; i < indexMember; i++) // chack if ID member is exists by through all members IDs
        {
            if (member->memberID == members[i].memberID)
            {
                printf("%s", "The member ID %d already exists, try with another ID.\n", member->memberID);
                return;
            }
        }
    }

    printf("Your Name: ");
    getchar();
    fgets(member->name, nameLeng, stdin);
    member->name[strcspn(member->name, "\n")] = 0; // replace newline whith null to make it clean whene we print it out

    printf("%s", "Phone (must be 10 numbers): ");
    scanf("%10s", member->phone);

    while (strlen(member->phone) != 10) // check if the phone number is not 10 numbers
    {
        printf("%s", "The phone number is incorrect\n");
        printf("%s", "Phone (must be 10 numbers): ");
        scanf("%10s", member->phone);
    }

    if (indexMember != 0)
    {
        for (int i = 0; i < indexMember; i++) // chake if the phonr number is exist
        {
            if (strcmp(members[i].phone, member->phone) == 0)
            {
                printf("The Phone number %s already exists, try with another number.\n", member->phone);
                return;
            }
        }
    }

    indexMember++; //  add one to the list of books
    printf("%s", "\nThe member has been added successfully!\n");
    sleep(1);
    puts(" ");
}

void addBook() // funcation for add new book
{
    if (indexBook >= SizeBook) // cheke if there is place to add a new book
    {
        printf("Cannot add more books. Maximum limit reached.\n");
        sleep(1);
        return;
    }

    if (indexMember == 0) // check if there is a member in the array
    {
        printf("%s", "There is no member, do you want to add a member? (1. to add, 0 to exit)\n");
        int choose;
        printf("%s", "your choose: ");
        scanf("%d", &choose);
        while (choose != 0 && choose != 1) // check if the choose is 0 or 1
        {
            printf("%s", "Plese choose 1 to add , 0 to exit");
            printf("%s", "your choose: ");
            scanf("%d", &choose);
        }
        if (choose == 1)
            addMember();
        else
        {
            printf("Exiting...\n");
            sleep(1);
            return;
        }
    }

    struct Book *book = &books[indexBook]; // Pointer to the new member
    printf("Enter Book ID, Year Of Publication, Title, Author and choose your ID member:\n");
    sleep(0.5);

    printf("\nChoose the number of your ID member (1 for the first):\n"); // make the user select his ID member
    printf("%-10s     %-27s\n", "ID Members", "Name");
    for (int i = 0; i < indexMember; i++) // print all id member and Their names to make the user choose his ID
    {
        printf("%d-%-10d %-22s\n", i + 1, members[i].memberID, members[i].name);
    }
    puts(" ");
    int choose2 = 0;
    do
    {

        printf("%s", "your choose: ");
        scanf("%d", &choose2);

        switch (choose2) // set the ID member by the user choose
        {
        case 1:
            book->memberID = members[0].memberID;
            break;
        case 2:
            book->memberID = members[1].memberID;
            break;
        case 3:
            book->memberID = members[2].memberID;
            break;
        case 4:
            book->memberID = members[3].memberID;
            break;
        case 5:
            printf("%s", "Exiting...\n");
            sleep(1);
            return;
        }
        if (choose2 > indexMember || choose2 < 1) // check if the user enter a rong number
            printf("%s", "the number is out of range, try again or 5 to exit\n");
    } while (choose2 < 1 || choose2 > indexMember);

    printf("Book ID (Max 5 digits): ");
    scanf("%5s", book->bookID);
    while (strlen(book->bookID) != 5) // check if the user input highter o less number than 5
    {
        printf("The book ID must be exactly 5 digits!\n");
        printf("Book ID: ");
        scanf("%5s", book->bookID);
    }

    if (indexBook != 0)
    {
        for (int i = 0; i < indexBook; i++) // check if the book is already taken
        {
            int bookID2 = atoi(book->bookID);    // transformation book id from char to int for comparison
            int bookID1 = atoi(books[i].bookID); // transformation book id from char to int for comparison
            if (bookID1 == bookID2)
            {
                printf("The book is had taken by anouther member please try anouther book\n");
                puts(" ");
                return;
            }
        }
    }

    printf("Year Of Publication: ");
    scanf("%d", &book->YearOfPublication);
    while (book->YearOfPublication < 1980 || book->YearOfPublication > 2024) // check if the year between 1980 and 2024
    {
        printf("The year of publication must be between 1980 - 2024\n");
        sleep(0.5);
        printf("Year Of Publication: ");
        scanf("%d", &book->YearOfPublication);
    }

    printf("Title: ");
    getchar();
    fgets(book->Title, titleLeng, stdin);
    book->Title[strcspn(book->Title, "\n")] = 0; // Remove newline from the title to print the information clearly

    printf("Author name: ");
    fgets(book->Author, authorLeng, stdin);
    book->Author[strcspn(book->Author, "\n")] = 0; // Remove newline from the Author name to print the information clearly

    indexBook++; // add one to the list of books
    printf("\nThe book has been added successfully!\n");
    sleep(1);
    puts(" ");
}

void printMembers() // function to display members information
{
    if (indexMember == 0) // check if there are any members
    {
        printf("There are no members, do you want to add a member? (1. to add, 0 to exit)\n");
        int choose;
        scanf("%d", &choose);
        if (choose == 1)
        {
            addMember();
            return;
        }
        else if (choose == 0)
        {
            printf("Exiting...\n");
            sleep(1);
            return;
        }
    }

    printf("Wait a few seconds...\n\n");
    sleep(1.5);
    printf("%-10s %-25s %-15s\n", "Member ID", "Name", "Phone");
    printf("%-10s %-25s %-15s\n", "---------", "-------------------------", "---------------");

    for (int i = 0; i < indexMember; i++)
    {
        printf("%-10d %-25s %-15s\n", members[i].memberID, members[i].name, members[i].phone);
    }
    puts(" ");
}

void printBooks() // function to display books information
{
    if (indexBook == 0) // check if there are any books
    {
        printf("There are no books, do you want to add a book? (1. to add, 0 to exit)\n");
        int choose;
        scanf("%d", &choose);
        if (choose == 1)
        {
            addBook();
            return;
        }
        else if (choose == 0)
        {
            printf("Exiting...\n");
            sleep(1);
            return;
        }
    }

    printf("Wait a few seconds...\n\n");
    sleep(1.5);
    printf("%-10s %-10s %-30s %-30s %-10s\n", "Year", "Book ID", "Title", "Author", "Member ID");
    printf("%-10s %-10s %-30s %-30s %-10s\n", "----", "-------", "------------------------------", "------------------------------", "---------");

    for (int i = 0; i < indexBook; i++)
    {
        printf("%-10d %-10s %-30s %-30s %-10d\n", books[i].YearOfPublication, books[i].bookID, books[i].Title, books[i].Author, books[i].memberID);
    }
    puts(" ");
}

int main()
{
    int inputChoice;

    printf("Choose one of the following options:\n");

    do
    {
        printf("1 - to add a new member\n"
               "2 - to add a new book\n"
               "3 - to print all members' information\n"
               "4 - to print all books' information\n"
               "5 - to Exit\n"
               "\nChoose: ");
        scanf("%d", &inputChoice);
        puts(" ");

        switch (inputChoice)
        {
        case 1:
            addMember();
            break;
        case 2:
            addBook();
            break;
        case 3:
            printMembers();
            break;
        case 4:
            printBooks();
            break;
        case 5:
            printf("Exiting...\n");
            sleep(1);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (inputChoice != 5);

    return 0;
}