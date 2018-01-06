###########################
#         vulkan         #
###########################

set(INCLUDE_DIRECTORIES src/include)
list(APPEND INCLUDE_DIRECTORIES src/include/sockets)
list(APPEND INCLUDE_DIRECTORIES src/lib/jsoncpp)

set(SOURCE_FILES "")
set(FILES_PATH "src/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}clock.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}configparser.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}fraction.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}graphs_and_grids.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}main.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}message_writer.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}poker_hand.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}utils.cpp")

list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_01_10.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_11_20.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_21_30.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_31_40.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_41_50.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_51_60.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_61_70.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_71_80.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_81_90.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/eulerproblems_91_100.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}problems/problems_results.cpp")

list(APPEND SOURCE_FILES "${FILES_PATH}sockets/server_socket_TCP.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}sockets/server_socket_UDP.cpp")


set(HEADER_FILES "")
set(FILES_PATH "src/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}clock.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}configparser.h")
list(APPEND HEADER_FILES "${FILES_PATH}defines.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}enums.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}eulerproblems.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}fraction.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}graphs_and_grids.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}hash.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}message_writer.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}poker_hand.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}problems_results.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}structs.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}utils.hpp")

list(APPEND HEADER_FILES "${FILES_PATH}sockets/server_socket_TCP.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}sockets/server_socket_UDP.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}sockets/SocketException.h")

#lib folder
set(FILES_PATH "src/lib/jsoncpp/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}json-forwards.h")
list(APPEND HEADER_FILES "${FILES_PATH}json.h")
list(APPEND HEADER_FILES "${FILES_PATH}jsoncpp.cpp")
