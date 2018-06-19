# Escarole
Expression State Clustering on Lineages (Escarole)

## History
Escarole is a fork of an earlier version of CMINT (https://github.com/Roy-lab/CMINT). We made some changes to help the approach perform better on log-transformed RNA-seq data.

1. Rather than learn the variances per-state, the user can fix the variances to a constant through a command line argument. We have used 0.2 as the constant.
2. The state means for all cell types/time points are initialized to that of the source cell type/time point. This means that from the beginning, the interpretation of the expression states for each time point are matched.
