CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

# The Sources
SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

# The Library Sources
LIBSOURCES=$(wildcard src/**/*.c src/*.c)
LIBOBJECTS=$(patsubst %.c,%.o,$(LIBSOURCES))

# The Test Sources
TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# The Target
TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) $(OBJECTS) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(LIBOBJECTS)
	ar rcs $@ $(LIBOBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(LIBOBJECTS)
	$(CC) -shared -o $@ $(LIBOBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests

# tests: CFLAGS += -ldl
tests: $(TEST_SRC)
	$(CC) -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(TEST_SRC) $(LIBOBJECTS) -o $(TESTS) 
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
# 匹配 strcpy、strncpy、strcat、strncat、strxfrm、strncpy、strdup、strndup、strstr、strpbrk、strtok、str_、stpncpy、snprintf、asnprintf、sprintf、byte_ 等函数
	@grep $(BADFUNCS) $(SOURCES) || true
