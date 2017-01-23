# Accepts a paragraph and prints out the groups of words that are anagrams
#
set(SOURCE_FILES friendcircles.cpp)
add_executable(friendcircles ${SOURCE_FILES})

set(SOURCE_FILES knightbishop.cpp)
add_executable(knightbishop ${SOURCE_FILES})

set(SOURCE_FILES getline.cpp)
add_executable(getline ${SOURCE_FILES})

set(SOURCE_FILES currencymarket.cpp)
add_executable(currencymarket ${SOURCE_FILES})

# Determine num chars to delete to ocnvert to anagram
#
set(SOURCE_FILES anagrameditdist.cpp)
add_executable(anagrameditdist ${SOURCE_FILES})

# https://www.hackerrank.com/challenges/making-anagrams
#
set(SOURCE_FILES makinganagrams.cpp)
add_executable(makinganagrams ${SOURCE_FILES})
