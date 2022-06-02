#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;
 
// function to calculate area of triagle
double area_pf_triangle(triangle tr){
    double p = (double)(tr.a + tr.b + tr.c)/2;
    return sqrt(p*(p - tr.a)*(p - tr.b)*(p - tr.c));
}

// function sort n triangle in array by area
void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/
    int index_of_tri_max; // triangle with area max in unsorted array part
    
    // sort array using selection sort algorthm
    for (int i = n - 1; i > 0; i--){ // sorted part in array
        index_of_tri_max = i; // selection the largest element in array
        // unsorted part in array
        for (int j = 0; j < i; j++){
            if(area_pf_triangle(tr[j])>area_pf_triangle(tr[index_of_tri_max]))
                index_of_tri_max = j;
        }
        // swap the largest element to the correct position
        if(index_of_tri_max != i){
            triangle temp = tr[index_of_tri_max];
            tr[index_of_tri_max] = tr[i];
            tr[i] = temp;
        }
    }
}

int main()
{
    FILE *fptr;
    // establish communication between program and date file
    fptr = fopen("./dataTriangle.txt", "r");

	int n;
	fscanf(fptr, "%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		fscanf(fptr, "%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}

    // close the communication between program and data file
    fclose(fptr);
	return 0;
}