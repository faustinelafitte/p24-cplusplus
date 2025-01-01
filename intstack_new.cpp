#include <iostream>
#include <stdexcept>

// constante entière pour la taille de la pile

// on définit un type de donnée (une classe) pour gérer une pile d'entier de taille 12 (SIZE)
class IntStack
{
private:
    int top;
    int size;
    int *ti;

public:
    IntStack(int s) : top(0), size(s)
    {
        if (size < 0)
        {
            exit(0);
        }
        else
        {
            ti = new int[size];
        }
    }
    ~IntStack()
    {
        delete[] ti;
    } // destructeur

    void push(int e)
    {
        if (is_full() == false)
        {
            ti[top] = e; // car *ti donne l'adresse de la première case donc *(ti+top) l'adresse de la case ti+top ie la dernière remplie
            top++;
        }
        else
        {
            exit(5);
        }
    }
    int get_top()
    {
        if (is_empty() == false)
        {
            return ti[top];
        }
        else
        {
            exit(6);
        }
    }
    int pop()
    {
        if (is_empty() == false)
        {
            get_top();
            top--;
            return ti[top];
        }
        else
        {
            exit(7);
        }
    }
    bool is_empty()
    {
        return top == 0;
        // cette fonction teste si la pile est vide
        // votre code ici
    }
    bool is_full()
    {
        return top == size;
        // cette fonction teste si la pile est pleine
        // il y a SIZE entiers dans la pile
        // votre code ici
    }
    void print()
    {
        std::cout << '[';
        for (int i = 0; i < top; i++)
        {
            std::cout << ti[i] << " ";
        }
        std::cout << "]" << std::endl;
    }

    IntStack &operator=(IntStack &stack)
    {

        delete[] ti;
        size = stack.size;
        top = stack.top;

        ti = new int[size];

        // Copier les éléments de la pile
        for (int i = 0; i < top; ++i)
        {
            ti[i] = stack.ti[i];
        }
        return *this;
    }
};

// 1. réaliser le code pour faire fonctionner cette pile d'entier de taille fixée à la compilation
// 2. quelles sont les méthodes qui ne modifient pas l'objet sur lequel elles sont appelées
//    faites en sorte qu'elles puissent être appelées sur un objet constant
// 3. faites la fonction qui permet d'afficher un objet de type IntStack directement avec <<<
//    std::cout << s1;
//    il faut redéfinir l'operator<< en appelant la méthode print

int main()
{
    IntStack s1{12};
    s1.print(); // affichera []
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.print();                         // affichera [1 2 3 ]
    std::cout << s1.pop() << std::endl; // affichera 3
    s1.print();                         // affichera [1 2 ]
    return 0;
}
