# Escarole: Expression State Clustering on Lineages
Escarole is applied to RNA-seq data from time courses or from multiple cell types related by a hierarchical lineage tree. Escarole clusters genes into discrete expression states in each sample.

## History
Escarole is a fork of an early version of CMINT (https://github.com/Roy-lab/CMINT). We made some changes to help the approach perform better on log-transformed RNA-seq data. We have found that the state interpretations stay better matched across the cell types/time points with these changes.

1. Rather than learn the variances per-state, the user fixes the variances to a constant through a command line argument. We have used 0.2 as the constant. 
2. The state means for all cell types/time points are initialized to that of the source cell type/time point. This means that from the beginning, the interpretation of the expression states for each time point are matched.

## Compilation
Escarole requires the GNU Scientific Libraries (included). We provide a Makefile.
```
make escarole
```

## Usage
Escarole takes 11 arguments as follows:

```
./escarole sample_order gene_groups k sample_tree config_file rand[rseed|none] output_dir mode[learn] srcnode inittype[uniform] p_diagonal_nonleaf fixed_variance
```

The input arguments are as follows:

1. celltype_order: A file describing the order of the samples (time points or cell types). It's needed to parse the genegroup file. 

2. gene_groups: This file maps gene identifiers between samples (time points, cell types) to a common "group ID". Escarole's ancestral algorithm, Arboretum, was designed to be applied to multiple species and required such a map between data sets. However, if the the samples are all from the same species (as in our Escarole applications), this file will simply need to give different identifiers for the same gene in each sample (eg "gene1_time0")   The format of this file is the name of the gene group followed by a comma-separated list of unique gene identifiers.

3. k: The number of clusters that Escarole will learn.

4. sample_tree: A file describing the hierarchical relationships between time points or cell types. The format of this file is 2 column, tab-separated. First column is the name of the child sample and the second column is the name of the parent sample of each branch. For Escarole applications to time series, this is a linear tree.

5. config : A file describing the locations of the initial state assignments and expression data for each sample.
The assignment files can also be used to subset the data, as only genes with an input state assignment will be included in the analysis. The filenames in this file must be either full paths or relative to the directory in which you are running Escarole. We have applied Escarole with log-transformed TPMs (example provided).

6. output_dir: Location of results (must exist before running)

7. mode[learn]: Provide "learn" as this argument. (Other modes untested.)

8. srcnode: The sample/cell type specifying a reference point with which the rows in some output files are specified. For time series, we use the first time point.

9. inittype: An input argument specifying how the transition matrices should be initialized. Please use "uniform" for this argument.

10. p_diagonal_nonleaf: This is a number between 0-1 specifying the initial prior probability with which a region/gene maintains its state assignment between cell types. We recommend 0.8 as default.

11. const_var: Pick a value for fixing the variances (rather than learning them). We have used 0.2 as default.

## Command for running Escarole on example data
```
mkdir output
./escarole example_input/time_order.txt example_input/ortho_map.txt 5 example_input/time_tree.txt example_input/ashton_config.txt none output learn ashton_2hr uniform 0.8 0.2 1> running_escarole.log 2> running_escarole.err
```
