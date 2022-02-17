#include <stdio.h>
#include <string.h>

struct pw_node
{
   int key;
   char flName[100];
   char fnName[30];
   char fnType[10];
   struct pw_node* next;
};

/**
 * @brief number of nodes
 * @param pw 
 * @return int 
 **/
int lenght_list(struct pw_node *pw);

/**
 * @brief shouw nodes data 
 * 
 * @param pw 
 * @return ** void 
 */
void print_list(struct pw_node* pw);

/**
 * @brief Create a node object
 * 
 * @param oKey 
 * @param flName 
 * @param FnName 
 * @param fnType 
 * @return struct pw_node* 
 */
struct pw_node* create_node(int oKey, char* flName, char* FnName, char* fnType);

/**
 * @brief insert node at the and of list
 * 
 * @param pw 
 * @param fpath 
 * @param handle 
 * @param key 
 * @return struct pw_node* 
 **/
struct pw_node* insert_node(struct pw_node* pw, char* fpath, char* fnName, char* fnType, int key);
