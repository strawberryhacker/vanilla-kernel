/// Copyright (C) StrawberryHacker

#include "dlist.h"
#include "panic.h"

#include <stddef.h>

/// Inserts a `node` in the first in the `dlist`
void dlist_insert_first(struct dlist_node* node, struct dlist* list) {
    // Check if the list contains the `node`
    if (dlist_search(node, list)) {
        panic("Node is in the list");
    }

    if (list->first) {
        node->next = list->first;
        node->prev = NULL;
        list->first->prev = node;
        list->first = node;
    } else {
        // List is empty
        node->next = NULL;
        node->prev = NULL;
        list->first = node;
        list->last = node;
    }
    list->size++;
}

/// Insert `node` last in the `dlist`
void dlist_insert_last(struct dlist_node* node, struct dlist* list) {
    // Check if the list contains the `node`
    if (dlist_search(node, list)) {
        panic("Node is in the list");
    }

    if (list->last) {
        node->prev = list->last;
        node->next = NULL;
        list->last->next = node;
        list->last = node;
    } else {
        // List is empty
        node->next = NULL;
        node->prev = NULL;
        list->first = node;
        list->last = node;
    }
    list->size++;
}

/// Inserts the `i_node` in the position after `a_node` in the `dlist` 
void dlist_insert_after(struct dlist_node* i_node, struct dlist_node* a_node,
    struct dlist* list) {

    // Check if the list contains the `i_node`
    if (dlist_search(i_node, list)) {
        panic("Node is in the list");
    }
    // Check if the list contains the `a_node`
    if (dlist_search(a_node, list) == 0) {
        panic("Node is in not the list");
    }
    
    // Check if the `a_node` is the last node
    if (a_node == list->last) {
        // The `i_node` should be inserted last in the list
        dlist_insert_last(i_node, list);
    } else {
        // Link the `i_node` with the node after `a_node`
        i_node->next = a_node->next;
        a_node->next->prev = i_node;

        // Link the `a_node` with the `i_node`
        a_node->next = i_node;
        i_node->prev = a_node;

        // Increment the list size
        list->size++;
    }
}

/// Inserts the `i_node` in the position before `b_node` in the `dlist` 
void dlist_insert_before(struct dlist_node* i_node, struct dlist_node* b_node,
    struct dlist* list) {

    // Check if the list contains the `i_node`
    if (dlist_search(i_node, list)) {
        panic("Node is in the list");
    }
    // Check if the list contains the `b_node`
    if (dlist_search(b_node, list) == 0) {
        panic("Node is in not the list");
    }

    // Check if the `b_node` is the first node
    if (b_node == list->first) {
        // The `i_node` should be inserted first in the list
        dlist_insert_first(i_node, list);
    } else {
        // Link the `i_node` with the node before `b_node`
        i_node->prev = b_node->prev;
        b_node->prev->next = i_node;

        // Link the `i_node` with the `b_node`
        i_node->next = b_node;
        b_node->prev = i_node;

        // Increment the list size
        list->size++;
    }
}

/// Removes the first node from a `dlist`
struct dlist_node* dlist_remove_first(struct dlist* list) {
    // First node
    struct dlist_node* first = NULL;
    if (list->first) {
        first = list->first;

        // Check if the list contains more than one node
        if (list->first->next) {
            // Remove the backward link from the second node
            first->next->prev = NULL;

            list->first = first->next;
        } else {
            // Only one node present
            list->first = NULL;
            list->last = NULL;
        }

        // Decrement the size
        if (list->size == 0) {
            panic("List error");
        }
        list->size--;
    } else {
        panic("List error");
    }

    return first;
}

/// Removes the last node from a `dlist` 
struct dlist_node* dlist_remove_last(struct dlist* list) {
    // Last element
    struct dlist_node* last = NULL;
    if (list->last) {
        // Check if the list contains more than one node
        last = list->last;

        if (list->last->prev) {
            // Remove the forward link from the second last node
            last->prev->next = NULL;

            list->last = last->prev;
        } else {
            list->last = NULL;
            list->first = NULL;
        }
        
        // Decrement the size
        if (list->size == 0) {
            panic("List error");
        }
        list->size--;
    } else {
        panic("List error");
    }

    return last;
}

/// Removes a node from a list. The `list` paramenter is needed since the 
/// node might be the first or the last element. In this case the `dlist->first`
/// and `dlist->last` has to be updated
struct dlist_node* dlist_remove(struct dlist_node* node, struct dlist* list) {
    // Check if the list contains the node
    if (dlist_search(node, list) == 0) {
        panic("Node is not in the list");
    }

    // If the node is either the first or the last element the size is 
    // automatically decremented
    if (node == list->first) {
        dlist_remove_first(list);
    } else if (node == list->last) {
        dlist_remove_last(list);
    } else {
        // The node to remove in not first and not last
        node->prev->next = node->next;
        node->next->prev = node->prev;

        // Decrement the size
        if (list->size == 0) {
            panic("List error");
        }
        list->size--;
    }

    return node;
}

/// Search after `node` in the `dlist`. If found it returns `1`, if not `0` 
u32 dlist_search(struct dlist_node* node, struct dlist* list) {
    struct dlist_node* iter = list->first;

    while (iter != NULL) {
        if (iter == node) {
            return 1;
        }
        iter = iter->next;
    }
    return 0;
}
