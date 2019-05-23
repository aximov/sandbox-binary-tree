#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  Node* parent;
};

struct Tree {
  Node* root;
};

void inorderTreeWalk(Node* node){
  if (node != nullptr) {
    inorderTreeWalk(node->left);
    std::cout << node->key << std::endl;
    inorderTreeWalk(node->right);
  }
}

Node* treeSearch(Node* node, int key) {
  if (node == nullptr || key == node->key) {
    return node;
  }
  if (key < node->key) return treeSearch(node->left, key);
  else return treeSearch(node->right, key);
}

Node* iterativeTreeSearch(Node* node, int key) {
  while (node != nullptr && key != node->key) {
    if (key < node->key) node = node->left;
    else node = node->right;
  }
  return node;
}

void treeInsert(Tree* tree, Node* node_new) {
  Node* node_trailing = nullptr;
  Node* node = tree->root;

  while (node != nullptr) {
    node_trailing = node;
    if (node_new->key < node->key) node = node->left;
    else node = node->right;
  }

  node_new->parent = node_trailing;

  if (node_trailing == nullptr) tree->root = node_new;
  else if (node_new->key < node_trailing->key) node_trailing->left = node_new;
  else node_trailing->right = node_new;
}

void transplant(Tree* tree, Node* node_a, Node* node_b) {
  if (node_a->parent == nullptr) tree->root = node_b;
  else if (node_a == node_a->parent->left) node_a->parent->left = node_b;
  else node_a->parent->right = node_b;

  if (node_b != nullptr) node_b->parent = node_a->parent;
}

Node* treeMinimum(Node* node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

void treeDelete(Tree* tree, Node* node) {
  if (node->left == nullptr) transplant(tree, node, node->right);
  else if (node->right == nullptr) transplant(tree, node, node->left);
  else {
    Node* node_next = treeMinimum(node->right);

    if (node_next->parent != node) {
      transplant(tree, node_next, node_next->right);
      node_next->right = node->right;
      node_next->right->parent = node_next;
    }

    transplant(tree, node, node_next);
    node_next->left = node->left;
    node_next->left->parent = node_next;
  }
}

int main() {
  Tree t {nullptr};
  Node n {1, nullptr, nullptr, nullptr};
  treeInsert(&t, &n);

  inorderTreeWalk(t.root);

  if(iterativeTreeSearch(t.root, 1) != nullptr) std::cout << "Yes" << std::endl;
  else std::cout << "No" << std::endl;

  if(iterativeTreeSearch(t.root, 0) != nullptr) std::cout << "Yes" << std::endl;
  else std::cout << "No" << std::endl;

  auto node_1 = iterativeTreeSearch(t.root, 1);
  treeDelete(&t, node_1);
  if(iterativeTreeSearch(t.root, 1) != nullptr) std::cout << "Yes" << std::endl;
  else std::cout << "No" << std::endl;

  return 0;
}