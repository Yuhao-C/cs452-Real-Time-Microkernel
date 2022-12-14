#ifndef TRACK_TRACK_NODE_H_
#define TRACK_TRACK_NODE_H_

typedef enum {
  NODE_NONE,
  NODE_SENSOR,
  NODE_BRANCH,
  NODE_MERGE,
  NODE_ENTER,
  NODE_EXIT,
} node_type;

#define DIR_AHEAD 0
#define DIR_STRAIGHT 0
#define DIR_CURVED 1

struct track_node;
typedef struct track_node track_node;
typedef struct track_edge track_edge;

struct track_edge {
  track_edge *reverse;
  track_node *src, *dest;
  int dist; /* in millimetres */
};

struct track_node {
  const char *name;
  node_type type;
  int num;             /* sensor or switch number */
  track_node *reverse; /* same location, but opposite direction */
  track_edge edge[2];
  int status;               /* for NODE_BRANCH: DIR_STRAIGHT or DIR_CURVED */
  volatile int enterSeg[2]; /* after passing this node, the segment which the
                      train will enter */
  volatile int leaveSeg[2]; /* after passing this node, the segment which the
                      train will leave */
};

#endif  // TRACK_TRACK_NODE_H_