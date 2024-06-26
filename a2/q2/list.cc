#include "list.h"
#include <utility>

List::Node::~Node() { delete next; }

void List::swap(List &other) {
  std::swap(other.head, head);
  std::swap(other.count, count);
}

List::iterator::iterator(Node *location) : location{location} {}
List::iterator &List::iterator::operator++() {
  location = location->next;
  return *this;
}

const std::string &List::iterator::operator*() const { return location->value; }

bool List::iterator::operator!=(const List::iterator &other) const {
  return location != other.location;
}

List::List() : head{nullptr}, count{0} {}
List::~List() { delete head; }

List::iterator List::begin() const { return iterator(head); }
List::iterator List::end() const { return iterator(nullptr); }

void List::push_front(const std::string &value) {
  head = new Node{head, value};
  ++count;
}

void List::pop_front() {
  if (head) {
    --count;
    Node *tmp = head;
    head = head->next;
    tmp->next = nullptr;
    delete tmp;
  }
}

size_t List::size() const { return count; }
