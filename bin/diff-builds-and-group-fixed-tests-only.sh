if test -z $1; then olddate=2008_05_18; else olddate=$1; fi
if test -z $2; then prefix=`date -u +%Y%m%d%a`; else prefix=$2; fi
if test -z $ACE_ROOT; then ACE_ROOT=..; fi
#
grep -h \!FIXED_BUGS_ONLY ${ACE_ROOT}/tests/*.lst ${ACE_ROOT}/bin/*.lst | sed -e "s/^\([^\:]*\).*/\1/" | sed -e "s/\(\/run_test.pl\)\?\s*$//" > ${prefix}-Ignore.txt
#
perl ${ACE_ROOT}/bin/diff-builds.pl -D $olddate -D `date -u +%Y_%m_%d` | grep -v -P "^(\@\@|[ \-][a-zA-Z])" | grep -v -f ${prefix}-Ignore.txt | tee ${prefix}-Builds.txt | grep '+[a-zA-Z]' | sort | uniq -c | sort -n -r > ${prefix}-Tests.txt