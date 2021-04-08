/**
 *  Morris inorder traversal 
 *  Time : O(n)
 *  Space : O(1) 
 */

/**
 * class Tree {
 *     public:
 *         int val;
 *         Tree *left;
 *         Tree *right;
 * };
 */

vector<int> solve(Tree* root) {
    vector<int> inorder;
    while (root) {
        if (!root->left) {
            // no left subtree exists so push root.val to inorder and move to right subtree
            inorder.push_back(root->val); 
            root = root->right;
        } else {
            // get rightmost node in left subtree
            Tree *pred = root->left;
            while (pred->right && pred->right != root) pred = pred->right; 

            if (pred->right == root) { // we are already done with left subtree
                inorder.push_back(root->val); // push root value to inorder
                pred->right = NULL; // unlink pred.right
                root = root->right; // move to right subtree
            } else { // Need to exlpore left subtree first
                pred->right = root; // link pred.right to root for future access
                root = root->left; // move further to left subtree
            }
        }
    }
    return inorder;
}