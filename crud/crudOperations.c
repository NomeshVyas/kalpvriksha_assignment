#include<stdio.h>
#include<string.h>

#define MAX 100

typedef struct {
    char id[MAX];
    char age[3];
    char name[MAX];
} User;

User u;

// Utility Functions
int isAlreadyExist(char id[]){
    FILE * fp = fopen("sample.txt", "rb");
    if(!fp){
        return 0;
    }
    User temp;
    while(fread(&temp, sizeof(temp), 1, fp) > 0)
        if(strcmp(id, temp.id) == 0){
            fclose(fp);
            return 1;
        }

    fclose(fp);
    return 0;
}

// CRUD Functions
void createNewUser(){
    printf("\nEnter User ID : ");
    scanf("%s", &u.id);
    while(isAlreadyExist(u.id)){
        printf("\nGiven ID is already exist, user another one : ");
        scanf("%s", &u.id);
    }

    FILE * fp = fopen("sample.txt", "ab+");
    if(!fp){
        printf("Error : The file not found...");
        return;
    }

    printf("Enter User's Name : ");
    scanf("%s", &u.name);
    printf("Enter user's Age : ");
    scanf("%s", &u.age);

    // fprintf(fp, "%s\t\t%s\t\t%s\n", u.id, u.name, u.age);
    fwrite(&u, sizeof(u), 1, fp);
    printf("\n%s as user added successfully.\n", u.name);

    fclose(fp);
}

void displayAllUsers(){
    FILE * fp = fopen("sample.txt", "rb");
    if(!fp){
        printf("Error : The file not found...");
        return;
    }

    printf("\n----User Details Dashboard----\n");
    printf("UserID\t\tUserNmae\tAge\n");

    while(fread(&u, sizeof(u), 1, fp) == 1)
        printf("%s\t\t%s\t\t%s\n", u.id, u.name, u.age);

    fclose(fp);
}

void searchUser(){
    FILE * fp = fopen("sample.txt", "rb");
    if(!fp){
        printf("Error : The file not found...");
        return;
    }

    int found = 0;
    char id[MAX];
    printf("\nEnter the User ID which you want to search : ");
    scanf("%s", id);

    while(fread(&u, sizeof(u), 1, fp) > 0 && found == 0){
        if(!strcmp(id, u.id)){
            found = 1;
            printf("User found successfully ->\n");
            printf("UserID : %s, Name : %s, Age : %s\n", u.id, u.name, u.age);
        }
    }
    if(found == 0) printf("User not found...!\n");
    fclose(fp);
}

void deleteUser(){
    FILE * fp = fopen("sample.txt", "rb");
    if(!fp){
        printf("Error : The file not found...");
        return;
    }

    char delId[MAX];
    printf("Enter UserID which data you want to delete : ");
    scanf("%s", delId);

    int found = 0;
    FILE* tempFp = fopen("tempUser.txt", "wb");
    while(fread(&u, sizeof(u), 1, fp) == 1){
        if(strcmp(delId, u.id) != 0)
            fwrite(&u, sizeof(u), 1, tempFp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(tempFp);

    remove("sample.txt");
    if(found == 0) printf("\nNo such record found...\n");
    else printf("\nUser Deleted Successfully...\n");
    rename("tempUser.txt", "sample.txt");
}

void updateUser(){
    char userId[MAX];
    int found = 0;
    printf("\nEnter UserID which data u want to edit : ");
    scanf("%s", userId);

    FILE* fp =fopen("sample.txt", "rb+");
    if(!fp){
        printf("Error : The file not found...");
        return;
    }

    while(fread(&u, sizeof(u), 1, fp) == 1 && found == 0){
        if(strcmp(userId, u.id) == 0){
            found = 1;
            printf("Previously Stored record ->\n");
            printf("UserID : %s, Name : %s, Age : %s\n", u.id, u.name, u.age);

            printf("Now enter the new details -> \n");
            fflush(stdin);

            printf("\nEnter Correct Name : ");
            scanf("%s", &u.name);
            printf("\nEnter Correct Age : ");
            scanf("%s", &u.age);
            fseek(fp, -(long)sizeof(u), 1);
            fwrite(&u, sizeof(u), 1, fp);
            printf("\nRecord Updated Successfully...");
        }
    }

    if(found == 0) printf("\nRecord Not Found...\n");
    fclose(fp);
}

// Main Function
int main(){

    printf("---- User Management System with CRUD Operations ----\n");
    int on = 1;

    while(on){
        printf("\n1. Create a new user in records.\n");
        printf("2. Display all users from records.\n");
        printf("3. Search a user from UserID.\n");
        printf("4. Update an existing user from records.\n");
        printf("5. Delete an existing user from records.\n");
        printf("6. Exit.\n");

        int op;
        printf("Select required operation as number 1 to 5 : ");
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
            return 0;
        default:
            printf("\nDid not match with available options...");
            break;
        }

        printf("\nPress 1 for Main menu or 0 for exit : ");
        scanf("%d", &on);
        if(!on) return 0;
    }

    return 0;
}