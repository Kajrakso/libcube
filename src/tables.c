#include "_tables.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

// The table pointers is only visible in this file.
static void* ptable_H = NULL;
static void* sym_table_e_index = NULL;

void* mmap_table(const char* path, size_t* out_size) {
  int fd = open(path, O_RDONLY);
  if (fd < 0) return NULL;

  struct stat st;
  if (fstat(fd, &st) < 0) {
      close(fd);
      return NULL;
  }

  *out_size = st.st_size;
  void* mapped = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);

  if (mapped == MAP_FAILED) return NULL;
  return mapped;
}

void* load_table_from_file(const char* path, const size_t table_size) {
  FILE* fp = fopen(path, "rb");
  if (!fp) return NULL;
  void* buffer = malloc(table_size);
  if (!buffer) {
      fclose(fp);
      return NULL;
  }
  fread(buffer, 1, table_size, fp);
  fclose(fp);
  return buffer;
}

bool save_table_to_file(const char* path, void* table, const size_t table_size){
  fprintf(stderr, "writing table to disk. file: %s.\n", path);

  FILE *fp = fopen(path, "wb");
  if (!fp) return false;

  if (fwrite(table, table_size, 1, fp) != 1){
    fclose(fp);
    return false;
  }

  fclose(fp);
  return true;
}


int init_ptable_H(const char* path) {
  size_t table_size = sizeof(uint8_t) * SIZE_PTABLE_H;

  size_t out_size;
  if (ptable_H == NULL) {
    void* table_data = mmap_table(path, &out_size);
    if (out_size != table_size) {
      munmap(table_data, table_size);
      return 1;
    }
    ptable_H = table_data;
    return 0;
  }
  return 0;
}


int init_sym_table_e_index(const char* path) {
  size_t table_size = sizeof(uint64_t) * NECE*NEO*NSYMS;

  size_t out_size;
  if (sym_table_e_index == NULL) {
    void* table_data = mmap_table(path, &out_size);
    if (out_size != table_size) {
      munmap(table_data, table_size);
      return 1;
    }
    sym_table_e_index = table_data;
    return 0;
  }
  return 0;
}

void* get_ptable_H() {
    return ptable_H;
}

void* get_sym_table_e_index() {
  return sym_table_e_index;
}

void free_ptable_H() {
  munmap(ptable_H, sizeof(uint8_t) * SIZE_PTABLE_H);

  // free(ptable_H);
  ptable_H = NULL;
}

void free_sym_table_e_index() {
  munmap(sym_table_e_index, sizeof(uint64_t) * NECE*NEO*NSYMS);
  //free(sym_table_e_index);
  sym_table_e_index = NULL;
}

void cube_tables_generate(){
    // gen moves
    initialize_move_tables();
    gen_move_tables();

    // gen sym
    initialize_sym_tables();
    gen_sym_tables();

    gen_move_mask();

    // temp: combinatorials
    precompute_combinatorials();

    // temp: gen c_sym_cclass
    gen_c_sym_index_tables();
}


int cube_tables_load(){
  if (init_ptable_H("data/H.dat") != 0) {
    fprintf(stderr, "Failed to load pruning table H.\n");
    return 1;
  }
  if (init_sym_table_e_index("data/sym_table_e_index.dat") != 0) {
    fprintf(stderr, "Failed to load sym_table_e_index.\n");
    return 1;
  }
  return 0;
}


void cube_tables_free(){
  free_ptable_H();
  free_sym_table_e_index();
}


bool save_ptable(char* filename, uint8_t* ptable, size_t table_size){
  fprintf(stderr, "writing ptable to disk. file: %s.\n", filename);

  FILE *file = fopen(filename, "wb");
  if (!file) {
    fprintf(stderr, "Was not able to open file %s\n", filename);
    return false;
  }

  // Save the array
  if (fwrite(ptable, table_size, 1, file) != 1){
    fclose(file);
    return false;
  }

  fclose(file);
  return true;
}
