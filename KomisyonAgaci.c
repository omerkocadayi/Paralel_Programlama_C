#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Responsible {
    int id;
    char tc[11];
    char name[50];
    int commissionRate;
    int memberNumbers;
    struct Responsible *members[];
} Responsible;


Responsible admin;
Responsible you;
int idCounter = 0;


void createCompany(){
    admin.id = idCounter;
    strncpy(admin.tc, "33913498336", 11);
    strncpy(admin.name, "Hasan", 50);
    admin.memberNumbers = 0;
    admin.commissionRate = 10;
    idCounter++;

    admin.members[admin.memberNumbers] = (Responsible*) malloc(sizeof(Responsible));
    (admin.members[admin.memberNumbers])->id = idCounter;
    strncpy(admin.members[admin.memberNumbers]->tc, "38958837129", 11);
    strncpy(admin.members[admin.memberNumbers]->name, "Enes", 50);
    (admin.members[admin.memberNumbers])->commissionRate = 10;
    (admin.members[admin.memberNumbers])->memberNumbers = 0;
    admin.commissionRate = 0.1 * (admin.members[admin.memberNumbers])->commissionRate;
    admin.memberNumbers++;
    idCounter++;

    admin.members[admin.memberNumbers] = (Responsible*) malloc(sizeof(Responsible));
    (admin.members[admin.memberNumbers])->id = idCounter;
    strncpy(admin.members[admin.memberNumbers]->tc, "12345678912", 11);
    strncpy(admin.members[admin.memberNumbers]->name, "Mehmet", 50);
    (admin.members[admin.memberNumbers])->commissionRate = 10;
    (admin.members[admin.memberNumbers])->memberNumbers = 0;
    admin.commissionRate = 0.1 * (admin.members[admin.memberNumbers])->commissionRate;
    admin.memberNumbers++;
    idCounter++;

    admin.members[admin.memberNumbers] = (Responsible*) malloc(sizeof(Responsible));
    (admin.members[admin.memberNumbers])->id = idCounter;
    strncpy(admin.members[admin.memberNumbers]->tc, "98765432132", 11);
    strncpy(admin.members[admin.memberNumbers]->name, "Osman", 50);
    (admin.members[admin.memberNumbers])->commissionRate = 10;
    (admin.members[admin.memberNumbers])->memberNumbers = 0;
    admin.commissionRate = 0.1 * (admin.members[admin.memberNumbers])->commissionRate;
    admin.memberNumbers++;
    idCounter++;
}


void registerMember(int session){

    char member_tc[11];
    char member_name[50];
    int member_commissionRate;


    printf("\nTo register member into our system, please enter member's Turkish Identity Number:\n> ");
    scanf("%s", member_tc);
    printf("\n\nPlease enter member's name:\n> ");
    scanf("%s", member_name);
    printf("\n\nPlease enter member's gain in this month:\n> ");
    scanf("%d", &member_commissionRate);


    you.members[you.memberNumbers] = (Responsible*) malloc(sizeof(Responsible));

    /*
    you.members[0] = (Responsible*) malloc(sizeof(Responsible));
    you.members[you.memberNumbers]->id = idCounter;
    strncpy((you.members[0])->name, member_name, 50);
    printf("%s\n\n", ((admin.members[0])->members[0])->name);
    */


    (you.members[you.memberNumbers])->id = idCounter;
    strncpy(you.members[you.memberNumbers]->tc, member_tc, 11);
    strncpy(you.members[you.memberNumbers]->name, member_name, 50);
    (you.members[you.memberNumbers])->commissionRate = member_commissionRate;
    (you.members[you.memberNumbers])->memberNumbers = 0;
    you.memberNumbers++;
    idCounter++;
}


int findMember(char memberName[]){
    int i;

    // If person is admin himself
    if(strcmp(admin.name, memberName) == 0){
        you = admin;
        return admin.id;
    }

    // If person is a root member
    for(i=0; i<admin.memberNumbers; i++){
        if (strcmp(admin.members[i]->name, memberName) == 0){
            you = *admin.members[i];
            return (admin.members[i])->id;
        }
    }

    // If person is a sub member
    // ....

    // If person is not registered
    return -1;
}


int detectDepth(){
    int depth[admin.memberNumbers];
    int i;
    int max_depth;
    Responsible* temp = &admin;

    // Intialize depth variable
    for(i=0;i<admin.memberNumbers;i++){
        depth[i] = 0;
    }

    // Find depths
    for(i=0;i<admin.memberNumbers;i++){

        while(temp->memberNumbers != 0){
            temp = temp->members[i];
            depth[i]++;
        }

    }

    /*
    max_depth = depth[0];   // #=> 1
    printf("%d\n\n", max_depth);
    */

    // Find maximum depth
    for(i=0;i<admin.memberNumbers;i++)
        if( max_depth < depth[i])
            max_depth = depth[i];

    return max_depth;
}


int main()
{
    int connected = 0;
    int answer;
    int session;
    char memberName[50];


    // Creates Amway Company
    createCompany();

    printf("Give me your name (e.g. Hasan or Enes or Mehmet or a not existed name) :\n> ");
    scanf("%s", memberName);

    // Login to system  | e.g. Hasan
    while(!connected){

        session = findMember(memberName);

        // If person is registered
        if( session != -1 ){
            printf("\nDo you want to register any member into system? (1 or 0)\n> ");
            scanf("%d", &answer);

            while(answer){
                registerMember(session);

                printf("\nDo you want to register else member? (1 or 0)\n> ");
                scanf("%d", &answer);
            }
        }
        // If person is not registered
        else{
            printf("\nDo you want to register to our company's network? (1 or 0)\n> ");
            scanf("%d", &answer);

            if(answer){
                printf("Please enter your Turkish Identity Number:\n> ");
                scanf("%s", you.tc);

                printf("\nPlease enter your name:\n> ");
                scanf("%s", you.name);

                admin.members[admin.memberNumbers] = (Responsible*) malloc(sizeof(Responsible));
                strncpy(admin.members[admin.memberNumbers]->tc, you.tc, 11);
                strncpy(admin.members[admin.memberNumbers]->name, you.name, 50);
                admin.members[admin.memberNumbers]->commissionRate = 10;
                admin.memberNumbers++;
            }
        }


        printf("\n\nThe depth of network in Amway is : %d", detectDepth());


        printf("\n\nDo you want to exit from system (1 or 0)\n> ");
        scanf("%d", &connected);
    }


    return 0;
}

