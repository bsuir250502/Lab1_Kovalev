#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio_ext.h>

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
void sort_array(struct kindergarden*, int);
void search_illness(struct kindergarden*, int, char**);
int atoi_change();
void check_help(int, char**);

int main (int argc, char **argv)
{
    int array_size;
    struct kindergarden *children;
    children = (struct kindergarden*)malloc(max_base*sizeof(struct kindergarden));
    check_help(argc, argv);
    array_size = init_array(children);
    sort_array(children, array_size);
    search_illness(children, array_size, argv);
    free(children);
    return 0;
}

int init_array(struct kindergarden* new_kids_base)
{
    int n=0, identifier;
    do
    {
	new_kids_base[n].surname = check_string("Enter a child's surname: ");
	new_kids_base[n].name = check_string("Enter a child's name: ");
	printf("Was a child hospitalized?");
	identifier = atoi_change();
	if(identifier)
	{
	    new_kids_base[n].hosp_identify = 1;
	    new_kids_base[n].hospital.hosp.illness = check_string("Enter an illness: ");
	    new_kids_base[n].hospital.hosp.hospnum = check_string("Enter the number of hospital: ");
	    new_kids_base[n].hospital.hosp.hospplace = check_string("Enter the situation of hospital: ");
	    new_kids_base[n].hospital.hosp.hospdoc = check_string("Enter a hospital doc's surname: ");
	}
	else
	{
	    new_kids_base[n].hosp_identify = 0;
	    new_kids_base[n].hospital.nonhosp.illness = check_string("Enter an illness: ");
	    new_kids_base[n].hospital.nonhosp.doc = check_string("Enter a doc's surname: ");
	};
	identifier = 0;
	if(n<max_base-1)
	{
	    printf("Want to continue?");
	    identifier = atoi_change();
	    if (!identifier) { break; }
	}
    n++;
    } while (n<max_base);
    return n;
}

int atoi_change()
{
    int identifier;
    char string[128];
    while(1)
    {
	printf("(yes - 1/no - 0) ");
	fgets(string, 128, stdin);
	identifier = atoi(string);
	if(identifier == 1 || identifier == 0) { break; }
	puts("It's not correct. Please, input data again.");
    }
    return identifier;
}

char* check_string(char* comment)
{
    char *text;
    text = (char*)malloc(max_length*sizeof(char));
    do
    {
	printf("%s", comment);
        __fpurge(stdin);
        gets(text);
        if(text[0] == '\n') { continue; }
    } while (0);
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
    printf("This is the list of kids illed with %s:\n", argv[1]);
    for(i=0; i<=array_size; i++)
    {
	if (kids_base[i].hosp_identify == 0)
	{
	    if(!strcmp(kids_base[i].hospital.nonhosp.illness, argv[1]))
	    {
		printf("The child %s %s was searched by Doc.%s\n", kids_base[i].surname, kids_base[i].name, kids_base[i].hospital.nonhosp.doc);
	    }
	}
	else if(!strcmp(kids_base[i].hospital.hosp.illness, argv[1]))
	{
	    printf("The child %s %s was hospitalized  in Hospital %s in %s, where was searched by Doc.%s\n", kids_base[i].surname, kids_base[i].name, kids_base[i].hospital.hosp.hospnum, kids_base[i].hospital.hosp.hospplace, kids_base[i].hospital.hosp.hospdoc);
	}
    }
}

void check_help(int argc, char **argv)
{
    if(argc > 1 && !strcmp(argv[1], "-h"))
    {
	puts("\n=============================================\n"
	"Manual\n\n"
	"1) send an interested illness by command line\n"
	"2) A: Enter an information about children:\n"
	"- surname\n"
	"- name\n"
	"B: Choose if he/she was hospitalized and then put the information about illness, hospital and doctor"
	"- illness\n"
	"- doctor\n"
	"- hospital number\n"
	"- hospital situation\n"
	"3) Output data about interested illness\n\n"
	"=================================================\n");
	exit(0);
    }
}
