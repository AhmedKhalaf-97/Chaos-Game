#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Center the origin of the text transform.
void CenterTextRectOrigin(Text& text)
{
    FloatRect rect = text.getLocalBounds();
    text.setOrigin(rect.left + rect.width / 2.0f,
        rect.top + rect.height / 2.0f);
}

int main()
{
    int screenRes_X = 1920;
    int screenRes_Y = 1080;
    // Change this value if you want to change the window resolution, to adjust all text sizes.
    // For example, for large resolution like 1920px1080p, change this ratio to 2. But for smaller ones
    // like 800px600p or 1024px768p, change the ratio to 1 to appear smaller.
    int sizeRatio = 2;

    RenderWindow window(VideoMode(screenRes_X, screenRes_Y), "Chaos Game", Style::Default);

    Cursor cursor;
    if (cursor.loadFromSystem(Cursor::Arrow))
    {
        window.setMouseCursor(cursor);
    }

    // Change this value whenever you want to make text transition more visible.
    float charSizeIncreaseRatio = 1.2;

    int gameTitleTextCharSize = 100 * sizeRatio;
    int startGameTextCharSize = 30 * sizeRatio;


    Font font;
    font.loadFromFile("Fonts/sf-atarian-system.regular.ttf");

    Text gameTitleText;
    Text startGameButtonText;

    gameTitleText.setFont(font);
    startGameButtonText.setFont(font);

    gameTitleText.setString("Chaos Game");
    startGameButtonText.setString(">> Start New Game <<");

    gameTitleText.setCharacterSize(gameTitleTextCharSize);
    startGameButtonText.setCharacterSize(startGameTextCharSize);

    gameTitleText.setPosition(screenRes_X / 2.0f, 100.0f * sizeRatio);
    startGameButtonText.setPosition(screenRes_X / 2.0f, 250.0f * sizeRatio);

    CenterTextRectOrigin(gameTitleText);
    CenterTextRectOrigin(startGameButtonText);




    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Get the mouse position.
        Vector2i position = Mouse::getPosition(window);

        // Detects if the mouse is hovering over it.
        if (startGameButtonText.getGlobalBounds().contains((Vector2f)position))
        {
            if (startGameButtonText.getCharacterSize() == startGameTextCharSize)
            {
                startGameButtonText.setCharacterSize(startGameTextCharSize * charSizeIncreaseRatio);
                CenterTextRectOrigin(startGameButtonText);
            }
        }
        else
        {
            if (startGameButtonText.getCharacterSize() != startGameTextCharSize)
            {
                startGameButtonText.setCharacterSize(startGameTextCharSize);
                CenterTextRectOrigin(startGameButtonText);
            }
        }

        window.clear();

        window.draw(startGameButtonText);
        window.draw(gameTitleText);

        window.display();
    }


    return 0;
}