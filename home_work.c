/*Sangmyung university
 *Kyungha Min Prof.
 *student: LUONG DUC ANH
 *data-structure-homework no.1
 *2019/03/09
*/

#include<stdio.h>
#include<string.h>
#define LEN 100

//Structure to store student's information named info
typedef struct{
	char name[20];
	char gender;
	char address[20];
	char dptment[50];
	float grade;
	int height, weight;
}info;

//function prototype
int count(FILE*);
void input(FILE*, info*, int);
void output(info*, int);
void add(FILE*);

//main function
int main(void)
{	
	FILE *fp = fopen("C:\\Users\\Administrator\\Desktop\\data structure\\listt.txt","r+");
	
	/*If the file is invalid, tell user*/	
	if(fp == NULL){
		puts("Can not open file!");
		return -1;
	}
	
	/*count the numbers of student*/
	int num = count(fp);
	
	/*after counting, the pointer will point to the end of file so need resetting the pointer
	to point to the first position of file.*/
	fseek(fp,0,SEEK_SET);
	
	info std[num];//to save the memory source, The elements number of an array, exactly, equal the
				//real number of students.
	int choice;
	int var = 1;//a counter to count how many times user give order.
	
	/*input data and store it in "std" array*/
	input(fp,std,num);
	
	puts("MENU");
	puts("1. Print the result. \n2. Add student. \n0. Exit.");
	
	do{
		if(1 == var)
			puts("\nCan I help you? ^^");
		else
			puts("\nDo you wanna test another one? ^^");
	scanf("%d",&choice);
	
	switch(choice){
		/*Print out data and the number of students*/
		case 1: {
			output(std,num);
			printf("\nThere are total: %d student(s).\n",num);
			break;
			}
		/*Add student*/
		case 2: {
			add(fp);
			break;
			}
		case 0: {
			puts("Thanks for using and have a nice day ^^");
			break;
			}
		default: {
			puts("Sorry, your choice is invalid :(");
			break;
			}
		}//end switch
	var++;
	}while(0 != choice);
}

/*This function is to count the number of students*/
int count(FILE* fp){//take a pointer to a file as an argument
	static int i = 0;//i is a counter and should be stored in data 
	//segment instead of stack segment so that the value of "i" will
	// not be terminated after this function ends.
	char tmp[LEN];
	
	while(fscanf(fp,"%[^\n]%*c",tmp) != EOF)
		i++;//increment i by 1 until end of file
	return i;//return value of i as an integer
}

/*This function stores data to an "info"data-type array*/
void input(FILE *fp, info std[], int num){
	int i = 0;//counter
	
	for(;i < num; i++){//loop with the times equal to the number of students
		fscanf(fp,"%s %c %s %s %f %d %d\n",std[i].name,&std[i].gender,std[i].address,
			std[i].dptment, &std[i].grade,&std[i].height,&std[i].weight);
		//each time,respectively and separately store the detail informations of student
		//to corresponding element.
	}//end for
}//end function

/*This function will print out data that stored in "info"data-type array*/
void output(info std[], int num){
	int i;//counter
	/*printing header*/
	printf("%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n\n","Name","Gender","Address","Department","Grade","Height","Weight");
	
	for(i = 0; i < num; i++){
	/*Respectively print out the data to screen.*/
	printf("%s\t%c\t%s\t\t%s\t%.1f\t%d\t%d\n",std[i].name,std[i].gender,std[i].address,
				std[i].dptment, std[i].grade,std[i].height,std[i].weight);
			}
}//end function

/*This function add new student to the file*/
void add(FILE* fp){
	/*Declaring temporary variables*/
	char tmp[100];
	float tmp2;
	char tmpc;
	int tmp3;
	int tmp4;
	
	/*obviously, new student's informations will be written at the end of file.*/
	fseek(fp,0,SEEK_END);//set the pointer to the end of file.
	
	/*Asking user to enter informations from keyboard*/
	puts("Enter informations of student: ");
	printf("Name: ");
	scanf("%s",tmp);
	fflush(stdin);//because scanf-function doesn't read new-line character, so, to
	//prevent the next scanf-function from reading it, just delete the new-line character.
	fprintf(fp,"\n%s ",tmp);
	
	printf("Gender: ");
	scanf("%c",&tmpc);
	fflush(stdin); //in case user enter too much characters, scanf should read the first
	//character and the rest should be deleted.
	fprintf(fp,"%c ",tmpc);
	
	printf("Address: ");
	scanf("%s",tmp);
	fprintf(fp,"%s ",tmp);
	
	printf("Department: ");
	scanf("%s",tmp);
	fprintf(fp,"%s ",tmp);
	
	printf("Grade Height and Weight: ");
	scanf("%f%d%d",&tmp2,&tmp3,&tmp4);
	fprintf(fp,"%.1f %d %d",tmp2,tmp3,tmp4);
}
