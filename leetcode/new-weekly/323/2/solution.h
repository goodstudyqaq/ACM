#if __has_include("../../utils/cpp/help.hpp")
#include "../../utils/cpp/help.hpp"
#endif

class Allocator {
   public:
    Allocator(int n) {
    }

    int allocate(int size, int mID) {
    }

    int free(int mID) {
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */