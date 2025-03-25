//#include "includes.hpp"
#pragma once
#include "BTNode.hpp"
#include "Texte.hpp"
#include "Rectangle.hpp"
#include "BlackBoard.hpp"
#include  <SFML/Graphics.hpp>


class ActionBulle : public BTNode {
private:
    vector<Texte>& listeTexte;
    vector<Rectangle>& listeRectangle;
    RenderWindow& windows;
public:

    ActionBulle(RenderWindow& window, vector<Texte>& Texte, vector<Rectangle>& Rectangle) : windows(window),listeTexte(Texte), listeRectangle(Rectangle){};

    NodeState execute() override {

        
        for (auto Rectangle : listeRectangle) {
            windows.draw(Rectangle.creation());
           
        }
        for (auto Texte : listeTexte) {
            windows.draw(Texte.creation());

        }
        
       
        return NodeState::SUCCESS;
    }
};