#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>      

using namespace std;
//DECLARE TEMPLATES
template <class t>
int Total(t ob)
{
    ob.total_amt = ob.price * ob.qty;
    return ob.total_amt;
}

//DECLARE TEMPLATES
template <class k>
int search(k *ob, string s)
{

    string t, f;
    int p;
    ifstream infile;
    infile.open("Pfood.txt");       //FILE OPENING    
    int i = 0;
    int flag = 0;
    while (infile.peek() != EOF)
    {

        infile >> t >> f >> p;
        if (s.compare(f) == 0)
        {
            flag = 1;
            break;
        }
    }
    infile.close();        //COSING FILE

    if (flag == 1)
    {
        ob->ordered_food = f;
        ob->price = p;
        cout << "Enter The Quantity\n";
        cin >> ob->qty;
    }

    if (flag == 0)
    {
        return 0;
    }
    return 1;
}

class Food                        //CLASS FOOD
{
public:
    string name;
    string Food_type;
    int price;
    bool availability;

    void setAvailability()
    {
        int n;
        cout << "\n\nIs Food Available ??" << endl;
        cout << "\n\nIf Yes Enter 1\nIf No Enter 0\n"
             << endl;
        cin >> n;
        if (n == 1)
        {
            availability = true;
        }
        else
            availability = false;
    }
};

class payment             //CLASS PAYMENT
{
public:
    int given_amt;

    void Set_givenamt()
    {
        cout << "\n\nAmount given by Customer" << endl;
        cin >> given_amt;
    }
};

class Order          //CLASS ORDER
{
public:
    static int order_id;
    string ordered_food;
    int price;
    int total_amt;
    int qty;
    payment pay;

    void Transaction()
    {
        while (1)
        {
            pay.Set_givenamt();

            try
            {
                if (pay.given_amt < total_amt)
                    throw 10;

                else
                {
                    cout << "\nPayment is Done" << endl;
                    cout << "\n\nReturned amt:=" << pay.given_amt - total_amt << endl;
                    break;
                }
            }
            catch (int x)
            {
                cout << "\nAmount Should Be Greater than or equal to total amt" << endl;
            }
        }
    }
};

int Order::order_id = 0;

class Delivery : public Order
{
public:
    int extra_charge = 15;
    bool extra_cutleries;
    int cutleries_charge;

    void needCutleries()
    {

        int n;
        cout << "\n\nNeed Cutleries ??" << endl;
        cout << "\n\nIf Yes Enter 1\n If No Enter 0\n"
             << endl;
        cin >> n;

        if (n == 1)
        {
            extra_cutleries = true;
            cutleries_charge = 25;
            calculate_net(cutleries_charge, extra_charge);
        }
        else
        {
            cutleries_charge = 0;

            calculate_net(extra_charge);
        }
    }

    void calculate_net(int x, int y)
    {
        total_amt = total_amt + x + y;
    }

    void calculate_net(int x)
    {
        total_amt = total_amt + x;
    }
};

class customer              //CLASS CUSTOMER
{
public:
    string c_name;
    int c_id;
    bool Parcel;

    customer()
    {
        Parcel = false;
    }

    void setCustomer()
    {
        cout << "Enter Customer Id\n";
        cin >> c_id;
        cout << "Enter Customer Name\n";
        cin >> c_name;
        ofstream outfile;
        outfile.open("Customers.txt", ios::app);
        {
            outfile << c_id << "   " << c_name << endl;
        }
        outfile.close();
    }

    void printDetail()
    {

        cout << "Customer_Id"
             << "   |   "
             << "Name"
             << "   |      " << endl;
        cout << c_id << "      " << c_name << "        " << endl;
    }

    void Order_Detail()
    {
        Order ob;

        string s;
        int x;
        while (1)
        {
            try
            {
                cout << "\n\nWhat Food Do you Want to Order?\n";
                cin >> s;

                x = search(&ob, s);
                if (x == 0)
                    throw 10;

                break;
            }
            catch (int x)
            {
                cout << "\n\nTry Ordering other food\n";
            }
        }
        ob.total_amt = Total(ob);
        ob.order_id++;
        ofstream outfile;
        outfile.open("cus_order.txt", ios::app);
        {
            outfile << c_id << "   " << c_name << "   " << ob.order_id << "   " << ob.ordered_food << "   " << ob.price << "   " << ob.qty << "   " << ob.total_amt << endl;
        }

        outfile.close();

        cout << "--------------------------------------------------------" << endl;
        cout << "Order_Id"
             << "   |   "
             << "Ordered Food"
             << "  |      "
             << "Price"
             << "  |      "
             << "Qty"
             << "   |    "
             << "Amt" << endl;
        cout << ob.order_id << "  |            " << ob.ordered_food << "                   |     " << ob.price << "     |      " << ob.qty << "    |      " << ob.total_amt << endl;
        ob.Transaction();
    }

    void RequireParcel()
    {

        Parcel = true;

        Delivery ob;

        string s;
        int x;
        while (1)
        {
            try
            {
                cout << "What Food Do you Want to Order?\n";
                cin >> s;

                x = search(&ob, s);
                if (x == 0)
                    throw 10;

                break;
            }
            catch (int x)
            {
                cout << "\n\nTry Ordering other food\n";
            }
        }

        ob.total_amt = Total(ob);
        ob.order_id++;
        cout << "\n\nDetails Include Delivery charges\n";
        ob.needCutleries();
        ofstream outfile;
        outfile.open("cus_order.txt", ios::app);         //FILE OPENING
        {
            outfile << c_id << "   " << c_name << "   " << ob.order_id << "   " << ob.ordered_food << "   " << ob.price << "   " << ob.qty << "   " << ob.total_amt << endl;
        }

        outfile.close();                       //CLOSING FILE
        cout << "--------------------------------------------------------" << endl;

        cout << "Order_Id"
             << "   |   "
             << "Ordered Food"
             << "    |      "
             << "Price"
             << "  |   "
             << "Qty"
             << "  |   "
             << "Amt" << endl;

        cout << ob.order_id << "      " << ob.ordered_food << "       " << ob.price << "    " << ob.qty << "    " << ob.total_amt << endl;
        ob.Transaction();
    }
};

class Restaurant                 //CLASS TRANSACTION
{
public:
    string name;
    int id;
    string location;
    Food fd[100];
 

    void setRestaurantDetails()
    {
        cout << "Enter Restaurant name\n";
        cin >> name;
        cout << "Enter Restaurant Id\n";
        cin >> id;
        cout << "Enter Restaurant Location\n";
        cin >> location;
    }

    void menu()
    {
        cout << "--------------------------------------------------------" << endl;
        ifstream infile;
        infile.open("pfood.txt");            //FILE OPENING
        int i = 0;

        while (infile.peek() != EOF)
        {

            infile >> fd[i].Food_type >> fd[i].name >> fd[i].price;
            i++;
        }
        
        infile.close();                   //CLOSING FILE

        int x ;
        cout << "Food Type"
             << "   | "
             << "     "
             << "Name"
             << "   |  "
             << "   "
             << "Price"
             << "  |  "
             << "   " << endl;

        for (x = 0; x < i; x++)
            cout << fd[x].Food_type << "      " << fd[x].name << "        " << fd[x].price << endl;

      
    }

    void customer_Order_Details()           //FUNCTION CUSTOMER_ORDER_DETAILS
    {
        int n;
        
        customer cu;

        cu.setCustomer();
        cout << "--------------------------------------------------------" << endl;
        cu.printDetail();

        cout << "\n Do you Need Parcel?\n";
        cout << "\nIf Yes Enter 1\nIf No Enter 0\n"<< endl;
        cin >> n;

        if (n == 1)
        {
            cu.RequireParcel();
        }
        else

            cu.Order_Detail();
    }
};

int main()
{
    Restaurant r;          //OBJECT r OF CLASS RESTAURANT

    int choice;
    
    

    while (1)
    {  cout << "\n\nEnter 1 for Menu\nEnter 2 for Ordering Food\nEnter 3 to exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            r.menu();
            break;

        case 2:
            r.customer_Order_Details();
            break;

        case 3:
            exit(0);
        default:
            cout << " Enter Valid Choice\n";
        }
    }

    return 0;
}