#include<stdio.h>
#include<conio.h>
#include<iostream>

using namespace std;

#define max_length 30
#define max_base 20

struct kindergarden
{
	char *surname, *name;
	int hosp_identify;
	union
	{
		struct
		{
			char *illness, *doc;
		} nonhosp;
		struct
		{
			char *illness, *hospnum, *hospplace, *hospdoc;
		} hosp;
	} hospital;
};

int init_array(struct kindergarden*);
char* check_string(char*);
int yes_no();
void sort_array(struct kindergarden*, int);
void search_illness(struct kindergarden*, int, char**);

void main (int argc, char **argv)
{
	int array_size;
	struct kindergarden *children;
	children = (struct kindergarden*)malloc(max_base*sizeof(struct kindergarden));
	array_size = init_array(children);
	sort_array(children, array_size);
	search_illness(children, array_size, argv);
	free(children);
	getch();
}

int init_array(kindergarden* new_kids_base)
{
	int n=0;
	do
	{
		new_kids_base[n].surname = check_string("Enter a child's surname");
		new_kids_base[n].name = check_string("Enter a child's name");
		printf("Was a child hospitalized? y/n");
		if(yes_no())
		{
			new_kids_base[n].hosp_identify = 1;
			new_kids_base[n].hospital.hosp.illness = check_string("Enter an illness");
			new_kids_base[n].hospital.hosp.hospnum = check_string("Enter the number of hospital");
			new_kids_base[n].hospital.hosp.hospplace = check_string("Enter the situation of hospital");
			new_kids_base[n].hospital.hosp.hospdoc = check_string("Enter a hospital doc's surmane");
		}
		else
		{
			new_kids_base[n].hosp_identify = 0;
			new_kids_base[n].hospital.nonhosp.illness = check_string("Enter an illness");
			new_kids_base[n].hospital.nonhosp.doc = check_string("Enter a doc's surname");
		};

		if(n<max_base-1)
		{
			printf("Do you want to continue? y/n");
			if(!yes_no()) break;
		}
		n++;
	} while (n<max_base);
	return n+1;
}

int yes_no()
{
	int i;
	char *choice;
	choice = (char*)malloc(max_length*sizeof(char));
	do
		{
			__fpurge(stdin);
			fgets(choice, 1, stdin);
			if (choice[0] == 'y')
			{
				i = 1;
				break;
			}
			else if (choice[0] == 'n')
			{
				i = 0;
				break;
			}
		} while (1);
	return i;
}

char* check_string(char* comment)
{
	char *text;
	text = (char*)malloc(max_length*sizeof(char));
	do
	{
		printf("%s", comment);
        __fpurge(stdin);
        fgets(text, max_length, stdin);
        if (text[0] == '\n')
		{
            continue;
        }
        break;
	} while (1);
	return text;
}

void sort_array(struct kindergarden* kids_base, int array_size)
{
	struct kindergarden temp;
	int i, j;
	for(i=0; i<array_size-1; i++)
		for(j=i+1; j<array_size; j++)
			if(strcmp(kids_base[i].surname, kids_base[j].surname)>0)
			{
				temp = kids_base[i];
				kids_base[i] = kids_base[j];
				kids_base[j] = temp;
			}
}

void search_illness(struct kindergarden* kids_base, int array_size, char **argv)
{
	int i;
	argv++;
	printf("This is the list of kids illed with %s", *argv);
	for(i=0; i<array_size; i++)
		if (kids_base[i].hosp_identify == 0)
		{
			if(strcmp(kids_base[i].hospital.nonhosp.illness, *(argv))==0)
				printf("The child %s %s was searched by Doc.%s", kids_base[i].surname, kids_base[i].name, kids_base[i].hospital.nonhosp.doc);
		}
		else if(strcmp(kids_base[i].hospital.hosp.illness, *(argv))==0)
			printf("The child %s %s was hospitalized  in Hospital %s in %s, where was searched by Doc.%s", kids_base[i].surname, kids_base[i].name, kids_base[i].hospital.hosp.hospnum, kids_base[i].hospital.hosp.hospplace, kids_base[i].hospital.hosp.hospdoc);
}