project('dstructs', 'c',
  version: '0.1.0',
  meson_version: '>= 1.2.0',
  default_options: [ 'warning_level=3', 'c_std=c17' ]
)

cc = meson.get_compiler('c')
math_dep = cc.find_library('m', required: true)

includes = []
source_files = []

subdir('include')
subdir('src') # Inicia compilación del proyecto


gtest = subproject('gtest')
if get_option('enable-tests')
  subdir('tests')
endif

dstructs_dep = declare_dependency(
  include_directories: includes,
  link_with: dstructs_lib
)
