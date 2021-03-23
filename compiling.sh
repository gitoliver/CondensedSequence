#export GEMSHOME=YOUR/PATH/gems
#g++ -std=c++17 -I $GEMSHOME/gmml/includes/ -I includes/ -L$GEMSHOME/gmml/bin/ -Wl,-rpath,$GEMSHOME/gmml/bin/ src/*.cpp -lgmml -o gp_builder
#g++ -std=c++17 -I ../GraphTemplate/includes/ -I $GEMSHOME/gmml/includes/ -I includes/ -I $GEMSHOME/gmml/includes/InputSet/CondensedSequenceSpace/ -L$GEMSHOME/gmml/bin/ -Wl,-rpath,$GEMSHOME/gmml/bin/ src/*.cpp -lgmml -o runMe
g++ -std=c++17 -I ../GraphTemplate/includes/ -I ../GraphTemplate/GenericObject/includes/ -I includes/ -I -Wl,-rpath, src/*.c* ../GraphTemplate/GenericObject/src/*.c* testDriver.cc -o runMe
printf "Now do\n./runMe\n"
