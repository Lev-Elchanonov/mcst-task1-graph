project('1_graphs', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

gtest_dep = dependency('gtest', required: false)


subdir('src/view')
subdir('src/controller')
subdir('src/graph')
subdir('src/commands')

program = executable('graph',
                       'main.cpp',
                        dependencies : [
                            view_dep,
                            controller_dep,
                            all_graph_deps,
                            command_deps
                        ],
                        install : true)

if gtest_dep.found()
    test_sources = files(
        'tests/test_main.cpp',
        'tests/test_vertex.cpp',
        'tests/test_edge.cpp',
        'tests/test_maxflow.cpp',
        'tests/test_tarjan.cpp',
        'tests/test_dijkstra.cpp'
    )

    test_executable = executable('tests',
                                 test_sources,
                                 dependencies : [
                                     gtest_dep,
                                     controller_dep,
                                     all_graph_deps,
                                     command_deps
                                 ],
                                 install : false
    )

    test('tests', test_executable)
else
    warning('Google Test not found. Tests will not be built.')
endif