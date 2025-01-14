#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

namespace Crypto
{
    class MD5
    {
        protected: 
            static void appendBits(const std::string& data, unsigned char* input, int size) 
            {
                for(int i = 0; i < data.size(); i++) 
                {
                    input[i] = data[i];
                }

                input[data.size()] = 0x80;

                for(unsigned int i = data.size() + 1; i < size - 8; i++) 
                {
                    input[i] = 0x00;
                }

                unsigned long long bit_length = data.size() * 8;

                for(int i = 0; i < 8; i++) 
                {
                    input[size - 8 + i] = bit_length >> i * 8;
                }
            }

            static unsigned int* init(unsigned char* input, unsigned int* T) 
            {
                for(int i = 0; i < 64; i++) 
                {
                    T[i] = (unsigned int)(pow(2,32)*fabs(sin(i + 1)));
                }

                return (unsigned int*)(input);
            }

            static unsigned int rotate_left(unsigned int value, unsigned int shift) 
            {
                return value << shift | value >> (32-shift);
            }

            static unsigned int F(unsigned int x, unsigned int y, unsigned int z) 
            {
                return (x & y) | (~x & z);
            }

            static unsigned int G(unsigned int x, unsigned int y, unsigned int z) 
            {
                return (x & z) | (~z & y);
            }

            static unsigned int H(unsigned int x, unsigned int y, unsigned int z) 
            {
                return x ^ y ^ z;
            }

            static unsigned int I(unsigned int x, unsigned int y, unsigned int z) 
            {
                return y ^ (~z | x);
            }

            static void process_block(unsigned int* block, unsigned int* T, unsigned int& A, unsigned int& B, unsigned int& C, unsigned int& D) 
            {
                unsigned int AA = A;
                unsigned int BB = B;
                unsigned int CC = C;
                unsigned int DD = D;

                //раунд 1
                A = B + rotate_left((A + F(B, C, D) + block[0]  + T[0]), 7);
                D = A + rotate_left((D + F(A, B, C) + block[1]  + T[1]), 12);
                C = D + rotate_left((C + F(D, A, B) + block[2]  + T[2]), 17);
                B = C + rotate_left((B + F(C, D, A) + block[3]  + T[3]), 22);

                A = B + rotate_left((A + F(B, C, D) + block[4]  + T[4]), 7);
                D = A + rotate_left((D + F(A, B, C) + block[5]  + T[5]), 12);
                C = D + rotate_left((C + F(D, A, B) + block[6]  + T[6]), 17);
                B = C + rotate_left((B + F(C, D, A) + block[7]  + T[7]), 22);

                A = B + rotate_left((A + F(B, C, D) + block[8]  + T[8]), 7);
                D = A + rotate_left((D + F(A, B, C) + block[9]  + T[9]), 12);
                C = D + rotate_left((C + F(D, A, B) + block[10] + T[10]), 17);
                B = C + rotate_left((B + F(C, D, A) + block[11] + T[11]), 22);

                A = B + rotate_left((A + F(B, C, D) + block[12] + T[12]), 7);
                D = A + rotate_left((D + F(A, B, C) + block[13] + T[13]), 12);
                C = D + rotate_left((C + F(D, A, B) + block[14] + T[14]), 17);
                B = C + rotate_left((B + F(C, D, A) + block[15] + T[15]), 22);

                //раунд 2
                A = B + rotate_left((A + G(B, C, D) + block[1]  + T[16]), 5);
                D = A + rotate_left((D + G(A, B, C) + block[6]  + T[17]), 9);
                C = D + rotate_left((C + G(D, A, B) + block[11] + T[18]), 14);
                B = C + rotate_left((B + G(C, D, A) + block[0]  + T[19]), 20);

                A = B + rotate_left((A + G(B, C, D) + block[5]  + T[20]), 5);
                D = A + rotate_left((D + G(A, B, C) + block[10] + T[21]), 9);
                C = D + rotate_left((C + G(D, A, B) + block[15] + T[22]), 14);
                B = C + rotate_left((B + G(C, D, A) + block[4]  + T[23]), 20);

                A = B + rotate_left((A + G(B, C, D) + block[9]  + T[24]), 5);
                D = A + rotate_left((D + G(A, B, C) + block[14] + T[25]), 9);
                C = D + rotate_left((C + G(D, A, B) + block[3]  + T[26]), 14);
                B = C + rotate_left((B + G(C, D, A) + block[8]  + T[27]), 20);

                A = B + rotate_left((A + G(B, C, D) + block[13] + T[28]), 5);
                D = A + rotate_left((D + G(A, B, C) + block[2]  + T[29]), 9);
                C = D + rotate_left((C + G(D, A, B) + block[7]  + T[30]), 14);
                B = C + rotate_left((B + G(C, D, A) + block[12] + T[31]), 20);

                //раунд 3
                A = B + rotate_left((A + H(B, C, D) + block[5]  + T[32]), 4);
                D = A + rotate_left((D + H(A, B, C) + block[8]  + T[33]), 11);
                C = D + rotate_left((C + H(D, A, B) + block[11] + T[34]), 16);
                B = C + rotate_left((B + H(C, D, A) + block[14] + T[35]), 23);

                A = B + rotate_left((A + H(B, C, D) + block[1]  + T[36]), 4);
                D = A + rotate_left((D + H(A, B, C) + block[4]  + T[37]), 11);
                C = D + rotate_left((C + H(D, A, B) + block[7]  + T[38]), 16);
                B = C + rotate_left((B + H(C, D, A) + block[10] + T[39]), 23);

                A = B + rotate_left((A + H(B, C, D) + block[13] + T[40]), 4);
                D = A + rotate_left((D + H(A, B, C) + block[0]  + T[41]), 11);
                C = D + rotate_left((C + H(D, A, B) + block[3]  + T[42]), 16);
                B = C + rotate_left((B + H(C, D, A) + block[6]  + T[43]), 23);

                A = B + rotate_left((A + H(B, C, D) + block[9]  + T[44]), 4);
                D = A + rotate_left((D + H(A, B, C) + block[12] + T[45]), 11);
                C = D + rotate_left((C + H(D, A, B) + block[15] + T[46]), 16);
                B = C + rotate_left((B + H(C, D, A) + block[2]  + T[47]), 23);

                //раунд 4
                A = B + rotate_left((A + I(B, C, D) + block[0]  + T[48]), 6);
                D = A + rotate_left((D + I(A, B, C) + block[7]  + T[49]), 10);
                C = D + rotate_left((C + I(D, A, B) + block[14] + T[50]), 15);
                B = C + rotate_left((B + I(C, D, A) + block[5]  + T[51]), 21);

                A = B + rotate_left((A + I(B, C, D) + block[12] + T[52]), 6);
                D = A + rotate_left((D + I(A, B, C) + block[3]  + T[53]), 10);
                C = D + rotate_left((C + I(D, A, B) + block[10] + T[54]), 15);
                B = C + rotate_left((B + I(C, D, A) + block[1]  + T[55]), 21);

                A = B + rotate_left((A + I(B, C, D) + block[8]  + T[56]), 6);
                D = A + rotate_left((D + I(A, B, C) + block[15] + T[57]), 10);
                C = D + rotate_left((C + I(D, A, B) + block[6]  + T[58]), 15);
                B = C + rotate_left((B + I(C, D, A) + block[13] + T[59]), 21);

                A = B + rotate_left((A + I(B, C, D) + block[4]  + T[60]), 6);
                D = A + rotate_left((D + I(A, B, C) + block[11] + T[61]), 10);
                C = D + rotate_left((C + I(D, A, B) + block[2]  + T[62]), 15);
                B = C + rotate_left((B + I(C, D, A) + block[9]  + T[63]), 21);

                A += AA;
                B += BB;
                C += CC;
                D += DD;
            }

            static void process(unsigned int* block, int size, unsigned int* T, unsigned int& A, unsigned int& B, unsigned int& C, unsigned int& D) 
            {
                for(int i = 0; i < size; i += 64) 
                {
                    process_block(block, T, A, B, C, D);

                    block += 64;
                }
            }

            static std::vector<unsigned char> hashToArr(unsigned int& A, unsigned int& B, unsigned int& C, unsigned int& D) 
            {
                std::vector<unsigned char> hash(16);
            
                memcpy(&hash[0],  &A, 4);
                memcpy(&hash[4],  &B, 4);
                memcpy(&hash[8],  &C, 4);
                memcpy(&hash[12], &D, 4);

                return hash;
            }

            static std::string getHexMD5(std::vector<unsigned char> hash) 
            {
                std::string hex = "0123456789ABCDEF";
                std::string result;

                for(int i = 0; i < hash.size(); i++) {
                    result += hex[hash[i] >> 4];
                    result += hex[hash[i] & 0x0F];
                }

                return result;
            }

        public:
            static std::string hash(std::string data) 
            {
                unsigned char* input;
                unsigned int * block = nullptr;

                unsigned int A = 0x67452301;
                unsigned int B = 0xefcdab89;
                unsigned int C = 0x98badcfe;
                unsigned int D = 0x10325476;

                unsigned int T[64];

                int size       = 0;

                int length     = data.size();
                int rest       = length % 64;

                if(rest < 56) 
                {
                    size = length - rest + 56 + 8;
                }
                else 
                {
                    size = length + 64 - rest + 56 + 8;
                }

                input = new unsigned char[size];

                appendBits(data, input, size);

                block = init(input, T);

                process(block, size, T, A, B, C, D);

                delete[] input;

                return getHexMD5(hashToArr(A, B, C, D));
            }
    };
};