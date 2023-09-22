/*
 The BinarySearch tree struct is a collection of Nodes, each containing pointers to no more than two children.
 Children with data values less than the parent are stored to the left (previous), and those with values grater than the parent are stored to the right (next).
 Since the data type of the Nodes is unknown, users must specify their own comparison function for the tree in its constructor.
 Note that these functions should compare the stored data - not the Nodes themselves.
 Some generic comparison functions are provided for convenience.
 */
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef struct BinarySearchTree {
    // Head points to the top-most node in the tree.
    struct Node *head;
    
    /*PUBLIC MEMBER METHODS */
    // The compare function is specified by the user and is used to compare the data of two nodes.
    // It must take two void pointers as arguments and return 1, -1, or 0.
    int (*compare)(void *data_one, void *data_two);
    // The search function finds a node in the tree, returning its data or NULL if not found.
    void * (*search)(struct BinarySearchTree *tree, void *data);
    // The insert function adds a new node to the tree.  Since memory allocation is handled by the node constructor, the size of this node's data must be specified.
    void (*insert)(struct BinarySearchTree *tree, void *data, unsigned long size);
} BinarySearchTree;

// MARK: CONSTRUCTORS
// The BinarySearchTree_Create takes the desired compare function as its only argument.
BinarySearchTree BinarySearchTree_Create(int (*compare)(void *data_one, void *data_two));
void BinarySearchTree_Destroy(BinarySearchTree tree);

// MARK: PUBLIC HELPER FUNCTIONS
int BinarySearchTree_int_compare(void *data_one, void *data_two);
int BinarySearchTree_float_compare(void *data_one, void *data_two);
int BinarySearchTree_char_compare(void *data_one, void *data_two);
int BinarySearchTree_str_compare(void *data_one, void *data_two);


#endif//_BINARY_SEARCH_TREE_H_