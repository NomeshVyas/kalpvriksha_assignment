#include<stdio.h>

#define MAX 100

typedef struct {
    char id[MAX];
    char age[3];
    char name[MAX];
} User;

User u;

// Utility Functions
int stringCompare(char *str1, char *str2){
    while(*str1 != '\0' && *str2 != '\0'){
        if(*str1 != *str2) return 1;
        str1++;
        str2++;
    }

    if(*str1 != '\0' || *str2 != '\0')
        return 1;

    return 0;
}

int isAlreadyExist(char *id){
    FILE * filePointer = fopen("users.txt", "rb");
    if(!filePointer){
        return 0;
    }
    User temp;
    while(fread(&temp, sizeof(temp), 1, filePointer) > 0)
        if(stringCompare(id, temp.id) == 0){
            fclose(filePointer);
            return 1;
        }

    fclose(filePointer);
    return 0;
}

// CRUD Functions
void createNewUser(){
    printf("\nEnter User ID : ");
    scanf("%s", u.id);
    while(isAlreadyExist(u.id)){
        printf("\nGiven ID is already exist, user another one : ");
        scanf("%s", u.id);
    }

    FILE * filePointer = fopen("users.txt", "ab+");
    if(!filePointer){
        printf("Error : The file not found...");
        return;
    }

    printf("Enter User's Name : ");
    getchar();      // It will clear the Input Buffer
    scanf("%[^\n]%*c", u.name);
    printf("Enter user's Age : ");
    scanf("%s", u.age);
    

    fwrite(&u, sizeof(u), 1, filePointer);
    printf("\n%s as user added successfully.\n", u.name);

    fclose(filePointer);
}

void displayAllUsers(){
    FILE * filePointer = fopen("users.txt", "rb");
    if(!filePointer){
        printf("Error : The file not found...");
        return;
    }

    printf("\n----User Details Dashboard----\n");
    printf("UserID\t\t\tUserName\t\t\tAge\n");

    while(fread(&u, sizeof(u), 1, filePointer) == 1)
        printf("%s\t\t\t%s\t\t\t%s\n", u.id, u.name, u.age);

    printf("\n\nPress any key to go on main menu : ");
    char next;
    scanf("%c", &next);
    fclose(filePointer);
}

void searchUser(){
    FILE * filePointer = fopen("users.txt", "rb");
    if(!filePointer){
        printf("Error : The file not found...");
        return;
    }

    int found = 0;
    char id[MAX];
    printf("\nEnter the User ID which you want to search : ");
    scanf("%s", id);

    while(fread(&u, sizeof(u), 1, filePointer) > 0 && found == 0){
        if(!stringCompare(id, u.id)){
            found = 1;
            printf("User found successfully ->\n");
            printf("UserID : %s, Name : %s, Age : %s\n", u.id, u.name, u.age);
            break;
        }
    }
    if(found == 0) printf("User not found...!\n");
    fclose(filePointer);
}

void deleteUser(){
    FILE * filePointer = fopen("users.txt", "rb");
    if(!filePointer){
        printf("Error : The file not found...");
        return;
    }

    char delId[MAX];
    printf("Enter UserID which data you want to delete : ");
    scanf("%s", delId);
    

    int found = 0;
    FILE* tempfilePointer = fopen("tempUser.txt", "wb");
    while(fread(&u, sizeof(u), 1, filePointer) == 1){
        if(stringCompare(delId, u.id) != 0)
            fwrite(&u, sizeof(u), 1, tempfilePointer);
        else
            found = 1;
    }

    fclose(filePointer);
    fclose(tempfilePointer);

    remove("users.txt");
    if(found == 0) printf("\nNo such record found...\n");
    else printf("\nUser Deleted Successfully...\n");
    rename("tempUser.txt", "users.txt");
}

void updateUser(){
    char userId[MAX];
    int found = 0;
    printf("\nEnter UserID which data u want to edit : ");
    scanf("%s", userId);

    FILE* filePointer =fopen("users.txt", "rb+");
    if(!filePointer){
        printf("Error : The file not found...");
        return;
    }

    FILE* tempfilePointer = fopen("temp.txt", "wb+");
    if(!tempfilePointer){
        printf("Error : The file not found...");
        return;
    }

    while(fread(&u, sizeof(u), 1, filePointer) == 1){
        if(stringCompare(userId, u.id) == 0){
            found = 1;
            printf("Previously Stored record ->\n");
            printf("UserID : %s, Name : %s, Age : %s\n", u.id, u.name, u.age);

            printf("Now enter the new details -> \n");

            printf("\nEnter Correct Name : ");
            getchar();          // It will clear the Input Buffer
            scanf("%[^\n]%*c", u.name);
            
            printf("\nEnter Correct Age : ");
            scanf("%s", u.age);
            
            fwrite(&u, sizeof(u), 1, tempfilePointer);
            printf("\nRecord Updated Successfully...");
        } else {
            fwrite(&u, sizeof(u), 1, tempfilePointer);
        }
    }

    fclose(filePointer);
    fclose(tempfilePointer);
    remove("users.txt");
    if(found == 0) printf("\nRecord Not Found...\n");
    rename("temp.txt", "users.txt");
}

void userManageSystem(){
    printf("---- User Management System with CRUD Operations ----\n");

    while(1){
        int op;
        printf("\n1. Create a new user in records.\n");
        printf("2. Display all users from records.\n");
        printf("3. Search a user from UserID.\n");
        printf("4. Update an existing user from records.\n");
        printf("5. Delete an existing user from records.\n");
        printf("6. Exit.\n");
        printf("Select required operation as number 1 to 6 : ");
        scanf("%d", &op);

        switch (op){
            case 1:
                createNewUser();
                break;
            case 2:
                displayAllUsers();
                break;
            case 3:
                searchUser();
                break;
            case 4:
                updateUser();
                break;
            case 5:
                deleteUser();
                break;
            case 6:
                printf("\nExiting...");
                return;
            default:
                printf("\nDid not match with available options...");
        }
        printf("\n\n");
    }
}

// Main Function
int main(){
    userManageSystem();
    return 0;
}

// Key Note :- 
// 1. For input string with space use scanf("%[^\n]%*c"), scanf("%s") with skip string after space
// 2. fflush for clear input buffer for prevent unwanted stored input
// 3. we are using binary format for maintain user database in users.txt for structured format using User structure