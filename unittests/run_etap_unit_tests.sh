#!/usr/bin/env bash
# script to run all etap unit tests and check they output the correct results
export SRC_DIR=$1

echo -e "testing all unit tests produce expected output, including deliberately failing ones...\n"

strip-path () {
  local FILE=$1

  # elide build specific path so that the diff does not fail from path differences
  sed 's|/.*\(/etap/unittests/\)|...\1|g' ${FILE}
}

RESULT=0
for t in failing passing infra
do
  "./etap_${t}_test" > "${t}_output.txt"
  # we check the test produces the same output as a hand checked recording.
  # fold also in the result, remembering _any_ failures so we can fail the script return if _any_ have failed.
  diff <(strip-path "${t}_output.txt") <(strip-path "${SRC_DIR}/${t}_test_expected_data.txt") || RESULT=1
done

exit $RESULT
