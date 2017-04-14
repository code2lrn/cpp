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

# Binary Tree shallowest leaf node
#
set(SOURCE_FILES btreeleafdepth.cpp)
add_executable(btreeleafdepth ${SOURCE_FILES})

# Binary Matrix - Connected blob boundary
# Print Top, Left, Bottom, Right extremes of the
# blob of 1'es that are connected up, down, left or right.
set(SOURCE_FILES connectedblob.cpp)
add_executable(connectedblob ${SOURCE_FILES})

# Concordance
# Print word frequency along with place of occurrence
#
set(SOURCE_FILES concordance.cpp)
add_executable(concordance ${SOURCE_FILES})

# SCM
#
set(SOURCE_FILES smartcapacitymgt.cpp)
add_executable(scm ${SOURCE_FILES})

# Audible
#
set(SOURCE_FILES audible.cpp)
add_executable(audible ${SOURCE_FILES})

# Audible 2
#
set(SOURCE_FILES audible2.cpp)
add_executable(audible2 ${SOURCE_FILES})
