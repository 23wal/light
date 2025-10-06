# Light

Docs about our Light-Setup

## diy

- [dmx2vga](/light/dmx2vga/)

## Software

[QLC+](https://www.qlcplus.org/)

## Inventory

| Name                               | Quantity | DMX-Addresses | Links                                                                                                                      |
| ----                               | -------- | ------------- | -----                                                                                                                      |
| Varytec LED Typhoon True PAR 12x10 | 4        | 1: 090-102    | [thomann](https://www.thomann.de/de/varytec_led_typhoon_true_par_12x10_out.htm?gad_source=1)                               |
|                                    |          | 2: 103-115    | [manual](https://fast-images.static-thomann.de/pics/atg/atgdata/document/manual/420255_c_420255_v4_en_online.pdf)          |
|                                    |          | 3: 116-128    |                                                                                                                            |
|                                    |          | 4: 129-141    |                                                                                                                            |
| Aliexpress PAR                     | 4        | 1: 040-049    | [aliexpress](https://www.aliexpress.com/item/1005004430211428.html?spm=a2g0o.order_list.order_list_main.22.224c5c5fDzbOLc) |
|                                    |          | 2: 050-059    | [manual](https://forums.pioneerdj.com/hc/user_images/mqaxf0DW1cDbQthUUF3sag.jpeg)                                          |
|                                    |          | 3: 060-069    |                                                                                                                            |
|                                    |          | 4: 070-079    |                                                                                                                            |
| Eurolite LED THM-46                | 2        | 1: 001-018    | [thomann](https://www.thomann.de/de/eurolite_led_tmh_46_moving_head_wash.htm)                                              |
|                                    |          | 2: 019-036    |                                                                                                                            |
| Cameo Wookie series 400RGB         | 1        | 1: 501-509    |                                                                                                                            |
| Stairville AF-150                  | 1        | 1: 420        |                                                                                                                            |
| UKING ZQ06121 RETRO LIGHT          | 4        |               | [manual](https://www.uking-online.com/wp-content/uploads/2025/07/ZQ06121.pdf)

## Hardware

### Akai APC20

Used for interacting with QLC+. Needs to be configured for `Input` and `Feedback`. Needs channels `1-16` for input and output.

### Varytec LED Typhoon True PAR 12x10

Mode: 13-Channel

| Channel | Description                         | Value Range | Details                            |
| ------- | -----------                         | ----------- | -------                            |
| 1       | Brightness                          | 000 - 255   |                                    |
| 2       | Red intensity                       | 000 - 255   |                                    |
| 3       | Green intensity                     | 000 - 255   |                                    |
| 4       | Blue intensity                      | 000 - 255   |                                    |
| 5       | White intensity                     | 000 - 255   |                                    |
| 6       | Amber intensity                     | 000 - 255   |                                    |
| 7       | UV intensity                        | 000 - 255   |                                    |
| 8       | Automatic color transition          | 000 - 255   |                                    |
| 9       | Strobe                              | 000 - 255   | 0-8 Standard                       |
|         |                                     |             | 9-255 Strobe with increasing speed |
| 10      | Automatic Show                      | 000 - 255   |                                    |
| 11      | Automatic Show Running speed        | 000 - 255   |                                    |
| 12      | Dimmer curves with afterglow effect | 000 - 049   | Standard                           |
|         |                                     | 050 - 099   | Dimmer mode 1(slight afterglow)    |
|         |                                     | 100 - 149   | Dimmer mode 2                      |
|         |                                     | 150 - 199   | Dimmer mode 3                      |
|         |                                     | 200 - 255   | Dimmer mode 4(strong afterglow)    |
| 13      | ID assignment                       |             |                                    |

### Aliexpress PAR

Mode: 10-Channel

| Channel | Description                         | Value Range | Details                            |
| ------- | -----------                         | ----------- | -------                            |
| 1       | Brightness                          | 000 - 255   |                                    |
| 2       | Red intensity                       | 000 - 255   |                                    |
| 3       | Green intensity                     | 000 - 255   |                                    |
| 4       | Blue intensity                      | 000 - 255   |                                    |
| 5       | White intensity                     | 000 - 255   |                                    |
| 6       | Amber intensity                     | 000 - 255   |                                    |
| 7       | UV intensity                        | 000 - 255   |                                    |
| 8       | Strobe Speed                        | 000 - 255   |                                    |
| 9       | Function Choice                     | 000 - 255   |                                    |
| 10      | Function Speed                      | 000 - 255   |                                    |

### Eurolite LED TMH-46

Mode: 18-Channel

| Channel | Description                         | Value Range | Details                            |
| ------- | -----------                         | ----------- | -------                            |
| 1       | Pan                                 | 000 - 255   |                                    |
| 2       | Pan Fine                            | 000 - 255   |                                    |
| 3       | Tilt                                | 000 - 255   |                                    |
| 4       | Tilt Fine                           | 000 - 255   |                                    |
| 5       | Pan/Tilt speed                      | 000 - 255   |                                    |
| 6       | Dimmer                              | 000 - 255   |                                    |
| 7       | Strobe                              | 000 - 255   |                                    |
| 8       | Red                                 | 000 - 255   |                                    |
| 9       | Green                               | 000 - 255   |                                    |
| 10      | Blue                                | 000 - 255   |                                    |
| 11      | White                               | 000 - 255   |                                    |
| 12      | Amber                               | 000 - 255   |                                    |
| 13      | UV                                  | 000 - 255   |                                    |
| 14      | Motion Macros                       | 000 - 255   |                                    |
| 15      | Motion Macros Speed                 | 000 - 255   |                                    |
| 16      | Color Macros                        | 000 - 255   |                                    |
| 17      | Color Macros Speed                  | 000 - 255   |                                    |
| 18      | Reset                               | 000 - 255   |                                    |

### Cameo Wookie series 400RGB

Mode: 9-Channel
used mode: `d501`

| Channel | Description    | Value Range | Details                                      |
|---------|----------------|-------------|----------------------------------------------|
| 1       | Mode select    | 000 - 063   | Laser Off                                    |
|         |                | 064 - 127   | Auto Mode                                    |
|         |                | 128 - 191   | Sound mode                                   |
|         |                | 192 - 255   | DMX mode (CH2-CH8)                           |
| 2       | Colours        | 000 - 063   | Original colour                              |
|         |                | 064 - 095   | Red                                          |
|         |                | 096 - 127   | Green                                        |
|         |                | 128 - 159   | Blue                                         |
|         |                | 160 - 191   | Yellow                                       |
|         |                | 192 - 223   | Pink                                         |
|         |                | 224 - 255   | Cyan                                         |
| 3       | Pattern select | 000 - 255   | 32 Patterns (value 000 - 007, 008 - 015,...) |
| 4       | Zooming        | 000 - 127   | Manual pattern size                          |
|         |                | 128 - 255   | Loop zooming in/out                          |
| 5       | X axis rolling | 000 - 127   | Manual rolling                               |
|         |                | 128 - 255   | Rolling speed                                |
| 6       | Y axis rolling | 000 - 127   | Manual rolling                               |
|         |                | 128 - 255   | Rolling speed                                |
| 7       | Z axis rolling | 000 - 127   | Manual rolling                               |
|         |                | 128 - 255   | Rolling speed                                |
| 8       | X axis moving  | 000 - 127   | Manual position                              |
|         |                | 128 - 255   | Horizontal moving speed                      |
| 9       | Y axis moving  | 000 - 127   | Manual position                              |

### Stairville AF-150

Mode: 1-Channel

| Channel | Description       | Value Range | Details                              |
|---------|-------------------|-------------|--------------------------------------|
| 1       | Pump              | 000 - 255   |                                      |
