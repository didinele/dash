#include "kernel_heap.hpp"

namespace dash {
    KernelHeap::KernelHeap()
    {
        f_Head = reinterpret_cast<Node *>(f_Data);
        *f_Head = Node{nullptr, f_Data + sizeof(Node), sizeof(f_Data), true};
    }

    void *KernelHeap::allocate(size_t size)
    {
        Node *free_node = nullptr;

        if (f_Head->free && f_Head->data_size > size) {
            free_node = f_Head;
        }
        else {
            Node *node = f_Head;

            while (node->next != nullptr) {
                node = node->next;
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
        auto next_node_ptr = reinterpret_cast<Node *>(free_node->data_start +
                                                      free_node->data_size);

        *next_node_ptr =
            Node{nullptr,
                 free_node->data_start + free_node->data_size + sizeof(Node),
                 size, true};
        free_node->next = next_node_ptr;
        free_node->free = false;

        return free_node->data_start;
    }
} // namespace dash
