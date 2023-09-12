build:
	@gcc shell.c -o shell

run:
	@chmod +x shell
	@./shell