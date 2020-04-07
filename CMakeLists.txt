set(LIBS 
    liblua
    sol2
    Lua
    Dolce)

build_library(NAME DolceLua FOLDER Dolce/Lua TYPE STATIC LIBS "${LIBS}")