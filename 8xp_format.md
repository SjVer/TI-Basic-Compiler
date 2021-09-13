# 8xp FORMAT

## Header

### MimeType

    **TI83F*[SUB][NEWLINE]
    e.g:
    * * T I 8 3 F * 0x1a \n

### MetaData

    [NULL]40 characters[NULL]character[NULL][NULL][hex code][NEWLINE]
    e.g:
    0x00 M y C o m m e n t [to 40 chars] 0x00 0x00 N 0x00 \n

### File Info

    [NULL][LengthOfPrgm+2][sizeByte][carryByte] 0x05 [NAME (8 bytes)][NULL][NULL][SIZE AGAIN][SIZE AGAIN BUT -2]
    e.g:
    0x00 14 14 0 0x05 M Y P R G M 0x00 0x00 0x00 0x00 14 0 12 0