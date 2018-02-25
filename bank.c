#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <conio.h>


// define ASCII values of terms to be used in function passwords

#define ENTER 13
#define SPACE 32
#define BACKSPACE 8
#define TAB 9

/*Global variables */

char password[256];
int value;
FILE *fptr;

/*Structure containing all the user definition members
    structure variable user declared here*/

typedef struct user_info{

    int acc_no;
    char firstname[25];
    char lastname[25];
    char password[256];
    float balance;
}User;

User user;

//function prototyping 

float withdraw(float balance);
float deposit(float balance);
float transfer(float balance);
void balance(float balance);
void login(void);
void sign_up(void);

void clrscr(void){

    system("cls");

    return;
}

void invalid(void){                                                                                          //function invalid input upside_down definition
    clrscr();
    printf("Invalid Option.\a\n");
    printf("Exiting...");
    sleep(3);
    clrscr();
    exit(1);
    return;
}

void exits(void){                                                                                             //function exit program upside_down definition
    clrscr();
    printf("Exiting...");
    puts("\n\nThank You for using Kitengela Banking Systems.");
    sleep(3);
    clrscr();
    exit(1);

}

void passwords(void){                                                                                   //passwords upside_down definition
    
    fflush(stdin);
    char c;
    int i = 0;
    static int g = 0;
    
                                                                                                    /*if statement to change prompt message from 'enter password' to 'confirm password'
                                                                                                        variable g has been incremented in other parts of the program*/

    if(g > 0){

        printf("Confirm Password\n");
    }
    else if(g == 0){

        printf("Enter password\n");
    }

    while(1){

        fflush(stdin);
        c = getch();

        if(c == ENTER){
           
                                                                                                        /*if character entered is of ASCII value 13
                                                                                                            as defined above
                                                                                                                puts the value of element i in the password array as an end of line character*/
            
            if(g > 0){
                password[i] = '\0';
                printf("\n");
            }
            
            else if(g == 0){
                user.password[i] = '\0';
                printf("\n");
            }
            
            break;
        }

        else if(c == BACKSPACE){
           
                                                                                                           /*if character entered is of ASCII value 8
                                                                                                            as defined above 
                                                                                                                decrements the i variable and puts a backspace character in the password array*/

            if(i > 0){
            
                i--;
                printf("\b\b");
            }
        }

                                                                                                                /*if character entered is of ASCII value 32 or 9
                                                                                                                    as defined else where in the program
                                                                                                                        continue with the loop*/

        else if((c == TAB)||(c == SPACE)){
            
            continue;
        }

        else{
            
                                                                                                        /*if variable g > 0 store the password in the user.password[] array
                                                                                                            then compare the two passwords with strcmp()
                                                                                                        if g == 0 store the password in the password[] array*/

            if(g > 0){
                user.password[i] = c;
                value = strcmp(password, user.password);
            }
            else{
                password[i] = c;
            }

                                                                                                        //increment var i and print * everytime

            i++;
            printf("*");


        }
    }
    
                                                                                                    //increment static var g after running the passwords() function

    g++;
    return;
}


int main(){



    int choice;
    int acc_num;
    char pin[25];
    int g = 0;
    int m;

                                                                                                    /*check if the file bank.txt exists
                                                                                                        if not create it using the fptr FILE pointer declared else where as a global pointer
                                                                                                            if it does exist open it for appending
                                                                                                    */

    if((fptr = fopen("bank.txt","r")) == NULL){

        fptr = fopen("bank.txt","w");

        fprintf(fptr,"User_info");
    }

    else{
         
         fptr  = fopen("bank.txt","a");
    }

    clrscr();
    printf("WELCOME TO KITENGELA BANKING SYSTEM.\n");
    sleep(1);
                                                                                                    //prompt user to login or sign_up

    printf("\n1.\tLogin\n2.\tSign Up\n");
    scanf("%d",&m);

    if(m==1){
        clrscr();
        login();
    }

    else if(m==2){
        clrscr();
        sign_up();
    }

    else{
       invalid();
    }
    
     /*
     if the strcmp() returns a 0 value to show that passwords match
             print the user details and proceed with program
         else die with error  
     */

    if(value == 0){

        clrscr();
        LOOP:                                                                                         //goto label

        printf("\nName:\t\t%s%sAccNo:\t\t%d\nBalance:\t$%.2f\n",user.firstname, user.lastname, user.acc_no, user.balance);
        printf("%s",user.lastname);
            
             // give banking options to the user as many times as they want them
            
            do{

                puts("\n\n1.\tWithdraw Money");
                puts("2.\tDeposit Money");
                puts("3.\tCheck Balance");
                puts("4.\tTransfer Money");
                puts("5.\tExit");
                scanf("%d",&choice);

                switch(choice){

                case 1:{


                    user.balance = withdraw(user.balance);

                    break;
                }

                case 2:{ 

                    user.balance = deposit(user.balance);

                    break;
                }

                case 3:{
                    balance(user.balance);

                    break;
                }

                case 4:{
                    user.balance = transfer(user.balance);

                    break;
                }
                case 5:{
                    exits();

                    break;
                }

                default:{
                    printf("Invalid Option\n");
                    sleep(2);
                    clrscr();
                    goto LOOP;

                    break;
                }
                    }
                                                                                                //print new balance of the user and prompt them to run more banking services

                printf("\nYour new balance is:\n$%.2f",user.balance);
    
                printf("\nwould you like to do another transaction?\n0.\t NO\n1.\tYES\n");
                scanf("%d",&g);
                clrscr();
    
            }
        
                                                                                                //do while

        while(g==1);
        
    }
                                                                                                // if value != 0 
    else if(value != 0){
        
        fflush(stdin);
        clrscr();
        int q;
        printf("\npasswords don't match.\a\n");
        printf("1.\tTry again\n2.\tExit\n");
        scanf("%d",&q);
        if(q == 1){
            clrscr();
            main();                                                                            //recursion of the main function
        }
        else if(q == 2){
            exits();
        }
        else{
            invalid();
        }
    
    }
    
                                                                                                /*
                                                                                                finally
                                                                                                    in conclusion print the users new balance to the file
                                                                                                        close file pointer
                                                                                                            return 0
                                                                                                */
        clrscr();
        puts("\n\nThank You for using Kitengela Banking Systems.");
        sleep(5);
        clrscr();
        fprintf(fptr,"\n%.2f",user.balance);
        fclose(fptr);

    return (0);

}

float withdraw(float balance){                                                                //withdraw function definition
    clrscr();
     float amount;
     float transaction_fee = 45;

    printf("\nPlease Enter Amount to Withdraw:\n$");
    scanf("%f",&amount);

    if(balance>=(amount+transaction_fee)){
        
        balance-=(amount+transaction_fee);
    }

    else{

        printf("\nYou have insufficient balance.\nBalance:$%.2f\a",balance);
    }

    printf("You have successfully withdrawn $%.2f from your account.",amount);
    printf("\nTransaction cost $%.2f",transaction_fee);

    return(balance);
}

 float deposit(float balance){                                                               //deposit function definition
    clrscr();
    int amount;

    printf("Please Enter the amount to deposit:\n$");
    scanf("%d",&amount);

    balance+=amount;
    printf("You have successfully deposited $%d into your account.",amount);

    return(balance);
}

  void balance(float balance){                                                              //balance function definition
    clrscr();
    float value;

    printf("Your outstanding balance is:$%.2f",balance);

    return;
    }

  float transfer(float balance){                                                            //transfer function definition
    clrscr();
    int new_acc;
    int amount;
    float transaction_fee = 45;

     printf("Enter account to transfer to:");
     scanf("%d",&new_acc);

    printf("\nPlease Enter Amount to transfer:\n$");
    scanf("%d",&amount);

    if(balance>=(amount+transaction_fee)){
        balance-=(amount+transaction_fee);

        printf("You have successfully transfered $%d to account number %d\n",amount ,new_acc);
        printf("Transaction cost $%.2f",transaction_fee);
    }

    else{

        printf("\nYou have insufficient balance.\nBalance:%.2f",balance);
    }

        return(balance);
}

void login(void){                                                                           //login function definition
    clrscr();
    FILE *f3ptr;
    f3ptr = fopen("bank.txt", "r");
    int linecount = 0;
    char singlelines[256];
    int temp, w, value2;
    int i = 0;
    char buffer[256];


    printf("Enter Your account number:\n");
    scanf("%d",&user.acc_no);
    
    while(!feof(f3ptr)){
        fgets(singlelines, sizeof(singlelines), f3ptr);
        linecount++;
        if(isdigit(singlelines[0])){
            temp = atoi(singlelines);

            if(temp == user.acc_no){
                for(i = 0; i <= 2; i++){
                    if(i == 0){
                        fgets(user.firstname, sizeof(user.firstname), f3ptr);
                    }
                    
                    if(i == 1){
                        fflush(stdin);
                        fscanf(f3ptr,"%s",user.lastname);
                   }
                   
                    if(i == 1){
                        fflush(stdin);
                        fscanf(f3ptr,"%s",user.password);
                    }
                    if(i == 2){
                        fgets(buffer, sizeof(buffer), f3ptr);
                        user.balance = atof(buffer);
                        break;
                    }
                }

            }
            else{
                continue;
            }
        }
        else{
            continue;
        }

        if(feof(f3ptr)){
            break;
            printf("Account doesn't exist\n1.\tCreate Account\n2.\tExit");
            scanf("%d",w);
            if(w == 1){
                clrscr();
                sign_up();
            }
            else if(w == 2){
                exits();
            }
            else{
                invalid();
            }
        }
    }

    passwords();

    value2 = strcmp(user.password, password);
    
    if(value2 == 0){
        printf("Please Wait...\n");
        sleep(2);
    }
    else if(value2 != 0){
        fflush(stdin);
        clrscr();
        int q;
        printf("\npasswords don't match.\a\n");
        printf("password is %s\n",user.password);
        printf("1.\tTry again\n2.\tExit\n");
        scanf("%d",&q);
        if(q == 1){
            clrscr();
            login();                                                                            //recursion of the login function
        }
        else if(q == 2){
            exits();
        }
    }
    
    
    return;
}

void sign_up(void){
    clrscr();
    fflush(stdin);
    int number;
    int b;
    int temp;
    FILE *f2ptr;
    f2ptr = fopen("bank.txt", "r");                                                         //open the bank.txt file for reading
    char singleline[256];
    
    printf("Enter your account number:\n");                                                       //prompt for user account 
    scanf("%d",&user.acc_no);
    if(isalpha(user.acc_no)){
        printf("Account number must be in numerics!\a\n");
        sleep(3);
        clrscr();
        sign_up();
    }
    
    while(!feof(f2ptr)){                                                                    //create loop to scan through the entire file storing output in char buffer singleline
        fgets(singleline, sizeof(singleline), f2ptr);
        
                                                                                                /*if the contents of the single line buffer are integers 
                                                                                            go ahead and compare them to the account number entered by the user*/
        
        if(isdigit(singleline[0])){
            temp = atoi(singleline);
            if(temp == user.acc_no){
                clrscr();
                printf("Account already exists\n\a");
                printf("1.\tChange Account number\n2.\tLogin\n");
                scanf("%d",&b);
                if(b == 1){
                    sign_up();
                    break;
                }
                else if(b == 2){
                    login();
                    break;
                }
                else{
                    invalid();
                }
            }
            else{
                continue;
                }
        }
        else{
            continue;
        }

        if(feof){
            break;
        }
    }

    printf("Enter your first name:\n");
    scanf("%s",&user.firstname);
    printf("Enter your last name:\n");
    scanf("%s",&user.lastname);
    passwords();
    passwords();
     
    fprintf(fptr,"\n\n%d",user.acc_no);
    fprintf(fptr,"\n%s\n%s",user.firstname,user.lastname);
    fprintf(fptr,"\n%s",user.password);

    return;

}