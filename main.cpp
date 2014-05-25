#include "abc.h"

/**
 * @brief Concrete implementation of Sequence Base Class
 */
template<typename T>
class MyList:
    public Sequence<MyList<T>, T>
{
public:
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    MyList() :
        Sequence<MyList<T>, T>(this)
    {};

    MyList(const std::vector<T> vec) :
        Sequence<MyList<T>, T>(this),
        m_vec(vec)
    {};

    /// @brief concrete implementation of operator[]
    const T& operator[](size_t index) const { return m_vec[index]; };

    /// @brief concrete implementation of Size
    size_t Size() const { return m_vec.size(); }

    /// @brief concrete implementation of Iterable begin()
    const_iterator begin() const { return m_vec.begin(); }

    /// @brief concrete implementation of Iterable end()
    const_iterator end() const { return m_vec.end(); }
private:
    /// contained vector class
    std::vector<T> m_vec;

};



int main()
{
    using namespace std;
    std::vector<int> vec;
    vec.reserve(16);
    for (int i=0; i<10; i++) {
        vec.push_back(i);
    }
    vec.push_back(6);

    MyList<int> m(vec);
    cout << m.Size() << endl;
    cout << m.Contains(5) << endl;
    cout << m.index(4) << endl;
    cout << m.count(6) << endl;
}

