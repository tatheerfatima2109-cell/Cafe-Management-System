#include <iostream>
#include <string>
using namespace std;

class MenuItem
{
private:
    int id, price;
    string name;
public:
    MenuItem(int i = 0, string n = "", int p = 0)
    {
        id = i;
        name = n;
        price = p;
    }
    int getId() const
    { return id; }
    string getName() const
    { return name; }
    int getPrice() const
    { return price; }
    virtual void show() const
    { cout << id << ". " << name << " Rs." << price << endl; }
};

// class for fooditem (inherited)
class FoodItem: public MenuItem
{
public:
    FoodItem(int i = 0, string n = "", int p = 0): MenuItem(i, n, p){}
    void show() const override
    {
        cout << getId() << ". " << getName() << ": Rs." << getPrice() << " (Food)" << endl;
    }
};

// class for drinkitem (inherited)
class DrinkItem: public MenuItem
{
public:
    DrinkItem(int i = 0, string n = "", int p = 0): MenuItem(i, n, p){}
    void show() const override
    {
        cout << getId() << ". " << getName() << ": Rs." << getPrice() << " (Drink)" << endl;
    }
};

// customized drink (inherited from drinkitem)
class SpecialDrink: public DrinkItem
{
public:
    SpecialDrink(int i = 0, string n = "", int p = 0) : DrinkItem(i, n, p){};
    
    // calculation for customization
    int customCost()
    {
        int extra = 0, ch;
        cout << "Customizing Drink" << endl;
        while (true) {
            cout << "Size: 1.Small 2.Medium(+20) 3.Large(+50): ";
            cin >> ch;
            if (ch == 1) {
                break;
            }
            else if (ch == 2) {
                extra = extra + 20;
                break;
            }
            else if (ch == 3) {
                extra = extra + 50;
                break;
            }
            else
                cout << "Invalid\n";
        }
        while (true) {
            cout << "Milk: 1.Regular 2.Almond(+30) 3.Soy(+25): ";
            cin >> ch;
            if (ch == 1) {
                break;
            }
            else if (ch == 2) {
                extra = extra + 30;
                break;
            }
            else if (ch == 3)
            {
                extra = extra + 25;
                break;
            }
            else
                cout << "Invalid" << endl;
        }
        while (true) {
            cout << "Add-on: 1.None 2. Espresso(+50) 3.Whipped(+40) 4.Choco(+30): ";
            cin >> ch;
            if (ch == 1) {
                break;
            }
            else if (ch == 2) {
                extra = extra + 50;
                break;
            }
            else if (ch == 3) {
                extra = extra + 40;
                break;
            }
            else if (ch == 4)
            {
                extra = extra + 30;
                break;
            }
            else
                cout << "Invalid\n";
        }
        return extra;
    }

    void show() const override {
        cout << getId() << ". " << getName() << ": Rs." << getPrice() << " (Customizable)" << endl;
    }
};

class OrderLine
{
private:
    int itemId, price, qty, extra;
    string name;
public:
    OrderLine(int id = 0, string n = "", int p = 0, int q = 0, int e = 0)
    {
        itemId = id;
        name = n;
        price = p;
        qty = q;
        extra = e;
    }
    int getId() const
    { return itemId; }
    string getName() const
    { return name; }
    int getQty() const
    { return qty; }
    int getExtra() const
    { return extra; }
    int getPrice() const
    { return price; }
    int total() const
    {
        return (price + extra) * qty;
    }
    void show() const {
        cout << itemId << ". " << name << ", Price: " << price << ", Extra: " << extra << ", Qty: " << qty << ", Total: " << total() << endl;
    }
};

class Order
{
private:
    int orderId;
    bool cancelled;
    OrderLine items[20];
    int itemCount;
public:
    Order(int id = 0)
    {
        orderId = id;
        cancelled = false;
        itemCount = 0;
    }
    int getOrderId() const {
        return orderId;
    }
    bool isCancelled() const
    { return cancelled; }
    void cancel()
    { cancelled = true; }
    bool empty() const
    {
        return itemCount == 0;
    }
    int getItemCount() const
    { return itemCount; }
    OrderLine getItem(int i) const
    {
        return items[i];
    }
    void addItem(MenuItem item, int qty, int extra = 0)
    { 
        items[itemCount++] = OrderLine(item.getId(), item.getName(), item.getPrice(), qty, extra); 
    }
    int totalBill() const
    {
        int sum = 0;
        for (int i = 0; i < itemCount; i++)
        {
            sum += items[i].total();
        }
        return sum; 
    }
    void show() const
    {
        cout << endl << "Order ID: " << orderId << endl;
        if (cancelled)
        { cout << " (Cancelled)"; }
        cout << endl;
        for (int i = 0; i < itemCount; i++)
        {
            items[i].show(); 
        }
        cout << "Final Total: Rs." << totalBill() << endl;
    }
};

class CafeSystem
{
private:
    MenuItem* menu[9];
    SpecialDrink special;
    Order orders[50];
    int orderCount;
    int nextOrderId;
public:
    CafeSystem()
    {
        menu[0] = new FoodItem(1, "Croissant", 180);
        menu[1] = new FoodItem(2, "Chocolate Cake", 1350);
        menu[2] = new FoodItem(3, "Donut", 120);
        menu[3] = new FoodItem(4, "Cupcake", 150);
        menu[4] = new FoodItem(5, "Brownie", 200);
        menu[5] = new FoodItem(6, "Sandwich", 280);
        menu[6] = new DrinkItem(7, "Coffee", 220);
        menu[7] = new DrinkItem(8, "Tea", 100);
        menu[8] = new DrinkItem(9, "Juice", 250);
        special = SpecialDrink(10, "Special Drink", 300);
        orderCount = 0;
        nextOrderId = 1001;
    }
    
    ~CafeSystem()
    {
        for (int i = 0; i < 9; i++)
        {
            delete menu[i]; 
        }
    }

    int inputInt(string msg)
    {
        int x;
        cout << msg;
        cin >> x;
        while (cin.fail())
        {
            cout << "Invalid input. Enter again: " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> x;
        }
        return x;
    }

    MenuItem getItemById(int id)
    {
        for (int i = 0; i < 9; i++)
        {
            if (menu[i]->getId() == id)
            {
                return *menu[i]; 
            }
        }
        return MenuItem(-1, "Invalid", 0); 
    }

    void showMenu()
    {
        cout << "MENU" << endl;
        for (int i = 0; i < 9; i++)
        {
            menu[i]->show();
        }
        special.show();
    }

    void placeOrder()
    {
        Order order(nextOrderId);
        while (true)
        {
            int id = inputInt("Enter item ID (0 to finish): ");
            if (id == 0)
            { 
                break; 
            }
            if (id == 10)
            {
                int qty = inputInt("Qty: ");
                while (qty < 1)
                {
                    cout << "Quantity must be at least 1" << endl;
                    qty = inputInt("Qty: ");
                }
                int extra = special.customCost();
                order.addItem(special, qty, extra);
            }
            else
            {
                MenuItem item = getItemById(id);
                if (item.getId() == -1)
                {
                    cout << "Invalid item ID" << endl;
                    continue;
                }
                int qty = inputInt("Qty: ");
                while (qty < 1)
                {
                    cout << "Quantity must be at least 1." << endl;
                    qty = inputInt("Qty: ");
                }
                order.addItem(item, qty);
            }
        }
        if (order.empty())
        {
            return;
        }
        orders[orderCount++] = order;
        cout << "Order placed. ID: " << nextOrderId << endl;
        nextOrderId++;
    }

    // display order
    void showMyOrder()
    {
        int id = inputInt("Enter Order ID: ");
        for (int i = 0; i < orderCount; i++){
            if (orders[i].getOrderId() == id)
            {
                orders[i].show();
                return;
            }
        }
        cout << "Not found" << endl;
    }

    // cancellation
    void cancelOrder()
    {
        int id = inputInt("Enter Order ID: ");
        for (int i = 0; i < orderCount; i++){
            if (orders[i].getOrderId() == id)
            {
                orders[i].cancel();
                cout << "Cancelled" << endl;
                return;
            }
        }
        cout << "Not found" << endl;
    }

    // Menu Run Loop
    void run()
    {
        int ch;
        do
        {
            cout << endl << "Cafe Brew & Bliss " << endl;
            cout << endl << "...... Select any ONE option ......" << endl;
            cout << endl << "1.Show Menu" << endl << "2.Place Order" << endl << "3.Show Order" << endl << "4.Cancel Order" << endl << "5.Exit" << endl;
            ch = inputInt("Choice: ");
            if (ch == 1)
            {
                showMenu();
            }
            else if (ch == 2)
            {
                placeOrder();
            }
            else if (ch == 3)
            {
                showMyOrder(); 
            }
            else if (ch == 4)
            { 
                cancelOrder(); 
            }
            else if (ch != 5)
            { 
                cout << endl << "Invalid choice. Please enter 1-5." << endl; 
            }
        }
        while (ch != 5); 
    }
};

int main()
{
    CafeSystem c;
    c.run();
    return 0;
}