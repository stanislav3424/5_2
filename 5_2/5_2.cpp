#include <iostream>

struct NameInt
{
    std::string name;
    int value;
};

class Base
{
  protected:
    std::string nameFigure{"figure"};
    int numberOfSides{0};
    NameInt* angles = nullptr;
    NameInt* sides = nullptr;

  public:
    Base(std::string nameFigure, NameInt* angles, NameInt* sides) : nameFigure{nameFigure}, angles{angles}, sides{sides}
    {
    }

    std::string getName()
    {
        return nameFigure;
    }

    int getNumberOfSides()
    {
        return numberOfSides;
    }

    const NameInt* getAngles()
    {
        return angles;
    }

    const NameInt* getSides()
    {
        return sides;
    }

    virtual bool isValid() = 0;

    ~Base()
    {
        delete[] angles;
        delete[] sides;
    }
};

class TriangleBase : public Base
{
  public:
    TriangleBase(std::string nameFigure, NameInt* angles, NameInt* sides) : Base(nameFigure, angles, sides)
    {
        numberOfSides = 3;
    }

    bool isValid() override
    {
        return true;
    }
};

class QuadrangleBase : public Base
{
  public:
    QuadrangleBase(std::string nameFigure, NameInt* angles, NameInt* sides) : Base(nameFigure, angles, sides)
    {
        numberOfSides = 4;
    }

    bool isValid() override
    {
        return true;
    }
};

class RightAngledTriangle : public TriangleBase
{
  public:
    RightAngledTriangle(NameInt* angles, NameInt* sides) : TriangleBase("Right-Angled Triangle", angles, sides)
    {
    }

    bool isValid() override
    {

        return (sides[0].value == 90 || sides[1].value == 90 || sides[2].value == 90);
    }
};

class IsoscelesTriangle : public TriangleBase
{
  public:
    IsoscelesTriangle(NameInt* angles, NameInt* sides) : TriangleBase("Isosceles Triangle", angles, sides)
    {
    }

    bool isValid() override
    {
        bool any2SidesAreEqual =
            sides[0].value == sides[2].value || sides[1].value == sides[2].value || sides[0].value == sides[1].value;

        return any2SidesAreEqual;
    }
};

class EquilateralTriangle : public TriangleBase
{
  public:
    EquilateralTriangle(NameInt* angles, NameInt* sides) : TriangleBase("Equilateral Triangle", angles, sides)
    {
    }

    bool isValid() override
    {
        bool allSidesAreEqual =
            sides[0].value == sides[2].value && sides[1].value == sides[2].value && sides[0].value == sides[1].value;
        return allSidesAreEqual;
    }
};

class Rectangle : public QuadrangleBase
{
  public:
    Rectangle(NameInt* angles, NameInt* sides) : QuadrangleBase("Rectangle", angles, sides)
    {
    }

    bool isValid() override
    {
        return (angles[0].value == 90 && angles[1].value == 90);
    }
};

class Square : public QuadrangleBase
{
  public:
    Square(NameInt* angles, NameInt* sides) : QuadrangleBase("Square", angles, sides)
    {
    }

    bool isValid() override
    {
        bool isRectangle = angles[0].value == 90 && angles[1].value == 90;
        bool theSidesAreEqual = sides[0].value == sides[1].value && sides[0].value == sides[2].value;

        return (isRectangle && theSidesAreEqual);
    }
};

class Parallelogram : public QuadrangleBase
{
  public:
    Parallelogram(NameInt* angles, NameInt* sides) : QuadrangleBase("Parallelogram", angles, sides)
    {
    }

    bool isValid() override
    {
        return (sides[0].value == sides[2].value && sides[1].value == sides[3].value);
    }
};

class Rhombus : public QuadrangleBase
{
  public:
    Rhombus(NameInt* angles, NameInt* sides) : QuadrangleBase("Rhombus", angles, sides)
    {
    }

    bool isValid() override
    {
        return (sides[0].value == sides[1].value && sides[0].value == sides[2].value);
    }
};

void getData(Base* figures[], int& size)
{
    for (int indexFigures = 0; indexFigures < size; ++indexFigures)
    {
        std::cout << figures[indexFigures]->getName() << ":" << std::endl;

        std::cout << "Sides: ";
        for (int index = 0; index < figures[indexFigures]->getNumberOfSides(); ++index)
        {
            std::cout << figures[indexFigures]->getSides()[index].name;
            std::cout << "=";
            std::cout << figures[indexFigures]->getSides()[index].value;
            std::cout << " ";
        }

        std::cout << std::endl;

        std::cout << "Angles: ";
        for (int index = 0; index < figures[indexFigures]->getNumberOfSides(); ++index)
        {
            std::cout << figures[indexFigures]->getAngles()[index].name;
            std::cout << "=";
            std::cout << figures[indexFigures]->getAngles()[index].value;
            std::cout << " ";
        }

        std::cout << std::endl << std::endl;
    }
}

void destroy(Base* figures[], int& size)
{
    for (int index = 0; index < size; ++index)
    {
        delete figures[index];
    }
}

bool valid(Base* figures[], int& size)
{
    for (int index = 0; index < size; ++index)
    {
        if (figures[index]->isValid())
        {
        }
        else
        {
            std::cout << figures[index]->getName() << " is not valid." << std::endl;
            destroy(figures, size);

            return true;
        }
    }

    return false;
}

int main()
{
    Base* figures[] = {new TriangleBase("Triangle", new NameInt[3]{{"A", 50}, {"B", 60}, {"C", 70}},
                                        new NameInt[3]{{"a", 1}, {"b", 2}, {"c", 3}}),
                       new RightAngledTriangle(new NameInt[3]{{"A", 45}, {"B", 45}, {"C", 90}},
                                               new NameInt[3]{{"a", 3}, {"b", 4}, {"c", 5}}),
                       new IsoscelesTriangle(new NameInt[3]{{"A", 70}, {"B", 40}, {"C", 70}},
                                             new NameInt[3]{{"a", 5}, {"b", 6}, {"c", 5}}),
                       new EquilateralTriangle(new NameInt[3]{{"A", 60}, {"B", 60}, {"C", 60}},
                                               new NameInt[3]{{"a", 6}, {"b", 6}, {"c", 6}}),
                       new QuadrangleBase("Quadrangle", new NameInt[4]{{"A", 50}, {"B", 60}, {"C", 70}, {"D", 80}},
                                          new NameInt[4]{{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}}),
                       new Rectangle(new NameInt[4]{{"A", 90}, {"B", 90}, {"C", 90}, {"D", 90}},
                                     new NameInt[4]{{"a", 5}, {"b", 10}, {"c", 5}, {"d", 10}}),
                       new Square(new NameInt[4]{{"A", 90}, {"B", 90}, {"C", 90}, {"D", 90}},
                                  new NameInt[4]{{"a", 4}, {"b", 4}, {"c", 4}, {"d", 4}}),
                       new Parallelogram(new NameInt[4]{{"A", 60}, {"B", 120}, {"C", 60}, {"D", 120}},
                                         new NameInt[4]{{"a", 8}, {"b", 5}, {"c", 8}, {"d", 5}}),
                       new Rhombus(new NameInt[4]{{"A", 60}, {"B", 120}, {"C", 60}, {"D", 120}},
                                   new NameInt[4]{{"a", 6}, {"b", 6}, {"c", 6}, {"d", 6}})};

    int size = sizeof(figures) / sizeof(figures[0]);

    // test
    //
    // sides2[0].name = {""};
    // angles2[0].value = 0;

    if (valid(figures, size))
    {
        return 1;
    }

    getData(figures, size);

    destroy(figures, size);

    return 0;
}
