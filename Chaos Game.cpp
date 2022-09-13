#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Instantiate rectangle shape to be drawn as a point.
RectangleShape Point(float x, float y)
{
    RectangleShape rectangle;

    rectangle.setSize(Vector2f(3, 3));
    rectangle.setPosition(x, y);

    return rectangle;
}

// Pick random vertex.
Vector2f RandomVertexPosition(vector<RectangleShape> vertices)
{
    int size = vertices.size();
    int randomIndex = 0 + rand() % 3;

    return vertices[randomIndex].getPosition();
}

enum ShapeType
{
    TRIANGLE,
    PENTAGON,
    SQUARE
};

int main()
{
    srand(time(NULL));

    Clock clock;

    // Defines the rate of drawing in seconds. Decreasing this value will make the drawing process
    // slower a little bit. But you will see many points drawn in realtime.
    float drawingRate = 0.5;
    float nextTimeToDraw = 0;
    double elapsedTime = 0;

    // Keeps track of total number of drawn points.
    int pointsCount = 0;

    int screenRes_X = 1920;
    int screenRes_Y = 1080;

    RenderWindow window(VideoMode(screenRes_X, screenRes_Y), "Chaos Game", Style::Default);

    // Let's assume that the user selected this shape.
    // We'll probably need to write a function to let the user select the prefered shape type.
    ShapeType shapeType = ShapeType::TRIANGLE;

    vector<RectangleShape> shapeVertices;
    vector<RectangleShape> pointsToDraw;

    RectangleShape starterPoint;
    RectangleShape midwayPoint;
    RectangleShape previousPoint;

    bool isLeftMouseButtonPressed = false;

    while (window.isOpen())
    {
        // Closes the game window if the user pressed the Escape button.
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        Time deltaTime = clock.restart();

        Vector2i mousePosition;

        Event event;

        // Checks if ther user pressed left mouse button.
        isLeftMouseButtonPressed = false;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    isLeftMouseButtonPressed = true;
                }
            }
        }

        /************* The main algorithm to draw Sirpenski triangle. *************/
        if (shapeType == ShapeType::TRIANGLE)
        {
            if (shapeVertices.size() < 3)
            {
                if (isLeftMouseButtonPressed)
                {
                    mousePosition = Mouse::getPosition(window);
                    shapeVertices.push_back(Point(mousePosition.x, mousePosition.y));
                }
            }
            else
            {
                if (starterPoint.getPosition() == Vector2f(NULL,NULL))
                {
                    if (isLeftMouseButtonPressed)
                    {
                        mousePosition = Mouse::getPosition(window);
                        starterPoint = Point(mousePosition.x, mousePosition.y);
                        previousPoint = starterPoint;
                    }
                }
                else
                {
                    Vector2f randomVertex = RandomVertexPosition(shapeVertices);

                    Vector2f midwayPointPosition = Vector2f((randomVertex.x + previousPoint.getPosition().x) / 2.0
                        , (randomVertex.y + previousPoint.getPosition().y) / 2.0);

                    midwayPoint = Point(midwayPointPosition.x, midwayPointPosition.y);

                    previousPoint = midwayPoint;

                    pointsToDraw.push_back(previousPoint);
                }
            }
        }

        /*********** We'll probably need another algorithm for a pentagon shape fractal **************/

        /*********** We'll probably need another algorithm for a square shape fractal ***************/

        /**************** Clear and Draw all points ********************/

        // Draw all shape vertices.
        if (starterPoint.getPosition() == Vector2f(NULL, NULL))
        {
            window.clear();
            for (RectangleShape vertex : shapeVertices)
            {
                window.draw(vertex);
            }
            window.display();
        }

        // Draw the generated points inside the shape to form the fractal.
        // Drawing a couple of thousands of points every specific amount of time will make the 
        // drawing process more optimized.
        elapsedTime += 1 * deltaTime.asSeconds();
        if (elapsedTime >= nextTimeToDraw)
        {
            nextTimeToDraw = drawingRate + elapsedTime;

            window.clear();

            for (RectangleShape vertex : shapeVertices)
            {
                window.draw(vertex);
            }

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