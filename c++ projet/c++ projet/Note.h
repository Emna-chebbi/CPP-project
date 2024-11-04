#include"Module.h"
#include <iostream>
#include <string>
using namespace std;
class Note {
private:
    Matiere Mat;
    Etudiant Etu;
    float note;
    string Type;

public:
    Note();
    Note(Matiere& Mat, Etudiant& Etu, float Note, string Type);
    ~Note();
    friend istream& operator>>(istream& is, Note& note);
    friend ostream& operator<<(ostream& os, const Note& note);
       Matiere getMatiere() const {
        return Mat;
    }

    void setMatiere(Matiere mat) {
        Mat = mat;
    }


    Etudiant getEtudiant() const {
        return Etu;
    }

    void setEtudiant(Etudiant etu) {
        Etu = etu;
    }


    float getNote() const {
        return note;
    }

    void setNote(float newNote) {
        note = newNote;
    }


    string getType() const {
        return Type;
    }

    void setType(const string& newType) {
        Type = newType;
    }
};
Note::Note() : Mat(), Etu(), note(0.0), Type(" ") {}

Note::Note(Matiere& Mat, Etudiant& Etu, float note, string Type)
    : Mat(Mat),Etu(Etu),note(note), Type(Type) {}

Note::~Note() {}

istream& operator>>(istream& is, Note& note) {
    is >> note.Mat ;
    is >> note.Etu ;
    is >> note.note ;
    is >> note.Type ;
    return is;
}
ostream& operator<<(ostream& os, const Note& note) {
    os << note.getMatiere() << endl;
    os << note.getEtudiant()<< endl;
    os << note.note << endl;
    os << note.Type << endl;
    return os;
}

