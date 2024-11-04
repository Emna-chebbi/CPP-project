#include <iostream>
#include <string>
#include<fstream>
#include "Enseignant.h"
using namespace std;

class Matiere {
private:
    string IdMat;
    string NomMat;
    float coef;
    Enseignant Ens;

public:
    Matiere();
    Matiere(int id, string nom, float coef, const Enseignant& ens);
    Matiere( const Matiere &M);
    ~Matiere();

    string getIdMat() const;
    string getNomMat() const;
    float getCoef() const;
    Enseignant getEnseignant() const;

    void setIdMat(const string& idMat);
    void setNomMat(const string& nomMat);
    void setCoef(float coef);
    void setEns(const Enseignant& ens);
    Enseignant getEnseignantByIdFromFile(int enseignantId);

    friend istream& operator>>(istream& is, Matiere& matiere);
    friend ostream& operator<<(ostream& os, const Matiere& matiere);
};
Enseignant Matiere::getEnseignantByIdFromFile(int enseignantId) {
    int trouve=0;
    Enseignant e;
    Enseignant r;
     ifstream liste("teachers.txt");
     while (liste>>e){
        if (e.getCNSS() == enseignantId) {
                trouve=1;
                break;
        }
    }
    if (trouve==0){return r;}
    else return e;
}
Matiere::Matiere(const Matiere &M)
{
    this ->setNomMat(M.getNomMat());
    this->setIdMat(M.getIdMat());
    this->setEns(M.getEnseignant());
    this->setCoef(M.getCoef());

}
istream& operator>>(istream& is, Matiere& matiere) {
    int cnss;
    string IdMat;
    string NomMat;
    float coef;
    is>>IdMat>>NomMat>>coef>>cnss;
    matiere.setCoef(coef);
    matiere.setIdMat(IdMat);
    matiere.setNomMat(NomMat);
    matiere.Ens.Set(matiere.getEnseignantByIdFromFile(cnss));
    return is;
}

ostream& operator<<(ostream& os, const Matiere& matiere) {
    os << matiere.getIdMat() << " " << matiere.getNomMat() << " " << matiere.getCoef() << " " << matiere.getEnseignant().getCNSS()<<endl;
    return os;
}

Matiere::Matiere() : IdMat("0"), NomMat(" "), coef(0), Ens() {}

Matiere::Matiere(int id, string nom, float coef, const Enseignant& ens)
    : IdMat(to_string(id)), NomMat(nom), coef(coef), Ens(ens) {}



string Matiere::getIdMat() const {
    return IdMat;
}

string Matiere::getNomMat() const {
    return NomMat;
}

float Matiere::getCoef() const {
    return coef;
}

Enseignant Matiere::getEnseignant() const {
    return Ens;
}

void Matiere::setIdMat(const string& idMat) {
    IdMat = idMat;
}

void Matiere::setNomMat(const string& nomMat) {
    NomMat = nomMat;
}

void Matiere::setCoef(float coef) {
    this->coef = coef;
}

void Matiere::setEns(const Enseignant& ens) {
    this->Ens = ens;
}

Matiere::~Matiere() {}
