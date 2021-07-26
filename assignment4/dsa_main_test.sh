clear
echo "###################################################################################"
echo "##############              GRADING ASSINMENT4 OF DSA               ###############"
echo "##############             (unittest for C++: doctest)              ###############"
echo "###################################################################################"

echo "[1] removing previous output ..."
rm -f ./assignment4

echo "[2] building DSACPP, please wait ..."
g++ ./dsacpp/assignment4.cpp ./dsacpp/src/geom/*.cpp -I ./dsacpp/include -I ./doctest -o assignment4

echo "###################################################################################"
echo "[3] running the test ..."
echo "\n"
./assignment4
echo "\n"
