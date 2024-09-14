# Shopping Cart System in C++

This is a simple shopping cart system implemented in C++. It includes functionalities like adding/removing items from the cart, viewing the cart, applying various discounts, and checking out with the option to view the total in different currencies.

## Table of Contents

- [Features](#features)
- [Discounts](#discounts)
- [Product Catalog](#product-catalog)
- [How to Use](#how-to-use)
- [Commands](#commands)
- [Setup and Compilation](#setup-and-compilation)
- [Example Usage](#example-usage)


## Features

- **Add to Cart**: Add products to the shopping cart with specified quantities.
- **Remove from Cart**: Remove a product or reduce its quantity.
- **View Cart**: View all products in the cart, their quantities, and the total price.
- **Discounts**: Apply discounts such as "Buy 1 Get 1 Free on Fashion" and "10% off Electronics".
- **Checkout**: Checkout with the final total, including discounts.
- **Currency Conversion**: Convert the final price into different currencies (EUR, GBP, INR).

## Discounts

1. **Buy 1 Get 1 Free on Fashion items**: Every second item of a fashion product is free.
2. **10% off on Electronics items**: A 10% discount is applied to all electronics in the cart.

## Product Catalog

Pre-defined products available for purchase:

| Product ID | Name      | Category    | Price (USD) |
|------------|-----------|-------------|-------------|
| P001       | Laptop    | Electronics | 1000.00     |
| P002       | Phone     | Electronics | 500.00      |
| P003       | T-Shirt   | Fashion     | 20.00       |

## How to Use

1. **View the Cart**: View all items in the cart and their total cost.
2. **Add to Cart**: Add products by their product ID and specify quantity.
3. **Apply Discounts**: Discounts are automatically applied at checkout.
4. **Checkout**: See the final total price after discounts, and optionally convert it to another currency.

## Commands

Here are the available commands to interact with the cart system:

| Command                 | Description                                                  | Example                     |
|-------------------------|--------------------------------------------------------------|-----------------------------|
| `view_cart`             | View all items in the cart and the total price.               | `view_cart`                 |
| `list_discounts`         | List all available discounts.                                | `list_discounts`            |
| `checkout`              | Checkout and apply all discounts.                            | `checkout`                  |
| `add_to_cart [id] [qty]` | Add a product to the cart by its ID and quantity.             | `add_to_cart P001 1`        |
| `remove_from_cart [id]`  | Remove a product from the cart completely or reduce quantity. | `remove_from_cart P001`     |

## Setup and Compilation

To compile and run the shopping cart system on your local machine, follow these steps:

### Prerequisites

- You need a C++ compiler (e.g., GCC) installed on your system.

### Steps

1. Clone or download the repository:
   ```bash
   git clone https://github.com/Yatendrarajput/Assignment1.git
   cd ecommerce.cpp
2. Run the C++ File, Use Above Commands to Navigate
  
##Example Use case

 ```bash
> add_to_cart P001 1
1 Laptop(s) added to the cart.

> add_to_cart P003 2
2 T-Shirt(s) added to the cart.

> view_cart
Your Cart:
Laptop - Quantity: 1, Price: 1000 USD, Total: 1000 USD
T-Shirt - Quantity: 2, Price: 20 USD, Total: 40 USD
Total (before discounts): 1040 USD

> checkout
Applying discounts...
Buy 1 Get 1 Free applied on T-Shirt.
Final Total in USD: 1020 USD
Would you like to view the total in another currency? (yes/no): yes
Available Currencies: EUR, GBP, INR
Enter currency code: EUR
Final Total in EUR: 867.0

   
