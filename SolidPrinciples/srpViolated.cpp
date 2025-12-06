#include <bits/stdc++.h>
using namespace std;

class item{
    string title;
    int price;
    public:
    item(string title, int price){
        this->title = title;
        this->price = price;
    }

    int getPrice(){
        return price;
    }

    string getTitle(){
        return title;
    }
};

// Here shopping cart is responsible for listing items, calcuting total price & discount based on promocodes as well.
// Hence, SRP is clearly broken here as shooping cart class more than 1 responsibilities.
class shoppingCart{
    vector<item> items;
    unordered_map<string, float> promoCodes = {
        {"FIRST", 50},
        {"WINTER", 10}
    };

    public:
    int totalPrice(){
        int price = 0;
        for(item i: items){
            price += i.getPrice();
        }
        return price;
    }

    void addItem(item i){
        items.push_back(i);
    }

    void listItems(){
        if(items.size() == 0){
            cout<<"No available items in your cart."<<endl;
        } else{
            cout<<"Title <-------> Price"<<endl;
            for(item i: items){
                cout<<i.getTitle()<<" "<<i.getPrice()<<endl;
            }
        }
    }

    int applyPromoCodeAndGetDiscountedPrice(string promocode){
        int price = totalPrice();
        auto it = promoCodes.find(promocode);
        if(it != promoCodes.end()){
            float discountPercentage = promoCodes[promocode];
            float discount = (discountPercentage/100) * price;
            return price - int(discount);
        }
        cout<<"Log Message: Invalid Promocode."<<endl;
        return price;
    }
};

int main() {
    item *i1 = new item("BournVita", 455);
    shoppingCart s;
    s.listItems();
    s.addItem(*i1);
    s.listItems();
    cout<<"Total Price: "<<s.totalPrice()<<endl;
    cout<<"Discount Price: "<<s.applyPromoCodeAndGetDiscountedPrice("FIRST");
    return 0;
}
