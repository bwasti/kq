CPP=c++
CFLAGS=-Wall --std=c++14
CFLAGS_DEBUG=-g -O0
LDFLAGS=

SRCDIR=src
OBJDIR=obj
INCDIR=$(SRCDIR)/inc

SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET=kqd

debug: CPP+=$(CFLAGS_DEBUG)
all: $(TARGET)
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJS): | $(OBJDIR)
$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(INCDIR)/*.h) Makefile
	$(CPP) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf $(OBJDIR) $(TARGET)
