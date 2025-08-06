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
        return (!strstr(url,".css") && !strstr(url,".pdf") && !strstr(url,".jpg") && !strstr(url,".png") && !strstr(url,".js"));
    }

    static void normalizeURL(const char* url, const char* rel, char* curl) {
        if(strncmp(rel, "http", 4) == 0) {
            strcpy(curl, rel);
        }
        else{

            
            strcpy(curl, url);
            for (int i = strlen(curl)-1; i >= 0; i--){
                if(curl[i] == '/'){
                    curl[i + 1] = '\0';
                    break;
                }
            }
            strcat(curl, rel);
        }
    }



    static void extractLinks(const char* filepath){
        ifstream file(filepath);
        char line[2000];
        while (file.getline(line, sizeof(line))) {
            char* pos = line;
            

            char* atag= strstr(pos,"<a");
            while (atag != NULL) {
                char* start = strstr(atag, "href=\"");
                if(start!=NULL){
                    start += 6;
                    char* end = strchr(start, '"');
                    
                        int len = end-start;
                        
                            char* link = new char[len + 1];

                            strncpy(link, start, len);
                            link[len] = '\0';

                            if(endsWithHTML(link)){
                                l1.insertAtEnd(link);
                                
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

        int n = l1.length();
        for(int i = 0; i<n && visited<totallinks; i++){
            char* rel = l1.getAt(i);
            char curl[1000];
            normalizeURL(url, rel, curl);
            dfs(curl, curDepth + 1, downloader, folder);
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
