#include "sort.h"
namespace sort {
    void sort_strings(list<string> &listing) {
        int k = listing.size();
        list<string>::iterator first = listing.begin();
        list<string>::iterator second = listing.end();
        --second;
        for (int i = 0; i < k; ++i) {
            for (int j = k - 1; j > i; --j) {
                if (*first > *second) {
                    swap(*first, *second);
                }
                --second;
            }

            second = listing.end();
            --second;
            ++first;
        }
    }
}
