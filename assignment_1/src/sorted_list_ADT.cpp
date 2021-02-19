/** 
 * TODO
 * implement List
 * implement SortedList 
 */

#include <stdio.h>

using namespace std;

template <class T>
class SortedList
{
public:
    virtual void add(T item);
    virtual T least();
    virtual T greatest();
    virtual T get(int i);
    virtual int indexOf(T item);
    virtual void remove(int i);
    virtual List<T> searchRange(T from, T to);
    virtual int size();
    virtual bool isEmpty();
};

template <class T>
struct Node
{
    T data;
    struct Node *next_node;
};

template <class T>
class SinglyLinkedSortedList : SortedList<T>
{
public:
    SinglyLinkedSortedList()
    {
        int len = 0;
        T *head = NULL;
        T *tail = NULL;
    }

    void add(T item)
    {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        T current = head;
        int counter = 0;

        if (!head)
        {
            head = new_node;
            counter = 0;
        }

        else if (new_node->data <= current->data)
        {
            new_node->next_node = head;
            head = new_node;
            counter = 0;
        }
        else
        {
            counter = 1;
            while (current->next_node != NULL && current->next_node->data <= new_node->data)
            {
                current = current->next_node;
                counter++;
            }
            new_node->next_node = current->next_node;
            current->next = new_node;
        }

        if (counter == this->size())
        {
            tail = new_node;
        }
        len++;
    }

    void addLast(T item)
    {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

        if (!head)
        {
            head = new_node;
        }
        else
        {
            tail->next_node = new_node;
            tail = new_node
        }
    }

    T least()
    {
        return head;
    }

    T greatest()
    {
        return tail;
    }

    T get(int i)
    {
        T current = head;
        for (int j = 0; j <= i; j++)
        {
            current = current->next_node;
        }

        return current;
    }

    int indexOf(T item)
    {
        T current = head;
        while (current->data != item)
        {
            current = current->next_node;
        }

        return current;
    }

    void remove(int i)
    {
        T current = head;
        T prev = head;

        for (int j = 0; j <= i; ++j)
        {
            prev = current;
            current = current->next_node;
        }

        prev->next_node = current->next_node;
    }

    List<T> searchRange(T from, T to)
    {
        SinglyLinkedSortedList List;

        current = head;
        for (int i = 0; i <= to; i++)
        {
            current = current->next_node;
            if (i >= from)
            {
                List.addLast(current);
            }
        }

        return List
    }

    int size()
    {
        int size = 0;
        current = head;

        for (int i = 0; i < len; i++)
        {
            size++;
            current = current->next_node;
        }

        return size;
    }

    bool isEmpty()
    {
        return ? head;
    }
};

int main(int argc, char const *argv[])
{
}
