#pragma once
#include "includes.hpp"

class Texte {
public:
    Font font;
    string texte;
    int tailleChar;
    int R;
    int G;
    int B;
    float X;
    float Y;
    

    Texte(String b, int c, int d, int e, int f, float g, float h) : texte(b), tailleChar(c), R(d), G(e), B(f), X(g), Y(h) {}

    Text creation() {
        Text text;
        if (!font.loadFromFile("assets/Minecraft.ttf")) { cout << "error font"; }
        text.setFont(font);
        text.setString(texte);
        text.setCharacterSize(tailleChar);
        text.setFillColor(Color(R,G,B));
        text.setPosition(X, Y);
        return text;
    }

};