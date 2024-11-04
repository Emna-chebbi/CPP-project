#include<fstream>
#include <iostream>
#include <string>
using namespace std;
class Personne {
private:
    int id;
    string Nom;
    string Prenom;
    string Mail;

public:
    Personne();
    Personne(int, string, string, string);
    ~Personne(){};

    int getId() const {
        return id;
    }

    string getNom() const {
        return Nom;
    }

    string getPrenom() const {
        return Prenom;
    }

    string getMail() const {
        return Mail;
    }

    void setId(int newId) {
        id = newId;
    }

    void setNom(const string& newNom) {
        Nom = newNom;
    }

    void setPrenom(const string& newPrenom) {
        Prenom = newPrenom;
    }

    void setMail(const string& newMail) {
        Mail = newMail;
    }

    friend istream& operator>>(istream& is,Personne& personne);
    friend ostream& operator<<(ostream& os, const Personne& personne);
};
Personne::Personne()
{
    this->setId(0);
    this->setNom(" ");
    this->setPrenom(" ");
    this->setMail(" ");
}
Personne::Personne(int tempId,string tempNom, string tempPrenom, string tempMail)
{
    this->setId(tempId);
    this->setNom(tempNom);
    this->setPrenom(tempPrenom);
    this->setMail(tempMail);
}
istream& operator>>(istream& is, Personne& personne) {
    int tempId;
    string tempNom, tempPrenom, tempMail;


    is >> tempId >> tempNom >> tempPrenom >> tempMail;

    personne.setId(tempId);
    personne.setNom(tempNom);
    personne.setPrenom(tempPrenom);
    personne.setMail(tempMail);
    return is;
}


ostream& operator<<(ostream& os, const Personne& personne) {
    os << personne.getId() << " " << personne.getNom() << " " << personne.getPrenom() << " " << personne.getMail()<<endl;

    return os;
}
