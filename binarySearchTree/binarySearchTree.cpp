    #include <iostream>
    #include <string>
    using namespace std;

    struct TreeNode{
        int data;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int data){
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    class BinaryTree{
        private:
            TreeNode *root;
            int size = 0;

            bool insert(int value, TreeNode*& node){

                if(node == nullptr){
                    node = new TreeNode{value};
                    size++;
                    return true;
                }

                if(value < node->data){
                    return insert(value, node->left);
                }
                else if(value > node->data){
                    return insert(value, node->right);
                }
                else{
                    return false;
                }
                
            }
            bool search(int value, TreeNode*& node){

                if(node == nullptr){
                    return false;
                }

                if(value == node->data){
                    return true;
                }
                
                if(value < node->data){
                    return search(value, node->left);
                }
                else if(value > node->data){
                    return search(value, node->right);
                }
                else{
                    return false;
                }

            }
            TreeNode* predecessor(TreeNode* node){

                if(node->right == nullptr){
                    return node;
                }

                return predecessor(node->right);

            }
            bool remove(int value, TreeNode*& node){

                // search value:
                if(node == nullptr){ // if reached the end without finding it
                    return false;
                }

                // node not null
                if(value < node->data){ // if value less then crrNode->data, goes left
                    return remove(value, node->left);
                }
                if(value > node->data){ // if value more then crrNode->data, goes right
                    return remove(value, node->right);
                }
                
                // value == node->data (found):
                // no children(leaf) case:
                if(node->left == nullptr && node->right == nullptr){ // leaf node, no children
                    delete node;
                    node = nullptr;
                    size--;
                    return true;
                }

                // one-child case:
                if(node->left != nullptr && node->right == nullptr){ // one child (left)
                    TreeNode *temp = node->left;
                    delete node;
                    node = temp;
                    size--;
                    return true;
                }
                if(node->right != nullptr && node->left == nullptr){ // one child (right)
                    TreeNode *temp = node->right;
                    delete node;
                    node = temp;
                    size--;
                    return true;
                }

                // two children case:
                TreeNode *temp = predecessor(node->left);
                node->data = temp->data;
                return remove(temp->data, node->left);
                
            }
            void inorderPrint(TreeNode* node){

                if(node == nullptr){
                    return;
                }

                inorderPrint(node->left);
                cout << node->data << " ";
                inorderPrint(node->right);

            }
            void preorderPrint(TreeNode* node){
                
                if(node == nullptr){
                    return;
                }

                cout << node->data << " ";
                preorderPrint(node->left);
                preorderPrint(node->right);

            }
            void postorderPrint(TreeNode* node){

                if(node == nullptr){
                    return;
                }

                postorderPrint(node->left);
                postorderPrint(node->right);
                cout << node->data << " ";

            }
            void destructorRec(TreeNode*& node){

                if(node == nullptr){
                    return;
                }

                destructorRec(node->left);
                destructorRec(node->right);

                delete node;
                node = nullptr;

            }
            int getHeight(TreeNode* node){

                int lh = 0;
                int rh = 0;

                if(node == nullptr){
                    return 0;
                }

                lh += getHeight(node->left);
                rh += getHeight(node->right);            

                return max(lh, rh) + 1;

            }
        public:
            bool insert(int value){
                return insert(value, root);
            }
            bool search(int value){
                return search(value, root);
            }
            bool remove(int value){
                return remove(value, root);
            }
            void inorderPrint(){
                if(root == nullptr){
                    cout << "There are no nodes" << endl;
                    return;
                }
                inorderPrint(root);
                cout << endl;
            }
            void preorderPrint(){
                if(root == nullptr){
                    cout << "There are no nodes" << endl;
                    return;
                }
                preorderPrint(root);
                cout << endl;
            }
            void postorderPrint(){
                if(root == nullptr){
                    cout << "There are no nodes" << endl;
                    return;
                }
                postorderPrint(root);
                cout << endl;
            }
            int getHeight(){
                if(root == nullptr){
                    cout << "There are no nodes" << endl;
                    return 0;
                }
                return getHeight(root);
            }
            int getSize(){
                return size;
            }
        BinaryTree(){
            this->root = nullptr;
            this->size = 0;
        }
        ~BinaryTree(){
            destructorRec(root);
        }
    };

    int menu();
    int inputValue();

    int main(){

        BinaryTree bst;

        while(true){
            int option = menu();

            switch(option){
                case 1:
                    if(bst.insert(inputValue())){
                        cout << "Insert Succesfull" << endl;
                    }
                    else{
                        cout << "Can't insert duplicates" << endl;
                    }
                    break;
                case 2:
                    if(bst.search(inputValue())){
                        cout << "Found" << endl;
                    }
                    else{
                        cout << "Node not found" << endl;
                    }
                    break;
                case 3:
                    if(bst.remove(inputValue())){
                        cout << "Node removed" << endl;
                    }
                    else{
                        cout << "Node not found" << endl;
                    }
                    break;
                case 4:
                    bst.inorderPrint();
                    break;
                case 5:
                    bst.preorderPrint();
                    break;
                case 6:
                    bst.postorderPrint();
                    break;
                case 7:
                    {int h = bst.getHeight();
                    if(h != 0){
                        cout << "The tree's height is " << h << endl;
                    }}
                    break;
                case 8:
                    cout << "Size: " << bst.getSize() << endl;
                    break;
                case 0:
                    cout << "Exiting...";
                    return 0;
            }
        }

        return 0;

    }
    int menu(){

        cout << "==============================" << endl;
        cout << "      Binary Search Tree      " << endl;
        cout << "==============================" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Inorder Traversal" << endl;
        cout << "5. Preorder Traversal" << endl;
        cout << "6. Postorder Traversal" << endl;
        cout << "7. Get Height" << endl;
        cout << "8. Get Size" << endl;
        cout << "0. Exit" << endl;
        cout << "==============================" << endl;

        int option;
        while(true){
            cout << "Choose an option: ";
            cin >> option;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Option" << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(option < 0 || option > 8){
                cout << "Invalid Option" << endl;
                continue;
            }

            return option;

        }

    }
    int inputValue(){

        int n;
        while(true){
            cout << "Enter a number: ";
            cin >> n;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Input" << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            return n;
        }
    }

