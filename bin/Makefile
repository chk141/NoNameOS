MAKEFILE=Makefile

TARGET=amos.ima

IMAGE=grub.ima
IMAGE_DRIVE=a:
IMAGE_MENU=menu.cfg

COPY=copy
MCOPY=..\tools\mcopy -o
MMD=..\tools\mmd
RM=del
OBJDUMP=objdump-elf

all: $(TARGET)
	$(MCOPY) .\kernel\kernel.elf $(IMAGE_DRIVE)\amos
	$(MCOPY) .\apps\init.bin $(IMAGE_DRIVE)\amos
	$(MCOPY) .\apps\shell.bin $(IMAGE_DRIVE)\amos
	$(MCOPY) .\apps\test.bin $(IMAGE_DRIVE)\amos
	$(MCOPY) .\apps\hanoi.bin $(IMAGE_DRIVE)\amos
	$(MCOPY) .\lib\libc.a $(IMAGE_DRIVE)\amos\lib

$(TARGET):
	$(COPY) .\$(IMAGE) .\$(TARGET)
	$(MCOPY) .\$(IMAGE_MENU) $(IMAGE_DRIVE)\boot
	$(MMD) $(IMAGE_DRIVE)\amos
	$(MMD) $(IMAGE_DRIVE)\amos\lib

clean:
	$(RM) $(TARGET)
	$(RM) .\kernel\kernel.*
	$(RM) .\apps\*.bin
	$(RM) .\apps\*.map
	$(RM) .\lib\*.a