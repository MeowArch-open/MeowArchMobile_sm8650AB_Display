# Current ESP DT selection

Read from `/dev/block/by-name/esp` on 2026-09-07 using `mcopy`.

The ESP is a FAT32 filesystem with volume label `ESP` and serial `5BE6-B2DF`.
`EFI/BOOT/grub.cfg` contains:

```text
set default=2
```

Entry 2 boots `/Image` and loads:

```text
/dtb/zorn-display.dtb
```

The active ESP file is 141439 bytes and has SHA256:

```text
aa31a08c6f5eab677bfcbb728bf984ce0ca44ad4c9eec460e842adb4b654b140
```

It is byte-for-byte identical to the historical file represented by
`audio/dts/zorn-audio-micb.dts` and its compiled DTB in the original workspace.
Therefore the ESP currently uses the `audio-micb` DT content under the filename
`zorn-display.dtb`.

The older `work/tmp/zorn-display.dtb` is a different 137462-byte DTB and is not
the one selected by the current GRUB entry.
