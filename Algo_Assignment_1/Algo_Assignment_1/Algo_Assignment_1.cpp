#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Item
{
    public:
        int _id;
        string _name;
        float _price;
        string _category;
};

vector<Item> fetchData(const string& file);

vector<Item> addItem(vector<Item> items, int id, string name, float price, string category);

vector<Item> removeItem(vector<Item> items);

vector<Item> bubbleSort(vector<Item> items, int size);

void search(vector<Item> items, int input);

int main()
{
    string dataFile = "product_data.txt";
    int input;

    vector<Item> items = fetchData(dataFile);

    cout << "Unsorted: \n\n";

    for (Item i : items) {
        cout << i._id << ' ' << i._name << ' ' << i._price << ' ' << i._category << endl;
    }

    cout << "\nSorted: \n\n";

    items = bubbleSort(items, items.size());

    for (Item i : items) {
        cout << i._id << ' ' << i._name << ' ' << i._price << ' ' << i._category << endl;
    }

    cout << "\nSearch for an item: \n1: ID \n2: Name\n";
    cin >> input;

    search(items, input);

    cout << "\n\nAfter adding an item: \n\n";

    items = addItem(items, 12390, " Phone", 10.14f, "Entertainment");

    for (Item i : items) {
        cout << i._id << ' ' << i._name << ' ' << i._price << ' ' << i._category << endl;
    }

    items = removeItem(items);

    cout << "\n\nAfter removing an item: \n\n";

    for (Item i : items) {
        cout << i._id << ' ' << i._name << ' ' << i._price << ' ' << i._category << endl;
    }
}

vector<Item> fetchData(const string& file)
{
    ifstream product_data(file);
    string productInfo;
    vector<Item> itemVec;

    if (!product_data.is_open()) {
        cerr << "Error opening file.\n";
        throw;
    }

    while (getline(product_data, productInfo))
    {
        stringstream stream(productInfo);
        Item item;
        string numTemp;

        getline(stream, numTemp, ',');
        item._id = stoi(numTemp);

        getline(stream, item._name, ',');

        getline(stream, numTemp, ',');
        item._price = stof(numTemp);

        getline(stream, item._category, ',');

        itemVec.push_back(item);
    }

    return itemVec;
}

vector<Item> bubbleSort(vector<Item> items, int size)
{
    int i, j;
    bool swapped;   

    for (i = 0; i < size - 1; i++) {
        swapped = false;
        for (j = 0; j < size - i - 1; j++) {
            if (items[j]._price > items[j + 1]._price) {
                swap(items[j], items[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }

    return items;
}

void search(vector<Item> items, int input)
{
    int inputID;
    string inputName;

    switch (input)
    {
        case 1:
            cout << "Enter the ID: ";
            cin >> inputID;

            for (Item i : items) {
                if (i._id == inputID)
                {
                    cout << i._id << ' ' << i._name << ' ' << i._price << ' ' << i._category << endl;
                }
            }
            break;
        case 2:
            cout << "Enter the name: ";
            cin.ignore();
            getline(cin, inputName);

            for (Item i : items) {
                if (i._name == inputName)
                {
                    cout << i._id << ' ' << i._name << ' ' << i._price << ' ' << i._category << endl;
                }
            }
            break;
        default:
            break;
    }
}

vector<Item> addItem(vector<Item> items, int id, string name, float price, string category)
{
    Item addedItem;
    addedItem._id = id;
    addedItem._name = name;
    addedItem._price = price;
    addedItem._category = category;

    items.emplace_back(addedItem);

    items = bubbleSort(items, items.size());

    return items;
}

vector<Item> removeItem(vector<Item> items)
{
    int inputID;

    cout << "Type in the ID of the item you wish to remove: \n";
    cin >> inputID;

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]._id == inputID)
        {
            items.erase(items.begin() + i);
        }
    }

    return items;
}