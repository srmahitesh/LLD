#include <bits/stdc++.h>
using namespace std;

// Open Closed Principle says that, class must be open for extension, but closed for modification.
class Notepad{
    vector<string> notes;

    public:
    void addNote(string note){
        notes.push_back(note);
    }

    void deleteNoteByIndex(int index){
        if(index < 0 || notes.size() <= index){
            cout<<"Warn: Invalid Index."<<endl;
            return;
        }
        notes.erase(notes.begin() + index);
        cout<<"Note deleted successfully at index: "<<index<<"."<<endl;
        return;
    }

    int notesCount(){
        return notes.size();
    }

    void viewNotes(){
        if(!notes.size()){
            cout<<"No notes available in notepad. Add one to view."<<endl;
            return;
        }
        for(int index = 0; index< notesCount(); index++){
            cout<<index+1<<": "<<notes[index]<<endl;
        }
        return;
    }
};

// This class is violating the Open Closed Principle, as single has two function, which are
// different features. This should be done in different class.
class SaveToDB{
    Notepad *np;
    public:
    SaveToDB(Notepad *np){
        this->np = np;
    }

    //This function save the notes to SQLDB
    void saveToSQL(){
        if(np->notesCount() == 0){
            cout<<"Notepad is empty & nothing to save."<<endl;
            return;
        }
        cout<<np->notesCount()<<" notes successfully saved to SQL Database."<<endl;
    }

    //This function save the notes to MongoDB
    void saveToMongoDB(){
        if(np->notesCount() == 0){
            cout<<"Notepad is empty & nothing to save."<<endl;
            return;
        }
        cout<<np->notesCount()<<" notes successfully saved to MongoDB Database."<<endl;
    }
};

int main(){
    Notepad *np = new Notepad();
    np->addNote("I love my programming.");
    np->addNote("Problem solving on leetcode/gfg was my fav passtime during college times.");
    np->deleteNoteByIndex(2); //invalid index
    np->deleteNoteByIndex(-1); //invalid index
    np->addNote("I thanks JTG for giving me first oppurtunity.");
    np->viewNotes();
    np->deleteNoteByIndex(1);
    np->viewNotes();

    SaveToDB *db = new SaveToDB(np);
    db->saveToMongoDB();
    db->saveToSQL();

    return 0;
}