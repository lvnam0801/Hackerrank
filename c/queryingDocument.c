// program to convert raw text document into its component paragraphs, sentences, and words
// preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
// macros
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
// global variable
FILE *fptr;

// function prototype
char* get_input_text(); // get input from stream (file or stdin buffer)
char**** get_document(char* text); // convert raw text to components in document
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n);
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m);
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m);
void print_word(char* word);
void print_sentence(char** sentence);
void print_paragraph(char*** paragraph);

// main program
int main() 
{
    // openfile (establish comunicate from program to data file)
    fptr = fopen("./dataQuerying.txt", "r");
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    fscanf(fptr, "%d", &q);

    while (q--) {
        int type;
        fscanf(fptr, "%d", &type);

        if (type == 3){
            int k, m, n;
            fscanf(fptr, "%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            fscanf(fptr, "%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            fscanf(fptr, "%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     

    // close the file
    fclose(fptr);
    return 0;
}

// function definition
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

char**** get_document(char* text) {
    // find number paragraphs, number sentences of paragraph
    int numOfPara = 0, senTh = 0;
    int numOfSenInPara[MAX_PARAGRAPHS] = {0};
    int numOfWordInSen[100] = {0};
    for (int i = 0; i < strlen(text); i++){
        // find number pharagraphs in text
        if(text[i] == '\n') {
            numOfPara++;
        }
        // find number sentences in each paragraphs
        if(text[i] == '.') {
            numOfSenInPara[numOfPara]++;
            numOfWordInSen[senTh]++;
            senTh++;
        }
        // find number words in each sentence
        if(text[i] == ' ') numOfWordInSen[senTh]++; 
    }
    // the last paragraph does not end of '\n'
    numOfPara++;

    // dynamic allocated memory for document
    senTh = 0;
    int indexOfText = 0;  // index in array that store raw text
    // push input from text to document
    char**** document = (char****)malloc(numOfPara*sizeof(char***));
    // allocating memory for the pointer to store the paragraphs
    for (size_t i = 0; i < numOfPara; i++){ // the last paragraph not end of '\n'.
        document[i] = (char***)malloc(numOfSenInPara[i]*sizeof(char**));
        // allocating memory for the pointer to store senetens in corresponding paragraph
        for (size_t j = 0; j < numOfSenInPara[i]; j++){
            document[i][j] = (char**)malloc(numOfWordInSen[senTh]*sizeof(char*));
            // allocating memory for the pointer to store words in corresponding sentence
            for (size_t k = 0; k < numOfWordInSen[senTh]; k++){
                // find word in text
                while (indexOfText < strlen(text) && (text[indexOfText] == ' ' || text[indexOfText] == '\n' || text[indexOfText] == '.'))
                    indexOfText++;
                // get number of character in words
                int indexOfChar = indexOfText;
                while (indexOfText < strlen(text) && !(text[indexOfText] == ' ' || text[indexOfText] == '\n' || text[indexOfText] == '.'))
                    indexOfText++;
                // allocating memory for the array to store word in document
                document[i][j][k] = (char*)malloc((indexOfText - indexOfChar + 1)*sizeof(char));
                // copy word from raw text to word array in document
                int m = 0;
                for (; m < (indexOfText - indexOfChar); m++){
                    document[i][j][k][m] = text[indexOfChar + m];
                }
                document[i][j][k][m] = '\0';
            }
            senTh++;
            
        }
        
    }
    // // print document
    // senTh = 0;
    // for (size_t i = 0; i < numOfPara; i++){
    //     for (size_t j = 0; j < numOfSenInPara[i]; j++){
    //         for (size_t k = 0; k < numOfWordInSen[senTh]; k++){
    //             printf("%s", document[i][j][k]);
    //             if (k < numOfWordInSen[senTh] - 1) printf(" ");
    //         }
    //         senTh++;
    //         printf(".");
    //     }
    //     printf("\n"); 
    // }
    return document;   
}


char* get_input_text() {	
    int paragraph_count;
    fscanf(fptr, "%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    fgetc(fptr);
    for (int i = 0; i < paragraph_count; i++) {
        fscanf(fptr, "%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    fscanf(fptr, "%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    fscanf(fptr, "%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}