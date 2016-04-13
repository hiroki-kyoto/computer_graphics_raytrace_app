CC=g++
TARGETS=app.o
OBJECTS=cg_math.o cg_geom.o cg_material.o cg_model.o cg_scene.o cg_ray.o cg_canvas.o cg_pipeline.o

all:$(OBJECTS) $(TARGETS)

cg_math.o:cg_math.hpp
	$(CC) -o cg_math.o cg_math.hpp
cg_geom.o:cg_geom.hpp
	$(CC) -o cg_geom.o cg_geom.hpp
cg_material.o:cg_material.hpp
	$(CC) -o cg_material.o cg_material.hpp
cg_model.o:cg_model.hpp
	$(CC) -o cg_model.o cg_model.hpp
cg_scene.o:cg_scene.hpp
	$(CC) -o cg_scene.o cg_scene.hpp
cg_ray.o:cg_ray.hpp
	$(CC) -o cg_ray.o cg_ray.hpp
cg_canvas.o:cg_canvas.hpp
	$(CC) -o cg_canvas.o cg_canvas.hpp
cg_pipeline.o:cg_pipeline.hpp
	$(CC) -o cg_pipeline.o cg_pipeline.hpp
cg_bitmap.o:cg_bitmap.hpp
	$(CC) -o cg_bitmap.o cg_bitmap.hpp

app.o:main.cpp
	$(CC) -o main.o main.cpp
clean:
	-rm *.o
