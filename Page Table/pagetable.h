/**
 * 
 *  what is a node?
 *      _____ 
 *     |  |  |
 *     |__|__|
 *  * node has page info
 *  * node has frame info
 *  * node has pointer to next
 *  * node has pointer to previous
 *  * tail will have a null, and the head will simply be just the first node in the linked list. 
 * 
 * */

struct node{
    //signed or unsigned long or int
    int page;
    //signed or unsigned long or int
    int frame;
    struct node *next;
    struct node *previous;

};



/**
 *       head  _____        _____Next node    _____Next node    _____end node
 * linked lis |  |  |----->|  |  |---------->|  |  |---------->|  |  |
 *            |__|__|      |__|__|           |__|__|           |__|__|
 * Ptable struct would need
 *        * ptr head
 *        * ptr to next
 *        * ptr to tail
 *          ____________________________________________
 *          |logical address     |physical address     |
 *          |count               |                     |
 *          |                    |                     |
 *          |                    |                     |
 *          |                    |                     |
 *          |                    |                     |
 *          |____________________|_____________________|
 *        
 **/

struct pagetable{
    int fault;
    int count;
    struct node *head;
    struct node *tail;
};



void createpTable(struct pageTable *pTable);
