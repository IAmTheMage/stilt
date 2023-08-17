# CMakeLists.txt dentro do subdiretório "src"

# Lista de arquivos fonte nesta subpasta
set(SRC_FILES
    main.cpp
    Log.cpp
    # Adicione mais arquivos conforme necessário
)

# Criar uma biblioteca alvo a partir dos arquivos fonte
add_library(main ${SRC_FILES})

# Linkar quaisquer bibliotecas necessárias para esta biblioteca
target_link_libraries(main
    # Lista de bibliotecas necessárias, se houver
)

# Certifique-se de que o compilador saiba onde encontrar os cabeçalhos deste diretório
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})