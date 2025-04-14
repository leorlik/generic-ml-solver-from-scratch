parametrosCompilacao=-Wall #-Wshadow
nomePrograma=regressorBasico
cXX = g++
OBJS = main.o BaseRegression.o LogisticRegression.o LinearRegression.o Dataframe.o CommandLineArgs.o ModelEvaluator.o

all: $(nomePrograma)


$(nomePrograma): $(OBJS)
	$(cXX) -o $(nomePrograma) $(OBJS) $(parametrosCompilacao)

main.o: main.cpp
	$(cXX) -c main.cpp $(parametrosCompilacao)

Dataframe.o: Dataframe.hpp Dataframe.cpp
	$(cXX) -c Dataframe.cpp $(parametrosCompilacao)

BaseRegression.o: BaseRegression.cpp BaseRegression.hpp
	$(cXX) -c BaseRegression.cpp $(parametrosCompilacao)

LogisticRegression.o: LogisticRegression.hpp LogisticRegression.cpp
	$(cXX) -c LogisticRegression.cpp $(parametrosCompilacao)

LinearRegression.o: LinearRegression.hpp LinearRegression.cpp
	$(cXX) -c LinearRegression.cpp $(parametrosCompilacao)

CommandLineArgs.o: CommandLineArgs.hpp CommandLineArgs.cpp
	$(cXX) -c CommandLineArgs.cpp $(parametrosCompilacao)

ModelEvaluator.o: ModelEvaluator.hpp ModelEvaluator.cpp
	$(cXX) -c ModelEvaluator.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
