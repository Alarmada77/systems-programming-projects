cmake_minimum_required(VERSION 3.30)
project(mtm_blockchain)

set(CMAKE_CXX_STANDARD 17)

add_executable(mtm_blockchain main.cpp BlockChain.cpp Transaction.cpp Utilities.cpp)
