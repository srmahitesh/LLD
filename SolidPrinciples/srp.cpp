#include <bits/stdc++.h>
using namespace std;

//product is only responsible for maintaining product & return its name & price.
class product{
    string title;
    int price;

    public:
    product(string title, int price){
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

//Shopping cart will be now only responsible for maintaining the items list & their total cost.
class shoppingCart{
    vector<product> products;
    int totalAmount;

    public:
    shoppingCart(){
        totalAmount = 0;
    }

    void addProduct(product p){
        products.push_back(p);
        totalAmount += p.getPrice();
    }

    void productsList(){
        if(products.size() == 0){
            cout<<"No items in cart."<<endl;
            return;
        }
        for(product p: products){
            cout<<p.getTitle()<<"  "<<p.getPrice()<<endl;
        }
    }

    int getTotal(){
        return totalAmount;
    }

    // This function is used after promocode is applied. It change the totalAmount to discounted price.
    void setTotal(int total){
        totalAmount = total;
    }

    // This function can be used to reset any discounts, & add full price of items added in cart.
    void setTotal(){
        totalAmount = 0;
        for(product p: products){
            totalAmount += p.getPrice();
        }
    }
};

//Discount manager will be responsible for managing promocodes & applying discounts.
class discountManager{
    shoppingCart *cart;
    string *appliedPromoCode;
    unordered_map<string, float> promoCodes = {
        {"FIRST", 50},
        {"WINTER", 10}
    };

    public:
    discountManager(shoppingCart *cart){
        this->cart = cart;
    }

    void applyPromocode(string promoCode, int totalAmount){
        auto it = promoCodes.find(promoCode);
        if(it != promoCodes.end()){
            float discountPercentage = promoCodes[promoCode];
            float discount = (discountPercentage/100) * totalAmount;
            cart->setTotal(totalAmount - discount);
            appliedPromoCode = new string(promoCode);
        }
    }

    void removePromocode(){
        if(appliedPromoCode){
            cart->setTotal();
            appliedPromoCode = nullptr;
        }
    }

    void addPromoCode(string promoCode, float discountPercentage){
        promoCodes[promoCode] = discountPercentage;
    }

    void invalidatePromocode(string promoCode){
        promoCodes.erase(promoCode);
        if(appliedPromoCode && *appliedPromoCode == promoCode){
            removePromocode();
        }
    }
};


int main(){
    shoppingCart *cart = new shoppingCart();
    product *p1 = new product("Mobile", 10000);
    cart->addProduct(*p1);
    cout<<p1->getPrice()<<endl;

    cout<<"Cart Totoal: "<<cart->getTotal()<<endl;

    //Apply promocode
    discountManager *dm = new discountManager(cart);
    dm->addPromoCode("XMAS25", 25);
    dm->applyPromocode("XMAS25", cart->getTotal());
    cout<<"Cart Total after discount: "<<cart->getTotal()<<endl;

    dm->invalidatePromocode("XMAS25");
    cout<<"Cart Total after removing discount: "<<cart->getTotal()<<endl;

    return 0;
}
