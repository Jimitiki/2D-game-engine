import os

def get_dependencies(file_name, dir_path, dependency_set):
	try:
		f = open(file=dir_path + file_name)
	except FileNotFoundError:
		return
	else:
		dependency_set.add(dir_path + file_name)
		for line in f:
			if line.startswith("#include \""):
				dependency_set.add(dir_path + line[10:-2])

def get_objects(dir, objs):
	for src in os.listdir(dir):
		if src.endswith(".cpp"):
			obj = src[:-4]
			header = obj + ".hpp"
			obj = obj + ".o"
			objs[obj] = set()
			get_dependencies(file_name=src, dir_path="../src/" + dir + "/", dependency_set=objs[obj])
			get_dependencies(file_name=header, dir_path="../src/" + dir + "/", dependency_set=objs[obj])


makef = open(file="Makefile", mode="w")

makef.write("C = g++ -std=c++11\nCFLAGS = -Wall\nLFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf\n\nTARGET = JAM\n\n")

objs = {}
os.chdir("../src")
get_objects("engine", objs)
get_objects("game", objs)

makef.write("OBJS =")
for obj in objs.keys():
	makef.write(" " + obj)

makef.write("\n\nall : game\n\ngame : $(OBJS)\n\t$(C) $(CFLAGS) -o $(TARGET) $^ $(LFLAGS)\n\trm ../src/engine/*.gch\n\trm ../src/game/*.gch\n\n")

for obj, deps in objs.items():
	makef.write(obj + " :")
	for dep in deps:
		makef.write(" " + dep)

	makef.write("\n\t$(C) $(CFLAGS) -c -g $^ $(LFLAGS)\n\n")

makef.write("\nclean :\n\trm ./*.o\n\trm ../src/engine/*.gch\n\trm ../src/game/*.gch")
makef.close()
