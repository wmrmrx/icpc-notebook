// Linked Linked
//
// Parameters:
// 	CAP: How many nodes can be created at most
// 	T: What type to be stored in a node in the linked list
//
// Functions:
// 	append(T info): puts node with info in the tail
// 	remove(Node* nd): removes node in O(1)
//
// Tested: https://codeforces.com/contest/1181/submission/246289459
namespace linked_list {
	constexpr int CAP = 10'000'000;
	using T = int;

	struct Node {
		T info;
		Node *prv, *nxt;
	};

	Node arena[CAP];
	int arena_cnt = 0;

	struct LinkedList {
		Node* new_node(T info) {
			Node* ret = arena + (arena_cnt++);
			ret->info = info;
			ret->prv = ret->nxt = 0;
			return ret;
		}

		Node *head, *tail;
		LinkedList(): head(0), tail(0) {}
		void append(T info) {
			Node* nd = new_node(info);
			if(!head) 
				head = tail = nd;
			else {
				tail->nxt = nd;
				nd->prv = tail;
				tail = nd;
			}
		}
		void remove(Node* nd) {
			if(nd == head && nd == tail)
				head = tail = 0;
			else if(nd == head)
				head = nd->nxt, head->prv = 0;
			else if(nd == tail)
				tail = nd->prv, tail->nxt = 0;
			else {
				auto prv = nd->prv, nxt = nd->nxt;
				prv->nxt = nxt;
				nxt->prv = prv;
			}
		}
	};
}
