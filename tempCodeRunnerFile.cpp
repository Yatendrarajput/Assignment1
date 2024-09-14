#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream> // For parsing command input

using namespace std;

// Product class representing an individual product
class Product
{
public:
    string productId;
    string name;
    double price;
    string category;

    // Default constructor (necessary for containers like unordered_map)
    Product() : productId(""), name(""), price(0.0), category("") {}

    Product(string productId, string name, double price, string category)
        : productId(productId), name(name), price(price), category(category) {}
};

// CartItem class representing an item in the cart
class CartItem
{
public:
    Product product;
    int quantity;

    // Default constructor (necessary for containers like unordered_map)
    CartItem() : product(), quantity(0) {}

    CartItem(Product product, int quantity) : product(product), quantity(quantity) {}

    double totalPrice() const
    {
        return product.price * quantity;
    }
};

// Discount base class (for applying different types of discounts)
class Discount
{
public:
    virtual double applyDiscount(const unordered_map<string, CartItem> &cart, double total) = 0;
    virtual string getDescription() const = 0;
};

// Buy 1 Get 1 Free Discount for Fashion category
class Buy1Get1FreeFashion : public Discount
{
public:
    double applyDiscount(const unordered_map<string, CartItem> &cart, double total) override
    {
        for (const auto &item : cart)
        {
            if (item.second.product.category == "Fashion")
            {
                int freeItems = item.second.quantity / 2;
                total -= freeItems * item.second.product.price;
                cout << "Buy 1 Get 1 Free on " << item.second.product.name << " applied.\n";
            }
        }
        return total;
    }

    string getDescription() const override
    {
        return "Buy 1 Get 1 Free on Fashion items";
    }
};

// 10% Discount on Electronics
class TenPercentOffElectronics : public Discount
{
public:
    double applyDiscount(const unordered_map<string, CartItem> &cart, double total) override
    {
        for (const auto &item : cart)
        {
            if (item.second.product.category == "Electronics")
            {
                total -= item.second.totalPrice() * 0.1;
                cout << "10% Off on " << item.second.product.name << " applied.\n";
            }
        }
        return total;
    }

    string getDescription() const override
    {
        return "10% Off on Electronics";
    }
};

// Cart class managing cart operations
class Cart
{
private:
    unordered_map<string, CartItem> items;
    vector<Discount *> discounts;

public:
    void addDiscount(Discount *discount)
    {
        discounts.push_back(discount);
    }

    void addToCart(const Product &product, int quantity = 1)
    {
        if (items.find(product.productId) != items.end())
        {
            items[product.productId].quantity += quantity;
        }
        else
        {
            items[product.productId] = CartItem(product, quantity);
        }
        cout << quantity << " " << product.name << "(s) added to the cart.\n";
    }

    void removeFromCart(const string &productId, int quantity = 0)
    {
        if (items.find(productId) != items.end())
        {
            if (quantity == 0 || items[productId].quantity <= quantity)
            {
                cout << "Removed all " << items[productId].product.name << "(s) from the cart.\n";
                items.erase(productId);
            }
            else
            {
                items[productId].quantity -= quantity;
                cout << "Removed " << quantity << " " << items[productId].product.name << "(s) from the cart.\n";
            }
        }
        else
        {
            cout << "Product not found in the cart.\n";
        }
    }

    void viewCart() const
    {
        if (items.empty())
        {
            cout << "Your cart is empty.\n";
            return;
        }

        double total = 0.0;
        cout << "Your Cart:\n";
        for (const auto &item : items)
        {
            double totalPrice = item.second.totalPrice();
            cout << item.second.product.name << " - Quantity: " << item.second.quantity
                 << ", Price: " << fixed << setprecision(2) << item.second.product.price
                 << " USD, Total: " << totalPrice << " USD\n";
            total += totalPrice;
        }
        cout << "Total (before discounts): " << total << " USD\n";
    }

    double applyDiscounts()
    {
        double total = 0.0;
        for (const auto &item : items)
        {
            total += item.second.totalPrice();
        }

        for (auto &discount : discounts)
        {
            total = discount->applyDiscount(items, total);
        }
        return total;
    }

    void checkout()
    {
        cout << "Applying discounts...\n";
        double finalTotal = applyDiscounts();
        cout << "Final Total in USD: " << fixed << setprecision(2) << finalTotal << endl;
        convertCurrency(finalTotal);
    }

    void listDiscounts() const
    {
        cout << "Available Discounts:\n";
        for (auto discount : discounts)
        {
            cout << discount->getDescription() << endl;
        }
    }

    void convertCurrency(double total) const
    {
        unordered_map<string, double> conversionRates = {
            {"EUR", 0.85},
            {"GBP", 0.75},
            {"INR", 74.85} // Added INR conversion rate
        };
        string response, currency;
        cout << "Would you like to view it in a different currency? (yes/no): ";
        cin >> response;
        if (response == "yes")
        {
            cout << "Available Currencies: EUR, GBP, INR\n";
            cout << "Enter currency: ";
            cin >> currency;
            if (conversionRates.find(currency) != conversionRates.end())
            {
                double convertedTotal = total * conversionRates[currency];
                cout << "Final Total in " << currency << ": " << fixed << setprecision(2) << convertedTotal << endl;
            }
            else
            {
                cout << "Invalid currency!" << endl;
            }
        }
    }
};

// Pre-populate product catalog
unordered_map<string, Product> createProductCatalog()
{
    return {
        {"P001", Product("P001", "Laptop", 1000.00, "Electronics")},
        {"P002", Product("P002", "Phone", 500.00, "Electronics")},
        {"P003", Product("P003", "T-Shirt", 20.00, "Fashion")}};
}

void handleCommand(const string &command, Cart &cart, unordered_map<string, Product> &catalog)
{
    stringstream ss(command);
    string action, productId;
    int quantity;

    ss >> action;

    if (action == "view_cart")
    {
        cart.viewCart();
    }
    else if (action == "list_discounts")
    {
        cart.listDiscounts();
    }
    else if (action == "checkout")
    {
        cart.checkout();
    }
    else if (action == "add_to_cart")
    {
        ss >> productId >> quantity;
        if (catalog.find(productId) != catalog.end())
        {
            cart.addToCart(catalog[productId], quantity);
        }
        else
        {
            cout << "Invalid product ID.\n";
        }
    }
    else if (action == "remove_from_cart")
    {
        ss >> productId >> quantity;
        cart.removeFromCart(productId, quantity);
    }
    else
    {
        cout << "Unknown command.\n";
    }
}

int main()
{
    unordered_map<string, Product> catalog = createProductCatalog();
    Cart cart;

    // Add discounts
    cart.addDiscount(new Buy1Get1FreeFashion());
    cart.addDiscount(new TenPercentOffElectronics());

    // Command-line interaction
    string command;
    while (true)
    {
        cout << "\nEnter command (type 'exit' to quit): ";
        getline(cin, command);
        if (command == "exit")
            break;

        handleCommand(command, cart, catalog);
    }

    return 0;
}
