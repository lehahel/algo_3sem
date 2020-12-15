#include "wavheader.h"

void printWAVHeader(WAVHEADER header) {
    std::cout << header.chunkId[0] << header.chunkId[1] << header.chunkId[2] << header.chunkId[3] << std::endl;
    printf("Chunk size: %d\n", header.chunkSize);
    std::cout << header.format[0] << header.format[1] << header.format[2] << header.format[3] << std::endl;
    std::cout << header.subchunk1Id[0] << header.subchunk1Id[1] << header.subchunk1Id[2] << header.subchunk1Id[3] << std::endl;
    printf("SubChunkId1: %d\n", header.subchunk1Size);
    printf("Audio format: %d\n", header.audioFormat);
    printf("Channels: %d\n", header.numChannels);
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Bits per sample: %d\n", header.bitsPerSample);
    std::cout << header.subchunk2Id[0] << header.subchunk2Id[1] << header.subchunk2Id[2] << header.subchunk2Id[3] << std::endl;
    std::cout << header.subchunk2Size << std::endl;
}
