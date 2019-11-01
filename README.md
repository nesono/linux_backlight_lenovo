# Change backlight of Lenovo Thinkpads

I use this project to adjust the backlight in my linux notebook (Lenovo).

# Building

Use the following command in the terminal to build the C implementation.
```bash
cc backlight.c -o backlight
```

# Installation

I am using the application with mappings in i3. To change the brightness root access is required. 
Therefore I changed the ownership and permissions of the file after building as follows:

```bash
sudo chown root:root backlight
sudo chmod 4755 backlight
```

I then copy the application to `/usr/local/bin` and that's all:
```bash
sudo cp backlog /usr/local/bin
```

# i3 Configuration

I have the following shortcuts specified in my `$HOME/.config/i3/config`:

```
# Sreen brightness controls
bindsym XF86MonBrightnessUp exec --no-startup-id /usr/local/bin/backlight  /sys/class/backlight/intel_backlight +100 # increase screen brightness
bindsym XF86MonBrightnessDown exec --no-startup-id /usr/local/bin/backlight  /sys/class/backlight/intel_backlight -100 # decrease screen brightness

```

# Requirements

* C-compiler - tested with gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
* Notebook or monitor that has a root device path, e.g. `/sys/class/backlight/intel_backlight` with  `max_brightness` and `brightness` pseudo devices
