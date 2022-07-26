sources = main.c ui.c tools.c func.c io.c
output = main

$(output):$(sources)
		gcc -g -o $(output) $(sources) -lpthread

.PHONY : clean
    clean :
		-rm $(output)
