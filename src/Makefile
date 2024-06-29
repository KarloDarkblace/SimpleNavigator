#"┏====================================================┓"
#"┃                                                    ┃"
#"┃          O R G A N A H E  L A U R I E G E          ┃"
#"┃                  M C K I N L E Y                   ┃"
#"┃                                                    ┃"
#"┃                 S C H O O L   2 1                  ┃"
#"┃                                                    ┃"
#"┗====================================================┛"

CC := g++
CFLAGS = -Wall -Werror -Wextra -std=c++17

SRC_DIR := functions
LIBS_DIR := libs
BUILD_DIR := build
INCLUDE_DIR := structures
REPORT_DIR := report

GTEST_FLAGS = -lgtest -lgtest_main
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --tool=memcheck --leak-check=yes

SRCS := $(wildcard $(SRC_DIR)/*/*.cc)
OBJS := $(SRCS:.cc=.o)

GRAPH_SRCS := $(wildcard $(SRC_DIR)/graph/*.cc)
GRAPH_OBJS := $(GRAPH_SRCS:.cc=.o)

ALGO_SRCS := $(wildcard $(SRC_DIR)/algorithms/*.cc)
ALGO_OBJS := $(ALGO_SRCS:.cc=.o)

TEST_SRCS := $(wildcard tests/*.cc)
TEST_OBJS := $(TEST_SRCS:.cc=.o)

APP_SRCS := $(wildcard view/*.cc)
APP_OBJS := $(APP_SRCS:.cc=.o)

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	LDFLAGS += -lstdc++ -pthread -lrt -lm
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	LDFLAGS += -lstdc++ -lm
	OPEN_CMD := open
endif

all: clean s21_graph s21_graph_algorithms test run

ifeq ($(MAKECMDGOALS),gcov_report)
%.o: %.cc
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c -o $@ $<
else
%.o: %.cc
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
endif

test: $(TEST_OBJS) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/test $(TEST_OBJS) $(OBJS) -I$(INCLUDE_DIR) -I$(LIBS_DIR) $(GTEST_FLAGS) $(LDFLAGS)
	@$(BUILD_DIR)/test
	@rm *.dot

run: s21_graph s21_graph_algorithms $(APP_FILE) $(APP_OBJS)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/program $(APP_OBJS) -L$(BUILD_DIR) -ls21_graph -ls21_graph_algorithms -I$(INCLUDE_DIR) -I$(LIBS_DIR) $(LDFLAGS)
	@$(BUILD_DIR)/program

s21_graph: $(GRAPH_OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $(BUILD_DIR)/libs21_graph.a $(GRAPH_OBJS)

s21_graph_algorithms: $(ALGO_OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $(BUILD_DIR)/libs21_graph_algorithms.a $(ALGO_OBJS)

valgrind_test:
	@valgrind $(VALGRIND_FLAGS) $(BUILD_DIR)/test
	@rm *.dot

clang:
	@echo "┏=================================================┓"
	@echo "┃  Formatting code according to Google Style...   ┃"
	@echo "┗=================================================┛"
	@clang-format -i $(INCLUDE_DIR)/*.h $(SRCS) *.h tests/*.cc view/*.cc view/*.h

gcov_report: clean $(TEST_OBJS) $(OBJS)
	@echo "┏====================================┓"
	@echo "┃     Generating html report ...     ┃"
	@echo "┗====================================┛"
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_OBJS) $(OBJS) -I$(INCLUDE_DIR) -I$(LIBS_DIR) $(GTEST_FLAGS) $(LDFLAGS) -o $(BUILD_DIR)/test
	@$(BUILD_DIR)/test
	@lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
	@lcov --remove coverage.info '/usr/*' 'src/libs/nlohmann/*' --output-file coverage.info
	@lcov --list coverage.info
	@genhtml coverage.info --output-directory report
	@rm -f *.gcno *.gcda *.info
	@echo "┏=========================================┓"
	@echo "┃     HTML report is ready. Opening...    ┃"
	@echo "┗=========================================┛"
	@$(OPEN_CMD) ./report/index.html &

clean:
	@echo "┏===============================┓"
	@echo "┃  Deleting temporary files...  ┃"
	@echo "┗===============================┛"
	@rm -f $(OBJS) $(GRAPH_OBJS) $(ALGO_OBJS) $(TEST_OBJS) $(APP_OBJS) *.dot *.info
	@rm -rf $(BUILD_DIR) $(BUILD_DIR) $(REPORT_DIR)
	@find $(SRC_DIR) -type f \( -name '*.gcda' -o -name '*.gcno' \) -exec rm -f {} +
	@find tests -type f \( -name '*.gcda' -o -name '*.gcno' \) -exec rm -f {} +

.PHONY: all test s21_graph s21_graph_algorithms clang cleanf