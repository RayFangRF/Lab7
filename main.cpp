#include <iostream>
#include <fstream>
#include <vector>
#include <string>
typedef unsigned int inti;
using namespace std;
int main() {
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    /* Load files here */

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;

    cin >> option;
}



struct Arsenal{
    string weaponName;
    float weaponPowerConsumption;
    int weaponPower;
    Arsenal(){
        weaponPowerConsumption = 0;
        weaponPower = 0.0;
        weaponName = nullptr;
    }
};
struct Battleship{
    string shipName;
    string shipClass;
    short shipLength;
    int shieldCapacity;
    float maxWarpSpeed;
    vector<Arsenal> inventory;
    Battleship(){
     shipName = nullptr;
     shipClass = nullptr;
     shipLength = 0;
     shieldCapacity = 0;
     maxWarpSpeed = 0.0;
    }
};
void printShip(Battleship &ship){
    cout<<"Name: "<< ship.shipName<<endl;
    cout<<"Class: "<<ship.shipClass<<endl;
    cout<<"Length: "<<ship.shipLength<<endl;
    cout<<"Shield capacity: "<<ship.shieldCapacity<<endl;
    cout<<"Maximum Warp: "<<ship.maxWarpSpeed<<endl;
    cout<<"Armaments: "<<endl;
    if(ship.inventory.size() != 0){
        for(inti i = 0; i < ship.inventory.size(); i++){
            cout<<ship.inventory.at(i).weaponName<<", "<< ship.inventory.at(i).weaponPower<<", "<<ship.inventory.at(i).weaponPowerConsumption<<endl;
        }
    } else{
        cout<<"Unarmed"<<endl;
    }
    cout<<endl;
}


void loadFile(vector<Battleship>& ships, int fileNum){
    string path;
    if(fileNum == 1){
        path = "friendlyships.shp";
    }else if(fileNum == 2){
        path = "enemyships.shp";
    }else{
        cout<<"incorrect input!"<<endl;
    }
    ifstream file(path, ios_base::binary);
    if(file.is_open()){
        inti count;
        file.read((char*) &count, 4);
        for(inti i = 0; i < count; i++){
            Battleship newShip;
            inti nameLength;
            inti classLength;
            inti inventorySize = 0;
            file.read((char*)&nameLength, 4);
            file.read((char*)&classLength, 4);
            char* shipName = new char[nameLength];
            char* className = new char[classLength];
            for(inti j = 0; j< nameLength; j++){
                file.read(&shipName[j], 1);
            }
            for(inti z = 0; z< classLength; z++){
                file.read(&className[z], 1);
            }
            newShip.shipName = shipName;
            newShip.shipClass = className;
            delete[] shipName;
            delete[] className;
            file.read((char*) &newShip.shipLength,2);
            file.read((char*) &newShip.shieldCapacity, 4);
            file.read((char*) &newShip.maxWarpSpeed, 4);
            file.read((char*) &inventorySize, 4);
            //load in inventory
            if(inventorySize > 0){
                Arsenal ars;
                for(inti u = 0; u < inventorySize; u++){
                    file.read((char*) &nameLength,4);
                    char* name = new char[nameLength];
                    for(inti a = 0; a >nameLength; a++){
                        file.read(&name[a],1);
                    }
                    ars.weaponName = name;
                    delete[] name;
                    file.read((char*)&ars.weaponPower, 4);
                    file.read((char*)&ars.weaponPowerConsumption, 4);
                    newShip.inventory.push_back(ars);
                }

            }
            ships.push_back(newShip);

        }
        file.close();
    }
}
void printAll(vector<Battleship> &ships){
    for(inti i = 0; i < ships.size(); i++){
        printShip(ships.at((i)));
    }
}
void printStrongestShip(vector<Battleship> &ships){
    Battleship strong = ships.at(0);
    for(inti i = 0; i < ships.size()-1; i++){
        for(inti j = 0; i < ships[i].inventory.size(); j++){
            if(ships[i].inventory[j+1].weaponPower > ships[i].inventory[j].weaponPower){
                strong = ships[i+1];
            }
        }
    }
    printShip(strong);
}
void strongestOverall(vector<Battleship> &ships){
    inti totalPower;
    inti mostPower = 0;
    Battleship strongestShip = ships[0];
    for(inti i = 0; i < ships.size(); i++){
        totalPower = 0;
        for(inti j = 0; j < ships[i].inventory.size(); j++){
            totalPower += ships[i].inventory[j].weaponPower;
        }
        if(totalPower > mostPower){
            strongestShip = ships.at(i);
            mostPower = totalPower;
        }
    }
    printShip(strongestShip);
}
void weakestShip(vector<Battleship> &ships){
    inti totalPower;
    inti leastPower = 0;
    Battleship weakestShip = ships[0];
    for(inti i = 0; i < ships.size(); i++){
        totalPower = 0;
        for(inti j = 0; j < ships[i].inventory.size(); j++){
            if(ships[i].inventory.size() != 0){
                totalPower += ships[i].inventory[j].weaponPower;
            }
        }
        if(totalPower < leastPower){
            weakestShip = ships.at(i);
            leastPower = totalPower;
        }
    }
    printShip(weakestShip);
}

