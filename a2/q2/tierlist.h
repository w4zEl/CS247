#ifndef TIERLIST_H
#define TIERLIST_H
#include "list.h"
#include <string>
#include <cstddef>
class TierList {
    List** tiers;
    std::size_t tierCount;
    std::size_t reserved;

    void swap(TierList& other);
    void enlarge();

public:
    // Default constructor and destructor for a TierList.
    // The default constructor should initalize an empty tier list.
    TierList();
    ~TierList();

    // Adds/removes a tier at the end of the tier list.
    // Tiers are indexed starting at 0.  Runs in time
    // at most _linear in the number of tiers_, but _not_ in the number
    // of elements.
    void push_back_tier();
    void pop_back_tier();

    // Adds/removes an element at the front of the given tier.
    // Must run in constant time.
    void push_front_at_tier(std::size_t tier, const std::string& entry);
    void pop_front_at_tier(std::size_t tier);

    // Returns the number of tiers.  Runs in constant time.
    std::size_t tierSize() const;
    // Returns the number of elements.  Can run in time
    // up to linear in the number of tiers.
    std::size_t size() const;

public:
    struct value_type {
        std::size_t tier;
        std::string entry;
    };
    class iterator {
        friend TierList;
        std::size_t tierIndex;
        List::iterator itemIt;
        const TierList* tierList;
        iterator(std::size_t tierIndex, List::iterator itemIt, const TierList* tierList);

    public:
        // Returns a value_type instance, containing
        // - a) the tier the item that the iterator points to lives at.
        // - b) the item the iterator points to
        value_type operator*() const;

        iterator& operator++();

        // New iterator operators which return a iterator pointing to the
        // start of the tier bk elements behind/fwd elements later
        // of the tier the iterator is currently on.
        //
        // If said tier is empty, the iterator moves back/forward to the next
        // non-empty tier.
        iterator operator<<(int bk) const;
        iterator operator>>(int fwd) const;

        bool operator!=(const iterator& other) const;
    };
    iterator begin() const;
    iterator end() const;
};
#endif
