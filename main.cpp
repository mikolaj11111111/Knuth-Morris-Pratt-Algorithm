#include <iostream>
#include <vector>
#include <string>

using namespace std;

void KMP(string pattern, vector<int>& pattern_val) {

    int pattern_len = pattern.length();
    int prefiks_count = 0; 
    
    //pattern_val[0] = 0; 

    for (int i = 1; i < pattern_len; i++) {
        /*
        while (prefiks_count > 0 && pattern[i] != pattern[prefiks_count]) {
            cout << "wchodze do while dla i: " << i << " pattern[i]: " << pattern[i] << endl;
            cout << "before prefiks_count: " << prefiks_count << endl;
            prefiks_count = pattern_val[prefiks_count - 1]; // cofniecie do poprzedniego zgodnego prefiksu
            cout << "after prefiks_count: " << prefiks_count << endl;
        }
        */

        if (pattern[i] != pattern[prefiks_count]) {
            prefiks_count = 0;
        }

        else if (pattern[i] == pattern[prefiks_count]) {
            prefiks_count++; 
        }

        pattern_val[i] = prefiks_count;
    }

    cout << "Tablica pattern_val: ";
    for (int i = 0; i < pattern_len; i++) {
        cout << pattern_val[i] << " ";
    }
    cout << endl;
}

void KMPSearch(string pattern, vector<int>& pattern_val, string text, int max_index) {
    int text_len = text.length();
    int pattern_len = pattern.length();

    int i = 0; 
    int j = 0; 
    
    while (i < text_len) {
        if (pattern[j] == text[i]) {
            //przesuwamy sie o jedno dalej(w prawo)
            j++;
            i++;
        }

        if (j == pattern_len) {
            cout << "Znaleziono wzorzec na pozycji: " << i - j << endl;
            j = pattern_val[j - 1]; // kontynujemy wyszukiwania po kolejny wzorec w tekscie
        }
        else if (i < text_len && pattern[j] != text[i]) {
            // iedopasowanie po czesciowym dopasowaniu
            if (j > 0) {
                j = pattern_val[j - 1]; // przesuwamy wzorzec
            }
            else {
                i++; // przesuwamy tekst
            }
        }
    }
}


int FindMaxInKMP(string pattern, vector<int>& pattern_val) {
    int max_val = pattern_val[0];
    int max_index = 0;
    for (int i = 1; i < pattern.length(); i++) {
        for (int j = 0; j < i; j++) {
            if (pattern_val[j] > pattern_val[i]) {
                max_val = pattern_val[j];
                max_index = j;
            }
        }
    }
    cout << "max_val: " << max_val << " max_index: " << max_index << endl;
    return max_index;
}



int main() {
    string txt = "bacbababaabab";
    string pattern = "ababababca";

    vector<int> pattern_values(pattern.length(), 0);

    KMP(pattern, pattern_values);
    int index = FindMaxInKMP(pattern, pattern_values);
    KMPSearch(pattern, pattern_values, txt, index);

    return 0;
}
