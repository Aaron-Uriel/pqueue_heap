source_files += files('pqueue.c', 'list.c', 'node.c')

dstructs_lib = shared_library('dstructs', source_files,
  include_directories: includes,
  dependencies: math_dep,
  # Comprobar si esto no causa problemas al usarlo en otros proyectos.
  install: false,
)
