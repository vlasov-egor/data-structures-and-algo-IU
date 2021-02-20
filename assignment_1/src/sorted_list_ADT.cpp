#include <iostream>
#include <string>

using namespace std;

template <class T>
class Node
{
public:
    T data;
    Node<T> *next_node;
};
template <class T>
class SortedList
{
public:
    virtual void add(T item) = 0;
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual SortedList<T> *searchRange(T from, T to) = 0;
    virtual Node<T> *getHead() = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

template <class T>
class SinglyLinkedSortedList : SortedList<T>
{
private:
    int len = 0;
    Node<T> *head = NULL;
    Node<T> *tail = NULL;

public:
    void add(T item)
    {
        Node<T> *new_node = new Node<T>();
        new_node->data = item;
        Node<T> *current = head;

        if (!head)
        {
            head = new_node;
            tail = new_node;
        }
        else if (new_node->data <= head->data)
        {
            new_node->next_node = head;
            head = new_node;
        }
        else
        {
            while (current->next_node != NULL && current->next_node->data <= new_node->data)
            {
                current = current->next_node;
            }
            new_node->next_node = current->next_node;
            current->next_node = new_node;

            if (current == tail)
            {
                tail = new_node;
            }
        }

        len++;
    }

    void addLast(T item)
    {
        Node<T> *new_node = new Node<T>();
        new_node->data = item;

        if (!head)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next_node = new_node;
            tail = new_node;
        }
    }

    T least()
    {
        return head->data;
    }

    T greatest()
    {
        return tail->data;
    }

    T get(int i)
    {
        Node<T> *current = head;
        for (int j = 0; j <= i; j++)
        {
            current = current->next_node;
        }

        return current->data;
    }

    int indexOf(T item)
    {
        Node<T> *current = head;
        int index = 0;
        while (current->data != item)
        {
            current = current->next_node;
            index++;
        }

        return index;
    }

    void remove(int i)
    {
        Node<T> *current = head;
        Node<T> *prev = head;

        for (int j = 0; j <= i; ++j)
        {
            prev = current;
            current = current->next_node;
        }

        prev->next_node = current->next_node;
    }

    void removeItem(T item)
    {
        if (item == head->data)
        {
            head = head->next_node;
            // cout << "ЮХУ -3" << endl;
            return;
        }

        Node<T> *current = head;
        Node<T> *prev = head;
        while (current->data != item)
        {
            prev = current;
            current = current->next_node;
        }

        prev->next_node = current->next_node;
    }

    SortedList<T> *searchRange(T from, T to)
    {
        auto List = new SinglyLinkedSortedList<T>();

        Node<T> *current = head;

        for (; current->data < from; current = current->next_node)
            ;
        for (; current && current->data <= to; current = current->next_node)
        {
            List->addLast(current->data);
            // cout << current->data << endl;
        }

        return List;
    }

    Node<T> *getHead()
    {
        return head;
    }

    int size()
    {
        return len;
    }

    bool isEmpty()
    {
        return head ? true : false;
    }
};

class Item
{
public:
    string name;
    float price;

    bool operator==(const Item &rhs)
    {
        return (price == rhs.price) && (name == rhs.name);
    }
    bool operator!=(const Item &rhs)
    {
        return (price != rhs.price) || (name != rhs.name);
    }
    bool operator>=(const Item &rhs)
    {
        return price >= rhs.price;
    }
    bool operator<=(const Item &rhs)
    {
        return price <= rhs.price;
    }

    bool operator>(const Item &rhs)
    {
        return price > rhs.price;
    }

    bool operator<(const Item &rhs)
    {
        return price < rhs.price;
    }
};

int main(int argc, char const *argv[])
{

    auto items = new SinglyLinkedSortedList<Item>();
    int n;
    string line;

    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        getline(cin, line);
        int first_space = line.find(" ", 0);
        int second_space = line.find(" ", first_space + 1);
        string command = line.substr(0, first_space);

        // first_space + 1 - delete space
        // first_space + 2 - delete "$"

        string param1 = line.substr(first_space + 2, second_space - (first_space + 2));
        string param2 = (command == "LIST") ? line.substr(second_space + 2) : line.substr(second_space + 1);

        if (command == "ADD")
        {
            items->add(Item{
                param2,
                stof(param1)});
        }
        else if (command == "REMOVE")
        {
            items->removeItem(Item{
                param2,
                stof(param1)});
        }
        else
        {
            // cout << "FROM " << param1 << " " << param2 << endl;
            Item Item1{"", stof(param1)};
            Item Item2{"", stof(param2)};

            auto govno = items->searchRange(Item1, Item2);
            auto head = govno->getHead();

            Node<Item> *current = head;

            while (current)
            {
                float price = current->data.price;
                string name = current->data.name;

                printf("$%.2f", price);
                cout << " " << name;

                if (current->next_node) {
                    cout << ", ";
                }

                current = current->next_node;
            }

            cout << endl;
        }
    }
}
