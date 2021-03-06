/*
  Huffman Coding (decoder)
  lossless data compression algorithm, entropy decoding

  The main function takes as argument:
  arg1: input file name, this file should only contain 
        '0' and '1' (output of the Huffman encoder).
  arg2: file name containing the list of Huffman
        codeword mappings, e.g. 'a' -> 11101.

  It then writes the following files:
  fout1: output file name: fname1, 
         the decoded (original) ASCII text.

  Author: Josef Ziegler (ippeb24@gmail.com)

*/

#include <cstdio>
#include <map>
#include <string>
#define INPUT_BUFFER_SIZE 100000000
#define OUTPUT_BUFFER_SIZE 100000000
using std::map;
using std::string;

const char fname1[] = "HUFFMAN_decoded.txt";

// map<codeword, symbol of the alphabet> M: maps a 
//     codeword (sequence of '0' and '1' to a char
// S the input string after applying Huffman coding
// slen: length of S
// T the decoded text
void HuffmanCoding_decoder(map<string, char>& M, char const * const S, const int slen, string& T) {
  string temp = "";
  T = "";
  for (int i = 0; i < slen; i++) {
    temp += S[i];
    if (M.find(temp) != M.end()) {
      T += M[temp];
      printf("%c", M[temp]);
      temp = "";
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments specified.\n");
    return 1;
  }
  
  FILE *fin1 = fopen(argv[1], "r");
  FILE *fin2 = fopen(argv[2], "r");

  if (fin1 == NULL || fin2 == NULL) {
    fprintf(stderr, "Input file %s or %s could not be opened.\n", argv[1], argv[2]);
    return 1;
  }

  FILE *fout1 = fopen(fname1, "w");
  
  // read input
  char* S = new char[INPUT_BUFFER_SIZE];
  int slen = fread(S, sizeof(char), INPUT_BUFFER_SIZE, fin1);
  // read alphabet, codewords
  map<string, char> M;
  int alen;
  fscanf(fin2, "%d", &alen);
  printf("Length of the alphabet: %d\n", alen);
  char* C = new char[OUTPUT_BUFFER_SIZE];
  int a;
  for (int i = 0; i < alen; i++) {
    fscanf(fin2, "%d %s", &a, C);
    string c(C);
    M[c] = (char) a;
    printf("%c -> %s\n", (char) a, C);
  } 

  string T;
  printf("Huffman decoding...\n");
  HuffmanCoding_decoder(M, S, slen, T);

  // fout1
  fwrite(T.c_str(), sizeof(char), T.length(), fout1);
}
