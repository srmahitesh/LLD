#include <bits/stdc++.h>
using namespace std;


/*Requirements:
  1. User can only issue upto 3 books simuntaneosly. After 3 issued books new can only be after atlease 1 is returned.
  2. Edge cases must be handled carefully:
    2.1. No issue is all books already issued.
    2.2. No book can be returned if all are available in library.
  3. Proper record must be maintained of available books & issued books.
*/

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
  unordered_map<int, unordered_set<int>> issuedBooks; //{roll_no, serial no};


  public:
  Library(){
    serial_no = 0; //count, to asign unique id to each new book added   //change it later to static & private
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




  void issueBook(int serial_no, int roll_no){
    if(bookDetails.find(serial_no) == bookDetails.end()){
      cout<<"Invalid serial number. No such book exists."<<endl;
      return;
    }
    Book* b = bookDetails[serial_no];

    if(b->getStock() <= 0){
      cout<<"No book left in stock. Please try issuing after some days."<<endl;
      return;
    }
    else if(issuedBooks[roll_no].size() >= 3){
      cout<<"Maximum Book issued already. Please return atleast 1 before getting new one."<<endl;
      return;
    }
    else if(issuedBooks[roll_no].find(serial_no) != issuedBooks[roll_no].end()){
      cout<<"You have already taken the same Book."<<endl;
      return;
    }

    issuedBooks[roll_no].insert(serial_no);
    b->decreaseStock();
    //bookDetails[b->getSerialNo()] = b;
    cout<<"Book issued successfully"<<endl;
  }




  void returnBook(int serial_no, int roll_no){

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
    issuedBooks[roll_no].erase(serial_no);
    //bookDetails[b->getSerialNo()] = b;
    cout<<"Book recieved successfully"<<endl;
  }
};





class student{
  static int last_roll_no;
  int roll_no;
  string name;
  
  public:

  student(string name){
    this->name = name;
    roll_no = ++last_roll_no;
  }

  void availableBooks(Library* &L){
    L->showAvailableBooks();
  }

  void issueBook(Library* &L, int serial_no){
    L->issueBook(serial_no, this->roll_no);
  }

  void returnBook(Library* &L, int serial_no){
    L->returnBook(serial_no, this->roll_no);
  }

};


int student:: last_roll_no = 0;



int main(){
  Library* L = new Library();
  L->showAvailableBooks();
  L->addBook("My Life", "HItesh Sharma", 2);
  L->addBook("Let's C", "Denis Ritchie", 2);
  L->addBook("Let's C++", "John Startsup", 2);
  L->addBook("Rich Dad, Poor Dad", "Robert Kiyosaki", 1);

  student* s1 = new student("Hitesh");
  student* s2 = new student("Ram");
  student* s3 = new student("Radha");

  s1->availableBooks(L);
  s1->issueBook(L, 1); //success
  s1->issueBook(L, 1); //duplicate book
  s1->issueBook(L, 2); //success
  s1->issueBook(L, 3); //success
  s1->issueBook(L, 4); //limit exhausted
  s2->issueBook(L, 4); //success
  s3->issueBook(L, 4);//out of stock
  s2->returnBook(L, 4); //success
  s3->issueBook(L, 4); //success this time, as s2 has returned



  return 0;

}