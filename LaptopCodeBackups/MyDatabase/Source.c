#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_SIZE 51

struct Data_column
{
	char name[MAX_NAME_SIZE];
	long double value;
}column;

struct Data_node
{
	long key;
	char table_name[MAX_NAME_SIZE];
	int total_columns;
	struct Data_column* column;
}node;

FILE* access_database (char* path);    //Make sure the database is accasseable
bool read_database (FILE* fp);			//temp function to read the whole database
bool write_to_database (FILE* fp, struct Data_node* node);		//Function to add nodes
FILE* search_for_node (FILE* fp, long key);    //Search for a node, return NULL if not found
bool node_name_resolved (struct Data_node* new_node, FILE* fp);    //Input for node name should be uniqueue depends on hash as well
bool node_inputs (struct Data_node* new_node, int total_columns);	//Fill node inputs
bool update_node (FILE* fp);	// Update a node's contents
long calculate_hash(char* name);	//Canculate hash for creating and locating a node

int main()
{
	FILE* fp = access_database("StoredData//Database.txt");
	read_database(fp);
	return 0;
}

FILE* access_database(char* path)
{
	FILE* fp;
	fp = fopen(path , "r");
	if(!fp)
	{
		perror("\n\t[ Error! ] File was not opened\n");  
		return NULL;
	}
	return fp;
}

bool read_database(FILE *fp)
{
	if(!fp) return false;
	char ch = '\0';
	while(ch != EOF)
	{
		ch = fgetc(fp);
		printf("%c",ch);
	}
	return true;
}

long calculate_hash(char* name)
{
	//return Hash for the given name which will be used as the line number for the 
	//data to be written in the text file
	return 0;
}

bool node_name_resolved (struct Data_node* new_node, FILE* fp)
{
	char* proposed_name[MAX_NAME_SIZE];
	scanf("%50s",proposed_name);	//MAX_NAME	= 51
	// Search the database for the give name	
	return true;
}