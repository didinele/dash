#include <stddef.h>
#include <stdint.h>

namespace dash {
// 10MB
#define DASH_KERNEL_BUFFER_SIZE 10 * 1024 * 1024

    // TODO: Remove error-prone data_start and instead use pointer math to
    // TODO: figure out data start
    struct Node {
        Node(size_t size, Node *next) : next(next), data_size(size), free(true)
        {
        }

        Node(size_t size) : Node(size, nullptr)
        {
        }

        uint8_t *get_data()
        {
            return reinterpret_cast<uint8_t *>(this) + sizeof(Node);
        }

        Node *next;
        size_t data_size;
        bool free;
    };

    // TODO: Make this a proper singleton
    class KernelHeap {
      public:
        KernelHeap();
        [[nodiscard]] void *allocate(size_t size);

      private:
        Node *f_Head;
        uint8_t f_Data[DASH_KERNEL_BUFFER_SIZE];
    }; // namespace dash
} // namespace dash
