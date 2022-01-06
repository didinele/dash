#include "kernel_heap.hpp"

namespace dash {
    KernelHeap::KernelHeap()
    {
        f_Head = reinterpret_cast<Node *>(f_Data);
        *f_Head = Node(sizeof(f_Data));
    }

    void *KernelHeap::allocate(size_t size)
    {
        Node *free_node = nullptr;

        if (f_Head->free && f_Head->data_size >= size) {
            free_node = f_Head;
        }
        else {
            Node *node = f_Head;

            while (node->next != nullptr) {
                node = node->next;
                // TODO: As this is right now, it's possible we allocate more
                // TODO: than the user asked for.
                // TODO: This isn't really a problem, the user shouldn't be
                // TODO: going over what they asked for
                // TODO: the issue is that it's a total waste of memory. That
                // TODO: whole oversized block is
                // TODO: going to be marked as not free, and it won't be used
                // TODO: for a future allocation
                if (node->free && node->data_size >= size) {
                    free_node = node;
                    break;
                }
            }
        }

        if (free_node == nullptr) {
            // TODO: Try defragging and re-attempting the allocation
            return nullptr;
        }

        free_node->data_size = size;
        auto next_node_ptr = reinterpret_cast<Node *>(free_node->get_data() +
                                                      free_node->data_size);

        *next_node_ptr = Node(size);
        free_node->next = next_node_ptr;
        free_node->free = false;

        return free_node->get_data();
    }

    void KernelHeap::free(void *ptr)
    {
        // Ptr should be pointing to be the start of a data block, right
        // before a node
        auto node = reinterpret_cast<Node *>(ptr) - 1;
        node->free = true;
    }
} // namespace dash
