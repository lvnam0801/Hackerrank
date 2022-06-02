// program to convert raw text to component in document using type struct user define
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

FILE *fptr;

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

struct document get_document(char* text) {
    // variable store components in document
    struct document doc;
    // varialbe to determine number of components in document
    int numOfPara = {0};
    int numOfSenInPara[MAX_PARAGRAPHS] = {0}, paraTh = 0;
    int numOfWordInSen[100] = {0}, senTh = 0;
    int numOfCharInWord[100] = {0}, wordTh = 0;
    // determine number of components in document
    for (size_t i = 0; i < strlen(text); i++){
        // number of paragraphs
        if(text[i] == '\n') {
            numOfPara++;
            paraTh++;

        }
        // number of sentences in paraTh paragraph and number of words in senTh sentence
        else if(text[i] == '.'){
            numOfSenInPara[paraTh]++;
            numOfWordInSen[senTh]++;
            senTh++;
            wordTh++;

        }
        // number of words in sentences senTh
        else if(text[i] == ' '){
            wordTh++;
            numOfWordInSen[senTh]++;
        }
        // number of characters in wordTh word
        else numOfCharInWord[wordTh]++;
    }
    // increase number of paragraphs in document to 1 because end of file
    numOfPara++;
    // allocated memory to document structure
    doc.data = (struct paragraph*)malloc(numOfPara*sizeof(struct paragraph));
    doc.paragraph_count = numOfPara;
    // reset all variable index of array 
    paraTh = 0;
    senTh = 0;
    wordTh = 0;
    // variable to use copy raw text to word component in document structure
    int textTh = 0, inWord = 0;
    // allocate memory for sentences of paragraph i-th
    for (size_t i = 0; i < doc.paragraph_count; i++){ // retrieve paragraphs in document
        doc.data[i].data = (struct sentence*)malloc(numOfSenInPara[paraTh]*sizeof(struct sentence));
        doc.data[i].sentence_count = numOfSenInPara[paraTh];
        // allocate memory for words in sentence - j-th in i-th paragraph
        for (size_t j = 0; j < doc.data[i].sentence_count; j++){
            doc.data[i].data[j].data = (struct word*)malloc(numOfWordInSen[senTh]*sizeof(struct word));
            doc.data[i].data[j].word_count = numOfWordInSen[senTh];
            // allocate memory for characters in word - k-th in j-th sentence - i-paragraph
            for (size_t k = 0; k < doc.data[i].data[j].word_count; k++){
                doc.data[i].data[j].data[k].data = (char*)malloc((numOfCharInWord[wordTh] + 1)*sizeof(char));
                // copy data from raw text to documents word by word
                inWord = 0;
                // ignore character not belong to word
                while((text[textTh] == ' ' || text[textTh] == '\n' || text[textTh] == '.') && textTh < strlen(text)) textTh++;
                // copy all character of word in raw text to word component in document
                while(text[textTh] != ' ' && text[textTh] != '\n' && text[textTh] != '.' && textTh < strlen(text)){
                    doc.data[i].data[j].data[k].data[inWord] = text[textTh];
                    inWord++;
                    textTh++;
                }
                // insert end of string to last character of string
                doc.data[i].data[j].data[k].data[inWord] = '\0';
                // next word in raw text
                wordTh++;
            }
            // next sentence
            senTh++;
        }
        // next paragraph
        paraTh++;
    }
    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    // establish comunication between program to file
    fptr = fopen("dataOfStructgDoc.txt", "r");
    // get input from file to text variable
    char* text = get_input_text();
    // convert raw text to document structure
    struct document Doc = get_document(text);

    int q;
    fscanf(fptr, "%d", &q);

    while (q--) {
        int type;
        fscanf(fptr, "%d", &type);

        if (type == 3){
            int k, m, n;
            fscanf(fptr, "%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            fscanf(fptr, "%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            fscanf(fptr, "%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
    // close comunication between program and file
    fclose(fptr);
    return 0;
}