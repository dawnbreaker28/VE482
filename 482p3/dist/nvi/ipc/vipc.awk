#	@(#)vipc.awk	10.1 (Berkeley) 6/8/95
 
/^\/\* VI_[0-9A-Z_]*/ {
	printf("#define %s %d\n", $2, ++cnt);
	next;
}
