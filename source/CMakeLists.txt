################################################################
cmake_minimum_required(VERSION 3.5)
################################################################
set(LIBRARY_NAME "openssl")
set(LIBRARY_DESC "OpenSSL C++ wrapper library")

project(libict-${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LINK_LIBS "")

macro(add_ict_subdir ICT_NAME)
  set(CMAKE_SUBDIRECTORY      ${ICT_NAME})
  set(CMAKE_SUBDIRECTORY_DIR  ../${CMAKE_SUBDIRECTORY})
  set(CMAKE_SUBDIRECTORY_SRC  ${CMAKE_SUBDIRECTORY_DIR}/source)
  set(CMAKE_SUBDIRECTORY_BLD  ${CMAKE_SUBDIRECTORY_DIR}/build)
  set(CMAKE_SUBDIRECTORY_LIB  ${ICT_NAME}.so)

  add_subdirectory(${CMAKE_SUBDIRECTORY_SRC} ${CMAKE_SUBDIRECTORY_BLD} EXCLUDE_FROM_ALL)

  add_custom_target(
    ${CMAKE_SUBDIRECTORY} ALL
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_SUBDIRECTORY_DIR}
  )

  link_directories(${CMAKE_SUBDIRECTORY_BLD})
  include_directories(${CMAKE_SUBDIRECTORY_DIR})

  set(CMAKE_LINK_LIBS "${CMAKE_LINK_LIBS} ${CMAKE_SUBDIRECTORY_LIB}")
  string(STRIP ${CMAKE_LINK_LIBS} CMAKE_LINK_LIBS)
endmacro()

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/info.hpp 
  PRE_BUILD COMMAND ./info.sh ${LIBRARY_NAME} info.hpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/info.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/info.cpp 
  PRE_BUILD COMMAND ./info.sh ${LIBRARY_NAME} info.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/info.hpp ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/all.hpp 
  PRE_BUILD COMMAND ./all.sh 
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/all.sh ${CMAKE_CURRENT_SOURCE_DIR}/info.hpp 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CMAKE_SOURCE_FILES 
 hash.cpp 
 cipher.cpp
 padding.cpp
 info.cpp
)

set(CMAKE_LINK_LIBS "${CMAKE_LINK_LIBS} -lcrypto")
set(CMAKE_LINK_LIBS "${CMAKE_LINK_LIBS} -lssl")
string(STRIP ${CMAKE_LINK_LIBS} CMAKE_LINK_LIBS)

include_directories(BEFORE SYSTEM ${OPENSSL_INCLUDE_DIR})

add_library(ict-static-${LIBRARY_NAME} STATIC ${CMAKE_SOURCE_FILES})
target_link_libraries(ict-static-${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ict-static-${LIBRARY_NAME} ${CMAKE_LINK_LIBS})
set_target_properties(ict-static-${LIBRARY_NAME}  PROPERTIES OUTPUT_NAME ict-${LIBRARY_NAME})

add_library(ict-shared-${LIBRARY_NAME} SHARED ${CMAKE_SOURCE_FILES})
target_link_libraries(ict-shared-${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ict-shared-${LIBRARY_NAME} ${CMAKE_LINK_LIBS})
set_target_properties(ict-shared-${LIBRARY_NAME}  PROPERTIES OUTPUT_NAME ict-${LIBRARY_NAME})

add_executable(${PROJECT_NAME}-test all.hpp test.cpp ${CMAKE_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_LINK_LIBS})
target_compile_definitions(${PROJECT_NAME}-test PUBLIC -DENABLE_TESTING)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../.git)
  find_package(Git)
  if(GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} describe
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "GIT_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    message( STATUS "Git version: ${GIT_VERSION}" )
  else(GIT_FOUND)
    set(GIT_VERSION unknown)
  endif(GIT_FOUND)
else(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../.git)
 set(GIT_VERSION unknown)
endif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../.git)

file(GLOB HEADER_LIST . *.hpp)

install(TARGETS ict-static-${LIBRARY_NAME} ict-shared-${LIBRARY_NAME} DESTINATION lib COMPONENT libraries)
install(
  FILES ${HEADER_LIST}
  DESTINATION include/libict/${LIBRARY_NAME} COMPONENT headers
)
################################################################
enable_testing()

add_test(NAME ict-hash-tc_blake2b512 COMMAND ${PROJECT_NAME}-test ict hash tc_blake2b512)
add_test(NAME ict-hash-tc_blake2s256 COMMAND ${PROJECT_NAME}-test ict hash tc_blake2s256)
add_test(NAME ict-hash-tc_md5 COMMAND ${PROJECT_NAME}-test ict hash tc_md5)
add_test(NAME ict-hash-tc_md5_sha1 COMMAND ${PROJECT_NAME}-test ict hash tc_md5_sha1)
add_test(NAME ict-hash-tc_sha1 COMMAND ${PROJECT_NAME}-test ict hash tc_sha1)
add_test(NAME ict-hash-tc_sha224 COMMAND ${PROJECT_NAME}-test ict hash tc_sha224)
add_test(NAME ict-hash-tc_sha256 COMMAND ${PROJECT_NAME}-test ict hash tc_sha256)
add_test(NAME ict-hash-tc_sha3_224 COMMAND ${PROJECT_NAME}-test ict hash tc_sha3_224)
add_test(NAME ict-hash-tc_sha3_256 COMMAND ${PROJECT_NAME}-test ict hash tc_sha3_256)
add_test(NAME ict-hash-tc_sha3_384 COMMAND ${PROJECT_NAME}-test ict hash tc_sha3_384)
add_test(NAME ict-hash-tc_sha3_512 COMMAND ${PROJECT_NAME}-test ict hash tc_sha3_512)
add_test(NAME ict-hash-tc_sha384 COMMAND ${PROJECT_NAME}-test ict hash tc_sha384)
add_test(NAME ict-hash-tc_sha512 COMMAND ${PROJECT_NAME}-test ict hash tc_sha512)
add_test(NAME ict-hash-tc_sha512_224 COMMAND ${PROJECT_NAME}-test ict hash tc_sha512_224)
add_test(NAME ict-hash-tc_sha512_256 COMMAND ${PROJECT_NAME}-test ict hash tc_sha512_256)
add_test(NAME ict-hash-tc_shake128 COMMAND ${PROJECT_NAME}-test ict hash tc_shake128)
add_test(NAME ict-hash-tc_shake256 COMMAND ${PROJECT_NAME}-test ict hash tc_shake256)
add_test(NAME ict-hash-tc_sm3 COMMAND ${PROJECT_NAME}-test ict hash tc_sm3)
add_test(NAME ict-hash-tc_ssl3_md5 COMMAND ${PROJECT_NAME}-test ict hash tc_ssl3_md5)
add_test(NAME ict-hash-tc_ssl3_sha1 COMMAND ${PROJECT_NAME}-test ict hash tc_ssl3_sha1)
add_test(NAME ict-cipher-tc_des_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ecb)
add_test(NAME ict-cipher-tc_des_ede COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede)
add_test(NAME ict-cipher-tc_des_ede3 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3)
add_test(NAME ict-cipher-tc_des_ede_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede_ecb)
add_test(NAME ict-cipher-tc_des_ede3_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_ecb)
add_test(NAME ict-cipher-tc_des_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_cfb64)
add_test(NAME ict-cipher-tc_des_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_cfb1)
add_test(NAME ict-cipher-tc_des_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_cfb8)
add_test(NAME ict-cipher-tc_des_ede_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede_cfb64)
add_test(NAME ict-cipher-tc_des_ede3_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_cfb64)
add_test(NAME ict-cipher-tc_des_ede3_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_cfb1)
add_test(NAME ict-cipher-tc_des_ede3_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_cfb8)
add_test(NAME ict-cipher-tc_des_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ofb)
add_test(NAME ict-cipher-tc_des_ede_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede_ofb)
add_test(NAME ict-cipher-tc_des_ede3_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_ofb)
add_test(NAME ict-cipher-tc_des_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_des_cbc)
add_test(NAME ict-cipher-tc_des_ede_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede_cbc)
add_test(NAME ict-cipher-tc_des_ede3_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_cbc)
add_test(NAME ict-cipher-tc_desx_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_desx_cbc)
add_test(NAME ict-cipher-tc_des_ede3_wrap COMMAND ${PROJECT_NAME}-test ict cipher tc_des_ede3_wrap)
add_test(NAME ict-cipher-tc_rc4 COMMAND ${PROJECT_NAME}-test ict cipher tc_rc4)
add_test(NAME ict-cipher-tc_rc4_40 COMMAND ${PROJECT_NAME}-test ict cipher tc_rc4_40)
add_test(NAME ict-cipher-tc_rc4_hmac_md5 COMMAND ${PROJECT_NAME}-test ict cipher tc_rc4_hmac_md5)
add_test(NAME ict-cipher-tc_idea_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_idea_ecb)
add_test(NAME ict-cipher-tc_idea_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_idea_cfb64)
add_test(NAME ict-cipher-tc_idea_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_idea_ofb)
add_test(NAME ict-cipher-tc_idea_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_idea_cbc)
add_test(NAME ict-cipher-tc_rc2_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_rc2_ecb)
add_test(NAME ict-cipher-tc_rc2_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_rc2_cbc)
add_test(NAME ict-cipher-tc_rc2_40_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_rc2_40_cbc)
add_test(NAME ict-cipher-tc_rc2_64_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_rc2_64_cbc)
add_test(NAME ict-cipher-tc_rc2_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_rc2_cfb64)
add_test(NAME ict-cipher-tc_rc2_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_rc2_ofb)
add_test(NAME ict-cipher-tc_bf_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_bf_ecb)
add_test(NAME ict-cipher-tc_bf_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_bf_cbc)
add_test(NAME ict-cipher-tc_bf_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_bf_cfb64)
add_test(NAME ict-cipher-tc_bf_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_bf_ofb)
add_test(NAME ict-cipher-tc_cast5_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_cast5_ecb)
add_test(NAME ict-cipher-tc_cast5_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_cast5_cbc)
add_test(NAME ict-cipher-tc_cast5_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_cast5_cfb64)
add_test(NAME ict-cipher-tc_cast5_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_cast5_ofb)
add_test(NAME ict-cipher-tc_rc5_32_12_16_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_rc5_32_12_16_cbc)
add_test(NAME ict-cipher-tc_rc5_32_12_16_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_rc5_32_12_16_ecb)
add_test(NAME ict-cipher-tc_rc5_32_12_16_cfb64 COMMAND ${PROJECT_NAME}-test ict cipher tc_rc5_32_12_16_cfb64)
add_test(NAME ict-cipher-tc_rc5_32_12_16_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_rc5_32_12_16_ofb)
add_test(NAME ict-cipher-tc_aes_128_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_ecb)
add_test(NAME ict-cipher-tc_aes_128_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_cbc)
add_test(NAME ict-cipher-tc_aes_128_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_cfb1)
add_test(NAME ict-cipher-tc_aes_128_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_cfb8)
add_test(NAME ict-cipher-tc_aes_128_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_cfb128)
add_test(NAME ict-cipher-tc_aes_128_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_ofb)
add_test(NAME ict-cipher-tc_aes_128_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_ctr)
add_test(NAME ict-cipher-tc_aes_128_ccm COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_ccm)
add_test(NAME ict-cipher-tc_aes_128_gcm COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_gcm)
add_test(NAME ict-cipher-tc_aes_128_xts COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_xts)
add_test(NAME ict-cipher-tc_aes_128_wrap COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_wrap)
add_test(NAME ict-cipher-tc_aes_128_wrap_pad COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_wrap_pad)
add_test(NAME ict-cipher-tc_aes_128_ocb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_ocb)
add_test(NAME ict-cipher-tc_aes_192_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_ecb)
add_test(NAME ict-cipher-tc_aes_192_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_cbc)
add_test(NAME ict-cipher-tc_aes_192_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_cfb1)
add_test(NAME ict-cipher-tc_aes_192_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_cfb8)
add_test(NAME ict-cipher-tc_aes_192_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_cfb128)
add_test(NAME ict-cipher-tc_aes_192_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_ofb)
add_test(NAME ict-cipher-tc_aes_192_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_ctr)
add_test(NAME ict-cipher-tc_aes_192_ccm COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_ccm)
add_test(NAME ict-cipher-tc_aes_192_gcm COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_gcm)
add_test(NAME ict-cipher-tc_aes_192_wrap COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_wrap)
add_test(NAME ict-cipher-tc_aes_192_wrap_pad COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_wrap_pad)
add_test(NAME ict-cipher-tc_aes_192_ocb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_192_ocb)
add_test(NAME ict-cipher-tc_aes_256_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_ecb)
add_test(NAME ict-cipher-tc_aes_256_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_cbc)
add_test(NAME ict-cipher-tc_aes_256_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_cfb1)
add_test(NAME ict-cipher-tc_aes_256_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_cfb8)
add_test(NAME ict-cipher-tc_aes_256_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_cfb128)
add_test(NAME ict-cipher-tc_aes_256_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_ofb)
add_test(NAME ict-cipher-tc_aes_256_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_ctr)
add_test(NAME ict-cipher-tc_aes_256_ccm COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_ccm)
add_test(NAME ict-cipher-tc_aes_256_gcm COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_gcm)
add_test(NAME ict-cipher-tc_aes_256_xts COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_xts)
add_test(NAME ict-cipher-tc_aes_256_wrap COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_wrap)
add_test(NAME ict-cipher-tc_aes_256_wrap_pad COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_wrap_pad)
add_test(NAME ict-cipher-tc_aes_256_ocb COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_ocb)
add_test(NAME ict-cipher-tc_aes_128_cbc_hmac_sha1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_cbc_hmac_sha1)
add_test(NAME ict-cipher-tc_aes_256_cbc_hmac_sha1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_cbc_hmac_sha1)
add_test(NAME ict-cipher-tc_aes_128_cbc_hmac_sha256 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_128_cbc_hmac_sha256)
add_test(NAME ict-cipher-tc_aes_256_cbc_hmac_sha256 COMMAND ${PROJECT_NAME}-test ict cipher tc_aes_256_cbc_hmac_sha256)
add_test(NAME ict-cipher-tc_aria_128_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_ecb)
add_test(NAME ict-cipher-tc_aria_128_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_cbc)
add_test(NAME ict-cipher-tc_aria_128_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_cfb1)
add_test(NAME ict-cipher-tc_aria_128_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_cfb8)
add_test(NAME ict-cipher-tc_aria_128_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_cfb128)
add_test(NAME ict-cipher-tc_aria_128_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_ctr)
add_test(NAME ict-cipher-tc_aria_128_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_ofb)
add_test(NAME ict-cipher-tc_aria_128_gcm COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_gcm)
add_test(NAME ict-cipher-tc_aria_128_ccm COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_128_ccm)
add_test(NAME ict-cipher-tc_aria_192_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_ecb)
add_test(NAME ict-cipher-tc_aria_192_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_cbc)
add_test(NAME ict-cipher-tc_aria_192_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_cfb1)
add_test(NAME ict-cipher-tc_aria_192_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_cfb8)
add_test(NAME ict-cipher-tc_aria_192_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_cfb128)
add_test(NAME ict-cipher-tc_aria_192_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_ctr)
add_test(NAME ict-cipher-tc_aria_192_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_ofb)
add_test(NAME ict-cipher-tc_aria_192_gcm COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_gcm)
add_test(NAME ict-cipher-tc_aria_192_ccm COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_192_ccm)
add_test(NAME ict-cipher-tc_aria_256_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_ecb)
add_test(NAME ict-cipher-tc_aria_256_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_cbc)
add_test(NAME ict-cipher-tc_aria_256_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_cfb1)
add_test(NAME ict-cipher-tc_aria_256_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_cfb8)
add_test(NAME ict-cipher-tc_aria_256_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_cfb128)
add_test(NAME ict-cipher-tc_aria_256_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_ctr)
add_test(NAME ict-cipher-tc_aria_256_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_ofb)
add_test(NAME ict-cipher-tc_aria_256_gcm COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_gcm)
add_test(NAME ict-cipher-tc_aria_256_ccm COMMAND ${PROJECT_NAME}-test ict cipher tc_aria_256_ccm)
add_test(NAME ict-cipher-tc_camellia_128_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_ecb)
add_test(NAME ict-cipher-tc_camellia_128_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_cbc)
add_test(NAME ict-cipher-tc_camellia_128_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_cfb1)
add_test(NAME ict-cipher-tc_camellia_128_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_cfb8)
add_test(NAME ict-cipher-tc_camellia_128_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_cfb128)
add_test(NAME ict-cipher-tc_camellia_128_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_ofb)
add_test(NAME ict-cipher-tc_camellia_128_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_128_ctr)
add_test(NAME ict-cipher-tc_camellia_192_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_ecb)
add_test(NAME ict-cipher-tc_camellia_192_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_cbc)
add_test(NAME ict-cipher-tc_camellia_192_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_cfb1)
add_test(NAME ict-cipher-tc_camellia_192_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_cfb8)
add_test(NAME ict-cipher-tc_camellia_192_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_cfb128)
add_test(NAME ict-cipher-tc_camellia_192_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_ofb)
add_test(NAME ict-cipher-tc_camellia_192_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_192_ctr)
add_test(NAME ict-cipher-tc_camellia_256_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_ecb)
add_test(NAME ict-cipher-tc_camellia_256_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_cbc)
add_test(NAME ict-cipher-tc_camellia_256_cfb1 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_cfb1)
add_test(NAME ict-cipher-tc_camellia_256_cfb8 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_cfb8)
add_test(NAME ict-cipher-tc_camellia_256_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_cfb128)
add_test(NAME ict-cipher-tc_camellia_256_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_ofb)
add_test(NAME ict-cipher-tc_camellia_256_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_camellia_256_ctr)
add_test(NAME ict-cipher-tc_chacha20 COMMAND ${PROJECT_NAME}-test ict cipher tc_chacha20)
add_test(NAME ict-cipher-tc_chacha20_poly1305 COMMAND ${PROJECT_NAME}-test ict cipher tc_chacha20_poly1305)
add_test(NAME ict-cipher-tc_seed_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_seed_ecb)
add_test(NAME ict-cipher-tc_seed_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_seed_cbc)
add_test(NAME ict-cipher-tc_seed_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_seed_cfb128)
add_test(NAME ict-cipher-tc_seed_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_seed_ofb)
add_test(NAME ict-cipher-tc_sm4_ecb COMMAND ${PROJECT_NAME}-test ict cipher tc_sm4_ecb)
add_test(NAME ict-cipher-tc_sm4_cbc COMMAND ${PROJECT_NAME}-test ict cipher tc_sm4_cbc)
add_test(NAME ict-cipher-tc_sm4_cfb128 COMMAND ${PROJECT_NAME}-test ict cipher tc_sm4_cfb128)
add_test(NAME ict-cipher-tc_sm4_ofb COMMAND ${PROJECT_NAME}-test ict cipher tc_sm4_ofb)
add_test(NAME ict-cipher-tc_sm4_ctr COMMAND ${PROJECT_NAME}-test ict cipher tc_sm4_ctr)
add_test(NAME ict-padding-tc1 COMMAND ${PROJECT_NAME}-test ict padding tc1)
add_test(NAME ict-padding-tc2 COMMAND ${PROJECT_NAME}-test ict padding tc2)
add_test(NAME ict-padding-tc3 COMMAND ${PROJECT_NAME}-test ict padding tc3)
add_test(NAME ict-padding-tc4 COMMAND ${PROJECT_NAME}-test ict padding tc4)

################################################################
#set(CPACK_GENERATOR "TZ;TGZ;STGZ;DEB;RPM") # Linux
#set(CPACK_GENERATOR "TZ;TGZ;STGZ")         # MacOS

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "ict-project.pl")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Mariusz Ornowski <mariusz.ornowski@ict-project.pl>")
set(CPACK_RPM_PACKAGE_LICENSE "BSD 3-clause")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} - ${LIBRARY_DESC}")
set(CPACK_PACKAGE_VERSION ${GIT_VERSION})

set(CPACK_COMPONENTS_ALL libraries headers)

set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Lib files for: ${LIBRARY_DESC}")

set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Headers")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION  "Header files for: ${LIBRARY_DESC}")
set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)

include(CPack)
################################################################