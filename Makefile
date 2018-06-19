SRC = Framework.C  SpeciesDistManager.C	SpeciesClusterManager.C	Expert.C Matrix.C GeneExpManager.C MappedOrthogroupReader.C     MappedOrthogroup.C GeneMap.C GeneTreeManager.C GammaManager.C Gamma.C GeneTree.C GeneNameMapper.C NewickReader.C

INCLPATH1=common
LIBPATH=gsl_install/lib
INCLPATH2=gsl_install/include


CC=g++ 
CFLAGS = -g -std=c++0x
LFLAG = -lgsl -lgslcblas 

mintInitFix: $(SRC)
	$(CC) $(SRC) -I $(INCLPATH1) -I $(INCLPATH2)  -L $(LIBPATH) $(LFLAG) $(CFLAGS) -o escarole

