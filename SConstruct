import os
from typing import List

def deep_search_directory(dir: str) -> List:
    sources = []
    for item in os.listdir(dir):
        path: str = os.path.join(dir, item)
        if os.path.isdir(path):
            sources += deep_search_directory(path)
    
    results = map(lambda source : str(source), Glob(dir + "/*.c"))
    return sources + list(results)

def source_to_obj(source: str) -> str:
    index = source.rfind("/")
    if index == -1:
        return "obj/" + source[0:len(source) - 1] + "o"
    return "obj" + source[index:len(source) - 1] + "o"

env = Environment()

sources = deep_search_directory("src")
objects = list(map(source_to_obj, sources))
for i in range(0, len(sources)):
    env.Object(target = objects[i], source = sources[i], CCFLAGS='-g')

libraries = ['m']
env.Program(target = "bin/main", source = objects, LIBS = libraries)
