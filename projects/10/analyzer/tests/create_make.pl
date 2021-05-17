#! /usr/bin/perl -w

use v5.14;

my $var = $ARGV[0] || "hello";

my $make_objects = "
# Test the $var
\$(O)\$(T)test_$var.o: \$(S)\$(T)test_$var.c
	gcc -I\$(TH) -c \$(S)\$(T)test_$var.c -o \$(O)\$(T)test_$var.o

# Get the $var module
\$(O)\$(T)test_module_$var.o: \$(TS)\$(T)$var.c
	gcc -I\$(TH) -c \$(TS)\$(T)$var.c -o \$(O)\$(T)test_module_$var.o
";

my $make_archive = "
    \$(O)\$(T)test_$var.o \$(O)\$(T)test_module_$var.o
";


say $make_objects;
say $make_archive;
