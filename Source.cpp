#include <iostream>
#include <string>
#include<fstream>
using namespace std;

// As structure for the database of Garment inventory: includes name, brand, type, color , size , quantity , gender
struct Garment {
    string name;
    string brand;
    string type;
    string color;
    int size;
    int quantity;
    char gender;
};


bool password( string &pass )
{
	while(true)
	{
	if(pass.empty())
	{
	   cout<<"You haven't set any password yet.  Enter a password (with no spaces): ";
	   cin>>pass;
    }
    string passcheck;
     cout<<" now you have a password. Enter your password to begin file operations : ";
     cin >> passcheck;
     
     if(pass == passcheck)
     return true;
    
     
    }
}

//loads initial in put for our database from the file named Text.txt
void loadfromfile(string filename, int& count ,int capacity, Garment*& inventory,string &pass)
{
    ifstream rdr("save.txt");
   
    while (!rdr.eof())
    {
        rdr >> count;
        for (int i = 0; i < count; i++)
        {
            //if the size has reched limit (capacity) we increase size
            if (i == capacity) {
                int c = capacity;
                capacity = capacity * 2 + 1;
                /*inventory = (Garment*)realloc(inventory, capacity * sizeof(Garment));*/
                Garment* newinvent = new Garment[capacity];
                for (int i = 0; i < c; i++)
                {
                    newinvent[i].name = inventory[i].name;
                    newinvent[i].brand = inventory[i].brand;
                    newinvent[i].type = inventory[i].type;
                    newinvent[i].color = inventory[i].color;
                    newinvent[i].size = inventory[i].size;
                    newinvent[i].quantity = inventory[i].quantity;
                    newinvent[i].gender = inventory[i].gender;
                }
                delete[] inventory;
                inventory = newinvent;
            }
            //reading from file
            rdr >> inventory[i].name;
            rdr >> inventory[i].brand;
            rdr >> inventory[i].type;
            rdr >> inventory[i].color;
            rdr >> inventory[i].size;
            rdr >> inventory[i].quantity;
            rdr >> inventory[i].gender;

        }
        rdr >> pass;
        return ;
    }
   
}
//writes our current inventory in file named Save.txt
void writeinfile(string filename, int count,  Garment*& inventory,string &pass)
{
    ofstream wtr("save.txt");

   //writes the count on top of file
    wtr  << count << endl;
        for (int i = 0; i < count; i++)
        {

          //writing all components
            wtr << inventory[i].name<<endl;
            wtr << inventory[i].brand<<endl;
            wtr << inventory[i].type << endl;
            wtr << inventory[i].color << endl;
            wtr << inventory[i].size << endl;
            wtr << inventory[i].quantity << endl;
            wtr << inventory[i].gender << endl;
            

        }
        wtr << pass<<endl;
        return;
    

}

//Adds a new garment and updates the record
void addGarment(Garment*& inventory, int& count, int& capacity) {
    Garment newGarment;

    cout << "Enter the name of the garment: ";
    getline(cin, newGarment.name);

    cout << "Enter the brand of the garment: ";
    getline(cin, newGarment.brand);

    cout << "Enter the type of the garment: ";
    getline(cin, newGarment.type);

    cout << "Enter the color of the garment: ";
    getline(cin, newGarment.color);

    cout << "Enter the size of the garment (number): ";
    cin >> newGarment.size;

    cout << "Enter the quantity of the garment (number): ";
    cin >> newGarment.quantity;

    cout << "Enter the Gender of the garment (M/F): ";
    cin >> newGarment.gender;

    cin.ignore();

    //if the size has reached limit (capacity) we increase size
    if (count == capacity) {
        capacity = capacity * 2 + 1;
       /* inventory = (Garment*)realloc(inventory, capacity * sizeof(Garment));*/
        Garment* newinvent = new Garment[capacity];
        for (int i = 0; i < count; i++)
        {
            newinvent[i].name = inventory[i].name;
            newinvent[i].brand = inventory[i].brand;
            newinvent[i].type = inventory[i].type;
            newinvent[i].color = inventory[i].color;
            newinvent[i].size = inventory[i].size;
            newinvent[i].quantity = inventory[i].quantity;
            newinvent[i].gender = inventory[i].gender;
        }
        delete[] inventory;
        inventory = newinvent;
    }

    inventory[count] = newGarment;
    count++;

    cout << "The garment has been added to the inventory." << endl;
}

//deletes a garment from record
void deleteGarment(Garment*& inventory, int& count, int& capacity) {
    int indexToDelete;

    cout << "Enter the index of the garment to delete: ";
    cin >> indexToDelete;
    indexToDelete--;
    if (indexToDelete < 0 || indexToDelete >= count) {
        cout << "Invalid index. Please try again." << endl;
        return;
    }

    for (int i = indexToDelete; i < count - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    count--;

    

    cout << "The garment has been deleted from the inventory." << endl;
}


//For display
void displayInventory(Garment* inventory, int count) {
    if (count == 0) {
        cout << "The inventory is empty." << endl;
    }
    else {
        cout << "Inventory:" << endl;
        for (int i = 0; i < count; i++) {
            Garment currentGarment = inventory[i];
            cout << " item: #" << i + 1 << endl;
            cout << "  Name: " << currentGarment.name << endl;
            cout << "  Brand: " << currentGarment.brand << endl;
            cout << "  Type: " << currentGarment.type << endl;
            cout << "  Color: " << currentGarment.color << endl;
            cout << "  Gender: " << currentGarment.gender << endl;
            cout << "  Size: " << currentGarment.size << endl;
            cout << "  Quantity: " << currentGarment.quantity << endl;
           
            cout << endl;
        }
    }
}

int main() {

string pass ;
    //we make a capacity for our record 
    const int starting_capacity = 1;
    //declare the main array for our record in heap
    Garment* inventory = new Garment[starting_capacity];
    int count = 0;
    int capacity = starting_capacity;
    int choice;
   
    //callig functions
    loadfromfile("Text.txt", count,capacity, inventory,pass);
    writeinfile("Save.txt", count, inventory,pass);
     password(pass);
    //loop
    while (true) {
        //Menu
        system("cls");
        cout << "Inventory Management System" << endl;
        cout << "1. Add a new garment" << endl;
        cout << "2. Display inventory" << endl;
        cout << "3. Delete a garment/record" << endl;
        cout << "4. Delete all record" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        //switch case for menu
        switch (choice) {
        case 1:
            addGarment(inventory, count, capacity);
            writeinfile("Save.txt", count, inventory,pass);
            system("pause");
            break;
        case 2:
            displayInventory(inventory, count);
            system("pause");
            break;
        case 3:
            displayInventory(inventory, count);
            deleteGarment(inventory, count, capacity);
            writeinfile("Save.txt", count, inventory,pass);
            system("pause");
            break;
        case 4:
            delete[] inventory;
            cout << "All records were deleted ! ";
            system("pause");
            break;
        case 5:
            system("cls");
            cout<<" You are about to exit ! ";
            system("pause");
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            system("pause");
            break;
        }
    }
    
    return 0;
}
