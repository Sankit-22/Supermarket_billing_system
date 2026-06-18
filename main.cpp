#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill():Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};


int levenshteinDistance(const string &s1, const string &s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for(int i=0; i<=m; i++) dp[i][0] = i;
    for(int j=0; j<=n; j++) dp[0][j] = j;

    for(int i=1; i<=m; i++) {
        for(int j=1; j<=n; j++) {
            if(s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[m][n];
}

void addItem(Bill b) {
    bool close = false;
    while(!close) {
        int choice;
        cout << "\t1.Add Item" << endl;
        cout << "\t2.Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if(choice == 1) {
            system("cls");
            string item;
            int rate, quant;
            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("D:/Bill.txt", ios::app);
            if(!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
                cout << "\tItem Added Successfully" << endl;
            }
            out.close();
            Sleep(2000);
        }
        else if(choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(1500);
        }
    }
}

void printBill() {
    system("cls");
    int count = 0;
    bool close = false;

    while(!close) {
        system("cls");
        int choice;
        cout << "\t1.Add Bill" << endl;
        cout << "\t2.Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if(choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("D:/Bill.txt");
            ofstream out("D:/Bill Temp.txt");

            string line;
            bool found = false;
            string suggestion = "";

            while(getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if(item == itemName) {
                    found = true;
                    if(quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;
                        int newQuant = itemQuant - quant;
                        count += amount;
                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    } else {
                        cout << "\tSorry, " << item << " Ended!" << endl;
                        out << line << endl;
                    }
                } else {
                    // Suggest similar item
                    if(levenshteinDistance(item, itemName) <= 2 && suggestion.empty()) {
                        suggestion = itemName;
                    }
                    out << line << endl;
                }
            }

            in.close();
            out.close();

            // If item not found but we have a suggestion
            if(!found && !suggestion.empty()) {
                char ch;
                cout << "\tDid you mean: " << suggestion << "? (y/n): ";
                cin >> ch;
                if(ch == 'y' || ch == 'Y') {
                    // Replace item with suggestion and recalculate immediately
                    item = suggestion;
                    // Re-run billing for the suggested item without restarting
                    ifstream in2("D:/Bill.txt");
                    ofstream out2("D:/Bill Temp.txt");
                    while(getline(in2, line)) {
                        stringstream ss(line);
                        string itemName;
                        int itemRate, itemQuant;
                        char delimiter;
                        ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                        if(item == itemName) {
                            if(quant <= itemQuant) {
                                int amount = itemRate * quant;
                                cout << "\tItem | Rate | Quantity | Amount" << endl;
                                cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;
                                int newQuant = itemQuant - quant;
                                count += amount;
                                out2 << itemName << " : " << itemRate << " : " << newQuant << endl;
                            } else {
                                cout << "\tSorry, " << item << " Ended!" << endl;
                                out2 << line << endl;
                            }
                        } else {
                            out2 << line << endl;
                        }
                    }
                    in2.close();
                    out2.close();
                } else {
                    cout << "\tItem Not Available!" << endl;
                }
            }

            remove("D:/Bill.txt");
            rename("D:/Bill Temp.txt", "D:/Bill.txt");
        }
        else if(choice == 2) {
            close = true;
            cout << "\tCounting Total Bill" << endl;
        }
        Sleep(2000);
    }

    system("cls");
    cout << "\n\n\tTotal Bill ----------------- : " << count << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(3000);
}


int main() {
    Bill b;
    bool exit = false;

    while(!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1.Add Item" << endl;
        cout << "\t2.Print Bill" << endl;
        cout << "\t3.Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if(val == 1) {
            addItem(b);
        }
        else if(val == 2) {
            printBill();
        }
        else if(val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(1500);
        }
    }
    return 0;
}
