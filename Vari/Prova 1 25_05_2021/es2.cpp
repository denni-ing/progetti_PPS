/*Software per tradurre testo*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

class TranslatorBase{
public:
    virtual void TranslateText(const std::string& text) = 0;
};

class Translator : public TranslatorBase{
protected:
    typedef std::map<std::string, std::string> Word2Translation;
    Word2Translation word2translation;

public:
    Translator(const std::string dictionary){
        std::ifstream is(dictionary);
        std::string word;
        std::string translation;
        while(is >> word >> translation){
            word2translation[word] = translation;
        }
    }

    void TranslateText(const std::string& text){
        std::vector<std::string> newText;
        std::ifstream is(text);
        if(!is.good()){
            std::cerr << "Can not open file " << text << std::endl;
            return;
        }

        std::string word;
        while(is >> word){
            std::string newWord;
            const auto& iter = word2translation.find(word);
            if(iter!=word2translation.end()){
                newWord = word2translation[word];
                newText.push_back(newWord);
            }else{
                newText.push_back(word);
            }
        }

        for(const auto& iter : newText){
            std::cout << iter << " ";
        }
        std::cout << std::endl;
    }

};

int main(){
    Translator tr("dictionary.txt");
    tr.TranslateText("text.txt");
    return 0;
}