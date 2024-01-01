
// Do NOT add any other includes
#include "search.h"
#include<iostream>
SearchEngine::SearchEngine(){
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    // Implement your function here  

}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string temp = "";
    for(char c:sentence){
        if(c >= 'A' && c <= 'Z'){
            c = c - 'A' + 'a';
        }
        temp += c;
    }
    // Implement your function here 
    sentence_node sen;
    sen.book_code = book_code;
    sen.page = page;
    sen.paragraph = paragraph;
    sen.sentence_no = sentence_no;
    sen.sentence = temp;
    sentences.push_back(sen);
    return;
}

vector<int> pref_func(const string& pattern){
    int m = pattern.length();
    std::vector<int> prefix(m, 0);
    int j = 0;

    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefix[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        prefix[i] = j;
    }

    return prefix;
}

 void searchPattern(const string& pattern, sentence_node sen, Node* &head,Node* &head1,int& n_matches) {
    Node* curr = head1;
    int resultIndex = -1;
    string sentence = sen.sentence;
    int patternLength = pattern.length();
    int sentenceLength = sentence.length();

    int n = sentence.length();
    int m = pattern.length();
    std::vector<int> prefix = pref_func(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == sentence[i]) {
            i++;
            j++;
        }

        if (j == m) {
            n_matches++;
            if (!head) {
                head = new Node(sen.book_code, sen.page, sen.paragraph, sen.sentence_no, i - j);
                head1 = head;
                curr = head;
            } else {
                Node* temp = new Node(sen.book_code, sen.page, sen.paragraph, sen.sentence_no, i - j);
                curr->right = temp;
                temp->left = curr;
                curr = temp;
                head1 = curr;
            }
            j = prefix[j - 1];
        } 
        else if (i < n && pattern[j] != sentence[i]) {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }
    }

}
Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here  
    // KMP Algorithm
    if(pattern == ""){
        return NULL;
    }
    n_matches = 0;
    Node* head = NULL;
    Node* head1 = head;
    for (int i = 0; i < sentences.size(); i++) {
        searchPattern(pattern, sentences[i], head, head1, n_matches);
    }
    return head;


}