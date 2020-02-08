// basic segment-tree structure
// usage:
//     This template can only be used to get and update interval sums,
//     and if other operations are needed, corresponding code should be 
//     modified.
//     Build the segment-tree before using it.
// Time complexity:(N is the length of the interval)
// build  -> O(N)
// search -> O(logN)
// modify -> O(logN)
//
// Space complexity: 4N
// 
// Note:
// If you want to get minimum space usage 2N - 2,
// add this function:
// bool not_equal(int a, int b) { return a != b; }
// then use tree_[(s+e)|not_equal(s, e)] to access node [s, e].

class SegTree {
public:
  void build(int s, int e) {
    build_(0, s, e);
  }

  int search(int s, int e) {
    return search_(0, s, e);
  }

  void modify(int s, int e, int to_add) {
    modify_(0, s, e, to_add);
  }

private:
  // if children need return value, modify return type.
  void build_(int idx, int s, int e) {
    tree_[idx].s = s; tree_[idx].e = e;
    tree_[idx].val = 0; tree_[idx].to_add = 0;
    int mid = (s + e) / 2;
    if (s < e) {
      build_(2 * idx + 1, s, mid);
      build_(2 * idx + 2, mid + 1, e);
    }
  }

  int search_(int idx, int s, int e) {
    pushdown(idx);
    if (!intersect(tree_[idx].s, tree_[idx].e, s, e)) {
      return 0;
    }
    if (contains(s, e, tree_[idx].s, tree_[idx].e)) {
      return tree_[idx].val;
    }
    return search_(2*idx+1, s, e) + search_(2*idx+2, s, e);
  }

  int modify_(int idx, int s, int e, int to_add) {
    pushdown(idx);
    if (!intersect(tree_[idx].s, tree_[idx].e, s, e)) {
      return 0;
    }
    if (contains(s, e, tree_[idx].s, tree_[idx].e)) {
      tree_[idx].to_add = to_add;
      pushdown(idx);
      return tree_[idx].val;
    }
    modify_(2*idx+1, s, e, to_add);
    modify_(2*idx+2, s, e, to_add);
    return tree_[idx].val = tree_[2*idx+1].val + tree_[2*idx+2].val;
  }


  bool intersect(int left1, int right1, int left2, int right2) {
    return !(left1 > right2 || right1 < left2);
  }

  bool contains(int left1, int right1, int left2, int right2) {
    return left1 <= left2 && right1 >= right2;
  }

  void pushdown(int idx) {
    int to_add = tree_[idx].to_add;
    tree_[idx].val += (tree_[idx].e - tree_[idx].s + 1) * to_add;
    tree_[idx].to_add = 0;
    if (tree_[idx].s < tree_[idx].e) {
      tree_[2*idx+1].to_add += to_add;
      tree_[2*idx+2].to_add += to_add;
    }
  }

  struct SegTreeNode {
    int s;
    int e;
    int val;
    int to_add;
  } tree_[4 * MAXN];
};
