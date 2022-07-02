# QROFS - Quark Read-Only File System

QROFS is the FS used by Quark's ramdisk VFS

 - Read-only (cannot write/delete/create/rename files)
 - Subdirectory support
 - File size limit: 2^32 bytes
 - File name limit: 255 characters
 - File name validation: ASCII only
 - File name case sensitivity: case-sensitive
 - Maximum files per directory: 255

## At a byte level

NOTE: Everything is stored in little-endian format, unless otherwise noted

### QROFS directory

| Bits | Description |
|-|-|
| 8 | Header (`0x02` for directories) |
| 8 | Name length |
| 8*n | The directory name itself - n is the name length |
| 8 | Number of child nodes |
| ? | Child nodes |

### QROFS file

| Bits | Description |
|-|-|
| 8 | Header (`0x01` for files) |
| 8 | Name length |
| 8*n | The file name itself - n is the name length |
| 32 | File size |
| 8*n | File data |
