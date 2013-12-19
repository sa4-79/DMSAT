#!/usr/bin/perl -w                                                        

use strict;
use Getopt::Std;
use File::Basename;
use XML::Simple;   

unless ( $ENV{SGE_CELL} ) {
    print "SGE environment is not setn";
    exit 1;                              
}                                        

our ( $opt_i, $opt_b );
getopts ( "ib" );      

unless ( ( $opt_i && ! $opt_b ) || ( ! $opt_i && $opt_b ) ) {
    $0 = basename $0;
    print STDERR "Usage: $0 { -i (idle) | -b (busy) }n";
    exit 2;
}

my $xml = `qhost -j -xml`;
my $status = XMLin ($xml);
foreach my $host ( sort keys %{$status->{host}}) {
    next if ( $host eq "global");
    my $job_counter = 0;
    foreach my $job ( keys %{$status->{host}->{$host}->{job}} ) {
        $job_counter++;
    }
    if ( $job_counter == 0 && $opt_i ) {
        print "$hostn";
    }
    if ( $job_counter > 0 && $opt_b ) {
        print "$hostn";
    }

}

