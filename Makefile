default: help

CC = zig cc

.PHONY: check build run help

check: ## Check prerequisites (zig)
	@which $(CC) > /dev/null && echo "SUCCESS: $(CC) is installed" || echo "ERROR: $(CC) not found, please install zig"

build: ## Compiles the program
	zig build

run: build ## Runs the program
	./zig-out/bin/c_hashtable

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
