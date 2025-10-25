#include "main.h"

#include <string>
#include <vector>
#include "lz4/lz4.h"
#include <cassert>

void lz4_basic_test(){
    std::vector<char> data;
    for(auto c : "Helllllllo Wooooorlllld!"){
        data.push_back(c);
    }
    std::vector<char> compressed_data(data.size()), decompressed_data(data.size());

    printf("original data size: %d\n",data.size());

    int compressed_size = LZ4_compress_default(data.data(), compressed_data.data(), data.size(), compressed_data.size());
    assert((compressed_size != 0) && "compression failed");
    compressed_data.resize(compressed_size);
    printf("compressed to size: %d\n",compressed_data.size());

    int decompressed_size = LZ4_decompress_safe(compressed_data.data(), decompressed_data.data(), compressed_data.size(), decompressed_data.size());
    assert((decompressed_size != 0) && "decompression failed");
    decompressed_data.resize(decompressed_size);

    assert((decompressed_size == data.size()) && "size of decompressed data does not match original");
    for(int i = 0;i < data.size();i++){
        if(decompressed_data[i] != data[i]) assert("data is not equal");
    }
    printf("decompressed data matches original\n");
}

void initialize() {
    lz4_basic_test();
}
