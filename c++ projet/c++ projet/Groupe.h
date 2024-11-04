#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include"Note.h"
using std::ostream;
using std::istream;
using namespace std;
class Groupe {
private:
    string IdGRP;
    string Niveau;
    string Diplome;
    string Specialite;
    int Num_G;
    vector<Etudiant> ListeEtudiants;
    vector<GroupeModule> ListeModules;

public:
    Groupe();
    Groupe(string, string, string, string, int, vector<Etudiant>, vector<GroupeModule>);
    ~Groupe();

    friend ostream& operator<<(ostream& os, Groupe& groupe) {
        os << groupe.IdGRP << " " << groupe.Niveau << " " << groupe.Diplome << " " << groupe.Specialite << " " << groupe.Num_G <<endl;
           string path1="liste_etudiant_";
           string path2="liste_module_";
        ofstream f(path1+groupe.IdGRP);
        for (const Etudiant& etu : groupe.ListeEtudiants) {
            f << etu;
        }
        ofstream f2(path2+groupe.IdGRP);
        for (size_t i=0;i<groupe.ListeModules.size();i++) {
            f2 << groupe.ListeModules[i];
        }

        return os;
    }

    friend istream& operator>>(istream& is, Groupe& groupe) {
        is >> groupe.IdGRP >> groupe.Niveau >> groupe.Diplome >> groupe.Specialite >> groupe.Num_G;
        string path1="liste_etudiant_";
        string path2="liste_module_";
        Etudiant e;
        GroupeModule m;
        groupe.ListeEtudiants.clear();
        groupe.ListeModules.clear();
        ifstream f(path1+groupe.IdGRP);
        while(f>>e)
        {
            groupe.ListeEtudiants.push_back(e);
        }
        ifstream f2(path2+groupe.IdGRP);
        while(f2>>m)
        {
            groupe.ListeModules.push_back(m);
        }
        return is;
    }

    void setListeEtudiants(const vector<Etudiant>& students) {
        ListeEtudiants = students;
    }

    void addEtudiant(const Etudiant& etudiant) {
        this->ListeEtudiants.push_back(etudiant);
    }
    void addModule(const GroupeModule& module) {
        this->ListeModules.push_back(module);
    }
    string getIdGRP() const {
        return IdGRP;
    }

    string getNiveau() const {
        return Niveau;
    }

    string getDiplome() const {
        return Diplome;
    }

    string getSpecialite() const {
        return Specialite;
    }

    int getNum_G() const {
        return Num_G;
    }

    vector<Etudiant> getListeEtudiants() const {
        return ListeEtudiants;
    }

    vector<GroupeModule> getListeModules() const {
        return ListeModules;
    }

    void setIdGRP(const string& id) {
        IdGRP = id;
    }

    void setNiveau(const string& niveau) {
        Niveau = niveau;
    }

    void setDiplome(const string& diplome) {
        Diplome = diplome;
    }

    void setSpecialite(const string& specialite) {
        Specialite = specialite;
    }

    void setNum_G(int numG) {
        Num_G = numG;
    }



    void setListeModules(const vector<GroupeModule>& modules) {
        ListeModules = modules;
    }
};

Groupe::Groupe() : IdGRP(" "), Niveau(" "), Diplome(" "), Specialite(" "), Num_G(0) {}

Groupe::Groupe(string idgrp, string Niv, string Dipl, string Spe, int num_g, vector<Etudiant> listeetudiant, vector<GroupeModule> listemodules)
    : IdGRP(idgrp), Niveau(Niv), Diplome(Dipl), Specialite(Spe), Num_G(num_g), ListeEtudiants(listeetudiant), ListeModules(listemodules) {}

Groupe::~Groupe() {}
