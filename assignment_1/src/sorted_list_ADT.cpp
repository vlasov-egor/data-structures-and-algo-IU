/**
 * @file cafe_accounting.cpp
 * @author Vlasov Egor (group-05)
 * @date 2021-02-20
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Node of linked list
 * 
 * @tparam T 
 */
template <class T>
class Node
{
public:
    T data;
    Node<T> *next_node;
};

/**
 * @brief interface of Sorted list
 * 
 * @tparam T 
 */
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

/**
 * @brief Linked list
 * 
 * @tparam T 
 */
template <class T>
class SinglyLinkedSortedList : SortedList<T>
{
private:
    int len = 0;
    Node<T> *head = NULL;
    Node<T> *tail = NULL;

public:
    /**
     * @brief adding element to list
     * 
     * @param item some element
     */
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

    /**
     * @brief adding element to the end
     * 
     * @param item some element
     */
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

    /**
     * @brief returns the smallest element
     * 
     * @return T smallest element
     */
    T least()
    {
        return head->data;
    }

    /**
     * @brief returns the greatest element
     * 
     * @return T greatest element
     */
    T greatest()
    {
        return tail->data;
    }

    /**
     * @brief getting element by index
     * 
     * @param i index
     * @return T element with index i
     */
    T get(int i)
    {
        Node<T> *current = head;
        for (int j = 0; j <= i; j++)
        {
            current = current->next_node;
        }

        return current->data;
    }

    /**
     * @brief returns index of item
     * 
     * @param item element
     * @return int index
     */
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

    /**
     * @brief removing of element by index
     * 
     * @param i index
     */
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

    /**
     * @brief remove element which is equal to item
     * 
     * @param item some element
     */
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

    /**
     * @brief search range in list from <from> to <to>
     * 
     * @param from lower bound
     * @param to upper bound
     * @return SortedList<T>* neww list with that range
     */
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

    /**
     * @brief Get the Head object
     * 
     * @return Node<T>* head element
     */
    Node<T> *getHead()
    {
        return head;
    }

    /**
     * @brief returns size of list
     * 
     * @return int size
     */
    int size()
    {
        return len;
    }

    /**
     * @brief checking emptiness of list
     * 
     * @return true if empty
     * @return false if not
     */
    bool isEmpty()
    {
        return head ? true : false;
    }
};

/**
 * @brief class for items
 * 
 */
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

    //  init
    auto items = new SinglyLinkedSortedList<Item>();
    int n;
    string line;

    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        // parsing
        getline(cin, line);
        int first_space = line.find(" ", 0);
        int second_space = line.find(" ", first_space + 1);
        string command = line.substr(0, first_space);

        // first_space + 1 - delete space
        // first_space + 2 - delete "$"

        string param1 = line.substr(first_space + 2, second_space - (first_space + 2));
        string param2 = (command == "LIST") ? line.substr(second_space + 2) : line.substr(second_space + 1);

        // command add
        if (command == "ADD")
        {
            items->add(Item{
                param2,
                stof(param1)});
        }
        // command remove
        else if (command == "REMOVE")
        {
            items->removeItem(Item{
                param2,
                stof(param1)});
        }
        // command list
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

                if (current->next_node)
                {
                    cout << ", ";
                }

                current = current->next_node;
            }

            cout << endl;
        }
    }
}
