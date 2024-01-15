#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include "motlepluslong.h"
using namespace std;

#ifdef _WIN32// pour le e accentuer 
#include <Windows.h>
#endif


vector<list<Article>>* DIC(int n, const string& nomF)
{
    ifstream fichier(nomF.c_str(), ios::in);
    vector<list<Article>>* dico = new vector<list<Article>>(n);

    if (fichier)
    {
        string mot;
        while (fichier >> mot)
        {
            if (mot.length() <= n)
            {
                (*dico)[mot.length() - 1].push_back(Article(mot));
            }
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    return dico;
}

void generateWords(const char* characters, int length, vector<string>& result, string current = "", int index = 0) {
    if (index == length) {
        result.push_back(current);
        return;
    }

    // Include the current character in the current combination
    generateWords(characters, length, result, current + characters[index], index + 1);

    // Exclude the current character from the current combination
    
    generateWords(characters, length, result, current, index + 1);

    result.erase(remove(result.begin(), result.end(), ""), result.end());

    // Sort by length and then alphabetically
    sort(result.begin(), result.end(), [](const string& a, const string& b) {
        if (a.length() == b.length()) {
            return a < b;
        }
        return a.length() > b.length();
    });

}

string chercherMotLePlusLong(const vector<string>& sequence, int n, const string& nomF,int &i)
{   
    string ok ="vide";
    
     string sequenceT = sequence[i];
    sort(sequenceT.begin(), sequenceT.end());

    if(sequence[i]=="") return ok;
    vector<list<Article>>* dicos = DIC(n, nomF);
    
    // Recherche directe dans la liste dicos[taille]
    for (const auto& article : (*dicos)[sequenceT.length() - 1])
    {
        if (article.pmot == sequenceT)
        {
            
            delete dicos; // N'oubliez pas de libérer l'espace mémoire alloué pour dicos
            cout<<"le mot le plus long est : ";cout << article.mot<<endl;
            return article.mot;
        }
    }
    i++;
   

    delete dicos; // N'oubliez pas de libérer l'espace mémoire alloué pour dicos
    return  chercherMotLePlusLong(sequence,n, nomF,i);
}


int main(int argc, char *argv[]) 
{

int n=strlen(argv[1]);
    
vector<string> result;

generateWords(argv[1], n, result);

int i= 0 ;

string a=chercherMotLePlusLong(result,n,"francais.txt",i);
if(a=="vide"){cout<<"aucun mot trouve"<<endl;}
    return 0;
}