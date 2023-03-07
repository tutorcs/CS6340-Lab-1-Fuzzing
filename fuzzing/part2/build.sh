https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#!/bin/bash

rm -f test/sanity.cov
rm -f test/fuzz_output/failure/input*

cd build
cmake ..
make

cd ../test
make

#mkdir fuzz_output
timeout 1 ../build/fuzzer ./sanity fuzz_input fuzz_output MutationC

exit 
