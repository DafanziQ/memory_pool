//
// Created by lsy on 16-7-3.
//

#ifndef LIB_NODE_H
#define LIB_NODE_H

/*
 * struct type:
 * typedef struct node_type{
 *     node_type *next;
 *     ...
 * }node_type;
 *
 * ! node must have a empty head and the last->next == NULL
 * ! node must have ->next
 *
 */


//-----------------------------------------------------------------------------------------------------------
// all function test OK
#define LIB_NODE_HAS_NEXT(node)                         (node->next != NULL)

#define LIB_NODE_FOR_EACH(head_node,obj_node)           for(obj_node = head_node;\
                                                        obj_node->next != NULL;\
                                                        obj_node = obj_node->next)

#define LIB_NODE_LENTH(head_node,temp_node,int_lenth)   int_lenth = 0;\
                                                        LIB_NODE_FOR_EACH(head_node,temp_node) int_lenth ++;

#define LIB_NODE_AT_INDEX(head_node,obj_node,index)     obj_node = head_node;\
                                                        while(index --) obj_node = obj_node->next;

#define LIB_NODE_ADD_NODE_NEXT(prev_node,obj_node)      obj_node->next = prev_node->next;\
                                                        prev_node->next = obj_node;

#define LIB_NODE_ADD_INDEX(head_node,temp_node,obj_node,index)\
                                                        LIB_NODE_AT_INDEX(head_node,temp_node,index);\
                                                        LIB_NODE_ADD_NODE_NEXT(temp_node,obj_node);

#define LIB_NODE_GET_NODE_NEXT(prev_node,obj_node)      obj_node = prev_node->next;\
                                                        prev_node->next = prev_node->next->next;

#define LIB_NODE_GET_INDEX(head_node,temp_node,obj_node,index)\
                                                        LIB_NODE_AT_INDEX(head_node,temp_node,index);\
                                                        LIB_NODE_GET_NODE_NEXT(temp_node,obj_node);

#define LIB_NODE_ADD_LAST(head_node,temp_node,obj_node) temp_node = head_node;\
                                                        while(LIB_NODE_HAS_NEXT(temp_node))temp_node = temp_node->next;\
                                                        LIB_NODE_ADD_NODE_NEXT(temp_node,obj_node);
//-------------------------------------------------------------------------------------------------------------
#endif //QUEUE_NODE_H
