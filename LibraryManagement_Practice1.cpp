#include <iostream>
#include <unordered_map>
using namespace std;


class Book{

  private:
  int serial_no;
  string name;
  int curr_stock;
  int max_stock;
  string author;

  public:
  Book(int serial_no, string name, string author, int stock){
    this->serial_no = serial_no;
    this->name = name;
    this->author = author;
    this->curr_stock = stock;
    this->max_stock = stock;
  }

  string getName(){
    return this->name;
  }

  int getSerialNo(){
    return this->serial_no;
  }

  string getAuthor(){
    return this->author;
  }

  int getStock(){
    return this->curr_stock;
  }

  int getMaxStock(){
    return this->max_stock;
  }

  void decreaseStock(){
    this->curr_stock =  this->curr_stock - 1;
  }

  void increaseStock(){
    this->curr_stock =  this->curr_stock + 1;
  }

};




class Library{

  int serial_no;
  unordered_map<int, Book*> bookDetails;

  public:
  Library(){
    serial_no = 0; //count, to asign unique id to each new book added
  }



  void addBook(string name, string author, int stock){
    Book* b = new Book(++serial_no, name, author, stock);
    bookDetails.insert({serial_no, b});
    cout<<"Book added Successfully to Library with Serial No. "<<serial_no<<endl;
  }




  void showAvailableBooks(){
    bool zeroAvailable = true;

    for(auto x: bookDetails){
      int id = x.first;
      Book* curr_book = x.second;
      if(curr_book->getStock() > 0){
      cout<<"Serial No. "<<id<<" Book Name: "<<curr_book->getName()<<" "<<"Author: "<<curr_book->getAuthor()<<" Left Stock: "<<curr_book->getStock()<<endl;
      zeroAvailable = false;
      }
    }

    if(zeroAvailable){
      cout<<"No books available at this moment"<<endl;
    }
  }




  void issueBook(int serial_no){
    if(bookDetails.find(serial_no) == bookDetails.end()){
      cout<<"Invalid serial number. No such book exists."<<endl;
      return;
    }
    Book* b = bookDetails[serial_no];

    if(b->getStock() <= 0){
      cout<<"No book left in stock. Please try issuing after some days."<<endl;
      return;
    }

    b->decreaseStock();
    bookDetails[b->getSerialNo()] = b;
    cout<<"Book issued successfully"<<endl;
  }




  void returnBook(int serial_no){

    if(bookDetails.find(serial_no) == bookDetails.end()){
      cout<<"Invalid serial number. No such book exists."<<endl;
      return;
    }

    Book* b = bookDetails[serial_no];

    if(b->getStock() == b->getMaxStock()){
      cout<<"No such book issued from stock."<<endl;
      return;
    }

    b->increaseStock();
    bookDetails[b->getSerialNo()] = b;
    cout<<"Book recieved successfully"<<endl;
  }
};




int main(){
  Library* L = new Library();
  L->showAvailableBooks();
  L->addBook("My Life", "HItesh Sharma", 2);
  L->showAvailableBooks();
  L->issueBook(1);
  L->issueBook(1);
  L->showAvailableBooks();
  L->returnBook(1);
  L->showAvailableBooks();
  L->returnBook(1);
  L->returnBook(1);
  L->returnBook(1);

  return 0;
}
