# --- Version ------------------------------------------------------------------

cmake_minimum_required(VERSION 3.28)

set(AUTH_API_VERSION_MAJOR 1)
set(AUTH_API_VERSION_MINOR 0)
set(AUTH_API_VERSION_PATCH 0)

# --- Project And Compiler -----------------------------------------------------

project(api_auth)
set(CMAKE_CXX_STANDARD 17)

# --- Directories --------------------------------------------------------------

set(AUTH_API_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(AUTH_API_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# --- Source Files -------------------------------------------------------------

set(AUTH_API_SOURCES 
  src/main.cpp
  src/db/Database.cpp
  src/db/QueryResponse.cpp
  src/db/models/User.cpp
)

# --- Executable ---------------------------------------------------------------

add_executable(${PROJECT_NAME} ${AUTH_API_SOURCES})

# --- Third Party --------------------------------------------------------------

find_package(Crow REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Crow::Crow)
target_include_directories(${PROJECT_NAME} PUBLIC ${Crow_INCLUDE_DIRS})


find_package(SQLite3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SQLite::SQLite3)
