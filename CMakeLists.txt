set(LIBS 
    liblua
    sol2
    Lua
    Dolce)

build_library(NAME DolceLua FOLDER Dolce TYPE STATIC LIBS "${LIBS}")