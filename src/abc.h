/**
 * @file
 *
 * @brief my first attempt to implement python's abstract base classes
 *
 * This file plays around with the idea python's abstract base classes
 * using C++ templates. Sequence is implemented, and only requires
 * a bit more work to implement than python's Sequence class.
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

#include <algorithm>    // std::any_of

#include <assert.h>     // assert

/**
 * @brief Abstract Base Class namespace
 */
namespace ABC
{

/**
 * @brief specifies that a class can be cloned using Clone()
 *
 * Concrete subclasses must implement Clone
 */
template<typename T>
class Clonable
{
    bool ValidateRequirements() const {
        T* (T::*test)() const = &T::Clone;
        test;
        return true;
    }
public:
    virtual ~Clonable()
    {
        assert(ValidateRequirements());
    }
};

/**
 * @brief specifies that size info can be returned from a class using Size()
 *
 * Concrete subclasses must implement Size
 */
template<typename T>
class Sized
{
    bool ValidateRequirements() const {
        size_t (T::*test)() const = &T::Size;
        test;
        return true;
    }
public:
    virtual ~Sized()
    {
        assert(ValidateRequirements());
    }
};

/**
 * @brief specifies that a class can be iterated over without changing it
 *
 * Concrete subclasses must implement const versions of begin and end
 */
template<typename T>
class ConstIterable
{
    bool ValidateRequirements() const {
        typename T::const_iterator (T::*const_test_begin)() const = &T::begin;
        const_test_begin;
        typename T::const_iterator (T::*const_test_end)() const = &T::end;
        const_test_end;
        return true;
    }
public:
    virtual ~ConstIterable()
    {
        assert(ValidateRequirements());
    }
};


/**
 * @brief specifies that a class can be iterated over
 *
 * Concrete subclasses must implement non-const begin and end
 */
template<typename T>
class MutIterable
{
    bool ValidateRequirements() const {
        typename T::iterator (T::*test_begin)() = &T::begin;
        test_begin;
        typename T::iterator (T::*test_end)() = &T::end;
        test_end;
        return true;
    }
public:
    virtual ~MutIterable()
    {
        assert(ValidateRequirements());
    }
};



/**
 * @brief specifies that a class can be iterated over
 *
 * Concrete subclasses must implement const and non-const begin and end
 */
template<typename T>
class Iterable :
    public ConstIterable<T>,
    public MutIterable<T>
{
    virtual ~Iterable() {};
};


/**
 * @brief specifies that a class acts as a container, holding other types
 *
 * Concreate subclasses must implement Contains
 */
template<typename T, typename U>
class Container
{
    bool ValidateRequirements() const {
        bool (T::*test)(const U&) const = &T::Contains;
        test;
        return true;
    }
public:
    virtual ~Container()
    {
        assert(ValidateRequirements());
    }
};


/**
 * @brief Base class for a vector-like class
 *
 * Concreate subclasses must implement operator[], begin, end, and Size
 */
template<typename T, typename U>
class Sequence:
    public Sized<T>,
    public ConstIterable<T>,
    public Container<T, U>
{
    bool ValidateRequirements() const {
        const U &(T::*test)(size_t) const = &T::operator[];
        test;
        return true;
    }
public:
    Sequence(T* childobj) :
        m_obj(childobj)
    {
        assert(childobj != NULL);
    };

    virtual ~Sequence()
    {
        assert(ValidateRequirements());
    }

    /**
     * @brief default implementation for Contains
     */
    virtual bool Contains(const U& value) const {
        return std::any_of(m_obj->begin(),
                           m_obj->end(),
                           [&value](const U& elem) {
                                return elem == value;
                            });
    }

    /**
     * @brief return the first index value is located at, or -1
     */
    int index(const U&  value) const {
        for (size_t i=0; i<m_obj->Size(); i++)
        {
            if ((*m_obj)[i] == value) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief return the number of occurrances of value
     */
    size_t count(const U& value) const {
        size_t num = 0;
        for(typename T::const_iterator it=m_obj->begin();
                     it != m_obj->end();
                     ++it) {
            if (*it == value) {
                num += 1;
            }
        };
        return num;
    }
private:

    /// a handle to the derived class
    T* m_obj;
};

};
