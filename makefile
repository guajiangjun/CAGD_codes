run:
	g++ main.cpp && ./a.out
python:
	python3 -m draw2d
draw:
	g++ main.cpp && ./a.out && python3 -m draw2d