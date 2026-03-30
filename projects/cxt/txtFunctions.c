#include "txtFunctions.h"


const char delim[] = " ";
const char *stop_words[] = {
    "a", "about", "above", "after", "again", "against", "all", "also", "am", "an",
    "and", "any", "are", "aren't", "as", "at", "be", "because", "been", "before",
    "being", "below", "between", "both", "but", "by", "can", "cannot", "can't", "come",
    "could", "couldn't", "day", "did", "didn't", "do", "does", "doesn't", "doing", "don't",
    "down", "during", "each", "even", "few", "find", "first", "for", "from", "further",
    "get", "give", "go", "had", "hadn't", "has", "hasn't", "have", "haven't", "having",
    "he", "he'd", "he'll", "her", "here", "here's", "hers", "herself", "him", "himself",
    "his", "how", "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into",
    "is", "isn't", "it", "it's", "its", "itself", "just", "know", "like", "look",
    "make", "man", "many", "me", "more", "most", "myself", "my", "new", "no",
    "nor", "not", "now", "of", "off", "on", "once", "one", "only", "or",
    "other", "our", "ours", "ourselves", "out", "over", "own", "people", "same", "say",
    "see", "she", "she'd", "she'll", "she's", "should", "shouldn't", "so", "some", "such",
    "take", "tell", "than", "that", "that's", "the", "their", "theirs", "them", "themselves",
    "then", "there", "there's", "these", "they", "they'd", "they'll", "they're", "they've", "thing",
    "think", "this", "those", "through", "to", "too", "two", "under", "until", "up",
    "use", "very", "want", "was", "wasn't", "way", "we", "we'd", "we'll", "we're",
    "we've", "well", "were", "weren't", "what", "what's", "when", "when's", "where", "where's",
    "which", "while", "who", "who's", "whom", "why", "why's", "will", "with", "won't",
    "would", "wouldn't", "year", "you", "you'd", "you'll", "you're", "you've", "your", "yours",
    "yourself", "yourselves"
};

int FindKey(char* key, Map* map, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (strcmp(map[i].key, key) == 0) {
            return (int)i;
        }
    }
    return -1;
}

bool ExistKey(char* key, Map* map, size_t n) {
    return FindKey(key, map, n) != -1;
}

AnalyzeTextData* AnalyzeText(char *txt, size_t *size){
    // Allocate the returning structure
    AnalyzeTextData* returning = malloc(sizeof(AnalyzeTextData) + 1);
    if (!returning) return NULL;
    
    // Allocate for words and newLines
    returning->words = malloc(sizeof(size_t));
    returning->newLines = malloc(sizeof(size_t));
    if (!returning->words || !returning->newLines) {
        free(returning->words);
        free(returning->newLines);
        free(returning);
        return NULL;
    }
    
    //gets wordFrequencyData first (modifies txt, so do it first)
    commonWordsData data = mostCommonWord(txt);
    returning->mostUsed = data.mostUsed;
    returning->tracker = data.tracker;
    returning->uniqueWords = data.count;
    //gets wordCount data
    *returning->words = countWords(txt);
    //gets newLines data
    *returning->newLines = countNewLines(txt);
    //returns structure with both data
    return returning;
};

size_t countWords(char *txt){
    char *copy = strdup(txt); // Copy to avoid modifying original
    if (!copy) return 0;
    size_t count = 0;
    char* token = strtok(copy, delim);

    while(token != NULL){
        count++;
        token = strtok(NULL, delim);
    }
    free(copy);
    return count;
}

size_t countNewLines(char *txt){
    char *copy = strdup(txt); // Copy to avoid modifying original
    if (!copy) return 0;
    size_t count = 0;
    char* token = strtok(copy, "\n");

    while(token != NULL){
        count++;
        token = strtok(NULL, "\n");
    }
    free(copy);
    return count;
}


commonWordsData mostCommonWord(char *txt){
    char *copy = strdup(txt); // Copy to avoid modifying original
    if (!copy) {
        commonWordsData res = {NULL, NULL, 0};
        return res;
    }
    // Initialize count and capacity
    size_t count = 0;
    size_t capacity = 10; // Initial capacity
    Map* tracker = malloc(capacity * sizeof(Map));
    if (!tracker) {
        free(copy);
        commonWordsData res = {NULL, NULL, 0};
        return res;
    }
    // Pointer to the most used word
    char* mostUsed = NULL;
    // Maximum appearance count
    int maxCount = 0;
    // Tokenize the text
    char* token = strtok(copy, delim);
    // length of the token
    size_t len;
    // last token character
    char last;

    while(token != NULL){
        // Clean the token
        len = strlen(token);
        for (int i = 0; i < sizeof(stop_words)/sizeof(stop_words[0]); i++) {
            if (strcmp(token, stop_words[i]) == 0) {
                token = strtok(NULL, delim);
                continue;
            }
        }
        if (len > 0) {
            last = token[len - 1];
            if(last == '.' || last == ',' || last == '"' || last == '-' || last == '\n'){
                token[len-1] = '\0';
                len--;
            }
            if (len > 0 && (token[0] == '"' || token[0] == '-')) {
                memmove(token, token + 1, len);
                len--;
            }
            if(len > 0 && token[0] == '\'') {
                memmove(token, token + 1, len);
                len--;
            }
            if(last == '\'' || last == '?' || last == '!' || last == '\n') {
                token[len - 1] = '\0';
                len--;
            }
        }
        if (len == 0) {
            token = strtok(NULL, delim);
            continue;
        }

        // Resize if needed
        if (count >= capacity) {
            capacity *= 2;
            Map* new_tracker = realloc(tracker, capacity * sizeof(Map));
            if (!new_tracker) {
                // Free and return error
                for (size_t i = 0; i < count; i++) free(tracker[i].key);
                free(tracker);
                free(copy);
                commonWordsData res = {NULL, NULL, 0};
                return res;
            }
            tracker = new_tracker;
        }

        // Check if key exists
        int idx = FindKey(token, tracker, count);
        if (idx != -1) {
            tracker[idx].timesAppeared++;
        } else {
            tracker[count].key = strdup(token); // Copy the string
            tracker[count].timesAppeared = 1;
            count++;
        }
        token = strtok(NULL, delim);
    }

    // Find the most common
    for (size_t i = 0; i < count; i++) {
        if (tracker[i].timesAppeared > maxCount) {
            maxCount = tracker[i].timesAppeared;
            mostUsed = tracker[i].key;
        }
    }
    free(copy);
    commonWordsData data = {tracker, mostUsed, count};
    return data;
}
