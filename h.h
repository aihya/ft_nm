#ifndef WEE_H
# define WEE_H

# include <stdio.h>
# if defined(N32)
#  define elfN() elf32()
# elif defined(N64)
#  define elfN() elf64()
# endif

void elf64(void);

#endif
