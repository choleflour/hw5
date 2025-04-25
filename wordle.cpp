#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> combos;
    std::set<std::string> words;
    std::multiset<char> floatset(floating.begin(), floating.end());
    size_t open = 0;
    for (size_t i = 0; i < in.length(); ++i) {
        if (in[i] == '-') {
            open ++;
        }
    }
    wordle_helper(in, in.length(), open, floatset, "", combos);

    for (auto it = combos.begin(); it != combos.end(); ++it) {
        // valid word
        if (dict.find(*it) != dict.end()) {
            words.insert(*it);
        }
    }
    return words;


}



// Define any helper functions here
void wordle_helper(const std::string& in, size_t n, size_t open, std::multiset<char> floating, std::string letters, std::set<std::string>& combos ) {
    if (n == 0) {
        combos.insert(letters);
        return;
    }
    int pos = in.length() - n;
    // not fixed
    if (in[pos] == '-') {
        if (open == floating.size()) {
            std::multiset<char>::iterator it;
            for ( it = floating.begin(); it != floating.end(); ++it) {
                char l = *it;
                std::multiset<char> new_floating = floating;
                std::multiset<char>::iterator it2 = new_floating.find(l);
                new_floating.erase(it2);
                wordle_helper(in, n-1, open-1, new_floating, letters + l, combos);
            }            
        } else {
            for (int i = 0; i < 26; i ++) {
                char letter = 'a' + i;
                // letter is yellow
                if (floating.find(letter) != floating.end()) {
                    std::multiset<char> new_floating = floating;
                    std::multiset<char>::iterator it2 = new_floating.find(letter);
                    new_floating.erase(it2);
                    wordle_helper(in, n-1, open-1, new_floating, letters + letter, combos);
                } else {
                    wordle_helper(in, n-1, open-1, floating, letters + letter, combos);
                }
                // wordle_helper(in, n-1, open, floating, letters + letter, combos);
            }

        }



    } else {
        wordle_helper(in, n-1, open, floating, letters + in[pos], combos);
    }
    
}