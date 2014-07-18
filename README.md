opd
===

PHP Opcode dumper like [vld](http://pecl.php.net/package/vld) but base on based on PHP embed sapi

##Install
Build PHP with Emebed SAP
```
$ cd php-src/
$ ./configure --enable-embed
$ make && make install
```
Modify the Makefile `LDFLAGS` where is your `libphp5.so[or libphp5.dylib]`   
Compile
```
$make 
```
##Example
test.php
```php
<?php
function foo($str) {
    echo $str;
}

$str = "hello world\n";
foo($str);
```
execute `./opd test.php `
```
Script: test.php
opnum	line	opcode	op1	op2	result
0	2	NOP			
1	6	ASSIGN	!0	"hello+world%0A"	
2	7	SEND_VAR	!0		
3	7	DO_FCALL	"foo"		
4	8	RETURN	1
```

##Blog (in Chinese)

- <http://solupro.org/php-opd-another-vld/>
