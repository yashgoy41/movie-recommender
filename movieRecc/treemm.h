#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>
#include <type_traits>

class Node;
template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator() {}
        Iterator(const Iterator& other) : m_cur(other.m_cur) {}
        Iterator(typename std::vector<ValueType>::iterator it_start, typename std::vector<ValueType>::iterator it_end ) : m_cur(it_start), m_end(it_end) {}
        ValueType& get_value() const
        {
            return *m_cur;
        }

        bool is_valid() const
        {
            if(m_cur == m_end){
                return false;
            }
            return true;
        }

        void advance()
        {
            m_cur++;            // Replace this line with correct code.
        }

      private:
        typename std::vector<ValueType>::iterator m_cur;
        typename std::vector<ValueType>::iterator m_end;
    };

    TreeMultimap() : m_root(nullptr)
    {
        // Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        deleteTree(m_root);
        // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        // Replace this line with correct code.
        // Tree is empty
        Node* newNode = new Node(key,value);
        if(m_root == nullptr){
           m_root = newNode;
            return;
        }
        // Traverse Right
        Node* curNode = m_root;
        while(true){
            if(key == curNode->m_key){
                curNode->m_vals.push_back(value);
                return;
            }
            if(key > curNode->m_key){
                if(curNode->m_rightChild == nullptr){
                    curNode->m_rightChild = newNode;
                    return;
                }
                else{
                    curNode = curNode->m_rightChild;
                }
            }
            else if(key < curNode->m_key){
                if(curNode->m_leftChild == nullptr){
                    curNode->m_leftChild = newNode;
                    return;
                }
                else{
                    curNode = curNode->m_leftChild;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* curNode = m_root;
        while(curNode != nullptr){
            if(key == curNode->m_key){
                return Iterator(curNode->m_vals.begin(), curNode->m_vals.end());
            }
            else if(key > curNode->m_key){
                curNode = curNode->m_rightChild;
            }
            else if(key < curNode->m_key){
                curNode = curNode->m_leftChild;
            }
        }
        return Iterator();
    }
  private:
    struct Node {
        KeyType m_key;
        std::vector<ValueType> m_vals;
        Node* m_leftChild;
        Node* m_rightChild;
        Node(const KeyType& key, const ValueType& value) {
            m_key = key;
            m_vals.push_back(value);
            m_leftChild = nullptr;
            m_rightChild = nullptr;
        }
    };
    Node* m_root; // root of the tree
    void deleteTree(Node* node) {
        if (node != nullptr) {
            // Recursively delete the left and right subtrees
            deleteTree(node->m_leftChild);
            deleteTree(node->m_rightChild);
            // Free the memory associated with the current node
            delete node;
        }
    }
};

#endif // TREEMULTIMAP_INCLUDED

