// Refs & ppl discussed with
// b09902009 b09902011 b09902100
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define lli long long int

using namespace std;

const int max_n = 1e5;

int mySign(lli x) {
    return (x>0) ? 1:-1;
}

struct node {
    lli key;
    node* prv;
    node* nxt;
    int deleted;
    const bool operator < (const node &a) const{
        return (key > a.key);
    }
};

auto myCmp = [](node* a, node* b) {return a->key > b->key;};

typedef struct {
    node* head;
    node* tail;
} llist;

void addLList(llist* list, lli key) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->deleted = 0;
    new_node->key = key;
    new_node->nxt = NULL;
    if (list->tail)  list->tail->nxt = new_node;
    else list->head = new_node;
    new_node->prv = list->tail;
    list->tail = new_node;
}

void printList(node* element) {
    node* head = element;
    while(element->nxt != head) {
        cout << element->key << " <--> ";
        element=element->nxt;
    }
    cout << element->key << "\n";
}

void printListBack(node* element) {
    node* head = element;
    while(element->prv != head) {
        cout << element->key << " <--> ";
        element=element->prv;
    }
    cout << element->key << "\n";
}

node* removeLList(llist* list, node* element) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->deleted = 0;
    new_node->key = element->prv->key - element->key + element->nxt->key;
    if (element->nxt->nxt == element->prv) {
        // special case
        list->head = new_node;
        list->tail = new_node;
        new_node->nxt = NULL;
        new_node->prv == NULL;
    } else {
        // cout << "remove " << element->key << "\n";
        new_node->nxt = element->nxt->nxt;
        new_node->prv = element->prv->prv;
        element->nxt->nxt->prv = new_node;
        element->prv->prv->nxt = new_node;
    }
    return new_node;
}

void initHeap(
        lli* candies
        , int n
        , priority_queue<node*, vector<node*>, decltype(myCmp)> &heap
        , llist* p_sum) {
    if (n>1) {
        for (int i=0; i<n-1; i++) {
            addLList(p_sum, candies[i]+candies[i+1]);
            heap.push(p_sum->tail);
        }
        addLList(p_sum, candies[n-1]+candies[0]);
        heap.push(p_sum->tail);
        p_sum->tail->nxt = p_sum->head;
        p_sum->head->prv = p_sum->tail;
    } else {
        addLList(p_sum, candies[0]);
        heap.push(p_sum->tail);
    }
}

void deleteHeap(
        priority_queue<node*, vector<node*>, decltype(myCmp)> &heap
        , priority_queue<node*, vector<node*>, decltype(myCmp)> &dl_heap) {
    while (!dl_heap.empty()) {
        // cout << "heap.top() = " << heap.top()->key << " @ " << heap.top() << "\n";
        // cout << "dl_heap.top() = " << dl_heap.top()->key << " @ " << dl_heap.top()<< "\n";
        if (heap.top()->key == dl_heap.top()->key && heap.top()->deleted) {
            node* tmp = heap.top();
            heap.pop();
            dl_heap.pop();
            // free(tmp);
            // cout << "popped\n";
            // cout << "dl_heap size: " << dl_heap.size() << "\n";
        } else {
            break;
        }
    }
}

lli removeMin(
        priority_queue<node*, vector<node*>, decltype(myCmp)> &heap
        , llist* p_sum
        , priority_queue<node*, vector<node*>, decltype(myCmp)> &dl_heap) {
    node* min_p = heap.top();
    lli ret = min_p->key;
    // cout << "got here\n";
    // cout << "min=" << ret << "\n";
    // printList(min_p);
    // printListBack(min_p);
    node* new_node = removeLList(p_sum, min_p);
    heap.pop();
    // dl_heap.push(min_p);
    // cout << "push " << min_p->key << " @ " << min_p << "\n";
    dl_heap.push(min_p->nxt);
    // cout << "push " << min_p->nxt->key << " @ " << min_p->nxt << "\n";
    // cout << "dl_heap size: " << dl_heap.size() << "\n";
    dl_heap.push(min_p->prv);
    // cout << "push " << min_p->prv->key << " @ " << min_p->prv << "\n";
    // cout << "dl_heap size: " << dl_heap.size() << "\n";
    min_p->deleted = 1;
    min_p->nxt->deleted = 1;
    min_p->prv->deleted = 1;
    
    // printList(new_node);
    deleteHeap(heap, dl_heap);
    // printList(new_node);
    // printListBack(new_node);
    heap.push(new_node);
    // cout << "here\n";
    free(min_p);
    return ret;
}


void clearHeap(priority_queue<node*, vector<node*>, decltype(myCmp)> &heap, int flag_f) {
    while (!heap.empty()) {
        if (flag_f) free(heap.top());
        heap.pop();
    }
}



int main() {
    int T, flag, n, N;
    lli candies[max_n], ans[max_n+1];
    cin >> T >> flag;
    for (int i=0; i<T; i++) {
        // read input
        lli c_sum=0;
        cin >> n;
        for (int j=0; j<n; j++) {
            cin >> candies[j];
        }

        // make array alternating
        int ed=1, ed_sign=mySign(candies[0]);
        for (int j=1; j<n; j++) {
            if (mySign(candies[j]) == ed_sign) {
                if (candies[j] > candies[ed-1]) {
                    candies[ed-1] = candies[j];
                }
            } else {
                ed++;
                candies[ed-1] = candies[j];
                ed_sign = -ed_sign;
            }
        }
        // fill 0
        for (int j=1; j<=n; j++) ans[j] = 0;
        N = n;
        n = ed;
        for (int j=0; j<n; j++) c_sum+=candies[j];
        
        // case 1: k = n, n-2, n-4, ...
        llist p_sum; p_sum.head=NULL; p_sum.tail=NULL;
        priority_queue<node*, vector<node*>, decltype(myCmp)> heap(myCmp), dl_heap(myCmp);
        initHeap(candies, n, heap, &p_sum);
        ans[n] = c_sum;
        for (int k=n-2; k>0; k-=2) {
            lli min_psum = removeMin(heap, &p_sum, dl_heap);
            ans[k] = ans[k+2]-min_psum;
        }
        // case 2: k = n-1, n-3, n-5, ...
        if (n>1) {
            p_sum.head=NULL; p_sum.tail=NULL;
            clearHeap(heap, 1);
            clearHeap(dl_heap, 0);
            if (candies[0] < candies[n-1]) {
                c_sum -= candies[0];
                for (int j=0; j<n-1; j++) candies[j]=candies[j+1];
            } else {
                c_sum -= candies[n-1];
            }
            initHeap(candies, n-1, heap, &p_sum);
            ans[n-1] = c_sum;
            for (int k=n-3; k>0; k-=2) {
                // cout << "running: " << k << "\n";
                lli min_psum = removeMin(heap, &p_sum, dl_heap);
                ans[k] = ans[k+2]-min_psum;
                // cout << "ended: " << k << "\n";
            }
        }
        
        // output
        for (int j=1; j<=N; j++) {
            cout << ans[j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
