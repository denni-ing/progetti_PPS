/*Classe per memorizzare account social Network
a) aggiungere account
b) ottenere i nomi degli account ordinati per numero di post decrescenti
c) permettere di scandire tutti gli account in sequenza*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class AccountBase{
public:
    virtual ~AccountBase() { }

    virtual std::string GetName() const = 0;
    virtual int GetFollowers() const = 0;
    virtual int GetPost() const = 0;

    static AccountBase* Build(const std::string& def);
};

class Account : public AccountBase{
protected:
    std::string name;
    int followers;
    int post;

public:
    Account(const std::string& name_,
            const int followers_,
            const int post_) :
            name(name_), followers(followers_), post(post_) { }

    virtual std::string GetName() const {return name;}
    virtual int GetFollowers() const {return followers;}
    virtual int GetPost() const {return post;}

    virtual ~Account() { }
};

class Person : public Account{
protected:
    std::string phone_number;

public:
    Person(const std::string& name_,
            const int followers_,
            const int post_,
            const std::string& phone_number_) :
            Account(name_, followers_, post_), phone_number(phone_number_) { }

    inline std::string GetPhone() const {return phone_number;}

    virtual ~Person() { }
};

class Company : public Account{
protected:
    std::string p_iva;

public:
    Company(const std::string& name_,
            const int followers_,
            const int post_,
            const std::string& p_iva_) : 
            Account(name_, followers_, post_), p_iva(p_iva_) { }

    inline std::string GetIva() const {return p_iva;}

    virtual ~Company() { }
};

class Social{
private:
    std::vector<AccountBase*> account;

    static bool CompareByPost(AccountBase* a, AccountBase* b){
        return a->GetPost() > b->GetPost();
    }

public:
    Social() { }
    ~Social(){
        for(const auto& iter : account){
            delete iter;
        }
    }

    void Add(AccountBase* a){
        account.push_back(a);
    }

    void SortByPost(){
        std::sort(account.begin(), account.end(), CompareByPost);
    }

    void Print() const{
        for(const auto& iter : account){
            std::cout << iter->GetName() << " " << iter->GetFollowers() << " " << iter->GetPost();
            std::cout << std::endl;
        }
    }
};

AccountBase* AccountBase::Build(const std::string& def){
    std::istringstream is(def);
    std::string type;
    is >> type;
    std::string name;
    int followers;
    int post;
    is >> name >> followers >> post;

    if(type=="Person"){
        std::string phone_number;
        is >> phone_number;
        return new Person(name, followers, post, phone_number);
    }

    if(type=="Company"){
        std::string p_iva;
        is >> p_iva;
        return new Company(name, followers, post, p_iva);
    }
    
    std::cerr << "Not well defined Account from line " << def << std::endl;
    return nullptr;
}

int main(){
    Social s;

    std::vector<std::string> inputs = {
        "Person Alice 150 20 1234567890",
        "Company OpenAI 1000 50 IT123456789",
        "Person Bob 75 10 0987654321"
    };

    for(const auto& line : inputs){
        AccountBase* acc = AccountBase::Build(line);
        if(acc)
            s.Add(acc);
    }

    std::cout << "Before sort:" << std::endl;
    s.Print();

    s.SortByPost();
    std::cout << "\nAfter sort:" << std::endl;
    s.Print();

    return 0;
}