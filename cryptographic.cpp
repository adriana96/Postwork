#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <map>
#include <random>
#include <numeric>
 

std::map<char, char> createMap();
void showMap(std::map<char,char> & m);
void encrypt(std::string & s, std::map<char,char> & m);
void decrypt(std::string & s, std::map<char,char> & m); 

int main ()
 {
     std::string s = "Ala ma kota";
     std::map<char, char> mc = createMap();
     encrypt(s,mc);
     std::cout << std::endl;
     decrypt(s,mc);
     std::cout << std::endl;
     return 0;
 }

std::map<char, char> createMap() {

    std::vector<int> v(95);
    std::iota(v.begin(), v.end(), 32);
    std::vector<char> word(v.size());
    std::vector<char> cypher(v.size());
    std::transform(v.begin(), v.end(), word.begin(), [](int i) {return static_cast<char>(i);});
    std::transform(v.begin(), v.end(), cypher.begin(), [](int i) {return static_cast<char>(i);});

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cypher.begin(), cypher.end(), g);

    std::map<char, char> m;
    for(auto i = 0; i <= word.size(); i++ ) 
        m.emplace(std::make_pair(word[i], cypher[i]));
    return m;
}

void showMap(std::map<char,char> & m) {

    for (const auto & a : m) {
        std::cout << a.first << " " << a.second << std::endl;
    }
}

void encrypt(std::string & s, std::map<char,char> & m) {

    std::vector<char> cs(s.c_str(),s.c_str() + s.size() + 1);

    for (const auto & i : cs) {
        auto search  = m.find(i);
        if(search != m.end())
            std::cout << search->second;
    }
}

void decrypt(std::string & s, std::map<char,char> & m) {

    std::vector<char> cs(s.c_str(),s.c_str() + s.size() + 1);

    for (const auto & i : cs) {
        auto search = std::find_if(m.begin(), m.end(),[=](const auto & m) {return m.second == i;});
        if (search != m.end())
            std::cout << search->first;
    }
}

