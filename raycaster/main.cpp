#include <iostream>
#include <vector>
#include "FileReader.h"
#include "Object.h"
#include "Game.h"
using namespace std;
int main() {
    vector<Object> objectList;

    if (FileReader::readObjectsFromFile("Texto.txt", objectList))
    {
        cout << "Por fin se lee esta monada" << endl;
 

        for (Object obj : objectList) 
        {
            cout << "Type: " << static_cast<int>(obj.getType()) << ", Position: (" << obj.getPosition().x << ", " << obj.getPosition().y << "), Scale: " << obj.getScale() << ", Shift: " << obj.getShift() << endl;
        }
    }
    else
    {
        cout << "No se puede leer." << endl;
        return 1;
    }

    Game game;
    game.startGame();

    return 0;
}
