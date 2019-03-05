#include "BinaryTree.h"
#include <stdlib.h>
#include <stdio.h>

BinaryTree *tree_init(void *elem, int (*comp)(void *, void *))
{
    if (comp == NULL || elem == NULL)
    {
        return NULL;
    }
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    if (tree == NULL)
    {
        fprintf(stderr, "Error: Could not initialize BinaryTree structure!\n");
        return NULL;
    }
    tree->elem = elem;
    tree->left = NULL;
    tree->right = NULL;
    tree->comp = comp;
    return tree;
}

static void free_struct(BinaryTree *node)
{
    if (node == NULL)
    {
        return;
    }
    BinaryTree *left = node->left;
    BinaryTree *right = node->right;
    free_struct(left);
    free_struct(right);
    free(node);
}

void tree_destroy(BinaryTree **tree)
{
    if (tree == NULL)
    {
        return;
    }
    free_struct(*tree);
    *tree = NULL;
}

void tree_insert(BinaryTree *tree, void *elem)
{
    if (tree == NULL || elem == NULL)
    {
        return;
    }
    if (tree->comp(elem, tree->elem) > 0)
    {
        if (tree->right == NULL)
        {
            tree->right = tree_init(elem, tree->comp);
        }
        else
        {
            tree_insert(tree->right, elem);
        }
    }
    else
    {
        if (tree->left == NULL)
        {
            tree->left = tree_init(elem, tree->comp);
        }
        else
        {
            tree_insert(tree->left, elem);
        }
    }
}

void *tree_get(BinaryTree *tree, void *elem)
{
    if (tree == NULL || elem == NULL)
    {
        return NULL;
    }
    if (tree->comp(elem, tree->elem) > 0)
    {
        if (tree->right != NULL)
        {
            return tree_get(tree->right, elem);
        }
    }
    else if (tree->comp(elem, tree->elem) < 0)
    {
        if (tree->left != NULL)
        {
            return tree_get(tree->left, elem);
        }
    }
    return tree->elem;
}

static BinaryTree *get_nearest(BinaryTree *curr)
{
    if (curr->right != NULL)
    {
        return get_nearest(curr->right);
    }
    else
    {
        return curr;
    }
}

static BinaryTree *delete_node(BinaryTree *curr, void *elem)
{
    if (curr == NULL)
    {
        return curr;
    }
    if (curr->comp(curr->elem, elem) > 0)
    {
        curr->left = delete_node(curr->left, elem);
    }
    else if (curr->comp(curr->elem, elem) < 0)
    {
        curr->right = delete_node(curr->right, elem);
    }
    else
    {
        if (curr->right == NULL)
        {
            BinaryTree *tmp = curr->left;
            free(curr);
            return tmp;
        }
        else if (curr->left == NULL)
        {
            BinaryTree *tmp = curr->right;
            free(curr);
            return tmp;
        }
        else
        {
            BinaryTree *tmp = get_nearest(curr->left);
            curr->elem = tmp->elem;
            curr->left = delete_node(curr->left, tmp->elem);
        }
    }
    return curr;
}

void tree_remove(BinaryTree **tree, void *elem)
{
    if (tree == NULL || elem == NULL)
    {
        return;
    }
    BinaryTree *curr = *tree;
    if (curr == NULL)
    {
        return;
    }
    *tree = delete_node(curr, elem);
}

void *tree_poll(BinaryTree **tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    BinaryTree *curr = *tree;
    if (curr == NULL)
    {
        return NULL;
    }
    void *elem = curr->elem;
    *tree = delete_node(curr, elem);
    return elem;
}

void *tree_peek(BinaryTree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    return tree->elem;
}

static int count = 0;

static void length(void *elem)
{
    count++;
}

size_t tree_size(BinaryTree *tree)
{
    count = 0;
    tree_foreach(tree, length);
    return count;
}

void tree_foreach(BinaryTree *tree, void (*f)(void *))
{
    if (tree == NULL || f == NULL)
    {
        return;
    }
    tree_foreach(tree->left, f);
    tree_foreach(tree->right, f);
    (*f)(tree->elem);
}