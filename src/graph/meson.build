subdir('vertex')
subdir('edge')
subdir('main_graph_class')

all_graph_deps = declare_dependency(
    include_directories : [
        include_directories('vertex/include'),
        include_directories('edge/include'),
        include_directories('main_graph_class/include')
    ],

    dependencies : [vertex_dep, edge_dep, graph_dep]
)