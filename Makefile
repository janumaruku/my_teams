##
## EPITECH PROJECT, 2025
## janumaruku
## File description:
## Makefile
##

include mk/config.mk
include mk/sources.mk

UTILS			=	$(BUILD_DIR)/libs/libutils.a
DESIGN_PATTERN	=	$(BUILD_DIR)/libs/libdesign-pattern.a
NETWORK			=	$(BUILD_DIR)/libs/libnetwork.a
SERVER			=	myteams_server
CLIENT			=	myteams_cli

UTILS_OBJ			=	$(UTILS_SRC:%.cpp=$(BUILD_DIR)/%.o)
DESIGN_PATTERN_OBJ	=	$(DESIGN_PATTERN_SRC:%.cpp=$(BUILD_DIR)/%.o)
NETWORK_OBJ			=	$(NETWORK_SRC:%.cpp=$(BUILD_DIR)/%.o)
SERVER_OBJ			=	$(SERVER_SRC:%.cpp=$(BUILD_DIR)/%.o)
CLIENT_OBJ			=	$(CLIENT_SRC:%.cpp=$(BUILD_DIR)/%.o)

LIBS = $(UTILS) $(DESIGN_PATTERN) $(NETWORK)

all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBS) $(SERVER_OBJ)
	$(CXX) $(SERVER_OBJ) -o $@ $(LDFLAGS)

$(CLIENT): $(LIBS) $(CLIENT_OBJ)
	$(CXX) $(CLIENT_OBJ) -o $@ $(LDFLAGS)

$(UTILS): $(UTILS_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(DESIGN_PATTERN): $(DESIGN_PATTERN_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(NETWORK): $(NETWORK_OBJ)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

debug: CXXFLAGS += -g3 -DDEBUG
debug: re

tests_run:
	@echo "No test Makefile target configured yet."

run: $(SERVER)
	@./$(SERVER) $(ARGS)

.PHONY: all clean fclean re debug tests_run run