SUMMARY = "Various tools relating to the Simple Network Management Protocol"
HOMEPAGE = "http://www.net-snmp.org/"
SECTION = "net"
LICENSE = "BSD"

do_install_append() {
    install -d ${D}${sysconfdir}/snmp
    install -d ${D}${sysconfdir}/init.d
    install -m 755 ${WORKDIR}/init ${D}${sysconfdir}/init.d/snmpd
    install -m 644 ${WORKDIR}/snmpd.conf ${D}${sysconfdir}/snmp/
    install -m 644 ${WORKDIR}/snmptrapd.conf ${D}${sysconfdir}/snmp/
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/snmpd.service ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/snmptrapd.service ${D}${systemd_unitdir}/system
    sed    -e "s@^NSC_SRCDIR=.*@NSC_SRCDIR=.@g" \
        -i ${D}${bindir}/net-snmp-create-v3-user
    sed    -e "s@^NSC_SRCDIR=.*@NSC_SRCDIR=.@g" \
           -e "s@\([^ ]*-fdebug-prefix-map=[^ ]*\)\1*@@g" \
           -e "s@\([^ ]*--sysroot=[^ ]*\)\1*@@g" \
           -e "s@\([^ ]*--with-libtool-sysroot=[^ ]*\)\1*@@g" \
           -e "s@\([^ ]*--with-install-prefix=[^ ]*\)\1*@@g" \
        -i ${D}${bindir}/net-snmp-config

    if [ "${HAS_PERL}" = "1" ]; then
        sed -e "s@^NSC_INCLUDEDIR=.*@NSC_INCLUDEDIR=\$\{includedir\}@g" \
            -e "s@^NSC_LIBDIR=-L.*@NSC_LIBDIR=-L\$\{libdir\}@g" \
            -i ${D}${bindir}/net-snmp-config
    fi

    rm -f ${D}${sysconfdir}/snmp/snmpd.conf
}
