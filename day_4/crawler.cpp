#include <iostream>
#include <cstdlib>
#include <direct.h>
#include <ctime>
#include <fstream>
#include <cstring>
#include "../hashtable/hash.h"
#include "../generic.h"

using namespace std;

int visited = 0;
int depth;
int totallinks = 10;

HashMap<char*, char*> mp(1000); 
List<char*> l1;

const char* correctwords[] = {
    "a", "about", "above", "after", "again", "against", "all", "am", "an", "and",
    "any", "are", "as", "at", "be", "because", "been", "before", "being", "below",
    "between", "both", "but", "by", "can", "did", "do", "does", "doing", "down",
    "during", "each", "few", "for", "from", "further", "had", "has", "have", "having",
    "he", "her", "here", "hers", "herself", "him", "himself", "his", "how", "i",
    "if", "in", "into", "is", "it", "its", "itself", "me", "more", "most", "my",
    "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other",
    "our", "ours", "ourselves", "out", "over", "own", "same", "she", "should", "so",
    "some", "such", "than", "that", "the", "their", "theirs", "them", "themselves",
    "then", "there", "these", "they", "this", "those", "through", "to", "too",
    "under", "until", "up", "very", "was", "we", "were", "what", "when", "where",
    "which", "while", "who", "whom", "why", "with", "you", "your", "yours",
    "yourself", "yourselves"
};
const int correctsize = sizeof(correctwords) / sizeof(correctwords[0]);

class urlvalid 
{
public:
    static bool isvalid(const char* url) {
        return strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0;
    }
};

class createpath
{
public:
    static void getcurDir(char* path, int size){
        _getcwd(path, size);
    }

    static void joinpath(char* path, const char* fol){
        strcat(path, "\\");
        strcat(path, fol);
    }
};

class downloading{
public:
    void genfilename(char* filename){
        time_t now = time(0);
        sprintf(filename, "%d.html", (int)now);
    }

    void download(const char* url, const char* folder, const char* filename){
        char fullPath[1000];
        createpath::getcurDir(fullPath, sizeof(fullPath));
        createpath::joinpath(fullPath, folder);
        _mkdir(fullPath);

        strcat(fullPath, "\\");
        strcat(fullPath, filename);

        char cmd[2000];
        strcpy(cmd, "wget \"");
        strcat(cmd, url);
        strcat(cmd, "\" -O \"");
        strcat(cmd, fullPath);
        strcat(cmd, "\"");

        cout << "Running: " << cmd << endl;
        int result = system(cmd);
        if (result == 0)
            cout << "Download complete" << endl;
        else
            cout << "Download failed" << endl;
    }
};

class mainoperation {
public:
    static bool endsWithHTML(const char* url){
        return (!strstr(url,".css") && !strstr(url,".pdf") && !strstr(url,".jpg") &&
                !strstr(url,".png") && !strstr(url,".js"));
    }

    static void normalizeURL(const char* base, const char* rel, char* curl) {
    if (strncmp(rel, "http://", 7) == 0 || strncmp(rel, "https://", 8) == 0) {
        strcpy(curl, rel);
    }
    else if (rel[0] == '/') {

        const char* start = strstr(base, "://");
        if (start) {
            start += 3;
            int len = 0;
            while (start[len] != '\0' && start[len] != '/') len++;

            strncpy(curl, base, start - base + len);
            curl[start - base + len] = '\0';
            strcat(curl, rel);
        } else {
            strcpy(curl, rel);
        }
    } else {
        strcpy(curl, base);
        for (int i = strlen(curl) - 1; i >= 0; i--) {
            if (curl[i] == '/') {
                curl[i + 1] = '\0';
                break;
            }
        }
        strcat(curl, rel);
    }
}




    static void extractLinks(const char* filepath){
        ifstream file(filepath);
        if(!file) return;
        char line[2000];
        while (file.getline(line, sizeof(line))) {
            char* pos = line;
            

            char* atag= strstr(pos,"<a");
            while (atag != NULL) {
                char* start = strstr(atag, "href=\"");
                if(start!=NULL){
                    start += 6;
                    char* end = strchr(start, '"');
                    if(end != NULL && end > start){
                        int len = end-start;
                        
                            char* link = new char[len + 1];

                            strncpy(link, start, len);
                            link[len] = '\0';

                            if(endsWithHTML(link)){
                                l1.insertAtEnd(link);
                                
                            }
                    }
                    
                }
                atag = strstr(atag+2,"<a");
            }
        }
        l1.display();
        file.close();
    }

    void dfs(char* url, int curDepth, downloading& downloader, const char* folder){
        if(curDepth > depth || visited >= totallinks) return;

        if (mp.containsKey((char*)url)) {
            return;
        }

        char filename[100];
        downloader.genfilename(filename);
        downloader.download(url, folder, filename);

        char fullPath[1000];
        createpath::getcurDir(fullPath, sizeof(fullPath));
        createpath::joinpath(fullPath, folder);
        strcat(fullPath, "\\");
        strcat(fullPath, filename);

        mp.insert(url, fullPath);
        visited++;

        extractLinks(fullPath);
        char* allWords[1000];
        int wordCount = 0;
        extractwords(fullPath, allWords, wordCount);

        char* validWords[1000];
        int validCount = 0;
        filtercorrectwords(allWords, wordCount, validWords, validCount);
  
        cout << "Valid words in : " << url << endl;
        for (int i = 0; i < validCount; ++i) {
            cout << validWords[i] << " ";
        }
        cout << endl << "Total valid words: " << validCount << endl;

        int n = l1.length();
        for(int i = 0; i<n && visited<totallinks; i++){
            char* rel = l1.getAt(i);
            char curl[1000];
            normalizeURL(url, rel, curl);
            dfs(curl, curDepth + 1, downloader, folder);
        }
    }
    bool iscorrectword(const char* word){
        for(int i = 0 ; i < correctsize ; i++){
            if(strcmp(word , correctwords[i])==0){
                return false;
            }
        }
        return true;
    }
    void extractwords(const char* filepath,char* words[],int& wordcount){
    ifstream file(filepath);
    if(!file) return;
    char line[2000];
    char current[100];
    int curLen = 0;
    bool inTag = false;
    wordcount = 0;

    while(file.getline(line, sizeof(line))){
        for(int i = 0; line[i] != '\0'; i++){
            char ch = line[i];
            if(ch == '<'){
                inTag = true;

            }
            else if(ch == '>'){
                inTag = false;


            }
            else if(!inTag){
                if(isalnum(ch)){

                    if(curLen < 99){

                        current[curLen++] = tolower(ch);
                    }
                }
                else if(curLen > 0){

                    current[curLen] = '\0';
                    char* word = new char[curLen + 1];
                    strcpy(word, current);
                    words[wordcount++] = word;
                    curLen = 0;
                }
            }
        }
    }

    // if (curLen > 0) {
    //     current[curLen] = '\0';
    //     char* word = new char[curLen + 1];
    //     strcpy(word, current);
    //     words[wordcount++] = word;
    // }

    file.close();
    }
    void filtercorrectwords(char* allWords[], int wordCount, char* filtered[], int& filteredCount) {
    filteredCount = 0;
    for(int i = 0; i < wordCount; i++){
        if(iscorrectword(allWords[i])){
            filtered[filteredCount++] = allWords[i];
        }
    }
}
};

int main(int argc, char* argv[]){
    cout << "Started\n";
    if(argc < 4){
        return 1;
    }

    char* url = argv[1];
    const char* folder = argv[2];
    depth = atoi(argv[3]);

    if(!urlvalid::isvalid(url)){
        cout << "Invalid URL: " << url << endl;
        return 1;
    }

    downloading downloader;
    mainoperation crawler;
    crawler.dfs(url,0,downloader,folder);

    cout << "visited: " << visited << endl;
    return 0;
}