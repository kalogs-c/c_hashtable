default: help

CC = zig cc

check: ## Check prerequisites (zig)
	@which $(CC) > /dev/null && echo "SUCCESS: $(CC) is installed" || echo "ERROR: $(CC) not found, please install zig"

.PHONY: build
build: ## Compiles the program
	zig build

.PHONY: run
run: build ## Runs the program
	./zig-out/bin/c_hashtable

.PHONY: clean
clean: ## Cleans the build
	rm -rf zig-out
	rm -rf .zig-cache

.PHONY: test
test: build ## Runs the tests
	zig build test --summary all

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
