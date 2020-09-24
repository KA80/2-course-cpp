#include <iostream>
#include <vector>
#include <algorithm>


class Set {
    std::vector<int64_t> vec;

 public:
    Set() = default;
    explicit Set(const std::vector<int64_t>& vec) {
        for (auto i : vec) {
            Add(i);
        }
    }

    Set Union(const Set& Other) const {
        Set new_set(vec);
        for (auto i : Other.vec) {
            if (!Contains(i))
                new_set.Add(i);
        }
        return new_set;
    }

    Set Intersection(const Set& Other) const {
        Set new_set(vec);
        for (auto i : this->vec) {
            if (!Other.Contains(i))
                new_set.Remove(i);
        }
        return new_set;
    }

    Set Difference(const Set& Other) const {
        Set new_set(vec);
        for (auto i : Other.vec) {
            if (Contains(i))
                new_set.Remove(i);
        }
        return new_set;
    }

    Set SymmetricDifference(const Set& Other) const {
        Set first_set = Union(Other);
        Set second_set = Intersection(Other);
        return first_set.Difference(second_set);
    }

    void Add(int64_t value) {
        if (!Contains(value)) {
            vec.push_back(value);
            std::sort(vec.begin(), vec.end());
        }
    }

    void Remove(int64_t value) {
        if (Contains(value)) {
            vec.erase(std::find(
                    vec.begin(), vec.end(), value));
        }
    }

    bool Contains(int64_t value) const {
        auto result = std::find(vec.begin(), vec.end(), value);
        if (result != vec.end())
            return true;
        return false;
    }

    std::vector<int64_t> Data() const {
        return vec;
    }
};
