# =============================
# 1. Thông tin dự án
# =============================
TARGET = spws_c

# Thư mục gốc chứa mã nguồn và header
SRC_DIR = src
INC_DIR = include

# Thư mục chứa các component
COMPONENTS = Config Button Led Sensor Pump State_Machine

# App (main)
APP ?= app_main
APP_DIR = app/$(APP)

# Thư mục chứa test
TEST_DIR = tests

# Thư mục build
BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
BIN_DIR   = $(BUILD_DIR)/bin

# =============================
# 2. Cờ biên dịch
# =============================
CC = gcc
COMPONENT_INCLUDE_PATHS = -I$(INC_DIR) $(foreach comp,$(COMPONENTS),-I$(SRC_DIR)/$(comp))
CFLAGS = -Wall -I$(APP_DIR) $(COMPONENT_INCLUDE_PATHS)
TEST_CFLAGS = $(CFLAGS) -DTESTING
LDFLAGS =

# =============================
# 3. Nguồn cho APP
# =============================
COMPONENT_SRC = $(foreach comp,$(COMPONENTS),$(wildcard $(SRC_DIR)/$(comp)/*.c))
APP_SRC       = $(wildcard $(APP_DIR)/*.c)

OBJ_FILES = \
  $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(COMPONENT_SRC)) \
  $(patsubst app/%.c,$(OBJ_DIR)/app/%.o,$(APP_SRC))

# =============================
# 4. Nguồn cho TEST
# =============================
TEST_SRC  = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%,$(TEST_SRC))

# =============================
# 5. Targets
# =============================
.PHONY: all tests clean run

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(TARGET)

tests: $(TEST_BINS)

# Build app
$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

# Build mỗi test thành binary riêng
$(BIN_DIR)/%: $(OBJ_DIR)/tests/%.o $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(COMPONENT_SRC))
	@mkdir -p $(dir $@)
	$(CC) $(TEST_CFLAGS) $^ -o $@

# Build 1 test cụ thể bằng: make test_led  (hoặc test_button)
test_%: $(BIN_DIR)/test_%
	@echo "===> Test binary $< đã build xong."

# =============================
# 6. Compile rules
# =============================
# Compile component/app .c → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/app/%.o: app/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test .c → .o
$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(TEST_CFLAGS) -c $< -o $@

# =============================
# 7. Utils
# =============================
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(BIN_DIR)/$(TARGET)
