#ifndef LIST_H
#define LIST_H
#include <string>
#include <utility>
#include <cstddef>
template<typename T> class List {
    struct Node {
        T data;
        Node* next;
    }* head{};
    std::size_t sz{};

public:
    template<typename ReturnType> class MyIterator {
        Node* ptr;
        explicit MyIterator(Node* ptr) : ptr{ptr} {}

    public:
        MyIterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        ReturnType& operator*() const {
            return ptr->data;
        }

        bool operator!=(const MyIterator& other) const {
            return ptr != other.ptr;
        }

        friend List;
    };

    List() {}
    ~List() {
        // Destroy by removing all elements (pop frees the memory)
        while (sz) pop();
    }

    List(const List<T>& other) : head{other.head ? new Node{*other.head} : nullptr}, sz{other.sz} {
        for (auto curr = head, currOther = other.head; curr && curr->next; curr = curr->next, currOther = currOther->next)
            curr->next = new Node{*currOther->next};
    }

    List(List<T>&& other) : head{other.head}, sz{other.sz} {
        other.sz = 0;
        other.head = nullptr;
    }

    List& operator=(const List& other) {
        return *this = List{other}; // delegate to move assignment after making copy
    }

    List& operator=(List&& other) {
        std::swap(head, other.head);
        std::swap(sz, other.sz);
        return *this;
    }

    using Iterator = MyIterator<T>;
    using ConstIterator = MyIterator<const T>;

    Iterator begin() {
        return Iterator{head};
    }

    Iterator end() {
        return Iterator{nullptr};
    }

    ConstIterator cbegin() const {
        return ConstIterator{head};
    }

    ConstIterator cend() const {
        return ConstIterator{nullptr};
    }

    void push(const T& data) {
        head = new Node{data, head};
        ++sz;
    }

    void pop() {
        if (head) {
            --sz;
            auto origHead = head;
            head = head->next;
            delete origHead;
        }
    }

    std::size_t size() const {
        return sz;
    }
};
#endif
