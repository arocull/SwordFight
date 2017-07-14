//Written by Alan O'Cull. Quick, fun, C++ test. Programmed on July 13th, 2017.

#include <iostream>
#include <string>
#include <sstream>

#include <cstdlib>
#include <ctime>

int RandomNumber(int min, int max){
    int rn = min + rand()%(max-min + 1);
    
    return rn;
};
int PrintCommands(){
    std::cout << "\nThere are a handful of simple commands in this game, here's a list of them:\n";
    std::cout << "exit - Exits the game.\n";
    std::cout << "commands - Lists all valid commands.\n";
    std::cout << "swing - A basic mid-damage swing attack.\n";
    std::cout << "jab - A basic mid-damage jab attack.\n";
    std::cout << "parry - A move that can block swinging blades by moving your sword perpendicular to them.\n";
    std::cout << "deflect - A move that deflects thrusting swords by pushing them aside quickly with your blade.\n";
    std::cout << "meditate - You don't attack or block any attacks, but you restore a small bit of health.\n";
    
    return 0;
};
int main(){
    srand(time(0));
    std::cout << "Sword Battle v1 -- A simple C++ console program written by Alan O, AKA Masteralan (@MasterAlan2001 on Twitter).\n";
    PrintCommands();
    
    int plr1HP = 100;
    int plr2HP = 100;
    
    std::string plr1Move;
    std::string plr2Move;
    
    do {
        std::cout << "\n~---=== Sword Battle ===---~\n";
        std::cout << "You have " << plr1HP << " HP left.\n";
        std::cout << "Your opponent has " << plr2HP << " HP left.\n";
        
        int p2 = RandomNumber(1,4);
        switch (p2) {
            case 2:
                plr2Move = "jab";
                break;
            case 3:
                plr2Move = "parry";
                break;
            case 4:
                plr2Move = "deflect";
                break;
            default:
                plr2Move = "swing";
        };
        if (RandomNumber(1,3) == 2) {
            std::cout << "Your opponent seems to be preparing to " << plr2Move << "...\n";
        };
        
        std::cout << "What action will you take?" << "\n";
        do {
            getline(std::cin, plr1Move);
            if (plr1Move == "commands")
                PrintCommands();
        } while (plr1Move == "commands");//(plr1Move != "parry" && plr1Move != "deflect" && plr1Move != "swing" && plr1Move != "jab" && plr1Move != "exit");
        
        std::cout << "\n";
        if (RandomNumber(1,3) == 2) {
            std::cout << "The enemy appears to forsee your action.\n";
            if (plr1Move == "parry" || plr1Move == "deflect"){
                if (plr2HP <= 50) {
                    plr2Move = "meditate";
                } else {
                    if (plr1Move == "parry")
                        plr2Move = "jab";
                    else if (plr1Move == "deflect")
                        plr2Move = "swing";
                };
            } else if (plr1Move == "swing") {
                plr2Move = "parry";
            } else if (plr1Move == "jab") {
                plr2Move = "deflect";
            } else if (plr1Move == "meditate"){
                if (RandomNumber(1,2) == 2)
                    plr2Move = "meditate";
                else
                    plr2Move = "swing";
            };
        };
        
        bool doP1 = true;
        bool doP2 = true;
        
        if (plr1Move == "exit"){
            continue;
        } else if (plr1Move == "parry" && plr2Move == "swing"){
            std::cout << "You parry the enemies sword mid-swing.\n";
            doP2 = false;
        } else if (plr1Move == "deflect" && plr2Move == "jab"){
            std::cout << "You deftly knock their blade out of the way right before it hits you.\n";
            doP2 = false;
        } else if (plr1Move == "swing" && plr2Move == "parry"){
            std::cout << "You attempt to dice them with your blade, but are parried.\n";
            doP1 = false;
        } else if (plr1Move == "jab" && plr2Move == "deflect"){
            std::cout << "You attempt to run them through with your sword, but are quickly deflected.\n";
            doP1 = false;
        } else if ((plr1Move == "parry" || plr1Move == "deflect") && (plr2Move == "parry" || plr2Move == "deflect")){
            std::cout << "You both try to counter each other's attacks, resulting in a clash of steel that isn't going anywhere.";
            doP1 = false;
            doP2 = false;
        } else if (plr1Move != "parry" && plr1Move != "deflect" && plr1Move != "swing" && plr1Move != "jab" && plr1Move != "exit" && plr1Move != "meditate"){
            std::cout << "You stumble and fail to make a move.\n";
            doP1 = false;
            if (plr2Move == "parry" || plr2Move == "deflect"){
                std::cout << "The enemy mistook your movement for an attack, and tried to " << plr2Move << " it.\n";
                doP2 = false;
            };
        };
        
        if (doP1 == true){
            if ((plr1Move == "swing" && plr2Move == "deflect") || (plr1Move == "jab" && plr2Move == "parry")){
                std::cout << "You " << plr1Move << " your blade while they move in error, incorrectly predicting your movements. That looked like it really hurt.\n";
                int dmg = RandomNumber(20,30);
                plr2HP-=dmg;
                std::cout << "You dealt " << dmg << " damage.\n";
            } else if (plr1Move == "swing" || plr1Move == "jab"){
                std::cout << "You " << plr1Move << " with your blade, landing the attack.\n";
                int dmg = RandomNumber(8,16);
                plr2HP-=dmg;
                std::cout << "You dealt " << dmg << " damage.\n";
            } else if (plr1Move == "meditate"){
                std::cout << "You decide calm your mind for a short moment.\n";
                if (plr2Move == "parry" || plr2Move == "deflect"){
                    std::cout << "Your opponent seems confused, and nervously prepares to defend themself.\n";
                };
                int dmg = RandomNumber(7,10);
                plr1HP+=dmg;
                std::cout << "You restored " << dmg << " health.\n";
            };
        };
        if (doP2 == true){
            if ((plr2Move == "swing" && plr1Move == "deflect") || (plr2Move == "jab" && plr1Move == "parry")){
                std::cout << "You attempted to counter your opponents attack, but predicted wrong, their " << plr2Move << " landing with a little extra sting.\n";
                int dmg = RandomNumber(20,30);
                std::cout << "You took " << dmg << " damage.\n";
                plr1HP-=dmg;
            } else if (plr2Move == "swing" || plr2Move == "jab"){
                std::cout << "They " << plr2Move << " their blade, catching you in the movement.\n";
                int dmg = RandomNumber(8,16);
                std::cout << "You took " << dmg << " damage.\n";
                plr1HP-=dmg;
            } else if (plr2Move == "meditate"){
                std::cout << "The enemy pauses for a moment and takes a deep breath.\n";
                if (plr1Move == "parry" || plr1Move == "deflect"){
                    std::cout << "You are confused by this action, and prepare for the worst.\n";
                };
                int dmg = RandomNumber(7,10);
                plr2HP+=dmg;
                std::cout << "The enemy restored " << dmg << " health.\n";
            };
        };
        
        std::cout << "\n";
        if (plr1HP <= 0){
            std::cout << "\nYou were slain by your opponent. Hit enter to close the program.\n";
            getline(std::cin, plr1Move);
            plr1Move = "exit";
            break;
        } else if (plr2HP <= 0){
            std::cout << "\nYou finished off your oppponent. Hit enter to close the program.\n";
            getline(std::cin, plr1Move);
            plr1Move = "exit";
            break;
        };
        
    } while (plr1Move != "exit");
    
    return 0;
}
