# 8xp FORMAT

## Signature (11 bytes)

    **TI83F*[SUB][NEWLINE][NULL]
    e.g:
    * * T I 8 3 F * 0x1a \n 0x00

## Comment (42 bytes)

    42 characters
    e.g:
    M y C o m m e n t [to 42 chars]

## Data length and signature (4 bytes)

    [lower byte][higher byte][STX][NULL]
    e.g:
    0x1c 0x00 0x0d 0x00
    (in this case 28, wich is the amount of
     bytes from here until the end of the
     program's bytes, so exl. the checksum)

## Program size + checksum size and signature (3 bytes)

    [lower byte][higher byte][ENQ]
    e.g:
    0x0b 0x00 0x05
    (in this case 11, because the program
     is 9 bytes long and the checksum 2)

## Name and signature (10 bytes)

    8 characters [NULL][NULL]
    e.g:
    M Y P R G M 0x00 0x00

## Program size + 2 and program size (4 bytes)

    [lower byte][higher byte][lower byte][higher byte]
    e.g:
    0x0b 0x00 0x09 0x00
    (in this case the program is 9 bytes)

## Program (x bytes)

    [program's bytes]
    e.g:
    0x19 0x8 0x31 0x2b 0x32 0x2b 0x33 0x2b 0x34 0x9 0x11
    ("max({1,2,3,4})")

## Checksum (2 bytes)

    [lower byte][higher byte]
    e.g:
    0x3e 0x03
    (in this case 830, which is the sum of all bytes
     from Data Length to checksum, incl. signatures)