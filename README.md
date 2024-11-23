# Light

Docs about our Light-Setup

## Software 

[QLC+](https://www.qlcplus.org/)

## Hardware

### Akai APC20

Used for interacting with QLC+. Needs to be configured for `Input` and `Feedback`. Needs channels `1-16` for input and output.

### 9-CH Mode WOOKIE400RGB

used mode: `d501`

| Channel | Description       | Value Range | Details                              |
|---------|-------------------|-------------|--------------------------------------|
| **CH1** | Mode select       | 000 - 063   | Laser Off                            |
|         |                   | 064 - 127   | Auto Mode                            |
|         |                   | 128 - 191   | Sound mode                           |
|         |                   | 192 - 255   | DMX mode (CH2-CH8)                   |
| **CH2** | Colours           | 000 - 063   | Original colour                      |
|         |                   | 064 - 095   | Red                                  |
|         |                   | 096 - 127   | Green                                |
|         |                   | 128 - 159   | Blue                                 |
|         |                   | 160 - 191   | Yellow                               |
|         |                   | 192 - 223   | Pink                                 |
|         |                   | 224 - 255   | Cyan                                 |
| **CH3** | Pattern select    | 000 - 255   | 32 Patterns (value 000 - 007, 008 - 015,...) |
| **CH4** | Zooming           | 000 - 127   | Manual pattern size                  |
|         |                   | 128 - 255   | Loop zooming in/out                  |
| **CH5** | X axis rolling    | 000 - 127   | Manual rolling                       |
|         |                   | 128 - 255   | Rolling speed                        |
| **CH6** | Y axis rolling    | 000 - 127   | Manual rolling                       |
|         |                   | 128 - 255   | Rolling speed                        |
| **CH7** | Z axis rolling    | 000 - 127   | Manual rolling                       |
|         |                   | 128 - 255   | Rolling speed                        |
| **CH8** | X axis moving     | 000 - 127   | Manual position                      |
|         |                   | 128 - 255   | Horizontal moving speed              |
| **CH9** | Y axis moving     | 000 - 127   | Manual position                      |
|      
