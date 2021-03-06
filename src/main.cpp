/**
 * @file
 *
 * @brief implementation and example of use of abstract base classes
 *
 *
 *
 *  Copyright (C) 2014  Vernon R. Jones
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>     // std::cout, std::endl
#include <vector>       // std::vector

#include "abc.h"        // Sequence



/**
 * @brief Concrete implementation of Sequence Base Class
 *
 * This class is similar to an immutable vector. It supports many
 * vector operations available for use with a const vector.
 * It serves as an example of what you can do with templates + inheritance.
 *
 * This is currently the minimum amount needed to implement ABC::Sequence.
 */
template<typename T>
class MyList :
    public ABC::Sequence<MyList<T>, T>
{
public:
    // iterator definitions
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;


    MyList() :
        ABC::Sequence<MyList<T>, T>(this)
    {};

    MyList(const std::vector<T> vec) :
        ABC::Sequence<MyList<T>, T>(this),
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
    const std::vector<T> m_vec;
};



int main()
{
    using namespace std;

    // start by building a vector
    std::vector<int> vec;
    vec.reserve(16);
    for (int i=0; i<10; i++) {
        vec.push_back(i);
    }
    vec.push_back(6);

    // now build our own immutable vectory type
    MyList<int> m(vec);

    // print some attributes of our vectory type
    cout << m.Size() << endl;
    cout << m.Contains(5) << endl;
    cout << m.index(4) << endl;
    cout << m.count(6) << endl;
}

