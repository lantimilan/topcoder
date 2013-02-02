# Given a forest, print levels
# node {
#   string label;
#   int id;
#   int parent_id;
# }

class Node:
    pass

def print_tree(nodes):
    #print_tree_rec(nodes, 0, 0)  # indent, root_id
    print_tree_iter(nodes)

# dfs
def print_tree_rec(nodes, indent, root_id):
    for node in nodes:
        if node.parent_id == root_id:
            print "%s%s" % ("  "*indent, node.label)
            print_tree_rec(nodes, indent+1, node.id)


# non-recursive version
# graph dfs
def print_tree_iter(nodes):
    # build graph as adj list
    graph = dict()
    graph[0] = []
    for node in nodes:
        graph[node.id] = []
    for node in nodes:
        graph[node.parent_id].append(node.id)

    # use stack of id for dfs
    child_idx = dict()
    labels = dict()
    for node in nodes:
        child_idx[node.id] = 0
        labels[node.id] = node.label

    prefix = "  "
    indent = 0
    st = [0]
    child_idx[0] = 0
    while st:
        root_id = st[-1]
        if child_idx[root_id] >= len(graph[root_id]):
            st = st[:-1]
            indent -= 1
        else:
            child = graph[root_id][child_idx[root_id]]
            print "%s%s" % (prefix * indent, labels[child])
            st.append(child)
            indent += 1
            child_idx[root_id] += 1

if __name__ == "__main__":
    nodes = [Node() for i in range(7)]

    nodes[0].label = "A"
    nodes[0].id = 10
    nodes[0].parent_id = 0

    nodes[1].label = "B"
    nodes[1].id = 20
    nodes[1].parent_id = 10

    nodes[2].label = "C"
    nodes[2].id = 30
    nodes[2].parent_id = 20

    nodes[3].label = "D"
    nodes[3].id = 40
    nodes[3].parent_id = 10

    nodes[4].label = "E"
    nodes[4].id = 50
    nodes[4].parent_id = 10

    nodes[5].label = "F"
    nodes[5].id = 60
    nodes[5].parent_id = 0

    nodes[6].label = "G"
    nodes[6].id = 70
    nodes[6].parent_id = 60

    print_tree(nodes)
