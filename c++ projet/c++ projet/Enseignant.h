
#include "Etudiant.h"
#include <iostream>

class Enseignant : public Personne {
private:
    int CNSS;

public:
    Enseignant();
    Enseignant(int id, string nom, string prenom, string mail, int CNSS);
    void Set (const Enseignant &);
    ~Enseignant();

    int getCNSS() const {
        return CNSS;
    }

    void setCNSS(int newCNSS) {
        CNSS = newCNSS;
    }

    friend istream& operator>>(istream& is, Enseignant& personne);
    friend ostream& operator<<(ostream& os, const Enseignant& Personne);
};
void Enseignant::Set (const Enseignant& enseignant)
{
    this->CNSS= enseignant.getCNSS();
    this->setId(enseignant.getId());
    this->setMail(enseignant.getMail());
    this->setNom( enseignant.getNom());
    this->setPrenom(enseignant.getPrenom());
}
istream& operator>>(istream& is, Enseignant& personne) {
    int tempId;
    int tempCNSS;
    string tempNom, tempPrenom, tempMail;

    is >> tempId >> tempNom >> tempPrenom >> tempMail>>tempCNSS;

    personne.setId(tempId);
    personne.setNom(tempNom);
    personne.setPrenom(tempPrenom);
    personne.setMail(tempMail);
    personne.CNSS=tempCNSS;
    return is;
}
std::ostream& operator<<(std::ostream& os, const Enseignant& personne) {
    os << personne.getId() << " " << personne.getNom() << " " << personne.getPrenom() << " " << personne.getMail() << " "<<personne.CNSS;
    return os;
}

Enseignant::Enseignant() : Personne() {CNSS=0;}

Enseignant::Enseignant(int id, std::string Nom, std::string Prenom, std::string Mail, int CNSS)
    : Personne(id, Nom, Prenom, Mail){this->CNSS=CNSS;}

Enseignant::~Enseignant() {
}


