AM_CPPFLAGS = -I$(top_srcdir)/libsrc -DUSBIDS_FILE='"@USBIDS_DIR@/usb.ids"'
AM_CFLAGS   = @EXTRA_CFLAGS@ @PACKAGE_CFLAGS@
LDADD       = $(top_builddir)/libsrc/libusbip.la @PACKAGE_LIBS@

sbin_PROGRAMS := usbip usbipd

usbip_SOURCES := usbip.c utils.c usbip_network.c \
		 usbip_attach.c usbip_detach.c usbip_list.c \
		 usbip_bind.c usbip_unbind.c usbip_port.c

usbipd_SOURCES := usbipd.c usbip_network.c
