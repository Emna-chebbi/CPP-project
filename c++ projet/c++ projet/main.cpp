#include <iostream>
#include"Menu.h"
#include<fstream>
#include<vector>

using namespace std;
int main() {
    const string fichierStudents="students.txt";
    const string fichierTeachers = "teachers.txt";
    const string fichiersMatieres = "matieres.txt";
    const string fichiereNotes = "notes.txt";
    const string fichierGroupesModules = "groupe_module.txt";
    const string fichierGroupes = "groupes.txt";
Enseignant ens;
Etudiant e;
Note n;
Matiere m;
GroupeModule gm;
Groupe g;
  ifstream teacherFile("teachers.txt");
while(teacherFile>>ens)
{
    teachers.push_back(ens);
}
 ifstream studentFile("students.txt");
while(studentFile>>e)
{
    students.push_back(e);
}
ifstream MatiereFile("matieres.txt");
while(MatiereFile>>m)
{
    matieres.push_back(m);
}
ifstream moduleFile("groupe_module.txt");
while(moduleFile>>gm)
{
    groupeModules.push_back(gm);
}
ifstream noteFile("notes.txt");
while(noteFile>>n)
{
    notes.push_back(n);
}
ifstream groupeFile("groupes.txt");
while(groupeFile>>g)
{
    groupes.push_back(g);
}

afficherMenuPrincipal();
    return 0;
}

