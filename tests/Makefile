default:
	$(error Please use the Makefile from root directory)

include ../config.env
.EXPORT_ALL_VARIABLES: test

TESTS := $(wildcard test_*.py)

test:
	@sdcc --version
	python3 -m unittest $(TESTS)

.PHONY: test default

