#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;


// town -> post office -> packages

// print all packages in t town according to form
void print_all_packages(town t) {
    printf("%s:\n", t.name);
    // print all post office in t town
    for (int i = 0; i < t.offices_count; i++){
        printf("\t%d:\n", i);
        // print all packages in i office
        for (size_t j = 0; j < t.offices[i].packages_count; j++){
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

// send all  acceptable packages in source office to target office
void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index){
	// find all package in the source post office that are accepted at the target post office
    int min_weight_of_target = target->offices[target_office_index].min_weight;
    int max_weight_of_target = target->offices[target_office_index].max_weight;
    int numOfAcceptPack = 0;
    // find number of packages acceptable in target office
    for (size_t i = 0; i < source->offices[source_office_index].packages_count; i++){
        if(source->offices[source_office_index].packages[i].weight >= min_weight_of_target && source->offices[source_office_index].packages[i].weight <= max_weight_of_target)
            numOfAcceptPack++;
    }
    printf("num = %d\n", numOfAcceptPack);
    // realloacation memory to target office to store new packages
    target->offices[target_office_index].packages = realloc(target->offices[target_office_index].packages, (target->offices[target_office_index].packages_count + numOfAcceptPack)*sizeof(package));
    // send all acceptable packages from source office to target office
    // store all unacceptable packages in source office
    package *unacceptablePack = (package*)malloc((source->offices[source_office_index].packages_count - numOfAcceptPack)*sizeof(package));
    int numOfUnacceptPack = 0;
    // transfer all acceptable packages from source office to targer office queue
    for(size_t i = 0; i < source->offices[source_office_index].packages_count; i++){
        // if current package satisfies the condition of target office -> sent package to target office
        if(source->offices[source_office_index].packages[i].weight >= min_weight_of_target && source->offices[source_office_index].packages[i].weight <= max_weight_of_target){
            // append package to queue of target office
            target->offices[target_office_index].packages[target->offices[target_office_index].packages_count] = source->offices[source_office_index].packages[i];
            // update number of packages in target office
            target->offices[target_office_index].packages_count++;
        }
        // if current package not satisfied the condition of target office -> store to queue of unacceptable packages
        else{
            // append to unacceptable package queue
            unacceptablePack[numOfUnacceptPack] = source->offices[source_office_index].packages[i];
            numOfUnacceptPack++;
        }
    }
    // release the memeory of source office if there is the sent of packages
    if(numOfAcceptPack > 0){
        free(source->offices[source_office_index].packages);
        source->offices[source_office_index].packages = unacceptablePack;
        source->offices[source_office_index].packages_count = numOfUnacceptPack;
    }
}

// find the town with the most packages in queue
town town_with_most_packages(town* towns, int towns_count) {
    // create struct to store result
    typedef struct most_packages_town{
        int numberOfPackages;
        size_t indexOfTownWithMostPackages;
    } most_packages_town;
    most_packages_town result;
    result.numberOfPackages = -1;
    result.indexOfTownWithMostPackages = -1;

    // retrive all town 
    for (size_t i = 0; i < towns_count; i++){
        int temp = 0;
        // calculate sum of packages in town
        for (size_t j = 0; j < towns[i].offices_count; j++)
            temp = temp + towns[i].offices[j].packages_count;
        // assign new town to result if number of packages in new town more than curren town result
        if(result.numberOfPackages < temp){
            result.indexOfTownWithMostPackages = i;
            result.numberOfPackages = temp;
        }
    }
    // return town with most of packages
    return towns[result.indexOfTownWithMostPackages];
}

// find the town with the name of town 
town* find_town(town* towns, int towns_count, char* name) {
    town *ptrTown;
    // retrive all town in town array
    for (size_t i = 0; i < towns_count; i++)
        // compare name of town and name
        if(strcmp(towns[i].name, name) == 0) {
            ptrTown = &towns[i];
            break;
        }
    // return reference of town with name
    return ptrTown;
}

// main program
int main()
{
    // create pointer
    FILE *fptr;
    // establish communication between pointer in program to data file
    fptr = fopen("dataPost.txt", "r");

	int towns_count;
	fscanf(fptr, "%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		fscanf(fptr, "%s", towns[i].name);
		fscanf(fptr, "%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			fscanf(fptr, "%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				fscanf(fptr, "%s", towns[i].offices[j].packages[k].id);
				fscanf(fptr, "%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	
	int queries;
	fscanf(fptr, "%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		fscanf(fptr, "%d", &type);
		switch (type) {
		case 1:
			fscanf(fptr, "%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			fscanf(fptr, "%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			fscanf(fptr, "%d", &source_index);
			fscanf(fptr, "%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			fscanf(fptr, "%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
    // close communication between pointer in program and data file
    fclose(fptr);
	return 0;
}
