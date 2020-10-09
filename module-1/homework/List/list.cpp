#include "list.h"

using namespace task;

Node::Node(): prev_element(nullptr), next_element(nullptr), value(0) {};

Node::Node(Node* const left, Node* const right, int elem) {
    prev_element = left;
    next_element = right;
    value = elem;
};

Node::Node(const Node& node) {
    prev_element = node.prev_element;
    next_element = node.next_element;
    value = node.value;
};

Node::~Node() {
    prev_element = next_element = nullptr;
    delete prev_element;
    delete next_element;
};

Node& Node::operator=(const Node& node) {
    next_element = node.next_element;
    prev_element = node.prev_element; 
    value = node.value;
    return *this;
}

void Node::set_prev_element(Node* const prev) {
    prev_element = prev;
}

Node* Node::get_ptr_to_prev_element() const {
    return prev_element;
}

void Node::set_next_element(Node* const next) {
    next_element = next;
}

Node* Node::get_ptr_to_next_element() const {
    return next_element;
}

const int& Node::get_value() const {
    return value;
}

int& Node::get_value() {
    return value;
}

void Node::swap(Node* &a, Node* &b) {
    Node* c = a;
    a = b;
    b = c;
}

list::list(): head(nullptr), tail(nullptr), list_size(0) {};

list::list(std::size_t count, const int& value): list_size(count) {
    head = new Node(nullptr, nullptr, value);
    Node* curr_node = head;

    for (std::size_t i = 0; i < count - 1; i++) {
        Node* new_node = new Node(nullptr, nullptr, value);
        new_node->set_prev_element(curr_node);
        curr_node->set_next_element(new_node);
        curr_node = new_node;
    }
    tail = curr_node;
}   

list::list(const list& other) {
    this->list_size = other.size();

    Node* curr_node = other.head;
    Node* prev_node = new Node(nullptr, nullptr, other.head->get_value());
    head = prev_node;

    for (std::size_t i = 0; i < other.size() - 1; i++) {
        curr_node = curr_node->get_ptr_to_next_element();
        Node* new_node = new Node(nullptr, nullptr, curr_node->get_value());
        
        prev_node->set_next_element(new_node);
        new_node->set_prev_element(prev_node);

        prev_node = new_node;
    }

    this->tail = prev_node;
}

list::~list() {
    Node* curr_node = tail;
    while (curr_node != head) {
        Node* node_to_delete = curr_node;
        curr_node = curr_node->get_ptr_to_prev_element();
        delete node_to_delete;
    }

    head = tail = nullptr;
    delete curr_node;
}

list& list::operator=(const list& other) {
    this->clear();

    this->list_size = other.size();
    Node* curr_node = other.head;
    Node* prev_node = new Node(nullptr, nullptr, other.head->get_value());
    head = prev_node;

    for (std::size_t i = 0; i < other.size() - 1; i++) {
        curr_node = curr_node->get_ptr_to_next_element();
        Node* new_node = new Node(nullptr, nullptr, curr_node->get_value());
        
        prev_node->set_next_element(new_node);
        new_node->set_prev_element(prev_node);

        prev_node = new_node;
    }

    this->tail = prev_node;
    return *this;
}

int& list::front() {
    return head->get_value();
}

const int& list::front() const {
    return head->get_value();
}

int& list::back() {
    return tail->get_value();
}

const int& list::back() const {
    return tail->get_value();
}

bool list::empty() const {
    return (list_size == 0);
}

std::size_t list::size() const {
    return this->list_size;
}

void list::clear() {
    Node* curr_node = tail;
    while (curr_node != head) {
        Node* node_to_delete = curr_node;
        curr_node = curr_node->get_ptr_to_prev_element();
        delete node_to_delete;
    }
    head = tail = nullptr;
    delete curr_node;
    list_size = 0;
}

void list::push_back(const int& value) {
    Node* new_node = new Node(nullptr, nullptr, value);

    if (list_size != 0) {
        new_node->set_prev_element(tail);
        tail->set_next_element(new_node);
    }
    
    tail = new_node;                
    if (list_size == 0)
        head = new_node;
    
    list_size++;
}

void list::pop_back() {
    if (list_size == 0)
        return;

    Node* node_to_delete = tail;
    if (list_size == 1)
        head = tail = nullptr;
    else {
        tail = tail->get_ptr_to_prev_element();
        tail->set_next_element(nullptr);
    }
    
    delete node_to_delete;
    list_size--;
}

void list::push_front(const int& value) {
    Node* new_node = new Node(nullptr, nullptr, value);
    
    if (list_size != 0) {
        new_node->set_next_element(head);
        head->set_prev_element(new_node);
    }

    head = new_node;
    if (list_size == 0)
        tail = new_node;

    list_size++;
}

void list::pop_front() {
    if (list_size == 0)
        return;

    Node* node_to_delete = head;
    if (list_size == 1)
        head = tail = nullptr;
    else {
        head = head->get_ptr_to_next_element();
        head->set_prev_element(nullptr);
    }

    delete node_to_delete;
    list_size--;
}

void list::resize(std::size_t count) {
    while (list_size > count)
        this->pop_back();

    while (list_size < count)
        this->push_back(0);
}

void list::swap(list& other) {
    Node::swap(this->head, other.head);
    Node::swap(this->tail, other.tail);
    std::swap(this->list_size, other.list_size);
}

void list::remove(const int& value) {
    while (list_size > 0 && head->get_value() == value)
        this->pop_front();

    while (list_size > 0 && tail->get_value() == value)
        this->pop_back();
    
    for (Node* curr_node = head; curr_node != tail; curr_node = curr_node->get_ptr_to_next_element()) {
        if (curr_node->get_value() != value)
            continue;

        erase_element_prev(curr_node);
    }
}

void list::unique() {
    for (Node* curr_node = head; curr_node != nullptr; curr_node = curr_node->get_ptr_to_next_element()) {
        if (list_size <= 1)
            break; 

        while (list_size > 1 && curr_node != tail && curr_node->get_ptr_to_next_element()->get_value() == curr_node->get_value()) {
            if (curr_node == head) {
                curr_node = curr_node->get_ptr_to_next_element();
                this->pop_front();
                continue;
            }

            erase_element_next(curr_node);
        }
    }
}

void list::sort() {
    *this = merge_sort(*this);
}

void list::erase_element_prev(Node* &elem) {
    Node* node_to_delete = elem;
    elem->prev_element->set_next_element(elem->next_element);
    elem->next_element->set_prev_element(elem->prev_element);

    elem = elem->get_ptr_to_prev_element();
    delete node_to_delete;
    list_size--;
}

void list::erase_element_next(Node* &elem) {
    Node* node_to_delete = elem;
    elem->prev_element->set_next_element(elem->next_element);
    elem->next_element->set_prev_element(elem->prev_element);

    elem = elem->get_ptr_to_next_element();
    delete node_to_delete;
    list_size--;
}

list list::merge_sort(const list l) {
    if (l.size() <= 1)
        return l;
    
    list left, right;
    Node* curr_element = l.head;


    for (std::size_t i = 0; i < (l.size() + 1) / 2; i++, curr_element = curr_element->get_ptr_to_next_element())
        left.push_back(curr_element->get_value());

    for (std::size_t i = 0; i < l.size() / 2; i++, curr_element = curr_element->get_ptr_to_next_element())
        right.push_back(curr_element->get_value());
    
    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

list list::merge(const list& a, const list& b) {
    list result;

    Node* first_curr_element = a.head;
    Node* second_curr_element = b.head;

    while (first_curr_element != nullptr && second_curr_element != nullptr) {
        if (first_curr_element->get_value() <= second_curr_element->get_value()) {
            result.push_back(first_curr_element->get_value());
            first_curr_element = first_curr_element->get_ptr_to_next_element();
        } else {
            result.push_back(second_curr_element->get_value());
            second_curr_element = second_curr_element->get_ptr_to_next_element();
        }

    }

    while (first_curr_element != nullptr) {
        result.push_back(first_curr_element->get_value());
        first_curr_element = first_curr_element->get_ptr_to_next_element();
    }

    while (second_curr_element != nullptr) {
        result.push_back(second_curr_element->get_value());
        second_curr_element = second_curr_element->get_ptr_to_next_element();
    }

    return result;
}