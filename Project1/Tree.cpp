#include "Tree.hpp"

Tree::Tree(RenderWindow& _window) : window(_window)
{
	
	InitBlackBoard();

    InitTexte(window);
    InitRectangle(window);

    InitTree(window);

    bool bill = false;
}



void Tree::InitTree(RenderWindow& window)
{
   root = make_unique<SelectorNode>();

   choix1 = make_unique<SelectorNode>();

   choix2 = make_unique<SelectorNode>();



   bulle1 = make_unique<SequenceNode>();

   bulle2 = make_unique<SequenceNode>();

   bulle3 = make_unique<SequenceNode>();

   choixUnUn = make_unique<SequenceNode>();

   choixUnDeux = make_unique<SequenceNode>();

   choixDeuxUn = make_unique<SequenceNode>();

   choixDeuxDeux = make_unique<SequenceNode>();

   choixTroisUn = make_unique<SequenceNode>();

   choixTroisDeux = make_unique<SequenceNode>();

    /***************************************************************************/
    bulle1->AddChild(make_unique<ConditionNode>(blackboard, "bulle1", 1));
    bulle1->AddChild(make_unique<ActionBulle>(window, listeTexteBulle1, listeRectangle));



    /**************************************************************************/
    choixUnUn->AddChild(make_unique<ConditionNode>(blackboard, "choix1-1", 1));

    bulle2->AddChild(make_unique<ConditionNode>(blackboard, "bulle2", 1));
    bulle2->AddChild(make_unique<ActionBulle>(window, listeTexteBulle2, listeRectangle));

    choixDeuxUn->AddChild(make_unique<ConditionNode>(blackboard, "choix2-1", 1));
    choixDeuxUn->AddChild(make_unique<ActionBulle>(window, listeTexteChoix21, listeRectangle));

    choixDeuxDeux->AddChild(make_unique<ConditionNode>(blackboard, "choix2-2", 1));
    choixDeuxDeux->AddChild(make_unique<ActionBulle>(window, listeTexteChoix22, listeRectangle));

    /******************************************************************************/

    choixUnDeux->AddChild(make_unique<ConditionNode>(blackboard, "choix1-2", 1));

    bulle3->AddChild(make_unique<ConditionNode>(blackboard, "bulle3", 1));
    bulle3->AddChild(make_unique<ActionBulle>(window, listeTexteBulle3, listeRectangle));

    choixTroisUn->AddChild(make_unique<ConditionNode>(blackboard, "choix3-1", 1));
    choixTroisUn->AddChild(make_unique<ActionBulle>(window, listeTexteChoix31, listeRectangle));

    choixTroisDeux->AddChild(make_unique<ConditionNode>(blackboard, "choix3-2", 1));
    choixTroisDeux->AddChild(make_unique<ActionBulle>(window, listeTexteChoix32, listeRectangle));




    root->AddChild(move(bulle1));
    choix1->AddChild(move(bulle2));
    choix1->AddChild(move(choixDeuxUn));
    choix1->AddChild(move(choixDeuxDeux));
    choix2->AddChild(move(bulle3));
    choix2->AddChild(move(choixTroisUn));
    choix2->AddChild(move(choixTroisDeux));



    choixUnUn->AddChild(move(choix1));
    choixUnDeux->AddChild(move(choix2));

    root->AddChild(move(choixUnUn));
    root->AddChild(move(choixUnDeux));


}






void Tree::InitBlackBoard()
{
    blackboard.SetValue("bulle1", 1);
    blackboard.SetValue("bulle2", 0);
    blackboard.SetValue("bulle3", 0);
    blackboard.SetValue("choix1-1", 0);
    blackboard.SetValue("choix1-2", 0);
    blackboard.SetValue("choix2-1", 0);
    blackboard.SetValue("choix2-2", 0);
    blackboard.SetValue("choix3-1", 0);
    blackboard.SetValue("choix3-2", 0);
}



void Tree::InitTexte(RenderWindow& window) {

    Texte Bulle1("Bonjour je m'appelle Isabelle ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2+40); //texte(b), tailleChar(c), R(d), G(e), B(f), X(g), Y(h) {}
    listeTexteBulle1.push_back(Bulle1);

    Texte choix1Bulle1("Bonjour Isabelle ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y - 130);
    listeTexteBulle1.push_back(choix1Bulle1);

    Texte choix2Bulle1("Vous dites ? ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y - 80);
    listeTexteBulle1.push_back(choix2Bulle1);

    /**********************************************************************************************************/

    Texte Bulle2("Faite attention ya Acquebouille qui rode  ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2 +40); 
    listeTexteBulle2.push_back(Bulle2);

    Texte choix1Bulle2("Je vais aller le battre ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y - 130);
    listeTexteBulle2.push_back(choix1Bulle2);

    Texte choix2Bulle2("Merci, je vais faire attention ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y - 80);
    listeTexteBulle2.push_back(choix2Bulle2);

    /*********************************************************************************************************/

    Texte Bulle3("Que le bonheur est irreductible : ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2+40); 
    listeTexteBulle3.push_back(Bulle3);

    Texte choix1Bulle3("'regarder les yeux d'isabelle' ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y - 130);
    listeTexteBulle3.push_back(choix1Bulle3);

    Texte choix2Bulle3("Et je dis ? ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y - 80);
    listeTexteBulle3.push_back(choix2Bulle3);

    /******************************************************************************************************************************************************************************************/

    Texte choix21("Quelle heros  ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2+40); 
    listeTexteChoix21.push_back(choix21);

    Texte choix22("Il est vraiment dangereux attention  ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2+40); 
    listeTexteChoix22.push_back(choix22);

    Texte choix31("Isabelle a les yeux bleu  ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2+40); 
    listeTexteChoix31.push_back(choix31);

    Texte choix32("Que ton espoir n'est pas si desespere,\nA condition d'analyser,\nQue l'absolu ne doit pas etre annihile\nPar l'illusoire precarite\nDe nos amours\nDestituees\nEt vice et versa  ", 25, 0, 0, 0, window.getSize().x - 720, window.getSize().y / 2+40); 
    listeTexteChoix32.push_back(choix32);
    
}

void Tree::InitRectangle(RenderWindow& window) {

    Rectangle Rec(660, 220, window.getSize().x-725, window.getSize().y /2 +40, 169, 169, 169,150); //  tailleX, tailleY, posX, posY, R, G, B
    listeRectangle.push_back(Rec);


    Rectangle button1(660, 40, window.getSize().x - 725, window.getSize().y - 130, 169, 169, 169,0); //  tailleX, tailleY, posX, posY, R, G, B
    listeRectangle.push_back(button1);

    Rectangle button2(660, 40, window.getSize().x - 725, window.getSize().y - 80, 169, 169, 169,0); //  tailleX, tailleY, posX, posY, R, G, B
    listeRectangle.push_back(button2);

    bouton1.setSize(Vector2f(660, 40)); //bouton clickable
    bouton1.setPosition(window.getSize().x - 725, window.getSize().y - 130);
   bouton1.setFillColor(Color(169, 169, 169, 150));

    bouton2.setSize(Vector2f(660, 40)); //bouton clickable
    bouton2.setPosition(window.getSize().x - 725, window.getSize().y - 80);
    bouton2.setFillColor(Color(169, 169, 169, 150));




}