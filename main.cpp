#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Axis.h"
#include "MouseWrapper.h"
#include "Function.h"
#include "SinIntegral.h"
#include "ExpIntegral.h"

using namespace sf;
enum {Func1, Both, Func2};

int main()
{
    // Welcome message
    std::cout << "==============================" << std::endl;
    std::cout << "Olivier CHENG & Nicolas KELLER" << std::endl;
    std::cout << "==============================" << std::endl << std::endl;
    std::cout << "[S] Enregistrer le graphique" << std::endl;
    std::cout << "[C] Choisir les courbes a afficher" << std::endl;
    std::cout << "[T] Afficher les tangentes en un point" << std::endl;
    std::cout << "[R] Reinitialiser le graphique" << std::endl;
    std::cout << "[Sourris gauche] Deplacer le graphique" << std::endl;
    std::cout << "[Sourris droite] Zoomer" << std::endl << std::endl;

    // Var declaration
    RenderWindow app(VideoMode(800, 600, 32), "DM de Maths | Olivier CHENG & Nicolas KELLER", Style::Close | Style::Titlebar | Style::Resize, WindowSettings(24, 8, 2));
    MouseWrapper mouse;
    Axis axis(app, mouse);
    SinIntegral func1(axis, 0.01);
    ExpIntegral func2(axis, 0.01);
    bool takeScreenshot = false;
    bool drawTangent = false;
    char selection = Both;

    // Main loop
    while (app.IsOpened())
    {
        Event event;

        // Manage events
        while (app.GetEvent(event))
        {
            if (event.Type == Event::Closed)
                app.Close();

            if (event.Type == Event::KeyPressed)
            {
                if (event.Key.Code == Key::S)
                    takeScreenshot = true;

                if (event.Key.Code == Key::C)
                    selection = (selection+1)%3;

                if (event.Key.Code == Key::T)
                    drawTangent = !drawTangent;

                if (event.Key.Code == Key::R)
                    axis.reset();
            }

            mouse.bind(event);
        }

        app.Clear(Color(255, 255, 255));

        axis.update();
        axis.render();

        if(selection <= Both)
            func1.render(axis.getCursorPos().x, drawTangent);
        if(selection >= Both)
            func2.render(axis.getCursorPos().x, drawTangent);

        if(takeScreenshot)
        {
            takeScreenshot = false;

            // Save screenshot
            if(app.Capture().SaveToFile("graph.bmp"))
                std::cout << "Image enregistre dans graph.bmp" << std::endl;
        }

        app.Display();
    }

    // Goodbye message
    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Olivier CHENG & Nicolas KELLER" << std::endl;
    std::cout << "==============================" << std::endl;
    return EXIT_SUCCESS;
}
