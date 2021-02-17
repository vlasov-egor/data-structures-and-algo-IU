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
private:
    /* data */
public:
    void add(T item);
    T least();
    T greatest();
    T get(int i);
    int indexOf(T item);
    void remove(int i);
    List<T> searchRange(T from, T to);
    int size();
    boolean isEmpty();
    
};


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
