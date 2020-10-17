#include "list.h"

task::Node::Node(): prev_element(nullptr), next_element(nullptr), value(0) {};

task::Node::Node(Node* const left, Node* const right, int elem) {
    prev_element = left;
    next_element = right;
    value = elem;
};

task::Node::Node(const Node& node) {
    prev_element = node.prev_element;
    next_element = node.next_element;
    value = node.value;
};

task::Node::~Node() {
    prev_element = next_element = nullptr;
    delete prev_element;
    delete next_element;
};

task::Node& task::Node::operator=(const Node& node) {
    next_element = node.next_element;
    prev_element = node.prev_element; 
    value = node.value;
    return *this;
}

void task::Node::set_prev_element(Node* const prev) {
    prev_element = prev;
}

task::Node* task::Node::get_ptr_to_prev_element() const {
    return prev_element;
}

void task::Node::set_next_element(Node* const next) {
    next_element = next;
}

task::Node* task::Node::get_ptr_to_next_element() const {
    return next_element;
}

const int& task::Node::get_value() const {
    return value;
}

int& task::Node::get_value() {
    return value;
}

void task::Node::swap(Node* &a, Node* &b) {
    Node* c = a;
    a = b;
    b = c;
}

task::list::list(): head(nullptr), tail(nullptr), list_size(0) {};

task::list::list(std::size_t count, const int& value): list_size(count) {
    head = new task::Node(nullptr, nullptr, value);
    task::Node* curr_node = head;

    for (std::size_t i = 0; i < count - 1; i++) {
        task::Node* new_node = new task::Node(nullptr, nullptr, value);
        new_node->set_prev_element(curr_node);
        curr_node->set_next_element(new_node);
        curr_node = new_node;
    }
    tail = curr_node;
}   

task::list::list(const task::list& other) {
    this->list_size = other.size();

    task::Node* curr_node = other.head;
    task::Node* prev_node = new task::Node(nullptr, nullptr, other.head->get_value());
    head = prev_node;

    for (std::size_t i = 0; i < other.size() - 1; i++) {
        curr_node = curr_node->get_ptr_to_next_element();
        task::Node* new_node = new task::Node(nullptr, nullptr, curr_node->get_value());
        
        prev_node->set_next_element(new_node);
        new_node->set_prev_element(prev_node);

        prev_node = new_node;
    }

    this->tail = prev_node;
}

task::list::~list() {
    task::Node* curr_node = tail;
    while (curr_node != head) {
        task::Node* node_to_delete = curr_node;
        curr_node = curr_node->get_ptr_to_prev_element();
        delete node_to_delete;
    }

    head = tail = nullptr;
    delete curr_node;
}

task::list& task::list::operator=(const list& other) {
    this->clear();

    this->list_size = other.size();
    task::Node* curr_node = other.head;
    task::Node* prev_node = new task::Node(nullptr, nullptr, other.head->get_value());
    head = prev_node;

    for (std::size_t i = 0; i < other.size() - 1; i++) {
        curr_node = curr_node->get_ptr_to_next_element();
        task::Node* new_node = new task::Node(nullptr, nullptr, curr_node->get_value());
        
        prev_node->set_next_element(new_node);
        new_node->set_prev_element(prev_node);

        prev_node = new_node;
    }

    this->tail = prev_node;
    return *this;
}

int& task::list::front() {
    return head->get_value();
}

const int& task::list::front() const {
    return head->get_value();
}

int& task::list::back() {
    return tail->get_value();
}

const int& task::list::back() const {
    return tail->get_value();
}

bool task::list::empty() const {
    return (list_size == 0);
}

std::size_t task::list::size() const {
    return this->list_size;
}

void task::list::clear() {
    task::Node* curr_node = tail;
    while (curr_node != head) {
        task::Node* node_to_delete = curr_node;
        curr_node = curr_node->get_ptr_to_prev_element();
        delete node_to_delete;
    }
    head = tail = nullptr;
    delete curr_node;
    list_size = 0;
}

void task::list::push_back(const int& value) {
    task::Node* new_node = new task::Node(nullptr, nullptr, value);

    if (list_size != 0) {
        new_node->set_prev_element(tail);
        tail->set_next_element(new_node);
    }
    
    tail = new_node;                
    if (list_size == 0)
        head = new_node;
    
    list_size++;
}

void task::list::pop_back() {
    if (list_size == 0)
        return;

    task::Node* node_to_delete = tail;
    if (list_size == 1)
        head = tail = nullptr;
    else {
        tail = tail->get_ptr_to_prev_element();
        tail->set_next_element(nullptr);
    }
    
    delete node_to_delete;
    list_size--;
}

void task::list::push_front(const int& value) {
    task::Node* new_node = new task::Node(nullptr, nullptr, value);
    
    if (list_size != 0) {
        new_node->set_next_element(head);
        head->set_prev_element(new_node);
    }

    head = new_node;
    if (list_size == 0)
        tail = new_node;

    list_size++;
}

void task::list::pop_front() {
    if (list_size == 0)
        return;

    task::Node* node_to_delete = head;
    if (list_size == 1)
        head = tail = nullptr;
    else {
        head = head->get_ptr_to_next_element();
        head->set_prev_element(nullptr);
    }

    delete node_to_delete;
    list_size--;
}

void task::list::resize(std::size_t count) {
    while (list_size > count)
        this->pop_back();

    while (list_size < count)
        this->push_back(0);
}

void task::list::swap(task::list& other) {
    task::Node::swap(this->head, other.head);
    task::Node::swap(this->tail, other.tail);

    std::size_t tmp_size = this->list_size;
    this->list_size = other.list_size;
    other.list_size = tmp_size;
}

void task::list::remove(const int& value) {
    while (list_size > 0 && head->get_value() == value)
        this->pop_front();

    while (list_size > 0 && tail->get_value() == value)
        this->pop_back();
    
    for (task::Node* curr_node = head; curr_node != tail; curr_node = curr_node->get_ptr_to_next_element()) {
        if (curr_node->get_value() != value)
            continue;

        erase_element_prev(curr_node);
    }
}

void task::list::unique() {
    for (task::Node* curr_node = head; curr_node != nullptr; curr_node = curr_node->get_ptr_to_next_element()) {
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

void task::list::sort() {
    *this = merge_sort(*this);
}

void task::list::erase_element_prev(task::Node* &elem) {
    task::Node* node_to_delete = elem;
    elem->prev_element->set_next_element(elem->next_element);
    elem->next_element->set_prev_element(elem->prev_element);

    elem = elem->get_ptr_to_prev_element();
    delete node_to_delete;
    list_size--;
}

void task::list::erase_element_next(task::Node* &elem) {
    task::Node* node_to_delete = elem;
    elem->prev_element->set_next_element(elem->next_element);
    elem->next_element->set_prev_element(elem->prev_element);

    elem = elem->get_ptr_to_next_element();
    delete node_to_delete;
    list_size--;
}

task::list task::list::merge_sort(const task::list l) {
    if (l.size() <= 1)
        return l;
    
    task::list left, right;
    task::Node* curr_element = l.head;


    for (std::size_t i = 0; i < (l.size() + 1) / 2; i++, curr_element = curr_element->get_ptr_to_next_element())
        left.push_back(curr_element->get_value());

    for (std::size_t i = 0; i < l.size() / 2; i++, curr_element = curr_element->get_ptr_to_next_element())
        right.push_back(curr_element->get_value());
    
    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

task::list task::list::merge(const task::list& a, const task::list& b) {
    task::list result;

    task::Node* first_curr_element = a.head;
    task::Node* second_curr_element = b.head;

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