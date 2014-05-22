// BinaryTree.java
//
// nonrecursive inorder traversal of binary tree

public class BinaryTree<T> {
    private Node<T> root;

    private Node<T> getNext(Node<T> node) {
        return null;
    }

    public BinaryTree(T value) {
        root = new Node(value);
    }

    public Node<T> getRoot() {
        return root;
    }

    public Node<T> addLeft(Node<T> parent, T value) {
        Node node = new Node(value);
        parent.left = node;
        node.parent = parent;
        return node;
    }

    public Node<T> addRight(Node<T> parent, T value) {
        Node node = new Node(value);
        parent.right = node;
        node.parent = parent;
        return node;
    }

    public void print() {
        printHelper(root);
    }

    private void printHelper(Node root) {
        if (root == null) return;
        printHelper(root.left);
        System.out.print(" " + root.getValue() + " ");
        printHelper(root.right);
    }

    public void inOrderTraversal() {
        Node<T> start = root;
        while (start.left != null) {
            start = start.left;
        }

        while (start != null) {
            System.out.print(" " + start.getValue() + " ");
            // get next
            // case 1: start has right child
            if (start.right != null) {
                start = start.right;
                while (start.left != null) {
                    start = start.left;
                }
            } else if (start.parent != null && start.parent.left == start) {
            // case 2: start is left child of its parent
                start = start.parent;
            } else if (start.parent != null && start.parent.right == start){
            // case 3: start is right child of its parent
                while (start.parent != null && start.parent.right == start) {
                    start = start.parent;
                }
                if (start.parent == null) break;
                else {
                    assert start == start.parent.left;
                    start = start.parent;
                }
            } else {
                assert start == root && start.right == null;
                break;
            }
        }
    }

    public static void main(String[] args) {
        {
            BinaryTree<Integer> tree = new BinaryTree<Integer>(10);
            Node<Integer> root = tree.getRoot();
            Node lchild = tree.addLeft(root, 5);
            Node rchild = tree.addRight(root, 20);
            Node leaf = tree.addRight(lchild, 7);
            Node leaf2 = tree.addRight(rchild, 30);
            tree.print();
            System.out.println();
            tree.inOrderTraversal();
            System.out.println();
        }
    }
}

class Node<T> {
    T value;
    Node<T> left, right, parent;

    Node(T value) {
        this.value = value;
        this.left = this.right = this.parent = null;
    }

    T getValue() {
        return value;
    }
}


// TODO: move Node into inner of BinaryTree
// serialize and deserialize of binary tree
