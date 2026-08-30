#ifndef LOGO_H
#define LOGO_H

#define LOGO_HEIGHT 20

void load_logo(void);
const char *get_logo_line(int line);
int get_logo_height(void);
void free_logo(void);

#endif
