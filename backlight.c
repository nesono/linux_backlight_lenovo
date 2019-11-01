#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX_LEN 256
#define FILE_MAX_LEN 128

void setup_devices(char *device_max, char *device_cur, char *device_base) {
  device_max[0] = '\0';
  device_cur[0] = '\0';

  strncat(device_max, device_base, PATH_MAX_LEN - 1);
  fprintf(stdout, "device %s\n", device_max);
  strncat(device_cur, device_base, PATH_MAX_LEN - 1);
  fprintf(stdout, "device %s\n", device_cur);

  strncat(device_max, "/max_brightness", PATH_MAX_LEN - 1);
  fprintf(stdout, "device %s\n", device_max);
  strncat(device_cur, "/brightness", PATH_MAX_LEN - 1);
  fprintf(stdout, "device %s\n", device_cur);
}

int get_brightness(char *device) {
  FILE *f = fopen(device, "r");
  if (!f) {
    fprintf(stderr, "Error opening device %s\n", device);
  }
  char buf[FILE_MAX_LEN];
  size_t read = fread(buf, sizeof(char), FILE_MAX_LEN, f);
  fclose(f);
  if (read == 0) {
    fprintf(stderr, "Not read anything from %s\n", device);
    exit(-3);
  }
  return atoi(buf);
}

void apply_brightness(int brightness, char *device) {
  FILE *f = fopen(device, "w");
  if (!f) {
    fprintf(stderr, "Error opening device %s for writing\n", device);
    exit(-4);
  }
  char buf[FILE_MAX_LEN];
  snprintf(buf, FILE_MAX_LEN, "%d\n", brightness);
  size_t written = fwrite(buf, sizeof(char), sizeof(buf), f);
  fclose(f);
  if (written == 0) {
    fprintf(stderr, "Could not write new brightness value\n");
  }
}

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <device:path> <change:int>\n", argv[0]);
    return -1;
  }

  char device_max[PATH_MAX_LEN];
  char device_cur[PATH_MAX_LEN];

  setup_devices(device_max, device_cur, argv[1]);

  int max_brightness = get_brightness(device_max);
  int current_brightness = get_brightness(device_cur);

  int change = atoi(argv[2]);

  // clip brightness
  int new_brightness = min(current_brightness + change, max_brightness);
  new_brightness = max(new_brightness, 0);

  fprintf(stdout, "Brightness now: %d of %d; New: %d\n", current_brightness,
          max_brightness, new_brightness);

  apply_brightness(new_brightness, device_cur);
  return 0;
}
