# ConsoleTrees

Console trees is a C library for binary tree visualization in terminal, includes some methods for working
with binary trees.
![ConsoleTrees screenshot 1](https://github.com/RikiTikkiTavi/ConsoleTrees/blob/docs/docs/images/Screen1.png)
![ConsoleTrees screenshot 1](https://github.com/RikiTikkiTavi/ConsoleTrees/blob/docs/docs/images/Screen2.png)

## Table of contents:
[Installation](https://github.com/RikiTikkiTavi/ConsoleTrees#installation) <br>
[Usage guide](https://github.com/RikiTikkiTavi/ConsoleTrees#usage--guide) <br>
[Types](https://github.com/RikiTikkiTavi/ConsoleTrees#types) <br>


## Installation

Clone library to your project folder:
```bash
git clone https://github.com/RikiTikkiTavi/ConsoleTrees.git
```

#### Using CMake:
In your CMakeLists add:

If you want use static library:
```
target_link_libraries(YourProjectName ${CMAKE_SOURCE_DIR}/ConsoleTrees/src/build/static/ConsoleTrees.a)
 ```
If you want use dynamic/shared library:
 ```
 ```

### Using GCC

If you want use static library:
```bash
gcc -o test.out test.c path/to/.../ConsoleTrees/src/build/static/ConsoleTrees.a
```

If you want use dynamic/shared library:
 ```
 ```

## Usage  guide

Include ConsoleTrees.h:
```c
#include "./path/to/.../ConsoleTrees/src/lib/ConsoleTrees.h"
```

   #### Tree visualization:
```c
void ct_visualize_tree(ct_tree t, int step_v0, char *val_to_string(void *val));
```

Accepts 3 arguments: <br>
```ct_tree t``` - root of tree <br/>
```int step_v0```  - initial margin between 2 vertices (recommend ```step_v0 = 5 ``` ) <br/>
```char *val_to_string(void *val)``` - pointer on function to convert value of tree node to string <br/>

So: <br>
1: You must convert your tree to following type, declared in /ConsoleTrees/src/lib/utils/types.h. <br>
( For that purpose you can use [ct_tree ct_create_node(void *value_ptr)](https://github.com/RikiTikkiTavi/ConsoleTrees#create-node-of-tree) )
```c
typedef struct ct_node *ct_tree;
typedef struct ct_node {
  void *value_ptr; // pointer on node value
  ct_tree left; // pointer on left node
  ct_tree right; // pointer on right node
} ct_node;
```
2: You must create function, that accepts void pointer on value and returns value converted to string. For example ready int to string function from ConsoleTrees library: ```char *ct_int_to_string(void *val)```
```c
char *ct_int_to_string(void *val) {
  if(val==NULL){
    printf("\nl: %d ::: Error in ct_int_to_string(void *val) ::: val is NULL\n", __LINE__);
    char *str_buffer = calloc(1, 15);
    sprintf(str_buffer, "%d", 0);
    return str_buffer;
  }
  char *str_buffer = calloc(1, 15);
  sprintf(str_buffer, "%d", (*(int *) val));
  return str_buffer;
}
```
  Finally: <br/>
  root - root of tree from 1. <br/>
  ct_int_to_string - tree node value to string convertion function from 2. <br/>
 ```c
 ct_visualize_tree(root, 5, ct_int_to_string);
  ```

#### Convert array to tree:
```c
ct_tree ct_array_to_tree(int *arr, int arr_length);
```
If you are working with for example with Heap Sort it might be useful to visualize your array as tree.

Takes 2 arguments: <br/>
``` int *arr ``` - pointer on integer array <br/>
```  int arr_length ``` - length of array

Returns:
```ct_tree```  variable - root of tree

#### Create node of tree:
 ```c
ct_tree ct_create_node(void *value_ptr);
```
Creates nodes (```ct_node```) for ```ct_tree ``` (pointer on ```ct_node```)

Takes 1 argument: <br/>
```void *value_ptr``` - pointer on node value;

Returns:
```ct_tree``` variable - pointer on t_node

#### Delete tree
```c
void ct_delete_tree(ct_tree t);
```
Deletes tree

Takes 1 argument: <br/>
```ct_tree t ``` - pointer on tree root

#### Calculate tree height:
```c
 int ct_calc_tree_height(ct_tree t);
```
Calculates height of tree

Takes 1 argument: <br/>
```ct_tree t ``` - pointer on tree root

Returns:
```int ``` variable - tree height

#### Create right-only tree:
```c
ct_tree ct_create_rightist_tree(int *values, int values_q);
```
Creates tree with only right nodes.

Takes 2 arguments: <br/>
```int *values``` - integer array <br/>
```int values_q``` - array length

Returns:
```ct_tree``` variable - pointer on tree root

#### Create random 1-regular tree:
``` c
ct_tree ct_create_random_single_child_tree(int values[], int values_q);
```
Creates random 1-regular tree.

Takes 2 arguments: <br/>
```int values[]``` - integer array <br/>
```int values_q``` - array length

Returns
```ct_tree``` variable - pointer on tree root

## Types
[Types declarations](https://github.com/RikiTikkiTavi/ConsoleTrees/blob/master/src/lib/utils/types.h)


## License
[MIT](https://choosealicense.com/licenses/mit/)