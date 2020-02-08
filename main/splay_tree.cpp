// A basic splay tree template
// Time Complexity:
// size()     -> O(1)
// clear()    -> O(1)
// insert()   -> amortized O(logN)
// find()     -> amortized O(logN)
// remove()   -> amortized O(logN)
// get_kth()  -> amortized O(logN)
// Space Complexity:
// NUMBER OF OPERATIONS!!!
// Note:
// The code uses the easiest way to generate a
// new code and won't actually delete any node from memory.
// If number of insertions/removals is too large,
// try rewrite '_new_node', 'insert' and 'remove' function.

class splay_tree {
public:
  splay_tree() {
    _nil = &_nil_node;
    _nil_node.value = 0;
    _nil_node.size = 0;
    _nil_node.parent = _nil;
    _nil_node.children[LEFT] = _nil;
    _nil_node.children[RIGHT] = _nil;
    clear();
  }

  size_t size() const {
    return _root->size - 2; // '-2' for -INF node and INF node
  }

  void clear() {
    _num_nodes = 0;
    _root = _nil;
    insert(-INF);
    insert(INF);
  }

  void insert(int value) {
    if(_root == _nil) {
      _root = _new_node(_nil, value);
      return;
    }
    _inner_node *x = _root;
    while(true) {
      int direction = (x->value < value);
      if(x->children[direction] == _nil) {
        x->children[direction] = _new_node(x, value);
        _update(x);
        _splay(x->children[direction], _nil);
        return;
      }
      else {
        x = x->children[direction];
      }
    }
  }

  int find(int value) {
    return _find(value) - 1;
  }

  void remove(int value) {
    int k = _find(value);
    _find(k - 1, _nil);
    _find(k + 1, _root);
    _root->children[RIGHT]->children[LEFT] = _nil;
    _update(_root->children[RIGHT]);
    _update(_root);
  }

  int get_kth(int k) {
    _find(k + 1, _nil); // '+1' since '-INF' is inserted for safety by splay tree itself.
    return _root->value;
  }

  enum Direction{ LEFT=0, RIGHT };
private:
  struct _inner_node{
    int value;
    int size;
    _inner_node *parent;
    _inner_node *children[2];
  }node[MAXN], _nil_node;  //  _nil_node is a dummy node pointed by _nil(a pointer). This node is added mainly for coding convenience.

  _inner_node *_root, *_nil;
  int _num_nodes;

  _inner_node* _new_node(_inner_node *parent, int value) {
    node[_num_nodes].value = value;
    node[_num_nodes].size = 1;
    node[_num_nodes].parent = parent;
    node[_num_nodes].children[LEFT] = _nil;
    node[_num_nodes].children[RIGHT] = _nil;
    return &node[_num_nodes++];
  }

  void _update(_inner_node *x) {
    if(x == _nil) return;
    x->size = x->children[LEFT]->size + x->children[RIGHT]->size + 1;
  }

  void _rotate(_inner_node *x, Direction direction) {
    _inner_node *p = x->parent;
    p->children[!direction] = x->children[direction];
    p->children[!direction]->parent = p;
    x->children[direction] = p;
    x->parent = p->parent;
    if(p->parent->children[LEFT] == p){
      p->parent->children[LEFT] = x;
    }
    else{
      p->parent->children[RIGHT] = x;
    }
    p->parent = x;
    _update(p);
    _update(x);
    if(_root == p) _root = x;
  }

  // splay x to the child of y. to root if y is nil.
  void _splay(_inner_node *x, _inner_node *y) {
    while(x->parent != y) {
      if(x->parent->parent == y) {
        if(x->parent->children[LEFT] == x) {
          _rotate(x, RIGHT);
        }
        else{
          _rotate(x, LEFT);
        }
      }
      else if(x->parent->parent->children[LEFT] == x->parent) {
        if(x->parent->children[LEFT] == x) {
          _rotate(x->parent, RIGHT);
          _rotate(x, RIGHT);
        }
        else {
          _rotate(x, LEFT);
          _rotate(x, RIGHT);
        }
      }
      else{
        if(x->parent->children[RIGHT] == x) {
          _rotate(x->parent, LEFT);
          _rotate(x, LEFT);
        }
        else {
          _rotate(x, RIGHT);
          _rotate(x, LEFT);
        }
      }
      _update(x);
    }
  }

  int _find(int value) {
    _inner_node *x = _root;
    int count = 0;
    while(true){
      if(x->value == value) {
        return count + x->size - x->children[RIGHT]->size;
      }
      else if(x->value > value){
        x = x->children[LEFT];
      }
      else{
        count += x->size - x->children[RIGHT]->size;
        x = x->children[RIGHT];
      }
    }
  }

  void _find(int k, _inner_node *y) {
    _inner_node *x = _root;
    while(k != x->children[LEFT]->size + 1){
      if(k <= x->children[LEFT]->size){
        x = x->children[LEFT];
      }
      else{
        k -= x->children[LEFT]->size + 1;
        x = x->children[RIGHT];
      }
    }

    _splay(x, y);
  }
};
