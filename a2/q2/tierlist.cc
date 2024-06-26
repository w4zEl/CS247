#include "tierlist.h"
#include <utility>

void TierList::swap(TierList& other) {
    std::swap(tiers, other.tiers);
    std::swap(tierCount, other.tierCount);
    std::swap(reserved, other.reserved);
}

void TierList::enlarge() {
    reserved = 2 + 2 * std::max(reserved, tierCount);
    List** newTiers = new List*[reserved];
    for (size_t i = 0; i < reserved; ++i) {
        newTiers[i] = nullptr;
    }
    for (size_t i = 0; i < tierCount; ++i) {
        newTiers[i] = tiers[i];
    }
    delete[] tiers;
    tiers = newTiers;
}

TierList::TierList() : tiers{nullptr}, tierCount{0}, reserved(0) {}
TierList::~TierList() {
    if (tiers) {
        for (size_t i = 0; i < tierCount; ++i) {
            delete tiers[i];
        }
    }
    delete[] tiers;
}

void TierList::push_back_tier() {
    // Need at least 1 extra as sentinel.
    if (tierCount + 1 >= reserved) {
        enlarge();
    }
    tiers[tierCount++] = new List;
}
void TierList::pop_back_tier() {
    if (tierCount > 0) {
        delete tiers[--tierCount];
        tiers[tierCount] = nullptr;
    }
}

void TierList::push_front_at_tier(size_t tier, const std::string& entry) {
    tiers[tier]->push_front(entry);
}
void TierList::pop_front_at_tier(size_t tier) {
    tiers[tier]->pop_front();
}

size_t TierList::tierSize() const { return tierCount; }
size_t TierList::size() const {
    size_t result = 0;
    for (size_t i = 0; i < tierCount; i++) {
        result += tiers[i]->size();
    }
    return result;
}

TierList::iterator::iterator(std::size_t tierIndex, List::iterator itemIt, const TierList* tierList) : tierIndex{tierIndex}, itemIt{itemIt}, tierList{tierList} {}

TierList::value_type TierList::iterator::operator*() const {
    return {tierIndex, *itemIt};
}

TierList::iterator& TierList::iterator::operator++() {
    for (++itemIt; !(itemIt != tierList->tiers[tierIndex]->end()) && ++tierIndex < tierList->tierCount;)
        itemIt = tierList->tiers[tierIndex]->begin();
    return *this;
}

// Returns end iterator if there are no non-empty tiers to move to (required behavior is undefined in that case)
TierList::iterator TierList::iterator::operator<<(int bk) const {
	iterator it{tierIndex - bk, tierList->tiers[tierIndex - bk]->begin(), tierList};
	return tierList->tiers[tierIndex - bk]->size() ? it : tierIndex - bk ? it << 1 : tierList->end();
}

TierList::iterator TierList::iterator::operator>>(int fwd) const {
    iterator it{tierIndex + fwd, tierIndex + fwd < tierList->tierCount ? tierList->tiers[tierIndex + fwd]->begin() : List{}.end(), tierList};
	return it.tierIndex >= tierList->tierCount || it.itemIt != List{}.end() ? it : it >> 1;
}

bool TierList::iterator::operator!=(const iterator& other) const {
    return tierList != other.tierList || tierIndex != other.tierIndex || itemIt != other.itemIt;
}

TierList::iterator TierList::begin() const {
    // right shift 0 to ensure iterator starts at first non-empty tier
    return tierCount ? iterator{0, tiers[0]->begin(), this} >> 0 : end();
}

TierList::iterator TierList::end() const {
    return {tierCount, List{}.end(), this};
}
