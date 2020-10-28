#include "list.h"

task::Node::Node(): 
    prev_element(nullptr), 
    next_element(nullptr), 
    value(0) 
{}

task::Node::Node(Node* const left, Node* const right, int elem) {
    prev_element = left;
    next_element = right;
    value = elem;
}

task::Node::Node(int elem): 
    prev_element(nullptr), 
    next_element(nullptr), 
    value(elem) 
{}

task::Node::Node(const Node& node) {
    prev_element = node.prev_element;
    next_element = node.next_element;
    value = node.value;
}

task::Node::~Node() {
    prev_element = next_element = nullptr;
    delete prev_element;
    delete next_element;
}

task::Node& task::Node::operator=(const Node& node) {
    next_element = node.next_element;
    prev_element = node.prev_element; 
    value = node.value;
    return *this;
}

void task::Node::set_prev_element(Node* const prev) {
    prev_element = prev;
}

task::Node* task::Node::get_ptr_to_prev() const {
    return prev_element;
}

void task::Node::set_next_element(Node* const next) {
    next_element = next;
}

task::Node* task::Node::get_ptr_to_next() const {
    return next_element;
}

const int& task::Node::get() const {
    return value;
}

int& task::Node::get() {
    return value;
}

int task::Node::get_next_value() const {
    return this->get_ptr_to_next()->get();
}

int task::Node::get_prev_value() const {
    return this->get_ptr_to_prev()->get();
}

void task::Node::swap(Node* &a, Node* &b) {
    Node* c = a;
    a = b;
    b = c;
}

void task::Node::inc(Node* &ptr) {
    ptr = ptr->get_ptr_to_next();
}

void task::Node::dec(Node* &ptr) {
    ptr = ptr->get_ptr_to_prev();
}

task::list::list(): 
    head(nullptr), 
    tail(nullptr), 
    list_size(0) 
{};

task::list::list(std::size_t count, const int& value) {
    head = new task::Node(value);
    task::Node* curr_node = head;

    for (std::size_t i = 0; i + 1 < count; i++) {
        task::Node* new_node = new task::Node(value);
        new_node->set_prev_element(curr_node);
        curr_node->set_next_element(new_node);
        curr_node = new_node;
    }

    tail = curr_node;
    list_size = count;
}  

task::list::list(const task::list& other) {
    this->list_size = other.size();

    task::Node* curr_node = other.head;
    task::Node* prev_node = new task::Node(other.head->get());
    head = prev_node;

    for (std::size_t i = 0; i + 1 < other.size(); i++) {
        curr_node = curr_node->get_ptr_to_next();
        task::Node* new_node = new task::Node(curr_node->get());
        
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
        task::Node::dec(curr_node);
        delete node_to_delete;
    }

    head = tail = nullptr;
    delete curr_node;
}

task::list& task::list::operator=(const list& other) {
    this->clear();

    this->list_size = other.size();
    task::Node* curr_node = other.head;
    task::Node* prev_node = new task::Node(other.head->get());
    head = prev_node;

    for (std::size_t i = 0; i + 1< other.size(); i++) {
        task::Node::inc(curr_node);
        task::Node* new_node = new task::Node(curr_node->get());
        
        prev_node->set_next_element(new_node);
        new_node->set_prev_element(prev_node);

        prev_node = new_node;
    }

    this->tail = prev_node;
    return *this;
}

int& task::list::front() {
    return head->get();
}

const int& task::list::front() const {
    return head->get();
}

int& task::list::back() {
    return tail->get();
}

const int& task::list::back() const {
    return tail->get();
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
        task::Node::dec(curr_node);
        delete node_to_delete;
    }

    head = tail = nullptr;
    delete curr_node;
    list_size = 0;
}

void task::list::push_back(const int& val) {
    int value = val;
    task::Node* new_node = new task::Node(value);

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
        task::Node::dec(tail);
        tail->set_next_element(nullptr);
    }
    
    delete node_to_delete;
    list_size--;
}

void task::list::push_front(const int& val) {
    int value = val;
    task::Node* new_node = new task::Node(value);
    
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
        task::Node::inc(head);
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

void task::list::remove(const int& val) {
    int value = val;
    while (list_size > 0 && head->get() == value)
        this->pop_front();

    while (list_size > 0 && tail->get() == value)
        this->pop_back();
    
    task::Node* curr_node = head;
    while (curr_node != tail) {
        if (curr_node->get() != value) {
            task::Node::inc(curr_node);
            continue;
        }

        erase_element_prev(curr_node);
        task::Node::inc(curr_node);
    }
}

void task::list::unique() {
    task::Node* curr_node = head;
    while (curr_node != nullptr) {
        if (list_size <= 1)
            break; 

        while (list_size > 1 && 
            curr_node != tail && 
            curr_node->get_next_value() == curr_node->get()) {
            
            if (curr_node == head) {
                task::Node::inc(curr_node);
                this->pop_front();
                continue;
            }

            erase_element_next(curr_node);
        }

        task::Node::inc(curr_node);
    }
}

void task::list::sort() {
    *this = merge_sort(*this);
}

void task::list::erase_element_prev(task::Node* &elem) {
    task::Node* node_to_delete = elem;
    elem->prev_element->set_next_element(elem->next_element);
    elem->next_element->set_prev_element(elem->prev_element);

    task::Node::dec(elem);
    delete node_to_delete;
    list_size--;
}

void task::list::erase_element_next(task::Node* &elem) {
    task::Node* node_to_delete = elem;
    elem->prev_element->set_next_element(elem->next_element);
    elem->next_element->set_prev_element(elem->prev_element);

    task::Node::inc(elem);
    delete node_to_delete;
    list_size--;
}

task::list task::list::merge_sort(const task::list l) {
    if (l.size() <= 1)
        return l;
    
    task::list left, right;
    task::Node* curr_elem = l.head;


    for (std::size_t i = 0; i < (l.size() + 1) / 2; i++) {
        left.push_back(curr_elem->get());
        task::Node::inc(curr_elem);
    }

    for (std::size_t i = 0; i < l.size() / 2; i++) {
        right.push_back(curr_elem->get());
        task::Node::inc(curr_elem);
    }
    
    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

task::list task::list::merge(const task::list& a, const task::list& b) {
    task::list result;

    task::Node* curr_elem_a = a.head;
    task::Node* curr_elem_b = b.head;

    while (curr_elem_a != nullptr && curr_elem_b != nullptr) {
        if (curr_elem_a->get() <= curr_elem_b->get()) {
            result.push_back(curr_elem_a->get());
            task::Node::inc(curr_elem_a);
        } else {
            result.push_back(curr_elem_b->get());
            task::Node::inc(curr_elem_b);
        }

    }

    while (curr_elem_a != nullptr) {
        result.push_back(curr_elem_a->get());
        task::Node::inc(curr_elem_a);
    }

    while (curr_elem_b != nullptr) {
        result.push_back(curr_elem_b->get());
        task::Node::inc(curr_elem_b);
    }

    return result;
}