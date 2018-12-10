/*practice 5: student management
 *Shawnadl - prac5.c
 *2018.12.10
 *Sangmyung university*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10
int freg[6];//global array for using in both main and input function
			//to count the freqence of type A,B,C... freg[0] = A,
			//freg[1] = B, freg[2] = C, freg[3] = D, freg[5] = F(skip freg[4])

typedef struct{//Structure declaration to store necessary informations in the members.
	char name[30];//store name
	char id[10];//store id
	int midterm;//store midterm exam grade
	int final;//store final exam grade
	int practice;//store practice grade
	int homework;//store homework grade
	int average;//store average
	char type;//store type
}info;//structure named info

/*Function prototype*/
void print(info std[MAX]);
void input(FILE* fp, info std[MAX]);
void swap(info* std1, info* std2 );
void sort_by_id(info* std);
void sort_by_average(info* std);
void draw_line(char);


/*Main function*/
int main(void){
	FILE* fp = fopen("C:\\Users\\400T6B\\Desktop\\test.txt","r");//Open test.txt to read
	info std[MAX];//declaring std array with 10 elements have info data type
	
	if(fp == NULL){//if file is invalid, return -1
		printf("Can not open file");
		return -1;
	}
	
	input(fp,std);//Call input() function to read data from test.txt and store in std array
	
	draw_line('=');//draw line
	puts("Original:");
	draw_line('-');//draw line
	print(std);//call print() function to print out data
	
	draw_line('=');//draw line
	puts("Sort by average grade in descending order:");
	draw_line('-');//draw line
	sort_by_average(std);//call this function to sort data by average grade (descending order)
	print(std);//after sorting, print out data
	
	draw_line('=');//draw line
	puts("Sort by ID:");
	draw_line('-');//draw line
	sort_by_id(std);//call this function to sort data by ID (ascending order)
	print(std);//after sorting, print out data
	
	draw_line('=');//draw line
	printf("There are total: %d students\n",MAX);//print out total number of students
	//Calculate the frequency of type A, B, C...(formula: frequency of type * 100/total)
	printf(" A: %d%%\n B: %d%%\n C: %d%%\n D: %d%%\n F: %d%%\n",freg[0]*10,freg[1]*10,freg[2]*10,
																freg[3]*10,freg[5]*10);
}

/*This function read data from file test.txt and store data in std array
 *2 parameters: address of file test.txt and array std with 10 elements*/
void input(FILE* fp, info std[MAX]){
	char type(int);//prototype, type() can not be used outside input() function
	int average(info std);//prototype, average() function can not be used outside input() function
	int i;//counter
	
	for(i = 0; i<MAX; i++){//count 10 times
		fscanf(fp,"%s%s%d%d%d%d",std[i].id,std[i].name,&std[i].midterm,&std[i].final,
				&std[i].practice,&std[i].homework);//eachtime read 1 line of data from test.txt and
									//store it in the array with correspond data-type respectively
		std[i].average = average(std[i]);//calculate average grade by average() function and store
										//the result in current std.average
		std[i].type = type(std[i].average);//determine type of student by type() and store result
		freg[std[i].type - 65]++;//count the frequence. type of student is always A,B,C,D or F then 
								 //std[i].type - 65 always equalize 0,1,2,3,4,5, base on type.
								// (65 = A in ASCII)
	}//end for
}//end function

/*This function print out data from std array*/
void print(info std[MAX]){//paramater is an array with 10 elements and has info data type
	int i;//counter
	printf("ID\t\tName\t\tMidterm\t\tFinal\t\tPractice\tHomeWork\tAverage\t\tType\n\n");//print header
	for(i = 0; i < MAX; i++){//print out all stored data from element 1st to 10th
		printf("%-16s%-16s%-16d%-16d%-16d%-16d%-16d%-16c\n",std[i].id,std[i].name,std[i].midterm,
						std[i].final,std[i].practice,std[i].homework,std[i].average,std[i].type);								
	}//end for
}//end function

/*This function sort the data in std array by ID in ascending order*/
void sort_by_id(info std[MAX]){//parameter is an array with 10 elements with info data type
	int i,j;//counter for bubble sort algorithm
	//Bubble sort in ascending order
	for(i = 0; i < MAX - 1; i++){//Sort 8 times
		for(j = 0; j < MAX - 1; j++){//Eachtime the element has the biggest data will go to the last
									 //position
			if(atoi(std[j].id) > atoi(std[j+1].id)){//atoi() convert string to integer, i.e: string 
													//"123" will be converted to 123 integer.
													//Compare 2 integers,if current id is bigger
													//than next id swap them
				swap(&std[j],&std[j+1]);//Call swap function
			}//end if
		}//end inner for
	}//end outter for
}//end function

/*This function sort the data in descending order*/
void sort_by_average(info std[MAX]){//parameter is an array with 10 elements with info data type
	int i,j;//counter for bubble sort algorithm
	//Bubble sort:
	for(i = 0; i < MAX - 1; i++){//sort 8 times
		for(j = 0; j < MAX - 1; j++){//eachtime, the element which has the smallest data will go
									 //to the last position
			if(std[j].average < std[j+1].average)//compare average grade of current element with the
												 //next element
				swap(&std[j],&std[j+1]);//if current grade is smaller than next grade, swap it
		}//end inner for
	}//end outter for
}//end function

/*This function calculate the average grade and return it*/
int average(info std){//parameter is a variable which has info data type
	return std.midterm*0.3 + std.final*0.3 + std.practice*1.25*0.2 + std.homework*2.5*0.2;
}

/*This function determine type of student base on average grade and return type A,B,C...*/
char type(int avrg){//parameter is an integer (average grade)
	if(avrg < 60)
		return 'F';
	else if(avrg < 70)
		return 'D';
	else if(avrg < 80)
		return 'C';
	else if(avrg < 90)
		return 'B';
	else
		return 'A';
}

/*This function swap value in address 1 to address 2*/
void swap(info* std1, info* std2){//parameter is 2 addresses
	info tmp = *std1;
	*std1 = *std2;
	*std2 = tmp;
}

/*This function draw a line*/
void draw_line(char a){//parameter is a character
	int i;//counter
	for(i = 0; i < 120; i++)//length of line = 119 so loop 119 times
		printf("%c",a);//each time print the character stored in a
	puts("");//After 119 times, put new line character
}


