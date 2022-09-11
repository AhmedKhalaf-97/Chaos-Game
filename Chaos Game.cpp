#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

RectangleShape Point(float x, float y)
{
    RectangleShape rectangle;

    rectangle.setSize(Vector2f(2, 2));
    rectangle.setPosition(x, y);

    return rectangle;
}

Vector2f RandomVertexPosition(RectangleShape threeVertices[3])
{
    int randomIndex = 0 + rand() % 3;

    return threeVertices[randomIndex].getPosition();
}

int main()
{
    srand(time(NULL));

    Clock clock;

    float drawingRate = 1;
    float nextTimeToDraw = 0;
    double elapsedTime = 0;

    int pointsCount = 0;

    RenderWindow window(VideoMode(1024, 768), "Chaos Game", Style::Default);
    
    RectangleShape topVertex = Point(400, 60);
    RectangleShape leftBottomVertex = Point(150, 540);
    RectangleShape rightBottomVertex = Point(650, 540);

    RectangleShape randomPoint = Point(450, 300);

    RectangleShape midwayPoint;
    RectangleShape previousPoint;

    RectangleShape triangleVertices[3] = {topVertex, leftBottomVertex, rightBottomVertex};

    previousPoint = randomPoint;

    vector<RectangleShape> pointsToDraw;

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        Vector2i position = Mouse::getPosition(window);

        Time deltaTime = clock.restart();

        Vector2f randomVertex = RandomVertexPosition(triangleVertices);

        Vector2f midwayPointPosition = Vector2f((randomVertex.x + previousPoint.getPosition().x) / 2.0
            , (randomVertex.y + previousPoint.getPosition().y) / 2.0);

        midwayPoint = Point(midwayPointPosition.x, midwayPointPosition.y);

        previousPoint = midwayPoint;

        pointsToDraw.push_back(previousPoint);

        window.clear();

        window.draw(topVertex);
        window.draw(leftBottomVertex);
        window.draw(rightBottomVertex);

        elapsedTime += 1 * deltaTime.asSeconds();
        if (elapsedTime >= nextTimeToDraw)
        {
            nextTimeToDraw = drawingRate + elapsedTime;


            for (int i = 0; i < pointsToDraw.size(); i++)
            {
                window.draw(pointsToDraw[i]);
                pointsCount++;
            }

            window.display();

            cout << "Number of points drawn: " << pointsCount << endl;
        }
    }


    return 0;
}