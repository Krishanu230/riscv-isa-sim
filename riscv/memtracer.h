// See LICENSE for license details.

#ifndef _MEMTRACER_H
#define _MEMTRACER_H

#include <cstdint>
#include <string.h>
#include <vector>
#include <iostream>

enum access_type {
  LOAD,
  STORE,
  FETCH,
};

class memtracer_t
{
 public:
  memtracer_t() {}
  virtual ~memtracer_t() {}

  virtual bool interested_in_range(uint64_t begin, uint64_t end, access_type type) = 0;
  virtual void trace(uint64_t addr, size_t bytes, access_type type) = 0;
};

class memtracer_list_t : public memtracer_t
{
 public:
  bool empty() { return list.empty(); }
  bool interested_in_range(uint64_t begin, uint64_t end, access_type type)
  {
  //  printf("[memtracer.h] - memtracer_list_t -> interested in range \n");
    for (std::vector<memtracer_t*>::iterator it = list.begin(); it != list.end(); ++it){
      if ((*it)->interested_in_range(begin, end, type)){
    //    printf("returning true\n" );
        return true;}}
  //  printf("memtracer list checking if in range returning false\n" );
    return false;
  }
  void trace(uint64_t addr, size_t bytes, access_type type)
  {
    //  printf("[memtracer.h] - memtracer_list_t -> trace \n");
    for (std::vector<memtracer_t*>::iterator it = list.begin(); it != list.end(); ++it)
      (*it)->trace(addr, bytes, type);
  }
  void hook(memtracer_t* h)
  {
    //printf("[memtracer.h] - hook \n ");
    list.push_back(h);
  }
 private:
  std::vector<memtracer_t*> list;
};

#endif
