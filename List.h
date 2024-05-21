#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

template <typename T>
class List
{
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  //EFFECTS:  returns true if the list is empty
  bool empty() const
  {
    if (capacity == 0)
      return true;
    else
      return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the capacity
  //         with a private member variable.  That's how std::list does it.
  int size() const
  {
    return capacity;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum)
  {
    Node *frontNode = new Node;
    frontNode->datum = datum;
    frontNode->prev = nullptr;
    frontNode->next = nullptr;

    if (empty())
    {
      first = frontNode;
      last = frontNode;
    }
    else
    {
      frontNode->next = first;
      first->prev = frontNode;
      first = frontNode;
    }
    capacity++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    Node *backNode = new Node;
    backNode->datum = datum;
    backNode->next = nullptr;
    backNode->prev = nullptr;

    if (empty())
    {
      last = backNode;
      first = backNode;
    }
    else
    {
      last->next = backNode;
      backNode->prev = last;
      last = backNode;
    }
    capacity++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
    assert(!empty());
    Node *newFirstNode = first->next;
    if (newFirstNode == nullptr)
    { //list has size 1
      delete last;
      last = nullptr;
      first = nullptr;
      capacity--;
    }
    else
    {
      newFirstNode->prev = nullptr;
      delete first;
      capacity--;
      if (capacity == 1) //list has size 2 -> 1
      {
        last = newFirstNode;
        first = newFirstNode;
      }
      else
      {
        first = newFirstNode;
      }
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
    assert(!empty());
    assert(last != nullptr);
    assert(first != nullptr);

    Node *newLastNode = last->prev;
    if (newLastNode == nullptr)
    { // list has size of 1
      delete last;
      last = nullptr;
      first = nullptr;
      capacity--;
    }
    else
    {
      newLastNode->next = nullptr; //else then make newLastnode last.
      delete last;
      capacity--;
      if (capacity == 1) //list has size 2 -> 1
      {
        last = newLastNode;
        first = newLastNode;
      }
      else
      {
        last = newLastNode;
      }
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
  List() : first(nullptr), last(nullptr), capacity(0) {}

  List(const List &other) : first(nullptr), last(nullptr), capacity(0)
  {
    copy_all(other);
  }

  List &operator=(const List &rhs)
  {
    if (this == &rhs)
      return *this;

    clear();
    copy_all(rhs);

    return *this;
  }

  ~List()
  {
    clear();
  }

private:
  //a private type
  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other)
  {
    for (Node *np = other.first; np; np = np->next)
    {
      push_back(np->datum);
    }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last;  // points to last Node in list, or nullptr if list is empty
  int capacity;

public:
  ////////////////////////////////////////
  class Iterator
  {
    //OVERVIEW: Iterator interface to List
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator &operator--()
    {
        
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }
    Iterator() : node_ptr(nullptr) {}
    T &operator*() const
    {
      return node_ptr->datum;
    }
    Iterator &operator++()
    {
      node_ptr = node_ptr->next;
      return *this;
    }
    bool operator==(Iterator rhs) const
    {
      if (node_ptr == rhs.node_ptr)
        return true;
      else
        return false;
    }
    bool operator!=(Iterator rhs) const
    {
      if (node_ptr == rhs.node_ptr)
        return false;
      else
        return true;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
                    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  }; //List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
    return Iterator();
  };

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
    Node *prevErase = i.node_ptr->prev;
    Node *nextErase = i.node_ptr->next;

    if (prevErase == nullptr)
    { // erase the beginning
      pop_front();
    }
    else if (nextErase == nullptr)
    { // erase the end
      pop_back();
    }
    else
    {
      prevErase->next = nextErase;
      nextErase->prev = prevErase;
      capacity--;
      delete i.node_ptr;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {
    if (i.node_ptr == nullptr)
    {
      push_back(datum);
      return;
    }

    // assert(first != nullptr);
    // assert(last != nullptr);

    Node *prevInsert = i.node_ptr->prev;
    if (prevInsert == nullptr)
    { // push at the beginning
      push_front(datum);
    }
    else
    {
      Node *insertedNode = new Node;
      insertedNode->datum = datum;

      prevInsert->next = insertedNode;
      insertedNode->prev = prevInsert;

      insertedNode->next = i.node_ptr;
      i.node_ptr->prev = insertedNode;

      capacity++;
    }
  }

}; //List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
