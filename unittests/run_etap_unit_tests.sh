#!/usr/bin/env bash
# script to run all etap unit tests and check they output the correct results
export SRC_DIR=$1

echo "testing everything...\n"


RESULT=0
for t in infra failing passing
do
  "./etap_${t}_test" > "${t}_output.txt"
  diff "${t}_output.txt" "${SRC_DIR}/${t}_test_expected_data.txt" || RESULT=1
  #RESULT=$?
  # fold in the result, remembering _any_ failures
  #echo "result [$RESULT] last [$?]"
  #((RESULT=RESULT && $?))
  echo "now result [$RESULT] last [$?]"
done

#((RESULT)) && echo "and result"
#((RESULT)) || echo "or result"

echo "result [${RESULT}]"
exit $RESULT
