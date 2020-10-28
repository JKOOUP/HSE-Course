#pragma once
#include <cstddef>

namespace task {

class Node {

friend class list;

public:
    
    Node();
    
    Node(Node* const left, Node* const right, int elem);

    Node(int elem);

    Node(const Node& node);

    ~Node();

    Node& operator=(const Node& node);

    void set_prev_element(Node* const prev);

    Node* get_ptr_to_prev() const;

    void set_next_element(Node* const next);

    Node* get_ptr_to_next() const;

    const int& get() const;

    int& get();

    int get_next_value() const;

    int get_prev_value() const;

    static void swap(Node* &a, Node* &b);

    static void inc(Node* &ptr);

    static void dec(Node* &ptr);

private:
    
    Node* prev_element;
    Node* next_element;
    int value;

};

class list {

public:
    
    list();

    list(std::size_t count, const int& value = int());

    list(const list& other);

    ~list();

    list& operator=(const list& other);

    int& front();

    const int& front() const;

    int& back();

    const int& back() const;

    bool empty() const;

    std::size_t size() const;

    void clear();

    void push_back(const int& value);

    void pop_back();

    void push_front(const int& value);
    
    void pop_front();

    void resize(std::size_t count);

    void swap(list& other);

    void remove(const int& value);

    void unique();

    void sort();

private:
    
    Node* head;
    Node* tail; 
    std::size_t list_size; 

    void erase_element_prev(Node* &elem);

    void erase_element_next(Node* &elem);

    static list merge_sort(const list l);

    static list merge(const list& a, const list& b);
};

};