SUMMARY = "Example"
HOMEPAGE = "http://www.net-snmp.org/"
SECTION = "net"
LICENSE = "CLOSED"

DEPENDS = "net-snmp"

SRC_URI = "git://github.com/bsafwen/bin"

SRCREV = "6499081328e6206b3afca4449fc535d8a6b5f1fc"

inherit update-alternatives

do_install_append() {
    install -d ${D}${sysconfdir}/snmp
    install -m 644 ${WORKDIR}/git/snmpd.conf ${D}${sysconfdir}/snmp/
}

CONFFILES_${PN} = "${sysconfdir}/snmp/snmpd.conf"
