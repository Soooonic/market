#include<bits/stdc++.h>
using namespace std;
static int cnt_ids=1;
// //the name of first class
class Item{
// member variables
private:
    string name;
    int ID;
    int quantity;
    int price;
public:
    //default  constructor
    Item(){
        ID=cnt_ids;
        cnt_ids++;
    }
    //parameterized constructor
    Item(string nm,int quan,int pric){
        name=nm;
        quantity=quan;
        price=pric;
        ID=cnt_ids;
        cnt_ids++;
    }
    //copy constructor
    Item(Item &obj){
        name=obj.name;
        quantity=obj.quantity;
        price=obj.price;
        ID=obj.ID;
    }
    // overloading operator +=
    Item operator+= (Item& object){
        quantity+=object.quantity;
        return *this;
    }
    // overloading operator ==
    bool operator== (Item& ob){
        return name==ob.name;
    }
    // overloading operator -=
    Item operator-= (int q){
        quantity-=q;
        return *this;
    }
    // overloading operator <<
    friend ostream& operator<<(ostream& os,Item& obj){
        os<<"item's id: "<<obj.ID<<"\n"<<"item's name: "<<obj.name<<"\n"<<"item's quantity: "<<obj.quantity<<"\n"<<"item's price: "<<obj.price<<'\n';
        return os;
    }
    // overloading operator >>
    friend istream& operator>>(istream& is,Item& obj){
        is>>obj.name>>obj.quantity>>obj.price;
        return is;
    }
    // setter to set the name
    void setname(string st){
        name=st;
    }
    // setter to set the quantity
    void setquantity(int q){
        quantity=q;
    }
    // setter to set the price
    void setprice(int p){
        price=p;
    }
    // getter to get the name
    string getname(){
        return name;
    }
    // getter to get the quantity
    int getquantity(){
        return quantity;
    }
    // getter to get the id
     int getid(){
        return ID;
    }
    // getter to get the price
    int getprice(){
        return price;
    }
};

//the name of second class
class Seller{
//member variables
private:
    string name;
    string email;
    int maxItems;
    Item* items;
    int ind=0;
public:
//parameterized constructor
    Seller(string nm,string mail,int size){
        name=nm;
        email=mail;
        maxItems=size;
        items=new Item[maxItems];
    }
    //function to add an item
    bool AddanItem(Item it){
        bool exist= false;
        for (int i = 0; i < maxItems; ++i) {
            if(it==items[i]){
                // if the item is found ,we increase its quantity by the new quantity
                items[i]+=it;
                exist= true;
                cnt_ids--;
                break;
            }
        }
        // if the item is not found,we add the item
        if(!exist){
            if(ind>=maxItems){
                return false;
            }
            else{
                items[ind]=it;
                ind++;
                return true;
            }
        }
        else{
            return true;
        }
    }
    //function to sell an item
    bool sellanitem(string sname,int quantity){
        bool found= false;
        for (int i = 0; i < maxItems; ++i) {
            if(items[i].getname()==sname){
                found=true;
                // if the required quantity less than or equal the current quantity, we sell the item and decrease the quantity
                if(quantity<=items[i].getquantity()){
                    items[i]-=quantity;
                }
                // if the required greater than the current quantity, we can not sell the item
                else{
                    cout<<"There is only {"<<items[i].getquantity()<<"} left for this item\n";
                }
                break;
            }
        }
        if(found){
            return true;
        }
        else{
            return false;
        }
    }
    //function to print the current items
    void printItems(){
        for (int i = 0; i < ind; ++i) {
            cout<<items[i]<<'\n';
        }
    }
    // function to find the item by id
    Item* findanitem(int id){
        for (int i = 0; i < maxItems; ++i) {
            if(items[i].getid()==id){
                return &items[i];
            }
        }
        return nullptr;
    }
    //destructor
    ~Seller(){
        delete[] items;
    }
    // overloading operator <<
    friend ostream& operator<<(ostream& os,Seller& obj){
        os<<"seller's name: "<<obj.name<<"\n"<<"seller's email: "<<obj.email<<'\n';
        return os;
    }
    // function to print the info of the seller
    void printmyinfo(){
        cout<<*this<<'\n';
    }
};
// function to show menu to the seller to choose option from it
void showmenu(){
    cout<<"choose one option from the following menu\n";
    cout<<"1. Print My Info\n";
    cout<<"2. Add An Item.\n";
    cout<<"3. Sell An Item.\n";
    cout<<"4. Print Items.\n";
    cout<<"5. Find an Item by ID.\n";
    cout<<"6. Exit.\n";
};
int main(){
    // getting the seller name and email and the size of the shop
    string name,email;
    int size;
    cout<<"enter your name\n";cin>>name;
    cout<<"enter your email\n";cin>>email;
    cout<<"the size of items\n";cin>>size;
    Seller s1(name,email,size);
    cnt_ids=1;
    while (true){
        // start showing the menu until the seller choose exit
        showmenu();
        int option;cin>>option;
        if(option==1){
            s1.printmyinfo();
        }
        else if(option==2){
            Item new_item;
            cout<<"enter item's name and quantity and price\n";
            cin>>new_item;
            Item i1(new_item);
            if(s1.AddanItem(i1)){
                // printing that the operation done and the item is added
                cout<<"the item is added\n";
            }
            else{
                // printing that there is not place in the shop
                cout<<"there is no place in the shop\n";
            }
        }
        else if(option==3){
            string productname;int productquantity;
            cout<<"enter item's name and quantity\n";
            cin>>productname>>productquantity;
            // use function sell an item that return true if the item is found otherwise return false
            if(s1.sellanitem(productname,productquantity)){
                cout<<"the item is found\n";
            }
            else{
                cout<<"the item is not found!\n";
            }
        }
        else if(option==4){
            // printing the current items
            s1.printItems();
        }
        else if(option==5){
            int id;
            // get id of the required item to find it using function  find an item by id
            cout<<"enter item's id\n";
            cin>>id;
           if(s1.findanitem(id)== nullptr){
               cout<<"this item not found!\n";
           }
           else{
               cout<<*s1.findanitem(id)<<'\n';
           }
        }
        else if(option==6){
            // closing the program
            cout<<"Thank you!\n";
            break;
        }
    }
    return 0;
}