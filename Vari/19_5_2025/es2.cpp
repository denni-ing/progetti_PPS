#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

class EBook {
public:
  typedef std::vector<std::string> Pages;
  typedef std::set<int> Indexes;
  typedef std::map<std::string, std::set<int>> Word2Indexes;

private:
  Pages pages;
  Word2Indexes word2indexes;

public:
  static const Indexes invalid_indexes;

  EBook() {}
  void AddPage(const std::string& page) {
    pages.push_back(page);
    std::istringstream is(page);
    std::string word;
    while (is >> word) {
      // TODO: remove punctuation from word.
      word2indexes[word].insert(pages.size() - 1);
    }
  }

  const Indexes& FindInPages(const std::string& word) const {
    auto indexes_iter = word2indexes.find(word);
    if (indexes_iter == word2indexes.end()) {
      return invalid_indexes;
    }
    return indexes_iter->second;
  }

  class Iterator {
   private:
    const EBook* ebook = nullptr;
    int index = -1;

  public:
    Iterator(const EBook& ebook_, unsigned int start_index) :
      ebook(&ebook_), index(start_index) {}

    std::string GetNext() {
      if (index + 1 < (int)(ebook->pages.size())) {
	index++;
      }
      return ebook->pages[index];
    }
    std::string GetPrevious() {
      if (index >= 1) {
	index--;
      }
      return ebook->pages[index];
    }
    bool HasNext() const {
      return index + 1 < (int)(ebook->pages.size());
    }
    bool HasPrevious() const {
      return index >= 1;
    }
  };
};

const EBook::Indexes EBook::invalid_indexes = EBook::Indexes();

int main() {
  EBook ebook;
  ebook.AddPage("Marco corre nella nebbia");
  ebook.AddPage("Nel mezzo del cammin di nostra vita");
  ebook.AddPage("La nebbia agli irti colli sale");

  EBook::Iterator iter(ebook, -1);
  while (iter.HasNext()) {
    std::cout << iter.GetNext() << std::endl;
  }

  // Now I can have multiple separate iterators for different readers.
  // EBook::Iterator iter1(ebook);
  // EBook::Iterator iter2(ebook);
  // ...

  const EBook::Indexes& results = ebook.FindInPages("nebbia");
  for (auto index : results) {
    std::cout << index << std::endl;
  }
  return 0;
}
