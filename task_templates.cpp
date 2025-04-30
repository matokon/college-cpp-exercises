#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

template<typename containertype, typename elementstype>
size_t count_elem(const containertype& container, const elementstype& elements)
{
    size_t counter = 0;
    for(int i = 0; i < elements.size(); i++)
    {
        auto el = elements[i];
        if(std::find(std::begin(container),std::end(container),el) != std::end(container))
        {
            counter++;
        }
    }
    return counter;
}



int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> elements_vec = {2, 4, 6};
    std::cout << "I found " << count_elem(vec, elements_vec) << " elements in vector.\n";

    std::list<std::string> lst = {"apple", "banana", "cherry"};
    std::vector<std::string> elements_lst = {"banana", "kiwi"};
    std::cout << "I found " << count_elem(lst, elements_lst) << " elements in list.\n";

    std::set<char> s = {'a', 'b', 'c'};
    std::vector<char> elements_set = {'b', 'd'};
    std::cout << "I found " << count_elem(s, elements_set) << " elements in set.\n";
}
