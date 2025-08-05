#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>


class Word{
private:
  typedef std::map<std::string, int> Word2Freq;
  Word2Freq word2freq;

  static void Clean(std::string* word){
    // Rimuove punteggiatura
    word->erase(std::remove_if(word->begin(), word->end(),
			       [](unsigned char c){ return std::ispunct(c); }),
		word->end());
    
    // Rende tutto minuscolo
    std::transform(word->begin(), word->end(), word->begin(),
		   [](unsigned char c){ return std::tolower(c); });
  }
  
  
  
public:
  Word(const std::string& filename);
  void Print() const;
  int GetFreq(const std::string& word) const;	
};

Word::Word(const std::string& filename){
  std::ifstream is(filename);
  if(!is.good()){
    std::cerr << "Can not open this file" << std::endl;
    return;
  }
  std::string word;
  while(is >> word){
    Clean(&word);
    word2freq[word]++;
  }
}

void Word::Print() const{
  for(const auto& iter : word2freq){
    std::cout << iter.first << "->" << iter.second << "\n";
  }
}

int Word::GetFreq(const std::string& word) const{
  Word2Freq::const_iterator iter = word2freq.find(word);
  return (iter!=word2freq.end() ? iter->second : 0);
}

int main(){

  Word ta("divina_commedia.txt");

  ta.Print();
  std::cout << "beatrice freq: " << ta.GetFreq("beatrice") << std::endl; 
  
  return 0;
}
