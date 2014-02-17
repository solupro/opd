/*                                                                -*- C -*-
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2007 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Stig Sæther Bakken <ssb@php.net>                             |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#define CONFIGURE_COMMAND " './configure'  '--prefix=/usr/local/Cellar/php54/5.4.24' '--localstatedir=/usr/local/var' '--sysconfdir=/usr/local/etc/php/5.4' '--with-config-file-path=/usr/local/etc/php/5.4' '--with-config-file-scan-dir=/usr/local/etc/php/5.4/conf.d' '--with-iconv-dir=/usr' '--enable-dba' '--with-ndbm=/usr' '--enable-exif' '--enable-soap' '--enable-wddx' '--enable-ftp' '--enable-sockets' '--enable-zip' '--enable-shmop' '--enable-sysvsem' '--enable-sysvshm' '--enable-sysvmsg' '--enable-mbstring' '--enable-mbregex' '--enable-bcmath' '--enable-calendar' '--with-zlib=/usr/local/opt/zlib' '--with-ldap' '--with-ldap-sasl=/usr' '--with-xmlrpc' '--with-kerberos=/usr' '--with-gd' '--enable-gd-native-ttf' '--with-freetype-dir=/usr/local/opt/freetype' '--with-jpeg-dir=/usr/local/opt/jpeg' '--with-png-dir=/usr/local/opt/libpng' '--with-gettext=/usr/local/opt/gettext' '--with-snmp=/usr' '--with-libedit' '--with-unixODBC=/usr/local/opt/unixodbc' '--with-pdo-odbc=unixODBC,/usr/local/opt/unixodbc' '--mandir=/usr/local/Cellar/php54/5.4.24/share/man' '--with-mhash' '--with-curl' '--with-bz2=/usr' '--disable-debug' '--with-openssl=/usr' '--with-xsl=/usr' '--with-apxs2=/usr/sbin/apxs' '--libexecdir=/usr/local/Cellar/php54/5.4.24/libexec' '--with-mysql-sock=/tmp/mysql.sock' '--with-mysqli=mysqlnd' '--with-mysql=mysqlnd' '--with-pdo-mysql=mysqlnd' '--enable-pcntl' '--enable-zend-signals' '--enable-dtrace'"
#define PHP_ADA_INCLUDE		""
#define PHP_ADA_LFLAGS		""
#define PHP_ADA_LIBS		""
#define PHP_APACHE_INCLUDE	""
#define PHP_APACHE_TARGET	""
#define PHP_FHTTPD_INCLUDE      ""
#define PHP_FHTTPD_LIB          ""
#define PHP_FHTTPD_TARGET       ""
#define PHP_CFLAGS		"$(CFLAGS_CLEAN) -prefer-non-pic -static"
#define PHP_DBASE_LIB		""
#define PHP_BUILD_DEBUG		""
#define PHP_GDBM_INCLUDE	""
#define PHP_IBASE_INCLUDE	""
#define PHP_IBASE_LFLAGS	""
#define PHP_IBASE_LIBS		""
#define PHP_IFX_INCLUDE		""
#define PHP_IFX_LFLAGS		""
#define PHP_IFX_LIBS		""
#define PHP_INSTALL_IT		"$(mkinstalldirs) '$(INSTALL_ROOT)/usr/libexec/apache2' &&                 $(mkinstalldirs) '$(INSTALL_ROOT)/private/etc/apache2' &&                  /usr/sbin/apxs -S LIBEXECDIR='$(INSTALL_ROOT)/usr/libexec/apache2'                        -S SYSCONFDIR='$(INSTALL_ROOT)/private/etc/apache2'                        -i -a -n php5 libs/libphp5.so"
#define PHP_IODBC_INCLUDE	""
#define PHP_IODBC_LFLAGS	""
#define PHP_IODBC_LIBS		""
#define PHP_MSQL_INCLUDE	""
#define PHP_MSQL_LFLAGS		""
#define PHP_MSQL_LIBS		""
#define PHP_MYSQL_INCLUDE	""
#define PHP_MYSQL_LIBS		""
#define PHP_MYSQL_TYPE		""
#define PHP_ODBC_INCLUDE	"-I/usr/local/opt/unixodbc/include"
#define PHP_ODBC_LFLAGS		"-L/usr/local/opt/unixodbc/lib"
#define PHP_ODBC_LIBS		"-lodbc"
#define PHP_ODBC_TYPE		"unixODBC"
#define PHP_OCI8_SHARED_LIBADD 	""
#define PHP_OCI8_DIR			""
#define PHP_OCI8_ORACLE_VERSION		""
#define PHP_ORACLE_SHARED_LIBADD 	"@ORACLE_SHARED_LIBADD@"
#define PHP_ORACLE_DIR				"@ORACLE_DIR@"
#define PHP_ORACLE_VERSION			"@ORACLE_VERSION@"
#define PHP_PGSQL_INCLUDE	""
#define PHP_PGSQL_LFLAGS	""
#define PHP_PGSQL_LIBS		""
#define PHP_PROG_SENDMAIL	"/usr/sbin/sendmail"
#define PHP_SOLID_INCLUDE	""
#define PHP_SOLID_LIBS		""
#define PHP_EMPRESS_INCLUDE	""
#define PHP_EMPRESS_LIBS	""
#define PHP_SYBASE_INCLUDE	""
#define PHP_SYBASE_LFLAGS	""
#define PHP_SYBASE_LIBS		""
#define PHP_DBM_TYPE		""
#define PHP_DBM_LIB		""
#define PHP_LDAP_LFLAGS		""
#define PHP_LDAP_INCLUDE	""
#define PHP_LDAP_LIBS		""
#define PHP_BIRDSTEP_INCLUDE     ""
#define PHP_BIRDSTEP_LIBS        ""
#define PEAR_INSTALLDIR         "/usr/local/Cellar/php54/5.4.24/lib/php"
#define PHP_INCLUDE_PATH	".:/usr/local/Cellar/php54/5.4.24/lib/php"
#define PHP_EXTENSION_DIR       "/usr/local/Cellar/php54/5.4.24/lib/php/extensions/no-debug-non-zts-20100525"
#define PHP_PREFIX              "/usr/local/Cellar/php54/5.4.24"
#define PHP_BINDIR              "/usr/local/Cellar/php54/5.4.24/bin"
#define PHP_SBINDIR             "/usr/local/Cellar/php54/5.4.24/sbin"
#define PHP_MANDIR              "/usr/local/Cellar/php54/5.4.24/share/man"
#define PHP_LIBDIR              "/usr/local/Cellar/php54/5.4.24/lib/php"
#define PHP_DATADIR             "${prefix}/share"
#define PHP_SYSCONFDIR          "/usr/local/etc/php/5.4"
#define PHP_LOCALSTATEDIR       "/usr/local/var"
#define PHP_CONFIG_FILE_PATH    "/usr/local/etc/php/5.4"
#define PHP_CONFIG_FILE_SCAN_DIR    "/usr/local/etc/php/5.4/conf.d"
#define PHP_SHLIB_SUFFIX        "so"
