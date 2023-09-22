#include "BinarySearchTree.h"
#include "Node/Node.h"

#include <stdlib.h>
#include <string.h>

Node * iterate_bst(BinarySearchTree *tree, Node *cursor, void *data, int *direction);
void recursive_tree_destruction(Node *node);

void * search_bst(BinarySearchTree *tree, void *data);
void insert_bst(BinarySearchTree *tree, void *data, unsigned long size);

BinarySearchTree BinarySearchTree_Create(int (*compare)(void *data_one, void *data_two)) {
    BinarySearchTree tree;
    tree.head = NULL;
    tree.compare = compare;
    tree.search = search_bst;
    tree.insert = insert_bst;
    return tree;
}

void BinarySearchTree_Destroy(BinarySearchTree tree) {
    recursive_tree_destruction(tree.head);
}

Node * iterate_bst(BinarySearchTree *tree, Node *cursor, void *data, int *direction)
{
    // Compare the cursor's data to the desired data.
    if (tree->compare(cursor->data, data) == 1)
    {
        // Check if there is another node in the chain to be tested.
        if (cursor->next)
        {
            // Recursively test the next (right) node.
            return iterate_bst(tree, cursor->next, data, direction);
        }
        else
        {
            // Set the direction pointer to reflect the next position is desired (moving right).
            *direction = 1;
            // Return the cursor.
            return cursor;
        }
    }
    // Alternative outcome of the compare.
    else if (tree->compare(cursor->data, data) == -1)
    {
        // Check if there is another node in the chain to be tested.
        if (cursor->previous)
        {
            // Recursively test the previous (left) node.
            return iterate_bst(tree, cursor->previous, data, direction);
        }
        else
        {
            // Set the direction pointer to reflect the previous position is desired (moving left).
            *direction = -1;
            return cursor;
        }
    }
    // The two data values are equal.
    else
    {
        // Set direction.
        *direction = 0;
        // Return the node.
        return cursor;
    }
}

void recursive_tree_destruction(Node *node)
{
    if (node->previous)
    {
        recursive_tree_destruction(node->previous);
    }
    if (node->next)
    {
        recursive_tree_destruction(node->next);
    }
    Node_Destroy(node);
}

// The search function utilizes the iterate function to test if a given node exists in the tree.
// If the node is found, its data is returned.  Otherwise, NULL is returned.
void * search_bst(BinarySearchTree *tree, void *data)
{
    // Set the direction int pointer.
    int direction = 0;
    // Utilize iterate to find the desired position.
    Node *cursor = iterate_bst(tree, tree->head, data, &direction);
    // Test if the found node is the desired node, or an adjacent one.
    if (direction == 0)
    {
        return cursor->data;
    }
    else
    {
        return NULL;
    }
}

// The insert function adds new nodes to the tree by finding their proper position.
void insert_bst(BinarySearchTree *tree, void *data, unsigned long size)
{
    // Check if this is the first node in the tree.
    if (!tree->head)
    {
        tree->head = Node_Create_Pointer(data, size);
    }
    else
    {
        // Set the direction int pointer.
        int direction = 0;
        // Find the desired position.
        Node *cursor = iterate_bst(tree, tree->head, data, &direction);
        // Check if the new node should be inserted to the left or right.
        if (direction == 1)
        {
            cursor->next = Node_Create_Pointer(data, size);
        }
        else if (direction == -1)
        {
            cursor->previous = Node_Create_Pointer(data, size);
        }
        // Duplicate nodes will not be added.
    }
}


int binary_search_tree_str_compare(void *data_one, void *data_two)
{
    int comparison = strcmp(data_one, data_two);
    
    if (comparison > 0)
    {
        return 1;
    }
    else if (comparison < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}