//Donovan Bale
#include <iostream>
using namespace std;

// -------------
// --------- Big 3 Member Functions ---
// -------------

// Purpose: Destructor
// Postconditions: All dynamically allocated Nodes are de-allocated
template<typename T>
LinkedList<T>::~LinkedList() {
  LLNode<T>* tmp;
  while(m_head != NULL){
    tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
  }
  m_size = 0;
  m_head = NULL;
}

// Purpose: performs a deep copy of the data from rhs into this linkedlist
// Parameters: rhs is linked list to be copied
// Returns: *this
// Postconditions: this list contains same data values (in the same order)
//     as are in rhs; any memory previously used by this list has been
//     deallocated.
template<typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
  if (this == &rhs)
    return *this;
  while (!isEmpty())
  {
    clear();
  }
  LLNode<T>* rp = m_head;
  LLNode<T>* rhsnode = rhs.m_head;
  while(rhsnode->m_next != NULL) {
    insert(rhsnode->m_data, rp);
    rp = rp->m_next;
    rhsnode = rhsnode->m_next;
  }
  m_size = rhs.m_size;
  return *this;
}

// Purpose: copy constructor
// Parameters: rhs is the LinkedList that is to be copied
// Postconditions: this list contains same data values (in same order) 
//      as in rhs.
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs) {
  m_head = new LLNode<T>;
  m_size = 0;
  clear();
  LLNode<T>* rp1 = m_head;
  LLNode<T>* rp2 = rhs.m_head;
  while(rp2->m_next != NULL)
  {
    insert(rp2->m_data, rp1);  
    rp1 = rp1 ->m_next;
    rp2 = rp2->m_next;
  }
  m_size = rhs.m_size; 
}

// -------------
// --------- Basic Accessor Operations ---
// -------------

// Purpose: accessor function to the size the list
// Returns: current size of the list
template<typename T>
int LinkedList<T>::size() const{
  return m_size;
}

// Purpose: determines whether the list is empty
// Returns: 'true' if list is empty; 'false' otherwise
template<typename T>
bool LinkedList<T>::isEmpty() const{
  return m_size == 0;
}

// Purpose: Get a pointer to the first element node
// Returns: pointer to the first node in the list; 
//     returns NULL if the list is empty
template<typename T>
LLNode<T>* LinkedList<T>::getFirstPtr() {
  return m_head;
}

// Purpose: accessor function for a node in the list
// Returns: pointer to the node at the i'th position in the list;
//          counting starts from '0' .
//     returns NULL if no such element exists.
template<typename T>
LLNode<T>* LinkedList<T>::getAtPtr(int i) {
  if (0 <= i && i <= size()) {
    LLNode<T>* rp = m_head;
    for (int k = 0; k < i; k++) {
      rp = rp->m_next;
    }
    return rp;
  }
  else {
    cout << "!!! ERROR : PANIC in LINKEDLIST !!!" << endl;
    cout << "Index out of range, returning NULL" << endl;
    return NULL;
  }
}

// -------------
// --------- Basic Mutator Operations ---
// -------------

// Purpose: effectively "empties" the list, 
//          Turn the list into an empty list.
// Postconditions: dynamically allocated non-sentinel nodes 
//          are de-allicated.
//          m_size is set to zero.
//          m_head points to a sentinel node AKA the last node.
template<typename T>
void LinkedList<T>::clear() {
  if(isEmpty() == false) {
    LLNode<T>* tmp = m_head;
    while(m_head->m_next != NULL) {
      m_head = tmp->m_next;
      delete tmp;
      tmp = m_head;
    }
    m_size = 0;
  }
}

// Purpose: insert element x in the front of the list 
// Parameters: x is data value to inserted
// Postconditions: x is the first element of the list
template<typename T>
void LinkedList<T>::insert_front(const T& x) {
  insert(x, getAtPtr(0));
}

// Purpose: insert element x in the back of the list 
// Parameters: x is data value to inserted
// Postconditions: x is the last element of the list
template<typename T>
void LinkedList<T>::insert_back(const T& x) { 
  insert(x, getAtPtr(m_size));
}

// Purpose: puts the data value x at the position pointed by pos
// Parameters: x : data value to be inserted
//     pos : pointer to the position to insert x at.
// Preconditions: pos is a pointer to a node in this list.
// Postconditions: x is inserted at the position pointed by pos
template<typename T>
void LinkedList<T>::insert(const T& x, LLNode<T>* pos){
  LLNode<T>* tmp = new LLNode<T>;
  tmp->m_data = pos->m_data;
  tmp->m_next = pos->m_next;
  pos->m_next = tmp;
  pos->m_data = x;
  m_size++;
  tmp = NULL;
}

// Purpose: remove the element in the front of the list 
// Postconditions: the first element of the list is removed
template<typename T>
void LinkedList<T>::remove_front() {
  remove(getAtPtr(0));
}

// Purpose: removes the element at the back of the list 
// Postconditions: the last element of the list is removed
template<typename T>
void LinkedList<T>::remove_back() {
  remove(getAtPtr(m_size - 1));
}

// Purpose: remove the element in the position pointed by pos
// Parameters: pos : pointer to the position to remove.
// Preconditions: pos is a pointer to a node in this list.
// Postconditions: element pointed by pos is removed from the list
template<typename T>
void LinkedList<T>::remove(LLNode<T>* pos) {
  LLNode<T>* tmp = pos->m_next;
  pos->m_data = tmp->m_data;
  pos->m_next = tmp->m_next;
  delete tmp;
  m_size--;
}

// --------
// ---- Complex Operations ---
// --------

// Purpose: determines whether this list is identical to rhs list in
//      terms of data values and their order in the list
// Parameters: rhs is list to be compared to this list
// Returns: true if lists are identical; otherwise, false
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
  LLNode<T>* rp = m_head;
  LLNode<T>* rhsnode = rhs.m_head;
  while(rp->m_next != NULL) {
    if(rp->m_data != rhsnode->m_data) {
      return false;
    }
    rp = rp->m_next;
    rhsnode = rhsnode->m_next;
  }
  return true;
}

// Purpose: determines whether x is in the list
// Parameters: x : data value to be found
// Returns: a pointer to the position of x in the list; 
//     otherwise, NULL
template<typename T>
LLNode<T>* LinkedList<T>::find(const T& x) {
  LLNode<T>* rp = m_head; 
  for(int i = 0; i < m_size; i++) {
    if(rp->m_data == x) {
      return rp;
    }
    rp = rp->m_next;
  }
  cout << "!!! ERROR : PANIC in LINKEDLIST !!!" << endl;
  cout << x << " not in Linked List" << endl;
  return NULL;
}

// Purpose: reverses the elements from the list
// Postconditions: the list is now in reverse order
template<typename T>
void LinkedList<T>::reverse() {
  LLNode<T>* curr = m_head;
  LLNode<T>* prev = NULL;
  LLNode<T>* next = NULL;
  while(curr->m_next != NULL) {
    next = curr->m_next;
    curr->m_next = prev;
    prev = curr;
    curr = next;
  }
  m_head = prev;
  delete curr;
  curr = NULL;
  next = NULL;
}

// Purpose: appends two lists
// Parameters: l2, a list to append to the end of 'this' list
// Postconditions: elements of l2 are appended to 'this' list 
template<typename T>
void LinkedList<T>::append(const LinkedList<T>& l2) {
  LLNode<T> *rp = l2.m_head;
    for (int i = 0; i < l2.size(); i++)
    {
        insert_back(rp->m_data);
        rp = rp->m_next;
    }
    rp = NULL;
    delete rp;
}

// Purpose: Makes 'this' list a slice of another list.
// Parameters:    l2, the source of a slice of data.
//                start, pointer to the begining of the slice.
//                end, pointer to the end of the slice.
// Preconditions: 'start' and 'end' are pointers to nodes in the l2 list.
//                'start' precedes 'end' in the l2 list
// Postconditions: 'this' list is made a copy of the elements between 'start'
//                  and 'end' (*exclusive*) in l2.
template<typename T>
void LinkedList<T>::slice(const LinkedList<T>& l2, LLNode<T>* start, LLNode<T>* stop) { 
  LLNode<T>* rp = start;
  while(rp!=stop) {
    this->insert_back(rp->m_data);
    rp = rp->m_next;
  }
}

// Purpose: prints the LinkedList
template <typename T>
ostream& operator<<(ostream& out, const LinkedList<T>& list) {
  out << "[";
  LLNode<T>* nNode = list.m_head;
  for(int i = 0; i < list.m_size; i++) {
    out << nNode -> m_data << ",";
    nNode = nNode -> m_next;
  }
  out << "]";
  return out;
}