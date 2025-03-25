#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Tree.hpp"



const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA GOAP");
    window.setFramerateLimit(60);

    Player player(400, 400, 100);
    vector<Entity*> enemies;


    RectangleShape pnj(Vector2f(40, 40)); 
    pnj.setPosition(100, 100);
    pnj.setFillColor(Color(0,255,0));

    RectangleShape yeux1(Vector2f(5, 5));
    yeux1.setPosition(110, 110);
    yeux1.setFillColor(Color(0, 0, 255));

    RectangleShape yeux2(Vector2f(5, 5));
    yeux2.setPosition(130, 110);
    yeux2.setFillColor(Color(0, 0, 255));





	enemies.push_back(new Enemy(700, 450, 50));


    Grid grid;
    grid.loadFromFile("map.txt");

    Clock clock;

    Tree tree(window);

    float distance = 0;
    

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();



        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::E)) {    
                distance = sqrt(player.shape.getPosition().x * pnj.getPosition().x + player.shape.getPosition().y * pnj.getPosition().y);

                if (distance < 180 && tree.bill == false) {
                    tree.InitBlackBoard();
                    tree.bill = true;
                    
                }                           
            } 
            if (Mouse::isButtonPressed(Mouse::Right)) {
                Vector2i mousePos = Mouse::getPosition(window);

                if (tree.bouton1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && tree.blackboard.GetValue("bulle1") == 1) {
                    tree.blackboard.SetValue("bulle1", 0);
                    tree.blackboard.SetValue("choix1-1", 1);
                    tree.blackboard.SetValue("bulle2", 1);
                    
                }
                else if (tree.bouton2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && tree.blackboard.GetValue("bulle1") == 1) {
                    tree.blackboard.SetValue("bulle1", 0);
                    tree.blackboard.SetValue("choix1-2", 1);
                    tree.blackboard.SetValue("bulle3", 1);

                }
                else if (tree.bouton1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && tree.blackboard.GetValue("bulle2") == 1) {
                    tree.blackboard.SetValue("bulle2", 0);
                    tree.blackboard.SetValue("choix2-1", 1);                    
                }
                else if (tree.bouton2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && tree.blackboard.GetValue("bulle2") == 1) {
                    tree.blackboard.SetValue("bulle2", 0);
                    tree.blackboard.SetValue("choix2-2", 1);
                }
                else if (tree.bouton1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && tree.blackboard.GetValue("bulle3") == 1) {
                    tree.blackboard.SetValue("bulle3", 0);
                    tree.blackboard.SetValue("choix3-1", 1);
                }
                else if (tree.bouton2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && tree.blackboard.GetValue("bulle3") == 1) {
                    tree.blackboard.SetValue("bulle3", 0);
                    tree.blackboard.SetValue("choix3-2", 1);
                }

            }
        }


        player.update(deltaTime, grid, enemies);
        for (auto& enemy : enemies) {
            enemy->update(deltaTime, grid, { &player });
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->shape);
            }
        }

        window.draw(pnj);
        window.draw(yeux1);
        window.draw(yeux2);

        if (tree.bill) {
            distance = sqrt(player.shape.getPosition().x * pnj.getPosition().x + player.shape.getPosition().y * pnj.getPosition().y);
            if (distance > 180) {
                tree.bill = false;
                tree.InitBlackBoard();
            }
            else
            tree.root->execute();
        }

        window.display();
    }

    for (auto& enemy : enemies) {
        delete enemy;
    }

    return 0;
}