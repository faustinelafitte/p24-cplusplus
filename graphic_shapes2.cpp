#include <iostream>
#include <cmath>
#include <vector>

// définition de vos classes ici
class Shape
{
protected:
    double x;
    double y;

public:
    Shape(double x, double y) : x(x), y(y) {}

    void move(double dx, double dy)
    {
        x = x + dx;
        y = y + dy;
    }

    double area(){
        return(99);
    }
};

class Circle : public Shape
{
protected: 
    double radius;

public: 
    Circle(double x, double y, double radius) : Shape(x, y), radius(radius) {}

    double area() 
    {
        return 3.14 * radius * radius; 
    }

    bool is_at_position(double px, double py)
    {
        return (std::sqrt((px - x) * (px - x) + (py - y) * (py - y)) <= radius);
    }
};

// Classe Rectangle
class Rectangle : public Shape
{
protected: 
    double width;
    double height;

public:
    Rectangle(double x, double y, double width, double height) : Shape(x, y), width(width), height(height) {}

    double area()
    {
        return width * height;
    }

    bool is_at_position(double px, double py)
    {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }
};
// optionnel:
// faire une fonction prend en argument x, y et un vecteur de formes et retourne la forme au point (x, y)

// bool find_at_position(double x, double y, std::shared_ptr<*Shape> shapes)
// {
//     for (auto &shape : shapes)
//     {
//         if (shape->is_at_position(x, y))
//         {
//             return true;
//         }
//     }
//     return false;
// }
bool find_at_position(double x, double y, std::vector<Shape *> &shapes) {
    for (Shape *shape : shapes)
    {
        // if (shape->is_at_position(x, y)) // vr: il faut définir la fonction
        if (true)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    Circle c{10, 20, 4.5};       // x, y, radius
    Rectangle r{20, 30, 30, 60}; // x, y, width, height
    std::vector<Shape *> shapes;
    shapes.push_back(&c);
    shapes.push_back(&r);

    // première version (sans find_at_position et is_at_position)
    shapes[0]->move(4, 6);
    shapes[1]->move(2, 8);
    // vr: comme dans le vector nous sommes obligés (parce que c++ est fortement typé) d'utiliser le type commun à tous les objets graphique
    //             (ce type est: adresse d'un objet de type Shape)
    // la méthode area doit être définie dans la classe Shape
    // bien sûr elle n'a aucun sens sur un objet de type Shape dans notre cas: renvoyez n'importe quelle valeur (-99) - nous verrons comment faire
    // std::cout << shapes[0]->area() << std::endl; // affiche dans les 63.6173
    // std::cout << shapes[1]->area() << std::endl; // 1800

    // deuxième version (avec find_at_position et is_at_position)
    //auto shape1 = find_at_position(10, 20, shapes);
    // appeler la méthode move et area sur shape1
    //auto shape2 = find_at_position(100, 200, shapes);
    // pouvez vous appeler la méthode move et area sur shape2 ?
    return 0;
}