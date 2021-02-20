#include <iostream>
#include <string>
#include <cmath>

using namespace std;

long long int hash(string token)
{
    long long h = 0;
    int i = 0;
    for (auto c : token)
    {
        h += c * pow(33.0, i);
        i += 1;
    }

    return h;
}

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
    virtual bool has(T item) = 0;
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
        if (!has(item))
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

    bool has(T item)
    {
        if (size() == 0) {
            return false;
        }

        Node<T> *current = head;
        while (current)
        {
            if (current->data == item){
                return true;
            }

            current = current->next_node;
        }

        return false;
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

template <class Key, class Value>
class Map
{
public:
    virtual bool exists(Key key) = 0;
    virtual Value &get(Key key) = 0;
    virtual void put(Key key, Value value) = 0;
    virtual Value remove(Key key) = 0;
    virtual SinglyLinkedSortedList<Key> *keys() = 0;
};

template <class Key, class Value>
class MapNode
{
public:
    Key key;
    Value value;
    int next_index = -1;
    bool used = false;
};

template <class Key, class Value>
class HashMap : public Map<Key, Value>
{
private:
    int len = 1000;
    int n = (int)round((float)len * 0.86);

    MapNode<Key, Value> *arr = new MapNode<Key, Value>[len];
    SinglyLinkedSortedList<Key> *keysList = new SinglyLinkedSortedList<Key>();

public:
    void resize()
    {
        MapNode<Key, Value> *old = arr;
        int old_len = len;

        keysList = new SinglyLinkedSortedList<Key>();
        arr = new MapNode<Key, Value>[len * 2];
        len *= 2;
        n = (int)round((float)len * 0.86);

        for (int i = 0; i < old_len; i++)
        {
            if (old[i].used)
            {
                put(old[i].key, old[i].value);
            }
        }
    }

    void put(Key key, Value value)
    {
        int h = ::hash(key) % n;

        if (!arr[h].used)
        {
            // cout << "wtf" << endl;
            arr[h] = MapNode<Key, Value>{key, value, -1, true};
            keysList->add(key);
            return;
        }

        if (arr[h].key == key)
        {
            arr[h].value = value;
            return;
        }

        int index = 0;
        while (index < len && arr[index].used && arr[index].key != key)
        {
            index++;
        }

        if (index == len)
        {
            resize();
            put(key, value);
            return;
        }

        if (!arr[index].used)
        {
            keysList->add(key);
        }

        arr[index] = MapNode<Key, Value>{key, value, -1, true};
        for (; arr[h].next_index != -1; h = arr[h].next_index)
            ;

        arr[h].next_index = index;
    }

    bool exists(Key key)
    {
        int h = ::hash(key) % n;

        if (!arr[h].used)
        {
            return false;
        }

        for (; h != -1 && arr[h].key != key; h = arr[h].next_index)
            ;

        if (h == -1)
        {
            return false;
        }

        return true;
    }

    Value &get(Key key)
    {
        int h = ::hash(key) % n;

        if (!arr[h].used)
        {
            throw invalid_argument("there are no such key");
        }

        for (; h != -1 && arr[h].key != key; h = arr[h].next_index)
            ;

        if (h == -1)
        {
            throw invalid_argument("there are no such key");
        }

        return arr[h].value;
    }

    Value remove(Key key)
    {
        int h = ::hash(key) % n;
        int p;

        if (!arr[h].used)
        {
            throw invalid_argument("there are no such key");
        }

        for (; h != -1 && arr[h].key != key; h = arr[h].next_index)
        {
            p = h;
        }

        if (h == -1)
        {
            throw invalid_argument("there are no such key");
        }

        arr[h].used = false;
        arr[p].next_index = arr[h].next_index;
        keysList->removeItem(key);
        return arr[h].value;
    }

    SinglyLinkedSortedList<Key> *keys()
    {
        return keysList;
    }
};

class Now
{
public:
    float total;
    HashMap<string, bool> *codes;
};

int main(int argc, char const *argv[])
{

    HashMap<string, Now> *all_time = new HashMap<string, Now>();

    int n;
    string line;

    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        getline(cin, line);
        int first_space = line.find(" ", 0);
        int second_space = line.find(" ", first_space + 1);
        int third_space = line.find(" ", second_space + 1);
        int fourth_space = line.find(" ", third_space + 1);

        string date = line.substr(0, first_space);
        string time = line.substr(first_space + 1, second_space - (first_space + 1));
        string id = line.substr(second_space + 2, third_space - (second_space + 2));
        float price = stof(line.substr(third_space + 2, fourth_space - (third_space + 2)));
        string name = line.substr(fourth_space + 1);

        if (all_time->exists(date))
        {
            // cout << "altered " << date << endl;
            Now &day = all_time->get(date);
            day.total += price;
            day.codes->put(id, true);
        }
        else
        {
            // cout << "created " << date << endl;
            auto day = Now{
                price,
                new HashMap<string, bool>()};
            // cout << "sasat tut" << endl;
            day.codes->put(id, true);
            // cout << "pososal" << endl;
            all_time->put(date, day);
        }
    }

    for (auto dN = all_time->keys()->getHead(); dN; dN = dN->next_node)
    {
        Now day = all_time->get(dN->data);
        printf("%s $%.2f %d\n", dN->data.c_str(), day.total, day.codes->keys()->size());
    }
}
