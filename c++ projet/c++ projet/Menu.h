#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include"Groupe.h"
#include<iomanip>
#include<limits>
class GroupeModule;
using namespace std;

vector<Etudiant> students;
vector<Enseignant> teachers;
vector<Matiere> matieres;
vector<Note>notes;
vector<GroupeModule> groupeModules;
vector<Groupe> groupes;

void GestionEtudiants();
void GestionEnseignants();
void GestionMatieres();
void afficherMenuPrincipal();


void AjoutEtudiant() {
    int id, NumInsc;
    string nom, prenom, mail;

    cout << "Enter student ID: ";
    cin >> id;

    cout << "Enter student Nom: ";
    cin >> nom;

    cout << "Enter student Prenom: ";
    cin >> prenom;

    cout << "Enter student Mail: ";
    cin >> mail;

    cout << "Enter student NumInsc: ";
    cin >> NumInsc;

    Etudiant newStudent(id, nom, prenom, mail, NumInsc);
    students.push_back(newStudent);

       ofstream outputFile("students.txt", ios::app);
    if (outputFile.is_open()) {

        if (outputFile.tellp() != 0) {
            outputFile << endl;
        }

        outputFile << id << " " << nom << " " << prenom << " " << mail << " " << NumInsc << endl;
        outputFile.close();
        cout << "Student added successfully." << endl;
    } else {
        cout << "Error updating file." << endl;
    }
}

void supprimerEtudiant() {
    int studentId;
    size_t i=0;
    cout << "Enter the ID of the student to delete: ";
    cin >> studentId;
    for( i=0;i<students.size();i++)
    {
        if(students[i].getId()==studentId) break;
    }
    if (i != students.size()) {
        students.erase(students.begin()+i);
        cout << "Student deleted successfully." << endl;

        ofstream outputFile("students.txt", ios::trunc);

        if (!outputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }

        for (const Etudiant& student : students) {
            outputFile << student.getId() << " "
                       << student.getNom() << " "
                       << student.getPrenom() << " "
                       << student.getMail() << " "
                       << student.getNumInsc() << endl;
        }

        outputFile.close();
    } else {
        cout << "Student with ID " << studentId << " not found." << endl;
    }
}


void RechercherEtudiant() {
    int studentId;
    cout << "Enter the ID of the student to search: ";
    cin >> studentId;

    ifstream inputFile("students.txt");

    if (inputFile.is_open()) {
        string line;
        bool studentFound = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            int id;

            if (iss >> id && id == studentId) {
                studentFound = true;
                cout << "Student found: " << line << endl;
                break;
            }
        }

        inputFile.close();

        if (!studentFound) {
            cout << "Student with ID " << studentId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}

void ModifierEtudiant() {
    int studentId;
    cout << "Enter the ID of the student to modify: ";
    cin >> studentId;

    ifstream inputFile("students.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        bool studentFound = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            int id;

            if (iss >> id && id == studentId) {

                string newNom, newPrenom, newMail;
                int newNumInsc;

                cout << "Enter new Nom: ";
                cin >> newNom;

                cout << "Enter new Prenom: ";
                cin >> newPrenom;

                cout << "Enter new Mail: ";
                cin >> newMail;

                cout << "Enter new NumInsc: ";
                cin >> newNumInsc;

                tempFile << studentId << " " << newNom << " " << newPrenom << " " << newMail << " " << newNumInsc << endl;

                studentFound = true;
            } else {
                tempFile << line << endl;
            }
        }


        inputFile.close();
        tempFile.close();

        remove("students.txt");

        rename("temp.txt", "students.txt");

        if (studentFound) {
            cout << "Student with ID " << studentId << " modified successfully." << endl;
        } else {
            cout << "Student with ID " << studentId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}


void AjoutEnseignant() {
    int id, CNSS;
    string nom, prenom, mail;

    cout << "Enter teacher ID: ";
    cin >> id;

    cout << "Enter teacher Nom: ";
    cin >> nom;

    cout << "Enter teacher Prenom: ";
    cin >> prenom;

    cout << "Enter teacher Mail: ";
    cin >> mail;

    cout << "Enter teacher CNSS: ";
    cin >> CNSS;

    Enseignant newTeacher(id, nom, prenom, mail, CNSS);
    teachers.push_back(newTeacher);

    ofstream outputFile("teachers.txt", ios::app);

    if (outputFile.is_open()) {
        if (outputFile.tellp() != 0) {
            outputFile << endl;
        }

        outputFile << id << " " << nom << " " << prenom << " " << mail << " " << CNSS << endl;
        outputFile.close();
        cout << "Teacher added successfully." << endl;
    } else {
        cout << "Error updating file." << endl;
    }
}


void supprimerEnseignant() {
    int enseignantId;
    cout << "Enter the ID of the teacher to delete: ";
    cin >> enseignantId;

    auto it = find_if(teachers.begin(), teachers.end(), [enseignantId](const Enseignant& e) {
        return e.getId() == enseignantId;
    });

    if (it != teachers.end()) {

        teachers.erase(it);
        cout << "Teacher deleted successfully." << endl;

        ofstream outputFile("teachers.txt", ios::trunc);

        if (!outputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }

        for (const Enseignant& enseignant : teachers) {
            outputFile << enseignant.getId() << " "
                       << enseignant.getNom() << " "
                       << enseignant.getPrenom() << " "
                       << enseignant.getMail() << " "
                       << enseignant.getCNSS() << endl;
        }

        outputFile.close();
    } else {
        cout << "Teacher with ID " << enseignantId << " not found." << endl;
    }
}

void RechercherEnseignant() {
    int teacherId;
    cout << "Enter the ID of the teacher to search: ";
    cin >> teacherId;

    ifstream inputFile("teachers.txt");

    if (inputFile.is_open()) {
        string line;
        bool teacherFound = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            int id;

            if (iss >> id && id == teacherId) {
                teacherFound = true;
                cout << "Teacher found: " << line << endl;
                break;
            }
        }

        inputFile.close();

        if (!teacherFound) {
            cout << "Teacher with ID " << teacherId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}

void ModifierEnseignant() {
    int teacherId;
    cout << "Enter the ID of the teacher to modify: ";
    cin >> teacherId;

    ifstream inputFile("teachers.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        bool teacherFound = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            int id;

            if (iss >> id && id == teacherId) {
                string newNom, newPrenom, newMail;
                int newCNSS;

                cout << "Enter new Nom: ";
                cin >> newNom;

                cout << "Enter new Prenom: ";
                cin >> newPrenom;

                cout << "Enter new Mail: ";
                cin >> newMail;

                cout << "Enter new CNSS: ";
                cin >> newCNSS;

                tempFile << teacherId << " " << newNom << " " << newPrenom << " " << newMail << " " << newCNSS << endl;

                teacherFound = true;
            } else {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        remove("teachers.txt");
        rename("temp.txt", "teachers.txt");

        if (teacherFound) {
            cout << "Teacher with ID " << teacherId << " modified successfully." << endl;
        } else {
            cout << "Teacher with ID " << teacherId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}


void GestionEtudiants() {
    int choix=0;

    while (choix != 5){
        cout << "1. Ajouter un Etudiant" << endl;
        cout << "2. Supprimer un Etudiant" << endl;
        cout << "3. Rechercher un Etudiant" << endl;
        cout << "4. Modifier un Etudiant" << endl;
        cout << "5. Retour au Menu Principal" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choix;

        switch (choix) {
            case 1:
                AjoutEtudiant();
                break;
            case 2:
                supprimerEtudiant();
                break;
            case 3:
                RechercherEtudiant();
                break;
            case 4:
                ModifierEtudiant();
                break;
            case 5:
                system("cls");
                break;
        }
    }
}

Matiere matiere;
void AjoutMatiere() {
    int id;
    string nom;
    float coef;
    int idEnseignant;

    cout << "Entrer Matiere ID: ";
    cin >> id;

    cout << "Entrer Matiere Nom: ";
    cin >> nom;

    cout << "Entrer Matiere Coefficient: ";
    cin >> coef;

    cout << "Entrer Enseignant ID for the Matiere: ";
    cin >> idEnseignant;

    Enseignant enseignant = matiere.getEnseignantByIdFromFile(idEnseignant);

    cout << "Retrieved Teacher Information:" << endl;
    cout << "ID: " << enseignant.getId() << endl;
    cout << "Nom: " << enseignant.getNom() << endl;
    cout << "Prenom: " << enseignant.getPrenom() << endl;
    cout << "Mail: " << enseignant.getMail() << endl;
    cout << "CNSS: " << enseignant.getCNSS() << endl;

    matieres.push_back(Matiere(id, nom, coef, enseignant));

    ofstream outputFile("matieres.txt", ios::app);

    if (outputFile.is_open()) {
        if (outputFile.tellp() != 0) {
            outputFile << endl;
        }

        outputFile << id << " " << nom << " " << coef << " " << idEnseignant << endl;
        outputFile.close();
        cout << "Matiere added successfully." << endl;
    } else {
        cout << "Error updating file." << endl;
    }
}


void supprimerMatiere() {
    string matiereId ;size_t i=0;
    cout << "Enter the ID of the matiere to delete: ";
    cin >> matiereId;

    for(i=0;i<matieres.size();i++)
    {
        cout<<matieres[i].getIdMat() ;
        if(matieres[i].getIdMat() == matiereId) break;
    }

    if (i != matieres.size()) {

        matieres.erase(matieres.begin()+i);
        cout << "Matiere deleted successfully." << endl;


        ofstream outputFile("matieres.txt", ios::trunc);

        if (!outputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }

        for (const Matiere& matiere : matieres) {
            outputFile << matiere.getIdMat() << " "
                       << matiere.getNomMat() << " "
                       << matiere.getCoef() << " "
                       << matiere.getEnseignant().getId() << endl;
        }


        outputFile.close();
    } else {
        cout << "Matiere with ID " << matiereId << " not found." << endl;
    }
}

void RechercherMatiere() {
    int subjectId;
    cout << "Enter the ID of the subject to search: ";
    cin >> subjectId;

    ifstream subjectsFile("matieres.txt");

    if (subjectsFile.is_open()) {
        string subjectLine;
        bool subjectFound = false;

        while (getline(subjectsFile, subjectLine)) {
            istringstream subjectIss(subjectLine);
            int subjectIdFromFile;

            if (subjectIss >> subjectIdFromFile && subjectIdFromFile == subjectId) {
                subjectFound = true;
                cout << "Matiere found: " << subjectLine << endl;
                break;
            }
        }

        if (!subjectFound) {
            cout << "Matiere with ID " << subjectId << " not found." << endl;
        }

        subjectsFile.close();
    } else {
        cerr << "Error opening the file." << endl;
    }
}


void ModifierMatiere() {
   int matiereId;
    cout << "Enter the ID of the Matiere to modify: ";
    cin >> matiereId;

    ifstream matieresFile("matieres.txt");
    ofstream tempFile("temp.txt");

    if (matieresFile.is_open() && tempFile.is_open()) {
        string matiereLine;
        bool matiereFound = false;

        while (getline(matieresFile, matiereLine)) {
            istringstream matiereIss(matiereLine);
            int id;

            if (matiereIss >> id && id == matiereId) {
                string newNom;
                float newCoef;
                int idEnseignant;

                cout << "Enter new Nom: ";
                cin >> newNom;

                cout << "Enter new Coefficient: ";
                cin >> newCoef;

                cout << "Enter new Enseignant ID: ";
                cin >> idEnseignant;

                tempFile << matiereId << " " << newNom << " " << newCoef << " " << idEnseignant << endl;

                matiereFound = true;
            } else {
                tempFile << matiereLine << endl;
            }
        }

        matieresFile.close();
        tempFile.close();

        remove("matieres.txt");
        rename("temp.txt", "matieres.txt");

        if (matiereFound) {
            cout << "Matiere with ID " << matiereId << " modified successfully." << endl;
        } else {
            cout << "Matiere with ID " << matiereId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}


void GestionMatieres() {
    int choice;
    do {
        cout << "1. Ajouter une Matiere" << endl;
        cout << "2. Supprimer une Matiere" << endl;
        cout << "3. Rechercher une Matiere" << endl;
        cout << "4. Modifier une Matiere" << endl;
        cout << "5. Retour au Menu Principal" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                AjoutMatiere();
                break;
            case 2:
               supprimerMatiere();
                break;
            case 3:
                RechercherMatiere();
                break;
            case 4:
               ModifierMatiere();
                break;
            case 5:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

void AjoutNote() {
    string matiereId;
    int  studentId;
    float noteValue;
    string noteType;

    cout << "Enter student ID: ";
    cin >> studentId;

    cout << "Enter matiere ID: ";
    cin >> matiereId;

    cout << "Enter note value: ";
    cin >> noteValue;

    cout << "Enter note type: ";
    cin>>noteType;
    size_t i=0,j=0;int trouve=-1; int trouve2=-1;

    for( i=0;i<students.size();i++)
    {
        if(students[i].getId()==studentId){trouve=i;break;}
    }

     for(j=0;j<matieres.size();j++)
    {
        if(matieres[j].getIdMat() == matiereId){trouve2=j;break;}
    }

    if (trouve2!=-1 && trouve != -1) {

        Note newNote(matieres[j], students[i], noteValue, noteType);

        notes.push_back(newNote);

        ofstream outputFile("notes.txt",ios::app);
        if (outputFile.is_open()){

            outputFile <<newNote;

            outputFile.close();

            cout << "Note added successfully:" << endl;
            cout << "Matiere: " << newNote.getMatiere().getNomMat() << endl;
            cout << "Student: " <<newNote.getEtudiant().getNom() << endl;
            cout << "Note Value: " << noteValue << endl;
            cout << "Note Type: " << noteType << endl;
        } else {
            cout << "Error updating file." << endl;
        }
    } else {
        cout << "Student or Matiere not found." << endl;
    }
}

void supprimerNote() {
    string matiereId; int etudiantId;
    cout << "Enter the ID of the matiere for the note: ";
    cin >> matiereId;

    cout << "Enter the ID of the etudiant for the note: ";
    cin >> etudiantId;
size_t i(0),trouve(-1);
    for( i=0;i<notes.size();i++)
    {
        if(notes[i].getEtudiant().getId() == etudiantId && notes[i].getMatiere().getIdMat()==matiereId)
        {
            trouve=i;
            break;
        }
    }

    if (trouve != -1) {

        notes.erase(notes.begin()+trouve);
        cout << "Note deleted successfully." << endl;

        ofstream outputFile("notes.txt");

        if (!outputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }

        for (const Note& note : notes) {
            outputFile << note.getMatiere().getIdMat() << " "
                       << note.getEtudiant().getId() << " "
                       << note.getNote() << " "
                       << note.getType() << endl;
        }

        outputFile.close();
    } else {
        cout << "Note for Matiere ID " << matiereId << " and Etudiant ID " << etudiantId << " not found." << endl;
    }
}


void RechercherNote() {
    int noteId;
    cout << "Enter the ID of the note to search: ";
    cin >> noteId;

    ifstream notesFile("notes.txt");

    if (notesFile.is_open()) {
        string noteLine;
        bool noteFound = false;

        while (getline(notesFile, noteLine)) {
            istringstream noteIss(noteLine);
            int noteIdFromFile;

            if (noteIss >> noteIdFromFile && noteIdFromFile == noteId) {
                noteFound = true;
                cout << "Note found: " << noteLine << endl;
                break;
            }
        }

        if (!noteFound) {
            cout << "Note with ID " << noteId << " not found." << endl;
        }

        notesFile.close();
    } else {
        cerr << "Error opening the file." << endl;
    }
}

void ModifierNote() {
    int noteId;
    cout << "Enter the ID of the note to modify: ";
    cin >> noteId;

    ifstream notesFile("notes.txt");
    ofstream tempFile("temp_notes.txt");

    if (notesFile.is_open() && tempFile.is_open()) {
        string noteLine;
        bool noteFound = false;

        while (getline(notesFile, noteLine)) {
            istringstream noteIss(noteLine);
            int id;

            if (noteIss >> id && id == noteId) {
                float newNote;
                string newType;

                cout << "Enter new Note: ";
                cin >> newNote;

                cout << "Enter new Type: ";
                cin >> newType;

                tempFile << noteId << " " << newNote << " " << newType << endl;

                noteFound = true;
            } else {
                tempFile << noteLine << endl;
            }
        }

        notesFile.close();
        tempFile.close();

        remove("notes.txt");
        rename("temp_notes.txt", "notes.txt");

        if (noteFound) {
            cout << "Note with ID " << noteId << " modified successfully." << endl;
        } else {
            cout << "Note with ID " << noteId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}

void GestionNotes() {
    int choice=0;
while (choice != 5)
     {
        cout << "1. Ajouter une Note" << endl;
        cout << "2. supprimer  une Note" << endl;
        cout << "3. rechercher une Note" << endl;
        cout << "4. modifier une Note" << endl;
        cout << "5. Retour au Menu Principal" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                AjoutNote();
                break;
            case 2:
                supprimerNote();
                break;
            case 3:
               RechercherNote();
                break;
            case 4:
                ModifierNote();
                break;
            case 5:
                system("cls");
                break;
        }
    }
}

void GestionEnseignants() {
    int choice;
    while (choice != 5){
        cout << "1. Ajouter un enseignant" << endl;
        cout << "2. Supprimer Enseignant" << endl;
        cout << "3. Rechercher Enseignant" << endl;
        cout << "4. Modifier Enseignant" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                AjoutEnseignant();
                break;
            case 2:
                supprimerEnseignant();
                 break;
            case 3:
                RechercherEnseignant();
                break;
            case 4:
                ModifierEnseignant();
                break;
            case 5:
                break;
            default:
                system("cls");
                cout << "Choix invalide. Essayer une autre fois." << endl;
        }
    }
}


void ajoutgroupeModule() {
    string IdGM;
    string NomGM;
    float CoefGM;


    cout << "Enter the ID of the GroupeModule: ";
    cin >> IdGM;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the Name of the GroupeModule: ";
    getline(cin, NomGM);

    cout << "Enter the Coefficient of the GroupeModule: ";
    cin >> CoefGM;

    vector<Matiere> ListeMat;

    int numberOfMatieres;
    cout << "Enter the number of Matieres: ";
    cin >> numberOfMatieres;

    for (int i = 0; i < numberOfMatieres; ++i) {
        int matiereId;
        cout << "Enter the ID of Matiere " << i + 1 << ": ";
        cin >> matiereId;

        Matiere matiere;
        ifstream matiereFile("matieres.txt");

        bool matiereFound = false;

        while (matiereFile >> matiere) {
            if (matiere.getIdMat() == to_string(matiereId)) {
                ListeMat.push_back(matiere);
                matieres.push_back(matiere);
                matiereFound = true;
                break;
            }
        }

        matiereFile.close();

        if (!matiereFound) {
            cerr << "Matiere with ID " << matiereId << " not found." << endl;
        }
    }

    GroupeModule newGroupeModule(IdGM, NomGM, CoefGM, ListeMat);

    groupeModules.push_back(newGroupeModule);

    ofstream groupeModuleFile("groupemodule.txt", ios::app);
    if (groupeModuleFile.is_open()) {
        if (groupeModuleFile.tellp() != 0) {
            groupeModuleFile << endl;
        }

        groupeModuleFile << newGroupeModule;

        groupeModuleFile.close();
        cout << "Groupe Module added successfully:\n" << newGroupeModule << endl;
    } else {
        cout << "Error updating file." << endl;
    }
}



void supprimerGroupeModule() {
    string groupeModuleId;
    cout << "Enter the ID of the Groupe Module to delete: ";
    cin >> groupeModuleId;
    int trouve=-1;
    for(size_t i=0;i<groupeModules.size();i++)
    {
        if(groupeModules[i].getIdGM()==groupeModuleId) {trouve=i;break;}
    }

    if (trouve!=-1) {
        groupeModules.erase(groupeModules.begin()+trouve);
        cout << "GroupeModule deleted successfully." << endl;

        ofstream outputFile("groupemodule.txt");


        if (!outputFile.is_open()) {
            cerr << "Error opening the file." << endl;
            return;
        }


        for (size_t i=0;i< groupeModules.size();i++) {
            outputFile << groupeModules[i].getIdGM() << " "
                       << groupeModules[i].getNomGM() << " "
                       << groupeModules[i].getCoefGM() << endl;
        }

        outputFile.close();
    }
     else {
        cout << "GroupeModule with ID " << groupeModuleId << " not found." << endl;
    }
}

void ModifierGroupeModule() {
    std::string groupId;
    cout << "Enter the ID of the GroupeModule to modify: ";
    cin >> groupId;

    ifstream inputFile("groupemodule.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        bool groupModuleFound = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            string idGM;

            if (getline(iss, idGM, ',') && idGM == groupId) {
                string newNom, newCoef;

                cout << "Enter new Nom: ";
                cin >> newNom;

                cout << "Enter new Coef: ";
                cin >> newCoef;

                tempFile << idGM << " " << newNom << " " << newCoef << " " << endl;

                groupModuleFound = true;
            } else {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        remove("groupemodule.txt");
        rename("temp.txt", "groupemodule.txt");

        if (groupModuleFound) {
            cout << "GroupeModule with ID " << groupId << " modified successfully." << endl;
        } else {
            cout << "GroupeModule with ID " << groupId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}
void RechercherGroupeModule() {
    std::string groupId;
    cout << "Enter the ID of the GroupeModule to search: ";
    cin >> groupId;
GroupeModule gm;
    ifstream inputFile("groupemodule.txt");
int trouve=0;
    if (inputFile.is_open()) {
            while(inputFile>>gm)
            {
                if(gm.getIdGM()==groupId)
                {
                    cout << "idGM:" << gm.getIdGM() <<endl<< "NomGm:"<<gm.getNomGM()<<endl<<"coef:"<<gm.getCoefGM()<<endl<<"___________"<<endl;
                    trouve=1;
                }
            }

        }
        inputFile.close();

        if (trouve!=1) {
            cout << "Groupe Module with ID " << groupId << " not found." << endl;
        }
     else {
        cerr << "Error opening the file." << endl;
    }
    }


void GestionGroupesModules() {
    int choice=0;
    while (choice != 5) {
        cout << "1. Ajouter un groupe de modules" << endl;
        cout << "2. Supprimer groupe de modules" << endl;
        cout << "3. Rechercher groupe de modules" << endl;
        cout << "4. Modifier groupe de modules" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ajoutgroupeModule();
                break;
           case 2:
                supprimerGroupeModule();
                break;
            case 3:
                RechercherGroupeModule();
               break;
           case 4:
                ModifierGroupeModule();
               break;
            case 5:
                break;
            default:
                cout << "Choix invalide. Essayer une autre fois." << endl;
        }
    }
}

void AjoutGroupe() {
    string idgrp, Niv, Dipl, Spe;
    int num_g;

    cout << "Enter group ID: ";
    cin >> idgrp;

    cout << "Enter group Niveau: ";
    cin >> Niv;

    cout << "Enter group Diplome: ";
    cin >> Dipl;

    cout << "Enter group Specialite: ";
    cin >> Spe;

    cout << "Enter group Num_G: ";
    cin >> num_g;

    Groupe newGroup(idgrp, Niv, Dipl, Spe, num_g, {}, {});

    ofstream groupesFile("groupes.txt", ios::app);

    int studentId;
    cout << "Enter student ID to add to the group: ";
    cin >> studentId;

    ifstream studentsFile("students.txt");

    if (studentsFile.is_open()) {
        string line;
        bool studentFound = false;

        while (getline(studentsFile, line)) {
            istringstream iss(line);
            int id;
            string nom, prenom, mail;
            int numInsc;

            if (iss >> id >> nom >> prenom >> mail >> numInsc) {

                if (id == studentId) {

                    cout << "Student found: " << nom << " " << prenom << endl;

                    Etudiant newStudent(id, nom, prenom, mail, numInsc);
                     newGroup.addEtudiant(newStudent);
                        cout << "Student added to the group successfully." << endl;
                    } else {
                        cout << "Error updating groupes.txt file." << endl;
                    }

                    studentFound = true;
                    break;
                }
            }


        studentsFile.close();


        if (!studentFound) {
            cout << "Student with ID " << studentId << " not found in students.txt." << endl;
        }
    }
     else {
        cout << "Error opening students.txt file." << endl;
    }
    cout << "Enter module ID to add to the group: ";
    string idm;
    cin >> idm;
    int trouve=0;
    for(size_t i=0;i<groupeModules.size();i++)
    {
        if(groupeModules[i].getIdGM()==idm)
        {
            newGroup.addModule(groupeModules[i]);
            trouve=1;
        }
    }
    if(trouve==1)
    {
        cout<<"module added";
    }
groupes.push_back(newGroup);
if (groupesFile.is_open()) {

        groupesFile << newGroup << endl;
        groupesFile.close();

        cout << "Group added successfully." << endl;
    } else {
        cout << "Error updating groupes.txt file." << endl;
        return;
    }
}


void SupprimerGroupe() {
    string groupId;
    cout << "Enter the ID of the group to delete: ";
    cin >> groupId;

    ifstream inputFile("groupes.txt");
    ofstream outputFile("temp.txt", ios::trunc);

    if (inputFile.is_open() && outputFile.is_open()) {
        string line;
        bool groupFound = false;


        while (getline(inputFile, line)) {
            istringstream iss(line);
            Groupe group;
            iss >> group;

            if (group.getIdGRP() == groupId) {

                groupFound = true;
                cout << "Group deleted successfully." << endl;
            } else {

                outputFile << line << endl;
            }
        }

        inputFile.close();
        outputFile.close();


        if (groupFound) {
            remove("groupes.txt");
            rename("temp.txt", "groupes.txt");
        } else {

            remove("temp.txt");
            cout << "Group with ID " << groupId << " not found." << endl;
        }
    } else {
        cerr << "Error opening files." << endl;
    }
}

void RechercherGroupe() {
    string groupId;
    cout << "Enter the ID of the group to search: ";
    cin >> groupId;

    ifstream groupsFile("groupes.txt");

    if (groupsFile.is_open()) {
        string groupLine;
        bool groupFound = false;

        while (getline(groupsFile, groupLine)) {
            istringstream groupIss(groupLine);
            Groupe group;


            groupIss >> group;

            if (group.getIdGRP() == groupId) {
                groupFound = true;
                cout << "Group found: " << groupLine << endl;
                break;
            }
        }

        if (!groupFound) {
            cout << "Group with ID " << groupId << " not found." << endl;
        }

        groupsFile.close();
    } else {
        cerr << "Error opening the file." << endl;
    }
}

void ModifierGroupe() {
    string groupId;
    cout << "Enter the ID of the group to modify: ";
    cin >> groupId;

    ifstream groupsFile("groupes.txt");
    ofstream tempFile("temp.txt");

    if (groupsFile.is_open() && tempFile.is_open()) {
        string groupLine;
        bool groupFound = false;

        while (getline(groupsFile, groupLine)) {
            istringstream groupIss(groupLine);
            Groupe group;

            groupIss >> group;

            if (group.getIdGRP() == groupId) {
                string newNiveau, newDiplome, newSpecialite;
                int newNumG;

                cout << "Enter new Niveau: ";
                cin >> newNiveau;

                cout << "Enter new Diplome: ";
                cin >> newDiplome;

                cout << "Enter new Specialite: ";
                cin >> newSpecialite;

                cout << "Enter new Num_G: ";
                cin >> newNumG;

                group.setNiveau(newNiveau);
                group.setDiplome(newDiplome);
                group.setSpecialite(newSpecialite);
                group.setNum_G(newNumG);

                tempFile << group << endl;

                groupFound = true;
            } else {
                tempFile << groupLine << endl;
            }
        }

        groupsFile.close();
        tempFile.close();

        remove("groupes.txt");
        rename("temp.txt", "groupes.txt");

        if (groupFound) {
            cout << "Group with ID " << groupId << " modified successfully." << endl;
        } else {
            cout << "Group with ID " << groupId << " not found." << endl;
        }
    } else {
        cerr << "Error opening the file." << endl;
    }
}



void GestionGroupes() {
    int choice;
    while (choice != 5){
        cout << "1. Ajouter un groupe" << endl;
        cout << "2. Supprimer groupe" << endl;
        cout << "3. Rechercher groupe" << endl;
        cout << "4. Modifier groupe" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                AjoutGroupe();
                break;
            case 2:
                SupprimerGroupe();
                break;
            case 3:
                RechercherGroupe();
                break;
           case 4:
               ModifierGroupe();
               break;
           case 5:
                break;
            default:
                cout << "Choix invalide. Essayer une autre fois." << endl;
        }
    }
}

double moyMat(Matiere mat,Etudiant etd){
double sommeNote=0;
int nombreNote=0;
vector<Note>::iterator it;
int found=0;
for(it=notes.begin();it<notes.end();it++){
    if((*it).getMatiere().getIdMat()==mat.getIdMat()&&(*it).getEtudiant().getNumInsc()==etd.getNumInsc()){
        nombreNote++;
        sommeNote=sommeNote+(*it).getNote();
        found=1;
    }
}
    if(found==0) {
    return 0;}
    else{return sommeNote/nombreNote;}
}
double moyGM(Etudiant etd,string idgm){
double sommeMoyMat=0;
double sommeCoef=0;
vector<Matiere> mat;
int found=0;
int k,n=groupeModules.size();
for(int i=0;i<n;i++){
    if(groupeModules[i].getIdGM()==idgm){
        found=1;
        k=i;
        break;
    }
}
if(found==0){
cout<<"element not found"<<endl;
return 0;
}else{
mat=groupeModules[k].getListeMat();
for(size_t j=0;j<mat.size();j++){
sommeMoyMat+=moyMat(mat[j],etd)*mat[j].getCoef();
sommeCoef+=mat[j].getCoef();
}
return sommeMoyMat/sommeCoef;
}
}
double moyenne(Etudiant etd){
float sommeGm=0;
float sommeCoef=0;
vector<GroupeModule> lgm=groupeModules;

for(size_t i=0;i<lgm.size();i++){
sommeGm+=lgm[i].getCoefGM()*moyGM(etd,lgm[i].getIdGM());
sommeCoef+=lgm[i].getCoefGM();
}
return sommeGm/sommeCoef;
}
string mention(Etudiant etd){
double moy=moyenne(etd);
if(moy>10 && moy<=12){
return "Passable";
}else if(moy>12 &&  moy<=14){
return "Assez bien";
}else if(moy>14 && moy<=16){
return "Bien";
}else if(moy>16 && moy<=18){
return "Tres bien";
}else if(moy>18 && moy<=20){
return "Exellent";}
else{return "Ajourne";
}
}
string resultat(Etudiant etd){
double moy=moyenne(etd);
if(moy>10){
    return "Admis";
}else{
return "Ajourne";
}
}
void Afficher_PV(string idG){

const int CW=12;
int indexG;
for(size_t i=0;i<groupes.size();i++)
{
    if(groupes[i].getIdGRP()==idG)
    {
        indexG=i;
    }
}
vector<GroupeModule> gm=groupes[indexG].getListeModules();
vector<Etudiant> etd=groupes[indexG].getListeEtudiants();
int n=gm.size(),n1,n2;
vector<Matiere> mat;
cout <<left<< setw(CW*3+3)<<" ";
for(int i=0;i<n;i++){
cout<<"|"<<setw(CW*(gm[i].getListeMat().size()+1)+gm[i].getListeMat().size())<<gm[i].getNomGM();
}

cout<<"|";
cout <<left<<setw(CW/2)<<"M";
cout<<"|";
cout <<left<<setw(CW)<<"R";
cout<<"|";
cout <<left<<setw(CW)<<"M";
cout<<"|"<<endl;
cout <<left<<setw(CW*3+3)<<" ";

for(int i=0;i<n;i++){
cout<<"|"<<setw(CW*(gm[i].getListeMat().size()+1)+gm[i].getListeMat().size())<<gm[i].getCoefGM();
}
cout<<"|";
cout <<left<<setw(CW/2)<<"O";
cout<<"|";
cout <<left<<setw(CW)<<"E";
cout<<"|";
cout <<left<<setw(CW)<<"E";
cout<<"|"<<endl;


cout <<left<< setw(CW*3+3)<<" ";
for(int i=0;i<n;i++){
    mat=gm[i].getListeMat();
    n1=mat.size();
    for(int j=0;j<n1;j++){
     cout<<"|"<<setw(CW)<<mat[j].getNomMat();
    }
    cout<<"|"<<setw(CW-1)<<"moyenne_GM  ";

}
cout<<"|";
cout <<left<<setw(CW/2)<<"y";
cout<<"|";
cout <<left<<setw(CW)<<"S";
cout<<"|";
cout <<left<<setw(CW)<<"N";
cout<<"|"<<endl;

cout<<setw(CW*3+3)<<"|Liste des etudiants";
for(int i=0;i<n;i++){
    mat=gm[i].getListeMat();
    n1=mat.size();
    for(int j=0;j<n1;j++){
     cout<<"|"<<setw(CW)<<mat[j].getCoef();
    }

     cout<<"|"<<setw(CW)<<"";
}
cout<<"|";
cout <<left<<setw(CW/2)<<".";
cout<<"|";
cout <<left<<setw(CW)<<".";
cout<<"|";
cout <<left<<setw(CW)<<".";
cout<<"|"<<endl;
n=etd.size();
for(int i=0;i<n;i++){
cout<<"|"<<setw(CW)<<etd[i].getNumInsc()<<"|"<<setw(CW)<<etd[i].getNom()<<"|"<<setw(CW)<<etd[i].getPrenom();
    n1=gm.size();
        for(int j=0;j<n1;j++){
             mat=gm[j].getListeMat();
             n2=mat.size();
              for(int k=0;k<n2;k++) {

                cout<<"|"<<setw(CW)<<moyMat(mat[k],etd[i]);
              }
        cout<<"|"<<setprecision(3)<<setw(CW)<<moyGM(etd[i],gm[j].getIdGM());
        mat.clear();
        }
        cout<<"|";
       cout <<left<<setw(CW/2)<<setprecision(3)<<moyenne(etd[i]);
        cout<<"|";
        cout <<left<<setw(CW)<<resultat(etd[i]);
        cout<<"|";
        cout <<left<<setw(CW)<<mention(etd[i]);
        cout<<"|"<<endl;

}



}
void afficherMenuPrincipal() {
    int choix=9;
    while (choix != 0)
    {
        cout << "Menu principal:" << endl;
        cout << "1. Gestion des etudiants" << endl;
        cout << "2. Gestion des enseignants" << endl;
        cout << "3. Gestion des matieres" << endl;
        cout << "4. Gestion des notes" << endl;
        cout << "5. Gestion des groupes Modules" << endl;
        cout << "6. Gestion des groupes" << endl;
        cout << "7. affichage du pv" << endl;
        cout << "0. Quitter" << endl;
        cout << "Entrez votre choix:" << endl;
        cin >> choix;

        switch (choix) {
            case 0:
                system("cls");
                cout << "Programme terminee" << endl;
                break;
            case 1:
                system("cls");
                GestionEtudiants();
                break;
            case 2:
                system("cls");
                GestionEnseignants();
                break;
            case 3:
                system("cls");
                GestionMatieres();
                break;
           case 4:
               system("cls");
                GestionNotes();
                break;
            case 5:
                system("cls");
                GestionGroupesModules();
                break;
            case 6:
                system("cls");
                GestionGroupes();
                break;
            case 7:
                system("cls");
                string idgrp;
                cout<<"Entrez l'id du groupe ";
                cin>>idgrp;
                Afficher_PV(idgrp);
                break;
        }
    }
}
