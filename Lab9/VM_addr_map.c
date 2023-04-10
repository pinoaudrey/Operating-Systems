#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXSTR 1000

int main(int argc, char *argv[])
{
  char line[MAXSTR];
  int *page_table, *mem_map;
  unsigned int log_size, phy_size, page_size, d;
  unsigned int num_pages, num_frames;
  unsigned int offset, logical_addr, physical_addr, page_num, frame_num;

  /* Get the memory characteristics from the input file */
  fgets(line, MAXSTR, stdin);
  if((sscanf(line, "Logical address space size: %d^%d", &d, &log_size)) != 2){
    fprintf(stderr, "Unexpected line 1. Abort.\n");
    exit(-1);
  }
  fgets(line, MAXSTR, stdin);
  if((sscanf(line, "Physical address space size: %d^%d", &d, &phy_size)) != 2){
    fprintf(stderr, "Unexpected line 2. Abort.\n");
    exit(-1);
  }
  fgets(line, MAXSTR, stdin);
  if((sscanf(line, "Page size: %d^%d", &d, &page_size)) != 2){
    fprintf(stderr, "Unexpected line 3. Abort.\n");
    exit(-1);
  }

  /* Allocate arrays to hold the page table and memory frames map */
  d = log_size - page_size; // 32 - 31 = 1 for page table
  num_pages = (unsigned int) pow(2, d); // 2^1 = 2 number of bits in page table
  page_table = (int *)malloc(num_pages * sizeof(int));

  d = phy_size - page_size; // 32 - 31 = 1 for page table
  num_frames = (unsigned int) pow(2, d); // 2^1 = 2 number of bits in page table
  mem_map = (int *)malloc(num_frames * sizeof(int));

  /* Initialize page table to indicate that no pages are currently mapped to
     physical memory */
  for(int i = 0; i < num_pages; i++){
    page_table[i] = -1; // -1 means no page is mapped to physical memory (invalid)
  }

  /* Initialize memory map table to indicate no valid frames */
  for(int i = 0; i < num_frames; i++){
    mem_map[i] = -1; // -1 means no page is mapped to physical memory (invalid)
  }
  
  printf("Number of Pages: %d, Number of Frames: %d\n\n",  num_pages, num_frames);

  /* Read each accessed address from input file. Map the logical address to
     corresponding physical address */
  fgets(line, MAXSTR, stdin);
  while(!(feof(stdin))){
    sscanf(line, "0x%x", &logical_addr);
    fprintf(stdout, "Logical address: 0x%x\n", logical_addr);
    
	/* Calculate page number and offset from the logical address */
    page_num = logical_addr >> page_size; // 0x00000001
    printf("Page Number: %d\n", page_num);
    offset = logical_addr & ((1 << page_size) - 1); 

    if(page_table[page_num] == -1){
      // Page fault. Find a free frame and map it to the page 
      printf("Page Fault!\n");
      for(int i = 0; i < num_frames; i++){
        if(mem_map[i] == -1){
          // Found a free frame
          mem_map[i] = page_num;
          page_table[page_num] = i;
          break;
        }
      }
    }

    /* Form corresponding physical address */
    physical_addr = (page_table[page_num] << page_size) | offset;
    printf("Frame Number: %d\nPhysical Address: 0x%x\n\n", page_table[page_num], physical_addr);

    /* Read next line */
    fgets(line, MAXSTR, stdin);    
  }

  return 0;
}
