#ifndef SET_UTILS_H
#define SET_UTILS_H

#include <vector>

namespace utils::set_utils {

    template<typename Tset>
    Tset set_intersection(std::vector<Tset> sets) {
        Tset intersection_set;
        Tset prev;
        for (const auto &set: sets) {
            for (const auto &element: set) {
                if (prev.contains(element)) {
                    intersection_set.insert(element);
                }
                prev.insert(element);
            }
        }
        return intersection_set;
    };

    template<typename Tset>
    Tset set_unification(std::vector<Tset> sets) {
        Tset result;
        for (const auto &set: sets) {
            for (const auto &element: set) {
                result.insert(element);
            }
        }
        return result;
    }

    template<typename Tset>
    Tset set_difference(Tset a, Tset b) {
        for (const auto &be: b) {
            a.erase(be);
        }
        return a;
    }

    template<typename Tset>
    bool set_equal(Tset a, Tset b) {
        if (a.size() != b.size()) {
            return false;
        }
        for (const auto &ai: a) {
            b.erase(ai);
        }
        return b.empty();
    }


} // utils::set_utils

#endif // SET_UTILS_H