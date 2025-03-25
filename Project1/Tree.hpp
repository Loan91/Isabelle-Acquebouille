#pragma once
#include "ActionBulle.hpp"
#include "BlackBoard.hpp"
#include "ConditionNode.hpp"
#include "SelectorNode.hpp"
#include "SequenceNode.hpp"
#include "Rectangle.hpp"
#include "Texte.hpp"


class Tree
{
public:

    RenderWindow& window;

	Blackboard blackboard;

    unique_ptr<SelectorNode> root; 
    unique_ptr<SelectorNode> choix1;
    unique_ptr<SelectorNode> choix2;

    unique_ptr<SequenceNode> bulle1;
    unique_ptr<SequenceNode> bulle2;
    unique_ptr<SequenceNode> bulle3;

    unique_ptr<SequenceNode> choixUnUn;
    unique_ptr<SequenceNode> choixUnDeux;

    unique_ptr<SequenceNode> choixDeuxUn;
    unique_ptr<SequenceNode> choixDeuxDeux;

    unique_ptr<SequenceNode> choixTroisUn;
    unique_ptr<SequenceNode> choixTroisDeux;

    bool bill = false;
   
    vector<Texte> listeTexteBulle1;
    vector<Texte> listeTexteBulle2;
    vector<Texte> listeTexteBulle3;

    vector<Texte> listeTexteChoix21;
    vector<Texte> listeTexteChoix22;
    vector<Texte> listeTexteChoix31;
    vector<Texte> listeTexteChoix32;

    vector<Rectangle> listeRectangle;
    /*********************************************************************/

	Tree(RenderWindow& window);

    RectangleShape bouton1;
    RectangleShape bouton2;

	void InitTree(RenderWindow& window);

	void InitBlackBoard();
    void InitTexte(RenderWindow& window);
    void InitRectangle(RenderWindow& window);
};

