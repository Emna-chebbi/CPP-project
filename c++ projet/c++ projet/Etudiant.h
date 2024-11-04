#include <iostream>
#include <string>
#include "Personne.h"
using namespace std;

class Etudiant : public Personne {
private:
    int NumInsc;

public:
    Etudiant();
    Etudiant(int, string, string, string, int);
    ~Etudiant();

  friend istream& operator>>(istream& is,Etudiant& personne);
    friend ostream& operator<<(ostream& os, const Etudiant& personne);

    int getNumInsc() const {
        return NumInsc;
    }

    void setNumInsc(int newNumInsc) {
        NumInsc = newNumInsc;
    }
};
istream& operator>>(istream& is, Etudiant& personne) {
    int tempId;
    int tempNum;
    string tempNom, tempPrenom, tempMail;

    is >> tempId >> tempNom >> tempPrenom >> tempMail>>tempNum;

    personne.setId(tempId);
    personne.setNom(tempNom);
    personne.setPrenom(tempPrenom);
    personne.setMail(tempMail);
    personne.NumInsc=tempNum;
    return is;
}
ostream& operator<<(ostream& os, const Etudiant& personne) {
    os << personne.getId() << " " << personne.getNom() << " " << personne.getPrenom() << " " << personne.getMail() << " "<<personne.NumInsc<<endl;
    return os;
}
Etudiant::Etudiant() : Personne() {NumInsc=0;}

Etudiant::Etudiant(int id, string nom, string prenom, string mail, int numInsc)
    : Personne(id, nom, prenom, mail), NumInsc(numInsc) {}

Etudiant::~Etudiant() {}
