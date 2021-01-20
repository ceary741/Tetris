


game: block.o container.o painter.o game.o
	gcc $^ -o $@
game.o: game.c
	gcc $^ -c -o $@
painter.o: painter.c
	gcc $^ -c -o $@
container.o: container.c
	gcc $^ -c -o $@
block.o: block.c
	gcc $^ -c -o $@

clean:
	rm -rf *.o game
