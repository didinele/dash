#include <stddef.h>
#include <stdint.h>

namespace dash {
// 10MB
#define DASH_KERNEL_BUFFER_SIZE 10 * 1024 * 1024

    // TODO: Write a little constructor to avoid error-prone data_start
    struct Node {
        Node *next;
        uint8_t *data_start;
        size_t data_size;
        bool free;
    };

    class KernelHeap {
      public:
        KernelHeap();
        [[nodiscard]] void *allocate(size_t size);

      private:
        Node *f_Head;
        uint8_t f_Data[DASH_KERNEL_BUFFER_SIZE];
    }; // namespace dash
} // namespace dash
