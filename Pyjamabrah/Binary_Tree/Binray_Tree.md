Binary Tree

- add 'A'
  - write to root and exit

- add 'B'
  - set to root->left and write and destory_queue()

- add'C'
  - enqueue root->left
  - write to root->left
  - destory queue --> free address of root->left

- add'D'
  - enqueue root->left (front)
  - enqueue root->right (end)
  - dequeue root->left and set as node
  - free front and set end as front 
  - write to node->left 
  - destory queue --> free address of front

- add'E'
  - enqueue root->left (front)
  - enqueue root->right  (end) -->(front)
  - dequeue root->left and set as node
  - free front and set end as front 
  - enqueue node->left (since its written) ( set this as end)
  - write to node->right
  - destory queue --> free address of front and end



Traverse

- Pre Order 
    - Root
    - Left Child
    - Right Child

- Inorder
    - Left Child
    - Root
    - Right Child

- Post Order
    - Right Child
    - Left Child
    - Root
 

- Result
    - Preorder : :A:  :B:  :D:  :H:  :E:  :C:  :F:  :G: 
    - Postorder : :G:  :F:  :C:  :E:  :H:  :D:  :B:  :A: 
    - Inorder : :H:  :D:  :B:  :E:  :A:  :F:  :C:  :G: 