#include <limits>
#include<fstream>
#include <string>
#include <vector>
#include "Matiere.h"
using namespace std;
class GroupeModule {
private:
    string IdGM;
    string NomGM;
    float CoefGM;
    vector<Matiere> ListeMat;

public:
    GroupeModule();
    GroupeModule(string IdGM, string NomGM, float CoefGM, vector<Matiere> ListeMat);
    void setid(string m){IdGM=m;};
    ~GroupeModule();
    string getIdGM(){return IdGM;};
    string getNomGM(){return NomGM;};
    vector<Matiere> getListeMat(){return ListeMat;};
    float getCoefGM(){return CoefGM;};
    friend istream& operator>>(istream& is, GroupeModule& groupemodule);
    friend ostream& operator<<(ostream& is, GroupeModule& groupemodule);
};
GroupeModule::GroupeModule() : IdGM(" "), NomGM(" "), CoefGM(0.0) {}

GroupeModule::GroupeModule(string IdGM, string NomGM, float CoefGM, vector<Matiere> ListeMat)
    : IdGM(IdGM), NomGM(NomGM), CoefGM(CoefGM), ListeMat(ListeMat) {}

GroupeModule::~GroupeModule() {}

istream& operator>>(istream& is, GroupeModule& groupemodule) {
    is >> groupemodule.IdGM >> groupemodule.NomGM >> groupemodule.CoefGM ;
    ifstream f(groupemodule.IdGM);
    Matiere m;
    while(f >> m){
        groupemodule.ListeMat.push_back(m);
    }
    return is;
}
ostream& operator<<(ostream& is, GroupeModule& groupemodule) {
   is<<" "<<groupemodule.getIdGM()<<" "<<groupemodule.getNomGM()<<" "<<groupemodule.getCoefGM()<<endl;
   ofstream f(groupemodule.IdGM);
   for (Matiere& mat : groupemodule.ListeMat) {
        f<<mat;
    }
    return is;
}
