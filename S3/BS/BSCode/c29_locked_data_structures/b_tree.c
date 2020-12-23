// In Zusammenarbeit von Vlad Bratulescu, Daniel Wollmann und Marco Mollo

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define ORDER 5

typedef struct __node_t {
    int num; // number of keys
    int keys[ORDER - 1];
    struct __node_t children[ORDER];
    pthread_mutex_t lock;
    struct __node_t *parent;
} node_t;

typedef struct __btree_t {
    node_t *root;
    pthread_mutex_t lock;
} btree_t;

void Node_Init(node_t *node, node_t *parent) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->num = 0;
    new->parent = parent;
    pthread_mutex_init(&new->lock, NULL);
    node = new;
}

void Btree_Init(btree_t *btree) {
    btree_t *new = malloc(sizeof(btree_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    pthread_mutex_init(&new->lock, NULL);
    Node_Init(new->root, NULL);
    for (size_t i = 0; i < ORDER; i++)
    {
        new->root->children[i] = NULL;
    }
    btree = new;
}

node_t *search(node_t *node, int key) {
    node_t *remainedAtNode = node; // failure, key was not found, left at node
    pthread_mutex_lock(&node->lock);
    for (size_t i = 0; i <= ORDER - 1; i++)
    {
        int nodeKey = node->keys[i];
        if (key == nodeKey) {
            remainedAtNode = NULL; // success, key was found
            break;
        } else if(nodeKey > key || i == ORDER - 1) {
            remainedAtNode = search(node->children[i], key);
            break;
        }
    }
    pthread_mutex_unlock(&node->lock);
    return remainedAtNode;
}

int insert(btree_t *btree, int key) {
    int retVal = 0; // insert success
    pthread_mutex_lock(&btree->lock);
    node_t *remainedAtNode = search(btree->root, key);
    if (remainedAtNode == NULL) { // Was key found?
        retVal = -1; // no insert happened
    } else {
        if (remainedAtNode->num + 1 > ORDER - 1) { // key overflow?
            // TODO: add parent to a node?
            // for each node k from remainedAtNode to btree->root
                // if (node has key overflow)
                    // use split operation for k
                // else
                    // break
        } else { // no key overflow
            remainedAtNode->keys[remainedAtNode->num] = key;
            remainedAtNode->num += 1;
        }
    }
    pthread_mutex_unlock(&btree->lock);
    return retVal;
}
