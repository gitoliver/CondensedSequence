#export GEMSHOME=YOUR/PATH/gems
#g++ -std=c++17 -I $GEMSHOME/gmml/includes/ -I includes/ -L$GEMSHOME/gmml/bin/ -Wl,-rpath,$GEMSHOME/gmml/bin/ src/*.cpp -lgmml -o gp_builder
#g++ -std=c++17o -I ../GraphTemplate/includes/ -I $GEMSHOME/gmml/includes/ -I includes/ -I $GEMSHOME/gmml/includes/InputSet/CondensedSequenceSpace/ -L$GEMSHOME/gmml/bin/ -Wl,-rpath,$GEMSHOME/gmml/bin/ src/*.cpp -lgmml -o runMe
#Remove old executable
if [ -f runMe ]; then
    rm runMe
fi
#Create log directory if necessary
if [ ! -d logs ]; then
    mkdir logs/
fi
#Compile
g++ -std=c++17 -I ../GraphTemplate/includes/ -I ../GraphTemplate/GenericObject/includes/ -I includes/ -I -Wl,-rpath, src/*.c* ../GraphTemplate/GenericObject/src/*.c* testDriver.cc -o runMe
#Check if compiled ok
if [ $? -ne 0 ]; then
	printf "COMPILE FAILED!!!\n".
else
	printf "Compile complete. Running runMe"
    dateToday=`date +%F_%T`
	./runMe > logs/$dateToday.log
    cat logs/$dateToday.log
fi
