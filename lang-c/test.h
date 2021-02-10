
struct LL_Node { 
    struct LL_Node* prev;      /* pointer to the previous node */
	struct LL_Node* next;		/* pointer to the next node */
	void* data_ptr; 			/* uncommitted pointer to the data item */
};

struct Unordered_container {
	struct LL_Node* first;
	struct LL_Node* last;
	int size;
};