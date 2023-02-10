#ifndef LIST_H_
#define LIST_H_

#include <stdexcept>
#include <cstddef>

/** Class list implements a subset of the standard
    list class using a double-linked list.
    @author Koffman and Wolfgang
 */
namespace KW {

    template<typename Item_Type>
    class list {
    private:
        // Insert definition of nested class DNode here.
#include "DNode.h"
    public:
        // Insert definition of nested class iterator here.
#include "list_iterator.h"
        // Give list access to internal values in iterator.
        friend class iterator;
        // Insert definition of nested class const_iterator here.
#include "list_const_iterator.h"
        // Give list access to internal values in const_iterator.
        friend class const_iterator;

        // Data fields
        /** A reference to the head of the list */
        DNode* head;
        /** A reference to the end of the list */
        DNode* tail;
        /** The size of the list */
        int num_items;
        // Functions
    public:

        /** Construct an empty list. */
        list() {
            head = NULL;
            tail = NULL;
            num_items = 0;
        }

        /** Construct a copy of a list. */
        list(const list<Item_Type>& other) {
            head = NULL;
            tail = NULL;
            num_items = 0;
            for (const_iterator itr = other.begin(); itr != other.end();
                    ++itr) {
                push_back(*itr);
            }
        }

        /** Construct a list from a sequence */
        template <typename iterator>
        list(iterator begin, iterator end) {
            head = NULL;
            tail = NULL;
            while (begin != end) {
                push_back(*begin++);
            }
        }

        /** Destroy a list. */
        ~list() {
            while (head != NULL) {
                DNode* current = head;
                head = head->next;
                delete current;
            }
            tail = NULL;
            num_items = 0;
        }

        /** Swap this list contents with another one */
        void swap(list<Item_Type>& other) {
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(num_items, other.num_items);
        }

        /** Assign the contents of one list to another. */
        list<Item_Type>& operator=(const list<Item_Type>& other) {
            // Make a copy of the other list.
            list<Item_Type> temp_copy(other);
            // Swap contents of self with the copy.
            swap(temp_copy);
            // Return -- upon return the copy will be destroyed.
            return *this;
        }

        /** Insert an object at the beginning of the list.
            @param item - the item to be added 
         */
        void push_front(const Item_Type& item) {
            head = new DNode(item, NULL, head); // Step 1
            if (head->next != NULL)
                head->next->prev = head; // Step 2
            if (tail == NULL) // List was empty.
                tail = head;
            num_items++;
        }

        /** Insert an object at the end of the list.
            @param item - the item to be added 
         */
        void push_back(const Item_Type& item) {
            if (tail != NULL) {
                tail->next = new DNode(item, tail, NULL); // Step 1
                tail = tail->next; // Step 2
                num_items++;
            } else { // List was empty.
                push_front(item);
            }
        }

        /** Insert an object at a position in the list
            indicated by an iterator.  The new item is
            inserted before the position indicated by
            the iterator.
            @param pos The iterator that references the 
                       position where the item is to be
                       inserted.
            @param item The item to be inserted
            @return An iterator that references the inserted
                    item.
         */
        iterator insert(iterator pos, const Item_Type& item) {
            // Check for special cases
            if (pos.current == head) {
                push_front(item);
                return begin();
            } else if (pos.current == NULL) { // Past the last node.
                push_back(item);
                return iterator(this, tail);
            }
            // Create a new node linked before node referenced by pos.
            DNode* new_node = new DNode(item,
                    pos.current->prev,
                    pos.current); // Step 1

            // Update links
            pos.current->prev->next = new_node; // Step 2
            pos.current->prev = new_node; // Step 3
            num_items++;
            return iterator(this, new_node);
        }

        /*<exercise chapter="4" section="7" type="programming" number="1">*/

        /** Get a reference to the first element in the list.
            This can be used on either side of an assignment.
            @return The first element in the list.
            @throws invaid_argument if the list is empty
         */
        Item_Type& front() {
            if (head == NULL)
                throw std::invalid_argument
                    ("Attempt to call front() on an empty list");
            return head->data;
        }

        /** Get a constant reference to first element in the list.
            This can only be used on the right side of an assignment.
            @return The first element in the list.
            @throws invaid_argument if the list is empty
         */
        const Item_Type& front() const {
            if (head == NULL)
                throw std::invalid_argument
                    ("Attempt to call front() on an empty list");
            return head->data;
        }


        /*<exercise chapter="1" section="7" type="programming" number="2">*/

        /** Get a reference to the last element in the list.
            This can be used on either side of an assignment.
            @return The last element in the list.
            @throws std::invalid_argument if the list is empty
         */
        Item_Type& back() {
            if (tail == NULL)
                throw std::invalid_argument
                    ("Attempt to call back() on an empty list");
            return tail->data;
        }

        /** Get a constant reference to the last element in the list.
            This can only be used on the right side of an assgnment.
            @return The last element in the list.
            @throws std::invalid_argument if the list is empty
         */
        const Item_Type& back() const {
            if (tail == NULL)
                throw std::invalid_argument
                    ("Attempt to call back() on an empty list");
            return tail->data;
        }
        /*</exercise>*/

        /** Query the size of the list
            @return The number of objects in the list 
         */
        int size() const {
            return num_items;
        }

        /** Indicate if the list is empty
            @return true if the list is empty
         */
        bool empty() const {
            return num_items == 0;
        }

        /** Remove the first item from the list
            @throws std::invalid_argument If the list is empty
         */
        void pop_front() {
            if (head == NULL)
                throw std::invalid_argument
                    ("Attempt to call pop_front() on an empty list");
            DNode* removed_node = head;
            head = head->next;
            delete removed_node;
            if (head != NULL)
                head->prev = NULL;
            else
                tail = NULL;
            num_items--;
        }

        /** Remove the last item from the list
            @throws std::invalid_argument If the list is empty
         */
        void pop_back() {
            if (tail == NULL)
                throw std::invalid_argument
                    ("Attempt to call pop_back() on an empty list");
            DNode* removed_node = tail;
            tail = tail->prev;
            delete removed_node;
            if (tail != NULL)
                tail->next = NULL;
            else
                head = NULL;
            num_items--;
        }

        /** Remove an item referenced by an iterator
            @param pos An iterator referencing the item to
            be removed
            @return An iterator that referenced the item
            following the item being removed
            @throws std::invalid_argument if the list is empty
                    or if pos references end()
         */
        iterator remove(iterator pos) {
            if (empty())
                throw std::invalid_argument
                    ("Attempt to call remove on an empty list");
            if (pos == end())
                throw std::invalid_argument
                    ("Attempt to call remove of end()");
            /* Create an iterator that references the position
               following pos. */
            iterator return_value = pos;
            ++return_value;
            // Check for special cases.
            if (pos.current == head) {
                pop_front();
                return return_value;
            } else if (pos.current == tail) {
                pop_back();
                return return_value;
            } else { // Remove a node in the interior of the list.
                // Unlink current node.
                DNode* removed_node = pos.current;
                removed_node->prev->next = removed_node->next;
                removed_node->next->prev = removed_node->prev;
                delete removed_node;
                return return_value;
            }
        }

        /*<exercise chapter="4" section="7" type="programming" number="4>*/

        /** Remove all occurences of a value from the list
            @param item The value to be removed
         */
//        void remove(const Item_Type& item) {
//            iterator itr = begin();
//            while (itr != end()) {
//                if (*itr == item)
//                    itr = erase(itr);
//                else
//                    ++itr;
//            }
//        }

        /** Remove a value from the list
            @param item The value to be removed
         */
        void remove(const Item_Type& item) {
            iterator itr = find(item);
            if (itr != end()) 
                    itr = remove(itr);
        }
        /*</exercise>*/

        /*<exercise chapter="4" section="3" type="programming" number="3">*/

        /** Return an iterator to the beginning of the list
            @return an itertor to the beginning of the list
         */
        iterator begin() {
            iterator return_value(this, head);
            return return_value;
        }

        /** Return a const_iterator to the beginning of
            the list
            @return a const_iterator to the beginning of
            the list
         */
        const_iterator begin() const {
            const_iterator return_value(this, head);
            return return_value;
        }
        /*</exercise>*/

        /** Return an iterator to the end of the list
            @return an iterator to the end of the list
         */
        iterator end() {
            iterator return_value(this, NULL);
            return return_value;
        }

        /** Return a const_iterator to the end of the list
            @return a const_iterator to the end of the list
         */
        const_iterator end() const {
            const_iterator return_value(this, NULL);
            return return_value;
        }

        /**
         * if found the target, return the iterator to the current position.
         * return NULL if the target is not in the list.
         * @param target
         * @return iterator points to the found target; NULL otherwise.
         */
        
        iterator find(const Item_Type& target) {
            iterator ibegin = begin();
            iterator iend = end();
            while (ibegin != iend) {
                if (*ibegin == target) return ibegin;
                else ++ibegin;
            }
            return ibegin;
        }
    }; // End list

    template <typename Item_Type>
    void swap(list<Item_Type>& x, list<Item_Type>& y) {
        x.swap(y);
    }
} // End namespace KW

#endif
