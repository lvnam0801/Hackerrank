#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

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
     // Tìm số đoạn
    int paragraph = 1;
    for(int i = 0; i < strlen(text); ++i) if(text[i] == '\n') ++paragraph;
    char ****document = (char****)calloc((paragraph + 1), sizeof(char***));
   
    int index_1 = 0;
    int lenght = strlen(text);
    
    // Tìm số câu cho từng đoạn
    for(int i = 0; i < paragraph; ++i){
        // Lưu vị trí của đầu của đoạn i
        int index_2 = index_1;                                             

        // Tìm số câu của đoạn
        int sentence = 0; 
        while(index_1 < lenght && text[index_1] != '\n'){ 
            if(text[index_1] == '.') ++sentence; ++index_1;}
        document[i] = (char***)calloc((sentence + 1), sizeof(char**));
       
        // index_2 : vị trí đầu đoạn i
        // index_1 : Vị trí cuối đoạn "\n";   
        for(int j = 0; j < sentence; ++j){

            // Lưu lại vị trí đầu câu j
            int index_3 = index_2;
            // Tìm số từ trong câu j
            int word = 1; 
            while(index_2 < index_1 && text[index_2] != '.'){
                if(text[index_2] == ' ') ++word; ++index_2;}
            document[i][j] = (char**)calloc((word + 1), sizeof(char*));
            
            // index_3 : vị trí đầu câu j
            // index_2 : vị trí cuối câu : '.' j
            
            // Tìm số kí tự trong mỗi từ thuộc câu j
            for(int k = 0; k < word; ++k){
                // Tìm số kí tự trong từ  k
                int index_4 = index_3; 
                int character = 0; 
                while(index_3 < index_2 && text[index_3] != ' '){ ++character; ++index_3;}
                ++character; 
                document[i][j][k] = (char*)calloc((character + 1), sizeof(char));

                // Gán giá trị của từ cho từ k
                for(int n = index_4; n < index_3; n++) document[i][j][k][n - index_4] = text[n];
                ++index_3;
            }
            ++index_2;
        }

        ++index_1;                  // Qua đầu câu kế tiếp
    }
    return document;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
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
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}