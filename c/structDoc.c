#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

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
    struct document doc;
    doc.paragraph_count = 0;

    // Tìm số đoạn và khởi tạo mảng struct đoạn
    for(int i = 0; i < strlen(text); ++i) if(text[i] == '\n') ++doc.paragraph_count;
    ++doc.paragraph_count;
    // Khởi tạo mảng với các đoạn tìm được
    doc.data = (struct paragraph*)calloc(doc.paragraph_count + 1, sizeof(struct paragraph));

    int index_1 = 0;                // Vị trí đầu của document
    // Duyệt văn bản
    for(int i = 0; i < doc.paragraph_count; ++i){
        int index_2 = index_1;        // Lưu lại vị trí đầu của đoạn tiếp theo
        
        // Duyệt đoạn tìm số câu
        doc.data[i].sentence_count = 0;
        while(text[index_1] != '\n' && index_1 < strlen(text)) {
            if(text[index_1] == '.')   ++doc.data[i].sentence_count;
             ++index_1;
        } 

        // Khởi tạo mảng với số câu tìm được
        doc.data[i].data = 
            (struct sentence*)calloc(doc.data[i].sentence_count + 1, sizeof(struct sentence));

        // Index_1 : Vị trí text[indext_1] == '\n'. (cuối đoạn hoặc cuối văn bản)
        // Index_2 : Vị trí đầu của đoạn 

        // Duyệt đoạn hiện tại
        for(int j = 0; j < doc.data[i].sentence_count; ++j){
            int index_3 = index_2;  // Lưu lại vị trí đầu của câu tiếp theo

            // Duyệt câu tìm số từ
            while(text[index_2] != '.'){
                if(text[index_2] == ' ')    ++doc.data[i].data[j].word_count; 
                ++index_2;
            }
            ++doc.data[i].data[j].word_count;
            // Index_2 : Vị trí phần tử text[index_2] == '.'(cuối câu);
            // Index_3 : Vị trí đầu của câu hiện tại

            // Khởi tạo mảng với số từ đã tìm được
            doc.data[i].data[j].data = (struct word*)calloc(doc.data[i].data[j].word_count + 1, sizeof(struct word));

            // Duyệt câu hiện tại
            for(int k = 0; k < doc.data[i].data[j].word_count; ++k){
                
                int index_4 = index_3; // Lưu lại vị trí đầu từ hiện tại


                //  Duyệt từ tìm số kí tự
                while(text[index_3] != ' ' && text[index_3] != '.') ++index_3;
                // Tạo mảng với số phần tử vừa tìm được
                doc.data[i].data[j].data[k].data = (char*)calloc(index_3 - index_4 + 1, sizeof(char));

                // Inden_3 : Vị trí cuối từ : text[indext_3] == " " || text[indext_3] == ".";

                // Thêm từ vào trong mảng
                for(int n = 0; n < index_3 - index_4; ++n)
                  doc.data[i].data[j].data[k].data[n] = text[index_4 + n];
                
                // Chuyển sang đầu từ mới
                ++index_3;
            }
            // Chuyển sang đầu câu mới
            ++index_2;
        }
        // Chuyển sang đầu đoạn mới
        ++index_1;
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}