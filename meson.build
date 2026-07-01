project('1_graphs', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

subdir('src/view')
subdir('src/controller')
subdir('src/graph')


_1_graphs = executable('_1_graphs',
                       'main.cpp',
                        dependencies : [view_dep,
                                        controller_dep,
                                        all_graph_deps],
                        install : true)

test('test', _1_graphs)